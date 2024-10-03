#include<iostream>
#include<cstdio>
const int N=1e5+10; 
int n,a[N],vis[N];
int main(){
	freopen("d.out","r",stdin);
	scanf("%d",&n);
	n=0;
	while(scanf("%d",&a[++n])!=EOF);
	long long sum=0;
	n--;
	for(int i=1;i<=n;i++)sum=(sum+a[i])%n,vis[sum]=1;
	bool fl=1;
	for(int i=0;i<n;i++)if(!vis[i])fl=0;
	if(fl)puts("AC");
	else puts("WA");
}
