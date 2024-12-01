/*FreeTimeLove's code.
Love has a nasty habit of disappearing over night.*/
#include<bits/stdc++.h>
namespace FRTMLV{
#define ll long long
#define LD long double
#define i7 __int128
#define re return
#define con continue
using namespace std;
template<class T>inline bool ckmin(T &a,T b){re b<a?a=b,1:0;}
template<class T>inline bool ckmax(T &a,T b){re a<b?a=b,1:0;}
const int N=1e3+5;
inline int rd(){
	int ans=0,f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9')ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	re f?-ans:ans;
}
const int mod1=1e9+7,mod2=1e9+9;
int n,n2;
ll ha1[N][N],hb1[N][N],ha2[N][N],hb2[N][N],mi1[N*N],mi2[N*N];
inline void MD(ll &x,int m){if(x>=m)x-=m;}
inline ll inc(int x,int y,int d,ll (*h)[N],ll *mi,ll m){
	ll ans=(h[x][y]-h[x][y-d]*mi[d]-h[x-d][y]*mi[d*n]+h[x-d][y-d]*mi[d*(n+1)])%m+m;
	MD (ans,m);
	re ans;
}
int nd[10000020],tt=1;
const int md=10000019;
struct hash{ll v;int nxt;}h[N*N];
inline void add(int u,ll v){h[++tt]={v,nd[u]};nd[u]=tt;}
bool chk(int d){
	memset(nd,0,sizeof nd),tt=1;
	for(int i=d;i<=n;i++)
		for(int j=d;j<=n;j++){
			ll tmp=(ll)mod2*inc(i,j,d,ha1,mi1,mod1)+inc(i,j,d,ha2,mi2,mod2);
			add(tmp%md,tmp);
		}
	for(int i=d;i<=n;i++)
		for(int j=d;j<=n;j++){
			ll tmp=(ll)mod2*inc(i,j,d,hb1,mi1,mod1)+inc(i,j,d,hb2,mi2,mod2);
			for(int k=nd[tmp%md];k;k=h[k].nxt)
				if(h[k].v==tmp)re 1;
		}
	re 0;
}
inline void calc(int i,int j,ll(*h)[N],ll *mi,int mod,int x){
	h[i][j]=((h[i-1][j]*mi[n]+h[i][j-1]*mi[1]-h[i-1][j-1]*mi[n+1]+x)%mod+mod)%mod;
}
int main(){
	freopen("arbiter.in","r",stdin);
	freopen("arbiter.out","w",stdout);
	n=rd(),n2=n*n;
	mi1[0]=mi2[0]=1;
	for(int i=1;i<=n2;i++)mi1[i]=mi1[i-1]*29%mod1,mi2[i]=mi2[i-1]*31%mod2;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			int x=rd();
			calc(i,j,ha1,mi1,mod1,x);
			calc(i,j,ha2,mi2,mod2,x);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			int x=rd();
			calc(i,j,hb1,mi1,mod1,x);
			calc(i,j,hb2,mi2,mod2,x);
		}
	int l=1,r=n+1,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(chk(mid))l=mid+1;
		else r=mid;
	}
	printf("%d\n",l-1);
	re 0;
}
/*

*/
}int main(){re FRTMLV::main();}
