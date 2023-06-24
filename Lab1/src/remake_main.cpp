#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <thread>
#include <pthread.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include "sudoku.h"

using namespace std;

const int lim_puzzle = 1024;

const int max_thread_num = 100;

int thread_num = 0;

int **buf;
bool *is_solved;

string infile_buffer;

thread ths[max_thread_num];
char puzzle[128];

void firstInit()
{
    // ios::sync_with_stdio(false);
    buf = new int* [lim_puzzle];
    is_solved = new bool [lim_puzzle];
    for(int i = 0; i < lim_puzzle; ++i) buf[i] = new int [N];
    thread_num = thread::hardware_concurrency();
}

void init()
{
    for(int i = 0; i < lim_puzzle; i++)
    {
        is_solved[i] = false;
    }
}

void workOfThread(const int sta, const int line_num)
{
    for(int i = 0; i < line_num; ++i)
    {
        is_solved[sta+i] = dancing(buf[sta+i]);
    }
}


void workOfOnefile(string file_path)
{
    ifstream input_file(file_path, ios::in);
    if(!input_file.is_open())
    {
        // printf("Filed to open file: %s\n", file_path.c_str());
        return;
    }
    init(); 
    bool end_of_file = false;
    while(!end_of_file)
    {
          int line_count = 0;
          do{
            //  char* ret_gets = fgets(puzzle, sizeof puzzle, fp);
             if(input_file.eof())
             {
                end_of_file = true;
                break;
             }
             input_file.getline(puzzle, N+1);
             if (strlen(puzzle) >= N)
             {
                trans(puzzle, buf[line_count]);
                line_count++;
             }
          }while(line_count < lim_puzzle-1);
//------------------------------------------------------------------
//          for(int i = 0; i < line_count; ++i)
//          {
//              is_solved[i] = dancing(buf[i]);
//          }
          int step = (line_count+thread_num-1)/thread_num, curr = 0;
          for(int i = 0; i < thread_num; ++i,curr+=step)
          {
              ths[i] = thread(workOfThread, curr, ((curr+step>=line_count)?(line_count-curr):step));
          }
          for(int i = 0; i < thread_num; ++i) ths[i].join();

//------------------------------------------------------------------
          for(int i = 0; i < line_count; ++i)
          {
              if(is_solved[i])
              {
                 for(int j = 0; j < N; j++) putchar('0'+buf[i][j]);
                 putchar('\n');
              }
              else puts("No result.");
          }
    }
    input_file.close();
}

int main()
{
    firstInit();
    string file;
    while(getline(cin, file))
    {
        workOfOnefile(file);
    }
    for(int i = 0; i < lim_puzzle; ++i) delete [] buf[i];
    delete [] buf;
    return 0;
}
