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
const int N = 50 + 10;
const int M = 1e5 + 10;

int f[M], a[N], n, m, pre[M], minn;

int main(){
	freopen("construct.in","r",stdin);
	freopen("construct.out","w",stdout);
//	cout<<"4\n3\n1 25 100\n";
//	return 0;
	memset(f, 0x3f, sizeof(f));
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin>>n; f[1] = 0;
	for(int i=1;i<=n;++i)	cin>>a[i], m = max(m, a[i]), f[1] += a[i];
	int ans = f[1], minn = 1;
	for(int i=1;i<=m;++i){
		for(int j=2;i*j<=m;++j){
			int mn = 0;
			for(int k=1;k<=n;++k)	mn += a[k]/(i*j);
			if(f[i]-(j-1)*mn < f[i*j])	f[i*j] = f[i] - (j-1)*mn, pre[i*j] = i;
			if(ans > f[i*j])	ans = f[i*j], minn = i*j;
		}
	}
	cout<<ans<<endl;
	vector<int> v;
	while(minn)	v.pb(minn), minn = pre[minn];
	cout<<v.size()<<endl;
	for(int i=v.size()-1;i>=0;--i)	cout<<v[i]<<" ";
	cout<<endl;
	return 0;
}
