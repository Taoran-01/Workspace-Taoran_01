#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define pb push_back
#define PII pair<int,int>
#define vo vector
const int N=5e2+5,inf=1e18;
int dp[N][N],a[N][N],p[N];
void solve(){
	//freopen("10.in","r",stdin);
	//freopen("10.out","w",stdout);
	int n,m,k;cin>>n>>m>>k;
	for(int i=0;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=dp[i][j]=inf;
		}
	}
	for(int i=1;i<=m;i++){
		int l,r,c;cin>>l>>r>>c;
		a[l][r]=min(a[l][r],c);
	}
	for(int i=1;i<=n;i++) cin>>p[i];//,p[i]=1
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++) dp[i][j]=dp[i-1][j];
		int tc=inf;
		for(int l=1;l<=i;l++){
			if(a[l][i]<tc||p[l-1]!=1){
				tc=min(tc,a[l][i]);
				for(int j=1;j<=i;j++){
					int d=j-(i-l+1);
					if(d>=0&&d<=l-1) dp[i][j]=min(dp[i][j],dp[l-1][d]+tc);
				}	
			}
			else if(p[l-1]==1) tc=inf;
		}
	}
	//比k大的都可以 
	int ans=inf;
	for(int i=k;i<=n;i++){
		ans=min(ans,dp[n][i]);
	}
	if(ans<inf) cout<<ans<<endl;
	else cout<<-1<<endl;
}
signed main(){
	//ios::sync_with_stdio(false);cin.tie(0);
	int T=1;
    //cin>>T;
	while(T--){
		solve();
	}
}
/*
1
3
1 1 1

*/
