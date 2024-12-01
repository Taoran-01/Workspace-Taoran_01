#include <bits/stdc++.h>
using namespace std;
const int N=205,P=1005,mod=998244353;
int n,k,p,a[N],f[N][P],g[N][P],ans;
signed main(){
	freopen("dice.in","r",stdin);
	freopen("dice.out","w",stdout); 
	ios::sync_with_stdio(0);
	cin>>n>>k>>p;
	for(int i=1;i<=n;i++) cin>>a[i];
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=k;j++) g[j][0]=0;
		for(int j=0;j<=k;j++) for(int t=1;t<=p;t++) g[j][t]=(g[j][t-1]+f[j][t-1])%mod;
		for(int j=1;j<=k;j++) for(int s=0;s<=p;s++) f[j][s]=((g[j-1][s]-g[j-1][s-min(s,a[i])]+f[j][s])%mod+mod)%mod;
	}
	for(int s=0;s<=p;s++) ans=(ans+f[k][s])%mod;
	cout<<ans;
	return 0;
}
