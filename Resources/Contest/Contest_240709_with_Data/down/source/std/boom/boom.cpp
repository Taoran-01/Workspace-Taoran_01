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
const int N = 1e6 + 1e4;
const int M = 1e6 + 10;

int T, p, k, phi, F[N];
int gcd(int x,int y){ return y==0 ? x : gcd(y, x%y);}
long long pre[N];
inline int ksm(int x,int m){
	int ans = 1;
	for(; m; x=x*x%k, m>>=1) if(m&1) ans = ans * x % k;
	return ans;
}
inline int f(int x){
	if(x < phi)	x = ksm(x%k, x);
	else	x = ksm(x%k, x%phi+phi);
	return x ? x : k;
}
unordered_map<int,int> ma;

signed main(){
	freopen("boom.in","r",stdin);
	freopen("boom.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin>>T;
	while(T--){
//		cout<<-1<<" "<<-1<<endl;
//		continue;
		cin>>k>>p; --k;
//		if(k==61)	return 0;
		phi = 0; bool flag = false;
		for(int i=1;i<k;++i)	phi += (gcd(i, k) == 1);
		if(k==1)	phi = 1;
		for(int r=1;r<phi && !flag;++r){
			pre[r] = (F[r] = f(r)) + pre[r-1];
			for(int l = 1; l<=r; ++l)
				if(pre[r] - pre[l-1] == p){
					cout<<l<<" "<<r<<endl;
					flag = true;
					break;
				}
		}
		if(flag)	continue;
		int len = k * phi / gcd(k, phi);
		long long sl = 0, ml = 0, sr = 0, mr = 0, ansl, ansr, sum = 0;
		for(int i = phi; i < phi+len; ++i)	sum += (F[i] = f(i));
		sr = pre[phi-1] + F[phi], mr = sr % sum, sl = p, ml = sl % sum;
		for(int r = phi, l = 1; l<phi + len; ){
			if(r < phi + len && sr <= sl){
				pre[r] = sr;
				ma[mr] = r; sr += F[++r];
				if((mr += F[r])>=sum)	mr -= sum;
			}else{
				if(ma.find(ml) != ma.end()){
					ansl = l, ansr = ma[ml];
					ansr += (sl - pre[ansr]) / sum * len;
					cout<<ansl<<" "<<ansr<<endl;
					flag = true;
					break;
				}
				if((ml += F[l])>=sum)	ml -= sum;
				sl += F[l++];
			}
		}
		if(!flag)	cout<<"-1 -1"<<endl;
		ma.clear();
	}
	return 0;
}
