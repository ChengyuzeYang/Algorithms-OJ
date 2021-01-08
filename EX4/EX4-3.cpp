
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;
#define maxn  110000
map <int, int> s, vis;
int n, m, ans;
struct node
{
    int x, val;
    node(int k, int b)
    {
        x = k; val = b;
    }
    bool operator < (node t) const
    {
        return val < t.val;
    }
};
priority_queue <node> q;
int main()
{
    scanf("%d%d", &n, &m);
    int a[maxn];
    int next[maxn];
    for(int i = 1; i <= n; i ++)
    {
        scanf("%d", &a[i]);
    }
    for(int i = n; i ; i --)
    {
        if(s.count(a[i])) next[i] = s[a[i]];
        else next[i] = n + 1;
        s[a[i]] = i;
    }
    int tot = 0;
    for(int i = 1; i <= n; i ++)
    {
        if(vis[a[i]] == 1)
        {
            q.push(node(a[i], next[i]));
            continue;
        }
        if(tot == m)
        {
            tot --;
            while(!q.empty())
            {
                node t = q.top();
                q.pop();
                if(vis[t.x] == 0) continue;
                vis[t.x] = 0;
                break;
            }
        }
        ans ++;
        vis[a[i]] = 1;
        q.push(node(a[i], next[i]));
        tot ++;
    }
    printf("%d\n", ans);
    return 0;
}