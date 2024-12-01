#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector> 
#include <random>
#include <chrono>
#include <set>
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
set <ll> s0,s1;
ll n,q,t[N<<2],c[N],tt;
void change(ll x,ll l,ll r,ll L,ll k){
	if(l==r){t[x]=min(t[x],k);return ;}
	ll mid=(l+r)>>1;
	if(mid>=L)change(x<<1,l,mid,L,k);
	else change(x<<1|1,mid+1,r,L,k);
	t[x]=min(t[x<<1],t[x<<1|1]);
}
ll ask(ll x,ll l,ll r,ll L,ll R){
	if(L<=l&&r<=R)return t[x];
	ll mid=(l+r)>>1;
	if(mid>=L&&mid<R)return min(ask(x<<1,l,mid,L,R),ask(x<<1|1,mid+1,r,L,R));
	if(mid>=L)return ask(x<<1,l,mid,L,R);
	return ask(x<<1|1,mid+1,r,L,R);
}
int main(){
	n=read();q=read();
	for(ll i=1;i<=n;i++)s1.insert(i);
	s1.insert(0);s1.insert(n+1);
	s0.insert(0);s0.insert(n+1);
	memset(t,0x3f,sizeof(t));
	while(q--){
		ll op=read();
		if(op==0){
			ll l=read(),r=read(),x=read();
			if(x==0){
				tt=0;
				for(set<ll>::iterator it=s1.lower_bound(l);*it<=r;it++){
					s0.insert(*it);
					c[++tt]=*it;
				}
				for(ll i=1;i<=tt;i++)s1.erase(c[i]);
			}else change(1,1,n,l,r);
		}
		else {
			ll x=read();
			if(*s0.lower_bound(x)==x)printf("0\n");
			else {
				set <ll>::iterator it=s1.lower_bound(x);
				it--;ll L=*it+1;it++;it++;ll R=*it-1;
				if(ask(1,1,n,L,x)<=R)printf("1\n");else printf("?\n");
			}
		}
	}
	return 0;
}/*







*/
