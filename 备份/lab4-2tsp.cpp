
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <queue>
const int INF = 100000;
const int MAX_N = 22;
using namespace std;

int n;
int cost[MAX_N][MAX_N];
struct myNode
{
    bool visited[MAX_N];
    int s;
    int s_p;
    int e;
    int e_p;
    int k;
    int sumv;
    int lb;
    bool operator<(const myNode &p) const
    {
        return p.lb < lb;
    }
};
priority_queue<myNode> pq;
int low, up;
bool dfs_visited[MAX_N];

int dfs(int u, int k, int l)
{
    if (k == n)
        return l + cost[u][1];
    int minlen = INF, p;
    for (int i = 1; i <= n; i++)
    {
        if (!dfs_visited[i] && minlen > cost[u][i])
        {
            minlen = cost[u][i];
            p = i;
        }
    }
    dfs_visited[p] = true;
    return dfs(p, k + 1, l + minlen);
}
void up_limit()
{
    dfs_visited[1] = true;
    up = dfs(1, 1, 0);
}

void down_limit()
{

    low = 0;
    for (int i = 1; i <= n; i++)
    {

        int tmpA[MAX_N];
        for (int j = 1; j <= n; j++)
        {
            tmpA[j] = cost[i][j];
        }
        sort(tmpA + 1, tmpA + 1 + n);
        low += tmpA[1];
    }
}
int get_lb(myNode p)
{
    int ret = p.sumv * 2;
    int min1 = INF, min2 = INF;
    for (int i = 1; i <= n; i++)
    {

        if (!p.visited[i] && min1 > cost[i][p.s])
        {
            min1 = cost[i][p.s];
        }
    }
    ret += min1;
    for (int i = 1; i <= n; i++)
    {
        if (!p.visited[i] && min2 > cost[p.e][i])
        {
            min2 = cost[p.e][i];
        }
    }
    ret += min2;
    for (int i = 1; i <= n; i++)
    {
        if (!p.visited[i])
        {
            min1 = min2 = INF;
            for (int j = 1; j <= n; j++)
            {
                if (min1 > cost[i][j])
                    min1 = cost[i][j];
            }
            for (int j = 1; j <= n; j++)
            {
                if (min2 > cost[j][i])
                    min2 = cost[j][i];
            }
            ret += min1 + min2;
        }
    }
    return (ret + 1) / 2;
}

int solution()
{

    up_limit();
    down_limit();
    myNode node;
    node.s = 1;
    node.e = 1;
    node.k = 1;
    for (int i = 1; i <= n; i++)
    {
        node.visited[i] = false;
    }
    node.visited[1] = true;
    node.sumv = 0;
    node.lb = low;
    int ret = INF;
    pq.push(node);
    while (pq.size())
    {

        myNode tmp = pq.top();
        pq.pop();
        if (tmp.k == n - 1)
        {

            int p;
            for (int i = 1; i <= n; i++)
            {
                if (!tmp.visited[i])
                {
                    p = i;
                    break;
                }
            }
            int ans = tmp.sumv + cost[p][tmp.s] + cost[tmp.e][p];
            if (ans <= tmp.lb)
            {
                ret = min(ans, ret);
                break;
            }

            else
            {
                up = min(up, ans);
                ret = min(ret, ans);
                continue;
            }
        }
        myNode next;
        for (int i = 1; i <= n; i++)
        {
            if (!tmp.visited[i])
            {

                next.s = tmp.s;
                next.sumv = tmp.sumv + cost[tmp.e][i];
                next.e = i;
                next.k = tmp.k + 1;
                for (int j = 1; j <= n; j++)
                    next.visited[j] = tmp.visited[j];
                next.visited[i] = true;

                next.lb = get_lb(next);

                if (next.lb > up)
                    continue;
                pq.push(next);
            }
        }
    }
    return ret;
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> cost[i][j];
            if (i == j)
            {
                cost[i][j] = INF;
            }
        }
    }
    cout << solution() << endl;
    return 0;
}

/*测试
5
100000 5 61 34 12
57 100000 43 20 7
39 42 100000 8 21
6 50 42 100000 8
41 26 10 35 100000
36
请按任意键继续. . .
*/
