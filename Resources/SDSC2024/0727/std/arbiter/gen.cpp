/*FreeTimeLove's code.
Love has a nasty habit of disappearing over night.*/
#include<bits/stdc++.h>
namespace chiptune{
#define ll long long
#define LD long double
#define i7 __int128
#define re return
#define con continue
using namespace std;
template<class T>inline bool ckmin(T &a,T b){re b<a?a=b,1:0;}
template<class T>inline bool ckmax(T &a,T b){re a<b?a=b,1:0;}
const int N=1e6+5;
inline ll rd(){
	ll ans=0,f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9')ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	re f?-ans:ans;
}
mt19937_64 rndll(chrono::system_clock::now().time_since_epoch().count());
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
const int INF=0x3f3f3f3f,mod=998244353;
int n,m,k=5e8;
//int n,m,k=1e9;
int l,r,x,y,K,T,u,v,Q,q=10,cnt;
int bk[N],c[N],sum;
char s[N];
int main(){
	freopen("arbiter.in","w",stdout);	
//	n=500;
//	n=250;
//	n=100;
//	n=1000;
	n=1500;
//	n=2000;
	printf("%d\n",n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)printf("%d ",rnd()%k+1);
		puts("");
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)printf("%d ",rnd()%k+1+k);
		puts("");
	}
	re 0;
}
/*


*/
}int main(){re chiptune::main();}
