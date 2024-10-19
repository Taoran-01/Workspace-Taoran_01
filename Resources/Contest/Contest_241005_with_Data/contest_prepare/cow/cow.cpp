#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#define ll long long
#define N 500010
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
const ll mod=1e9+7,inv2=(mod+1)/2;
ll q,qx[N],qy[N],a1[N],n;
struct node{
	ll s,ans,f;
}t[N<<2];
ll askcha(ll l,ll r){return ((l+r)%mod)*((r-l+1)%mod)%mod*inv2%mod;}
node ask(ll x,ll l,ll r,ll f){
	if(l==r){
		ll L=a1[l],R=a1[l+1]-1;ll k=t[x].s+f+t[x].f;
		if(k>R-L+1)return (node){R-L+1,askcha(L,R),k-(R-L+1)};
		return (node){k,askcha(L,L+k-1),0};
	}
	ll mid=(l+r)>>1;
	if(f<=a1[mid+1]-a1[l]-t[x<<1].s){
		node w=ask(x<<1,l,mid,f);
		return (node){w.s+t[x].s-t[x<<1].s,(t[x].ans-t[x<<1].ans+w.ans+mod)%mod,t[x].f};
	}
	node w=ask(x<<1|1,mid+1,r,t[x<<1].f+f-(a1[mid+1]-a1[l]-t[x<<1].s));
	return (node){a1[mid+1]-a1[l]+w.s,(askcha(a1[l],a1[mid+1]-1)+w.ans)%mod,w.f};
}
void change(ll x,ll l,ll r,ll Lx,ll k){
	if(l==r){
		ll L=a1[l],R=a1[l+1]-1;
		if(k>R-L+1)t[x]=(node){R-L+1,askcha(L,R),k-(R-L+1)};
		else t[x]=(node){k,askcha(L,L+k-1),0};
		return ;
	}
	ll mid=(l+r)>>1;
	if(mid>=Lx)change(x<<1,l,mid,Lx,k);
	else change(x<<1|1,mid+1,r,Lx,k);
	node w=ask(x<<1|1,mid+1,r,t[x<<1].f);
	t[x]=(node){t[x<<1].s+w.s,(t[x<<1].ans+w.ans)%mod,w.f};
}
int main(){
	q=read();for(ll i=1;i<=q;i++)a1[i]=qx[i]=read(),qy[i]=read();
	sort(a1+1,a1+q+1);n=unique(a1+1,a1+q+1)-(a1+1);
	a1[n+1]=1e15;	
	for(ll i=1;i<=q;i++){
		change(1,1,n,lower_bound(a1+1,a1+n+1,qx[i])-a1,qy[i]);
		write(t[1].ans);
	}
	return 0;
}
