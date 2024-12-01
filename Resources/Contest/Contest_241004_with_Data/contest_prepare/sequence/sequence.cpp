#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define ll long long
#define N 4000010
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
ll n,a[N],maxn,ans=-1;
int main(){
	n=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	maxn=-1e18;	
	for(ll i=1;i<=n;i++){
		maxn=max(maxn,-a[i]+i);
		ans=max(ans,a[i]-i+maxn);
	}
	maxn=-1e18;	
	for(ll i=1;i<=n;i++){
		maxn=max(maxn,a[i]+i);
		ans=max(ans,-a[i]-i+maxn);
	}
	write(ans-1);
	return 0;
}
