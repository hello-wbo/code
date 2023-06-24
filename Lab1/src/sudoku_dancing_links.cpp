#include <assert.h>
#include <memory.h>
#include <map>
#include <vector>

#include "sudoku.h"
using namespace std;

void trans(const char in[N], int* target)
{
    for(int i = 0; i < N; ++i)
    {
        target[i] = in[i] - 48;
    }
}

struct myNode;
typedef myNode myColumn;
struct myNode
{
    myNode* left;
    myNode* right;
    myNode* up;
    myNode* down;
    myColumn* col;
    int name;
    int size;
};


struct Dance
{
    myColumn* root_;
    int*    inout_;
    myColumn* columns_[400];
    vector<myNode*> stack_;
    myNode    nodes_[MaxNumOfNode];
    int     cur_node_;

    myColumn* new_column(int n = 0)
    {
        assert(cur_node_ < MaxNumOfNode);
        myColumn* c = &nodes_[cur_node_++];
        memset(c, 0, sizeof(myColumn));
        c->left = c;
        c->right = c;
        c->up = c;
        c->down = c;
        c->col = c;
        c->name = n;
        return c;
    }

    void append_column(int n)
    {
        assert(columns_[n] == NULL);

        myColumn* c = new_column(n);
        put_left(root_, c);
        columns_[n] = c;
    }

    myNode* new_row(int col)
    {
        assert(columns_[col] != NULL);
        assert(cur_node_ < MaxNumOfNode);

        myNode* r = &nodes_[cur_node_++];

        //myNode* r = new myNode;
        memset(r, 0, sizeof(myNode));
        r->left = r;
        r->right = r;
        r->up = r;
        r->down = r;
        r->name = col;
        r->col = columns_[col];
        put_up(r->col, r);
        return r;
    }

    int get_row_col(int row, int val)
    {
        return kRow+row*10+val;
    }

    int get_col_col(int col, int val)
    {
        return kCol+col*10+val;
    }

    int get_box_col(int box, int val)
    {
        return kBox+box*10+val;
    }

    Dance(int inout[81]) : inout_(inout), cur_node_(0)
    {
        stack_.reserve(100);

        root_ = new_column();
        root_->left = root_->right = root_;
        memset(columns_, 0, sizeof(columns_));

        bool rows[N][10] = {false};
        bool cols[N][10] = {false};
        bool boxes[N][10] = {false};

        for (int i = 0; i < N; ++i) {
            int row = i / 9;
            int col = i % 9;
            int box = row/3*3 + col/3;
            int val = inout[i];
            rows[row][val] = true;
            cols[col][val] = true;
            boxes[box][val] = true;
        }

        for (int i = 0; i < N; ++i) {
            if (inout[i] == 0) {
                append_column(i);
            }
        }

        for (int i = 0; i < 9; ++i) {
            for (int v = 1; v < 10; ++v) {
                if (!rows[i][v])
                    append_column(get_row_col(i, v));
                if (!cols[i][v])
                    append_column(get_col_col(i, v));
                if (!boxes[i][v])
                    append_column(get_box_col(i, v));
            }
        }

        for (int i = 0; i < N; ++i) {
            if (inout[i] == 0) {
                int row = i / 9;
                int col = i % 9;
                int box = row/3*3 + col/3;
                //int val = inout[i];
                for (int v = 1; v < 10; ++v) {
                    if (!(rows[row][v] || cols[col][v] || boxes[box][v])) {
                        myNode* n0 = new_row(i);
                        myNode* nr = new_row(get_row_col(row, v));
                        myNode* nc = new_row(get_col_col(col, v));
                        myNode* nb = new_row(get_box_col(box, v));
                        put_left(n0, nr);
                        put_left(n0, nc);
                        put_left(n0, nb);
                    }
                }
            }
        }
    }

    myColumn* get_min_column()
    {
        myColumn* c = root_->right;
        int min_size = c->size;
        if (min_size > 1) {
            for (myColumn* cc = c->right; cc != root_; cc = cc->right) {
                if (min_size > cc->size) {
                    c = cc;
                    min_size = cc->size;
                    if (min_size <= 1)
                        break;
                }
            }
        }
        return c;
    }

    void cover(myColumn* c)
    {
        c->right->left = c->left;
        c->left->right = c->right;
        for (myNode* row = c->down; row != c; row = row->down) {
            for (myNode* j = row->right; j != row; j = j->right) {
                j->down->up = j->up;
                j->up->down = j->down;
                j->col->size--;
            }
        }
    }

    void uncover(myColumn* c)
    {
        for (myNode* row = c->up; row != c; row = row->up) {
            for (myNode* j = row->left; j != row; j = j->left) {
                j->col->size++;
                j->down->up = j;
                j->up->down = j;
            }
        }
        c->right->left = c;
        c->left->right = c;
    }

    bool solve()
    {
        if (root_->left == root_) {
            for (size_t i = 0; i < stack_.size(); ++i) {
                myNode* n = stack_[i];
                int cell = -1;
                int val = -1;
                while (cell == -1 || val == -1) {
                    if (n->name < 100)
                        cell = n->name;
                    else
                        val = n->name % 10;
                    n = n->right;
                }

                //assert(cell != -1 && val != -1);
                inout_[cell] = val;
            }
            return true;
        }

        myColumn* const col = get_min_column();
        cover(col);
        for (myNode* row = col->down; row != col; row = row->down) {
            stack_.push_back(row);
            for (myNode* j = row->right; j != row; j = j->right) {
                cover(j->col);
            }
            if (solve()) {
                return true;
            }
            stack_.pop_back();
            for (myNode* j = row->left; j != row; j = j->left) {
                uncover(j->col);
            }
        }
        uncover(col);
        return false;
    }

    void put_left(myColumn* old, myColumn* nnew)
    {
        nnew->left = old->left;
        nnew->right = old;
        old->left->right = nnew;
        old->left = nnew;
    }

    void put_up(myColumn* old, myNode* nnew)
    {
        nnew->up = old->up;
        nnew->down = old;
        old->up->down = nnew;
        old->up = nnew;
        old->size++;
        nnew->col = old;
    }
};

bool dancing(int* board)
{
  Dance d(board);
  return d.solve();
}
