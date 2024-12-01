#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
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
const ll d1[4][2]={
{-1,0},
{0,1},
{0,-1},
{1,0}
},
d2[36][2]={
{-1,-1},{-1,0},
{0,-1},{1,0},
{0,1},{1,1},
{-1,0},{-1,1},
{0,-1},{1,-1},
{0,1},{1,0},
{-1,0},{0,-1},
{-1,1},{0,1},
{1,-1},{1,0},
{-1,-1},{0,-1},
{-1,0},{0,1},
{1,0},{1,1},
{0,-2},{0,-1},
{0,-1},{0,1},
{0,1},{0,2},
{-2,0},{-1,0},
{-1,0},{1,0},
{1,0},{2,0},
};
const ll mod=1e9+7,inv2=500000004,inv6=166666668;
ll T,n,m,k,t,M,ans1,ans2,ans;
map <ll,bool> c; 
ll dui(ll x,ll y){return x*mod+y;}
int main(){
//	freopen("data.in","r",stdin);
	T=read();
	while(T--){
		n=read();m=read();k=read();t=read();
		M=(n*m-t+mod)%mod;
	//	if(n*m-t<k){printf("0\n");continue;}
		c.clear();
		ans1=(2*n*m-n-m)%mod;
		ans2=(4*(n-1)*(m-1)%mod+(m>=2)*n*(m-2)%mod+(n>=2)*m*(n-2)%mod)%mod;
		while(t--){
			ll x=read(),y=read();
			c[dui(x,y)]=1;
			for(ll i=0;i<4;i++){
				ll nx=x+d1[i][0],ny=y+d1[i][1];
				if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&c.find(dui(nx,ny))==c.end())ans1--;
			}
			for(ll i=0;i<36;i+=2){
				ll nx1=x+d2[i][0],ny1=y+d2[i][1];
				ll nx2=x+d2[i+1][0],ny2=y+d2[i+1][1];
				if(nx1>=1&&nx1<=n&&ny1>=1&&ny1<=m&&nx2>=1&&nx2<=n&&ny2>=1&&ny2<=m&&c.find(dui(nx1,ny1))==c.end()&&c.find(dui(nx2,ny2))==c.end())ans2--;
			}
		}
		ans1=(ans1+mod)%mod;
		ans2=(ans2+mod)%mod;
		if(k==2)ans=(M*(M-1+mod)%mod*inv2%mod-ans1+mod)%mod;
		if(k==3)ans=(M*(M-1+mod)%mod*(M-2+mod)%mod*inv6%mod-ans1*(M-2+mod)%mod+ans2+mod)%mod;
		write(ans);
	}
	return 0;
}
/*

1
2 4 3 2
1 3
2 2





*/ 
