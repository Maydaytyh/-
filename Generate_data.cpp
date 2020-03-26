#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <stack>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <cstdlib>
#include <map>
#define ll long long
#define eps 1e-5
#define M0(a) memset(a, 0, sizeof a)
#define M_1(a) memset(a, -1, sizeof a)
using namespace std;
const int maxn = 100005;

int num[maxn], cnt;

map<int,map<int,int> > mp;

struct Edge
{
	int u, v;
}edge[maxn];

int main()
{
	freopen("in.txt", "w", stdout);
	int n, m, k, s;
	while (~scanf("%d%d%d%d", &n, &m, &k, &s)) {
		
		printf("%d %d %d %d\n", n, m, k, s);
		
		M0(num); 
		for (int i = 1; i <= k; ++i) {
			int index = rand() % n + 1;
			if (num[index] == 0) num[index] = i;
		}
		for (int i = 1; i <= n; ++i) {
			int nu = rand() % k + 1;
			if (num[i] == 0) num[i] = nu;
		}
		
		for (int i = 1; i <= n; ++i) {
			printf("%d ", num[i]);
		}
		printf("\n");
		
		for(int i = 1;i <= n - 1; ++i){
			int x = rand() % i + 1;
			int y = i + 1;
			edge[i].u = x;
			edge[i].v = y;
			mp[x][y] = mp[y][x] = 1;
		}
		for (int i = n; i <= m;) {
			int x = rand() % n + 1;
			int y = rand() % n + 1;
			if (x != y && mp[x][y] == 0 && mp[y][x] == 0) {
				edge[i].u = x;
				edge[i].v = y;
				mp[x][y] = mp[y][x] = 1;
				i++;
			} 
		}
		
		for (int i = 1; i <= m; ++i) {
			if (i % 2) printf("%d %d\n", edge[i].u, edge[i].v);
			else printf("%d %d\n", edge[i].v, edge[i].u);
		}	
		mp.clear();
	}
	return 0;
}
