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

int a[N], b[N], n;
vector<PII> ans1, ans2;

void add(int l,int r,vector<PII> &g){ g.pb(mk(l,r)), swap(a[l], a[r]);}
void merge(int l,int r,vector<PII> &g){
	bool flag = false; int mid = l, L = l, R = r;
	for(int i=l;i<r;++i)	flag |= a[i]>a[i+1];
	if(!flag)	return ;
	while(a[mid]<a[mid+1])	++mid;
	for(int i = l; i<=r; ++i)	b[i] = a[i];
	nth_element(b+l, b+mid, b+r+1);
	while(a[L]<=b[mid])	++L; while(a[R]>b[mid])	--R;
	for(int i = L, j = mid; i<j; ++i, --j)	add(i, j, g);
	for(int i = mid + 1, j = R; i<j; ++i, --j)	add(i, j, g);
	for(int i = L, j = R; i<j; ++i, --j)	add(i, j, g);
	merge(l, mid, g), merge(mid+1, r, g);
}
void split(int l,int r,vector<PII> &g){
	if(l==r)	return ;
	int mid = l+r>>1;
	split(l, mid, g), split(mid+1, r, g);
	merge(l, r, g);
}

int main(){
	freopen("information.in","r",stdin);
	freopen("information.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i)	cin>>a[i];
	split(1, n, ans1);
	for(int i=1;i<=n;++i)	cin>>a[i];
	split(1, n, ans2);
	reverse(ans2.begin(), ans2.end());
	for(auto x:ans2)	ans1.pb(x);
	cout<<ans1.size()<<endl;
	for(auto x:ans1)	cout<<x.fi<<" "<<x.se<<endl;
	return 0;
}
