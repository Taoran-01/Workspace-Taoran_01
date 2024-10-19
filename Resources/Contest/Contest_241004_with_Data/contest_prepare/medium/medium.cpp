#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#define ll long long
#define N 500010
using namespace std;
int read(){
	char cc;
	while(1){cc=getchar();if((cc>='0'&&cc<='9')||cc=='-')break;}
	int sum=0,flag=1;
	cc=='-'?flag=-1:sum=(cc^48);
	while(1){cc=getchar();if(!(cc>='0'&&cc<='9'))break;sum=(sum<<1)+(sum<<3)+(cc^48);}
	return sum*flag;
}
void write(int x){
	if(!x)putchar('0');
	if(x<0){x=-x;putchar('-');}
	int cc[25],cntt=0;
	while(x){cc[++cntt]=x%10;x/=10;}
	for(int i=cntt;i>=1;i--)putchar(cc[i]+'0');
	putchar('\n');
}
int n,k,a[N],f[N],val[N],cnt=0,s[N],vis[N],q[N][2],hh,tt,g[N<<1];
bool check(int V){
	for(int i=1;i<=n;i++)s[i]=s[i-1]+(a[i]>=V?1:-1);
	int lasts=1;
	for(int i=1;i<=n;i++)if(s[i-1]<lasts){lasts=s[i-1];vis[i]=1;}else vis[i]=0;
//	memset(g,0,sizeof(g));
	for(ll i=0;i<=(n<<1)+10;i++)g[i]=0;
	for(int i=1;i<=n;i++)g[s[i]+n]=i;
	for(int i=(n<<1);i>=0;i--)g[i]=max(g[i],g[i+1]);
	for(int i=1;i<=n;i++)f[i]=i-1;
	for(int lun=1;lun<=k&&(1<<(lun-1))<=n;lun++){
		hh=tt=1;
		for(int i=n;i>=1;i--)if(vis[i]){
			int val=f[i]-i+1-(s[f[i]]-s[i-1]);
			while(hh<tt&&q[tt-1][0]<=val)tt--;
			q[tt][0]=val;q[tt][1]=f[i];tt++;
			while(hh<tt&&g[max((int)0,s[i-1]-q[hh][0]+1+n)]<q[hh][1])hh++;
			if(hh<tt)f[i]=g[max((int)0,s[i-1]-q[hh][0]+1+n)];
		}
		if(f[1]==n)return 1;
	}
	return 0;
}
int main(){	
	int T=read();while(T--){
		n=read();k=read();
		for(int i=1;i<=n;i++)val[i]=a[i]=read();
		sort(val+1,val+n+1);cnt=unique(val+1,val+n+1)-(val+1);
		int l=1,r=cnt;
		while(l<r){
			int mid=(l+r+1)>>1;
			if(check(val[mid]))l=mid;
			else r=mid-1;
		}
		write(val[l]);
	}
	return 0;
} 
