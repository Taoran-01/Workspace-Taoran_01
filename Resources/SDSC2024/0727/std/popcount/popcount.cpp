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
const int N=3e5+5;
inline ll rd(){
	ll ans=0,f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9')ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	re f?-ans:ans;
}
const int B=30;
int n,m,a[N],f[50];
char ch[5];
namespace SGT{
	#define t d[v]
	#define vl v<<1
	#define vr v<<1|1 
	#define tl d[vl] 
	#define tr d[vr]
	#define mid ((l+r)>>1)
	struct data{
		int l,r,len;ll x,a,b;int p,f[50];
	}d[N<<2];
	void mdf(int v,int *f){
		if(t.l==t.r)t.x=f[__builtin_popcountll(t.x+t.b)];
		else{
			if(!t.p)t.p=1,t.a=t.b,memcpy(t.f,f,sizeof t.f);
			else for(int i=0;i<50;i++)t.f[i]=f[__builtin_popcountll(t.f[i]+t.b)];
		}
		t.b=0;
	}
	inline void pd(int v){
		tl.b+=t.a,tr.b+=t.a;
		if(t.p)mdf(vl,t.f),mdf(vr,t.f);
		tl.b+=t.b,tr.b+=t.b;
		t.a=t.b=t.p=0;
	}
	void bd(int l,int r,int v){
		t.l=l,t.r=r,t.len=r-l+1;
		if(l==r){t.x=a[l];re;}
		bd(l,mid,vl),bd(mid+1,r,vr);
	}
	void ud(int l,int r,int v,int k){
		if(t.l>=l&&t.r<=r){t.b+=k;re;}
		pd(v);
		if(tl.r>=l)ud(l,r,vl,k);
		if(tr.l<=r)ud(l,r,vr,k);
	}
	void ud1(int l,int r,int v){
		if(t.l>=l&&t.r<=r){mdf(v,f);re;}
		pd(v);
		if(tl.r>=l)ud1(l,r,vl);
		if(tr.l<=r)ud1(l,r,vr);
	}
	ll qry(int x,int v){
		if(t.l==t.r)re t.x+t.b;
		pd(v);
		re qry(x,tl.r>=x?vl:vr);
	}
	#undef t
	#undef mid
}
int main(){
	freopen("popcount.in","r",stdin);
	freopen("popcount.out","w",stdout);
//	freopen("popcount4_2.in","r",stdin);
//	freopen("popcount4_2.out","w",stdout);
	n=rd(),m=rd();
	for(int i=0;i<50;i++)f[i]=i;
	for(int i=1;i<=n;i++)a[i]=rd();
	SGT::bd(1,n,1);
	for(int i=1;i<=m;i++){
		int op=rd();
		switch(op){
			case 1:{int l=rd(),r=rd();SGT::ud(l,r,1,rd());break;}
			case 2:{int l=rd(),r=rd();SGT::ud1(l,r,1);break;}
			case 3:{int x=rd();printf("%lld\n",SGT::qry(x,1));break;}
		}
	}
	re 0;
}
/*

*/
}int main(){re chiptune::main();}
