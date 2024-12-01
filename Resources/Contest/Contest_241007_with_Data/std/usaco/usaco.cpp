#include<iostream>
#include<vector>
#define int long long
using namespace std;
const int N=3e3+5,mod=1e9+7;
int a[N][N],s[N][N];
int n,m,x;
int ans;
vector<int> v;
int solve(int k){
	if(k>n) return 0;
	if((x/2)/k>m) return 0;
	int l=1,ans=1;
	int avl=1;
	int tmp=1;
	v.clear();
	for(int i=1;i<=n;i++){
		if(s[i][m]==(x/k)*l){
			if(s[i][m]!=s[i+1][m]){
				v.push_back(i);
				l++;
				if(i<n) ans=ans*tmp%mod;
				tmp=1;
			}
			else tmp++;
		}
		else if(s[i][m]>(x/k)*l) avl=0;
		if(!avl) break;
	}
	if(!avl) return 0;
	l=1,tmp=1;
	for(int i=1;i<=m;i++){
		if(s[n][i]==2*k*l){
			int c=1,fl=1;
			for(auto u:v){
				if(s[u][i]!=2*c*l) fl=0; 
				c++;
			}
			if(!fl){
				avl=0;
				break;
			}
			if(s[n][i]!=s[n][i+1]){
				l++;
				if(i<m) ans=ans*tmp%mod;
				tmp=1;
			}
			else tmp++;
		}
		else if(s[n][i]>2*k*l) avl=0;
		if(!avl) break;
	}
	return avl*ans;
}
signed main(){
//	freopen("usaco.in","r",stdin);
//	freopen("usaco.out","w",stdout);
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char ch;
			cin>>ch;
			a[i][j]=ch-'G';
			s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];
		}
	}
	x=s[n][m];
	if(x&1){
		cout<<"0\n";
		return 0;
	}
	for(int i=1;i*i<=x/2;i++){
		if((x/2)%i==0){
			ans=(ans+solve(i))%mod;
			if(i*i<x/2) ans=(ans+solve((x/2)/i))%mod;
		}
	}
	cout<<ans<<"\n";
	return 0;
}
