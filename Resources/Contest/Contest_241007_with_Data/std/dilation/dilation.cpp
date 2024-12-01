#include<iostream>
#include<vector>
using namespace std;
const int N=2e5+5;
vector<int> v[N];
int n,ans=1e9;
int siz[N],d[N],w[N],ms[N],dp[N][2],tp[N][2],td[N];
void dfs(int u,int fa){
	siz[u]=d[u]=1;
	int mx=0;
	for(auto ver:v[u]){
		if(ver==fa) continue;
		dfs(ver,u);
		siz[u]+=siz[ver];
		d[u]=max(d[u],d[ver]+1);
		if(siz[ver]>siz[ms[u]]) ms[u]=ver;
		dp[u][0]+=min(w[ver],dp[ver][0]+2);
		mx=max(mx,min(w[ver],dp[ver][0]+2)-min(w[ver],dp[ver][1]+1));
	}
	dp[u][1]=dp[u][0]-mx;
	w[u]=2*siz[u]-d[u];
}
void getdep(int u,int fa){
	int k=max(td[u]+1,d[u]);
	td[ms[u]]=td[u]+1;
	for(auto ver:v[u]){
		if(ver==fa) continue;
		if(ver!=ms[u]){
			td[ver]=k;
			getdep(ver,u);
			td[ms[u]]=max(td[ms[u]],d[ver]+1);
		}
	}
	if(ms[u]) getdep(ms[u],u);
}
void solve(int u,int fa){
	int t=0,pc=0,W=2*n-2*siz[u]-td[u];
	int mx=min(W,tp[u][0]+2)-min(W,tp[u][1]+1),nx=mx;
	for(auto ver:v[u]){
		if(ver==fa) continue;
		t+=min(w[ver],dp[ver][0]+2);
		int c=min(w[ver],dp[ver][0]+2)-min(w[ver],dp[ver][1]+1);
		if(c>mx){
			mx=c;
			pc=ver;
		}
	}
	for(auto ver:v[u]){
		if(ver==fa) continue;
		tp[ver][0]=min(W,tp[u][0]+2)+t-min(w[ver],dp[ver][0]+2);
		if(ver!=pc){
			tp[ver][1]=min(W,tp[u][0]+2)+t-min(w[ver],dp[ver][0]+2)-mx;
			nx=max(nx,min(w[ver],dp[ver][0]+2)-min(w[ver],dp[ver][1]+1));
		}
	}
	tp[pc][1]=min(W,tp[u][0]+2)+t-min(w[pc],dp[pc][0]+2)-nx;
	for(auto ver:v[u]){
		if(ver==fa) continue;
		solve(ver,u);
	}
}
void calc(int u,int fa){
	int cur=0,mx=0;
	for(auto ver:v[u]){
		if(ver==fa) continue;
		cur+=min(w[ver],dp[ver][0]+2);
		mx=max(mx,min(w[ver],dp[ver][0]+2)-min(w[ver],dp[ver][1]+1));
	}
	int W=n*2-siz[u]*2-td[u];
	cur+=min(W,tp[u][0]+2);
	mx=max(mx,min(W,tp[u][0]+2)-min(W,tp[u][1]+1));
	ans=min(ans,cur-mx);
	for(auto ver:v[u]){
		if(ver==fa) continue;
		calc(ver,u);
	}
}
int main(){
//	freopen("dilation.in","r",stdin);
//	freopen("dilation.out","w",stdout); 
	cin>>n;
	for(int i=1,a,b;i<n;i++){
		cin>>a>>b;
		v[a].push_back(b);
		v[b].push_back(a);
	}
	dfs(1,0);
	getdep(1,0);
	solve(1,0);
	calc(1,0);
	cout<<ans<<"\n";
	return 0;
}//
