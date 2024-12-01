#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define ll long long
#define N 5000010
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
ll n,m,x,a[N],f[N],g[N],ans=-1,q[N],hh,tt;
int main(){
//	freopen("ex_insert5.in","r",stdin);
//	freopen("ex_insert5.ans","w",stdout);
//	freopen("insert.out","w",stdout);
	n=read();m=read();x=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	if(m==1){
		ans=x;for(ll i=1;i<=n;i++)ans+=a[i];
		write(ans);return 0;
	}
	hh=tt=1;
	for(ll i=1;i<=n;i++){
		while(hh<tt&&i-q[hh]+1>m-1)hh++;
		while(hh<tt&&a[q[tt-1]]<=a[i])tt--;
		q[tt++]=i;
		f[i]=a[q[hh]];
	}
	for(ll i=m-1;i<=n;i++)g[i]=max(f[i],x)+g[i-1];
	for(ll i=1;i<=m-1;i++)f[i]=0;
	for(ll i=m;i<=n;i++)f[i]=max(f[i],a[i-m+1])+f[i-1];
	for(ll i=1;i<=n+1;i++)ans=max(ans,f[i-1]+g[(i+m-2)>n?n:i+m-2]-g[(i-2)<0?0:i-2]+f[n]-f[(i+m-2)>n?n:i+m-2]);
	write(ans);
	return 0;
}
