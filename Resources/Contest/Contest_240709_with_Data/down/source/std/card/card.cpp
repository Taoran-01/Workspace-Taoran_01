#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
#include<stack>
#include<algorithm>
#include<map>
#include<iomanip>
#include<unordered_map>

#include<bitset>
#include<set>

#include<deque>
#include<cassert>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<vector>
#include<random>

#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define DBG cerr << __LINE__ << ' ' << __FUNCTION__ << endl

#define DRE default_random_engine
#define UID uniform_int_distribution
#define y0 Y0
#define y1 Y1

#define pi acos(-1)
#define eps (1e-8)
#define endl '\n'

using namespace std;

const int INF = 0x3f3f3f3f;
typedef pair<int,int> PII;
typedef pair<int,PII> PIII;
const int N = 1e5 + 10;
const int M = 1e6 + 10;

int n, m, k, st[N];
vector<int> ans, g[N];
bool vis[N];

void dfs(int x, int st){
	vis[x] = true;
	if(st == 2)	return ;
	for(int y:g[x])	dfs(y, st+1);
}

int main(){
	freopen("card.in","r",stdin);
	freopen("card.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1,x,y;i<=m;++i)	cin>>x>>y, g[x].pb(y), g[y].pb(x);
	for(int i=1;i<=n;++i)
		if(!vis[i])	ans.pb(i), dfs(i, 0);
	cout<<"Possible"<<endl;
	cout<<ans.size()<<endl;
	for(int x:ans)	cout<<x<<" ";
	cout<<endl;
	return 0;
}
