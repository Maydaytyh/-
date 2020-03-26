//单点增减，区间求和
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <string>
#include <stack>
#include <algorithm>
#include <map>
#include <queue>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f
#define MAXN 100000 + 50
#define MAXM 30000
#define ll long long
#define per(i, n, m) for (int i = n; i >= m; --i)
#define rep(i, n, m) for (int i = n; i <= m; ++i)
#define mod 1000000000 + 7
#define mian main
#define mem(a, b) memset(a, b, sizeof a)
#ifndef ONLINE_JUDGE
#define dbg(x) cout << #x << "=" << x << endl;
#else
#define dbg(x)
#endif
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = 10 * x + ch - '0';
        ch = getchar();
    }
    return x * f;
}
inline ll readll()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = 10 * x + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int a[MAXN * 4];
int sum[MAXN * 4];
int T, n, b, c, ans;
int build(int l, int r, int o)
{
    if (l == r)
        return sum[0] = a[l];
    else
    {
        int mid=l+(r-l)/2;//为什么这么写
        return sum[o]=build(l,mid,2*o)+build(mid+1,r,2*o+1);
    }
}
// 1 5 3   2 7 