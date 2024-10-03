#include <bits/stdc++.h>
using namespace std;
const int N=1000005,Mod=1e9+7;
int a[N],b[N];
int qpow(int a,int b){
	int ans=1;
	while (b){
		if (b&1) ans=1ll*ans*a%Mod;
		a=1ll*a*a%Mod,b>>=1;
	}
	return ans;
}
int main (){
	freopen ("10.in","r",stdin);
	freopen ("10.out","w",stdout);
	int n;scanf ("%d",&n);
	for (int i=1;i<=n;i++) {
		int m;scanf ("%d",&m);
		int inv=qpow(m,Mod-2);
		for (int j=1;j<=m;j++){
			int x;scanf ("%d",&x);
			a[x]=(a[x]+inv)%Mod,b[x]=(b[x]+1)%Mod;
		}
	}
	int ans=0;
	for (int i=1;i<=1000000;i++)
		ans=(ans+1ll*a[i]*b[i])%Mod;
	printf ("%d",1ll*ans*qpow(1ll*n*n%Mod,Mod-2)%Mod);
	return 0;
}

