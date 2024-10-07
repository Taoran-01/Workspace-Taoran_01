#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#define ll long long
#define N 2000010
using namespace std;
int read(){
	char cc;
	while(1){cc=getchar();if((cc>='0'&&cc<='9')||cc=='-')break;}
	int sum=0,flag=1;
	cc=='-'?flag=-1:sum=(cc^48);
	while(1){cc=getchar();if(!(cc>='0'&&cc<='9'))break;sum=(sum<<1)+(sum<<3)+(cc^48);}
	return sum*flag;
} 
void write(ll x){
	if(!x)putchar('0');
	if(x<0){x=-x;putchar('-');}
	int cc[25],cntt=0;
	while(x){cc[++cntt]=x%10;x/=10;}
	for(int i=cntt;i>=1;i--)putchar(cc[i]+'0');
	putchar('\n');
}
const int B=2000003;
int T,n,s[N],q[N],hh=0,a[N],tong[N<<1];
ll ans=0,sum=0;
char c[N]; 
int main(){
	T=read();
	while(T--){
		n=read();
		scanf("%s",c+1);
		for(int i=1;i<=n;i++)s[i]=s[i-1]+(c[i]==')'?-1:1);
		sum=0;ans=0;
		for(int i=B+n;i>=B-n;i--)tong[i]=0;
		for(int i=0;i<=n;i++)tong[s[i]+B]++; 
		for(int i=B+n;i>=B-n;i--){
			for(int j=1;j<=tong[i];j++){
				ans+=(ll)(n-sum-sum)*(i-B);
				sum++;
			}
		}
		hh=0;sum=0;
		for(int i=n;i>=0;i--){
			int _su=0;
			while(hh&&s[q[hh]]>s[i])sum-=a[hh--];
			if(hh&&s[q[hh]]==s[i]){_su+=a[hh];sum-=a[hh];hh--;}
			if(hh)ans+=n-q[hh]+1-sum;
			q[++hh]=i;a[hh]=_su+1;sum+=a[hh];
		}
		write(ans);
	}
	return 0;
} 
