#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define ll long long
#define N 100010
using namespace std;
ll read(){
	char cc;
	while(1){cc=getchar();if((cc>='0'&&cc<='9')||cc=='-')break;}
	ll sum=0,flag=1;
	cc=='-'?flag=-1:sum=(cc^48);
	while(1){cc=getchar();if(!(cc>='0'&&cc<='9'))break;sum=(sum<<1)+(sum<<3)+(cc^48);}
	return sum*flag;
}
void write(ll x){
	if(!x)putchar('0');
	if(x<0){x=-x;putchar('-');}
	ll cc[25],cntt=0;
	while(x){cc[++cntt]=x%10;x/=10;}
	for(ll i=cntt;i>=1;i--)putchar(cc[i]+'0');
	putchar('\n');
}
const ll B_=450,mod=1e9+7,B__=510,inv2=500000004; 
struct node{
	ll l,r;
}b[B__][B__],B[B__];
struct ope{
	ll d,w;
}Q[N];

ll n,val[N],cnt=0,t=0,L[B__],R[B__],ls[B__],rs[B__],pos[N],s[B__][B__],s1[B__][B__],ans[B__],c[B__],Ans=0,a[N],tot[B__];
ll ask(ll l,ll r){return ((l+r)%mod)*((r-l+1+mod)%mod)%mod*inv2%mod;}
void change(ll d,ll w){
	ll x=lower_bound(val+1,val+cnt+1,d)-val;
	a[x]=w;
	ll p=pos[x];
	Ans=(Ans-ans[p]+mod)%mod;
	ans[p]=0;c[p]=0;
	
	ll Tot=0;
	for(ll i=L[p];i<=R[p];i++)if(a[i]){
		B[++Tot]=(node){val[i],val[i]+a[i]-1};
		if(Tot>=2&&B[Tot].l<=B[Tot-1].r+1){
			Tot--;
			B[Tot].r+=a[i];
		}
	}
	if(Tot&&B[Tot].r>rs[p]){
		c[p]=B[Tot].r-rs[p];
		B[Tot].r=rs[p];
	}
	for(ll i=1;i<=Tot;i++)ans[p]=(ans[p]+ask(B[i].l,B[i].r))%mod;
	Ans=(Ans+ans[p])%mod;
	
	if(!Tot){
		tot[p]=1;
		b[p][1]=(node){ls[p],rs[p]};
	}
	else {
		tot[p]=0;
		if(B[1].l>ls[p])b[p][++tot[p]]=(node){ls[p],B[1].l-1};
		for(ll i=2;i<=Tot;i++)b[p][++tot[p]]=(node){B[i-1].r+1,B[i].l-1};
		if(B[Tot].r<rs[p])b[p][++tot[p]]=(node){B[Tot].r+1,rs[p]};
//		else c[p]=B[Tot].r-rs[p];
	}
	
	for(ll i=1;i<=tot[p];i++){
		s[p][i]=s[p][i-1]+b[p][i].r-b[p][i].l+1;
		s1[p][i]=(s1[p][i-1]+ask(b[p][i].l,b[p][i].r))%mod;
	}
}
ll solve(){
	ll sumflow=0,ans=0;
	for(ll i=1;i<=t;i++){
		if(sumflow>=s[i][tot[i]]){
			sumflow-=s[i][tot[i]];
			ans=(ans+s1[i][tot[i]])%mod;
		}
		else if(sumflow){
			ll zhi=upper_bound(s[i]+1,s[i]+tot[i]+1,sumflow)-(s[i]);
			ans=(ans+s1[i][zhi-1])%mod;
			ans=(ans+ask(b[i][zhi].l,b[i][zhi].l+sumflow-s[i][zhi-1]-1))%mod;
			sumflow=0;
		}
		sumflow+=c[i];
	}
	return ans;
}
int main(){
	n=read();
	for(ll i=1;i<=n;i++){
		Q[i].d=read();
		Q[i].w=read();
		val[i]=Q[i].d;
	}
	sort(val+1,val+n+1);cnt=unique(val+1,val+n+1)-(val+1);
	while(R[t]<cnt){
		t++;
		L[t]=R[t-1]+1;
		R[t]=R[t-1]+B_;
		ls[t]=rs[t-1]+1;
		if(R[t]>cnt)R[t]=cnt;
		rs[t]=val[R[t]];
	}
	rs[t]=1e15;
	for(ll j=1;j<=t;j++)for(ll i=L[j];i<=R[j];i++)pos[i]=j;
	for(ll j=1;j<=t;j++){
		tot[j]=1;
		b[j][1]=(node){ls[j],rs[j]};
		s[j][1]=rs[j]-ls[j]+1;
		s1[j][1]=ask(ls[j],rs[j]);
	}
	
	for(ll i=1;i<=n;i++){
		change(Q[i].d,Q[i].w);
		write((Ans+solve())%mod);
	}
	return 0;
} 
/*

10 
100000000000000 1000000000
100000000000001 1000000000
100000000000002 1000000000
100000000000003 1000000000
100000000000004 1000000000
100000000000005 1000000000
100000000000006 1000000000
100000000000007 1000000000
100000000000008 1000000000
100000000000009 1000000000
100000000000000 1000000000
100000000000000 1000000000
100000000000000 1000000000
100000000000000 1000000000
100000000000000 1000000000
100000000000000 1000000000
100000000000000 1000000000
100000000000000 1000000000



*/
