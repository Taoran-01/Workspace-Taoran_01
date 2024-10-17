#include<iostream>
#include<vector> 
#include<cstring>
#define int long long
using namespace std;
const int N=3e5+5;
int n,k;
vector<int> v[N];
int f[N],a[N],h[N],c[N],d[N],lst[N];
int t;
void solve(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
    	cin>>a[i];
    	v[a[i]].push_back(i);
	}
    for(int i=1;i<=k;i++) cin>>c[i];
    for(int i=1;i<=k;i++) cin>>h[i];
	for(int i=1;i<=k;i++){
		if(v[i].size()==0) continue;
		lst[v[i][0]]=0;
		for(int j=1;j<v[i].size();j++){
			lst[v[i][j]]=v[i][j-1];
		}
	}
	for(int i=1;i<=n;i++){
		if(a[i]==a[i-1]) d[i]=d[i-1]+h[a[i]];
		else d[i]=d[i-1]+c[a[i]];
        //cout<<lst[i]<<" "<<d[i]<<endl;
	}
    f[1]=c[a[1]];
    for(int i=2;i<=n;i++){
        int l=lst[i];
        if(l==i-1) f[i]=f[i-1]+h[a[i]];
        else f[i]=min(f[l+1]+d[i-1]-d[l+1]+(l==0?c[a[i]]:h[a[i]]),f[i-1]+c[a[i]]);
    }
    cout<<f[n]<<endl;
}
signed main(){
//	freopen("florrio.in","r",stdin);
//	freopen("florrio.out","w",stdout);
	ios::sync_with_stdio(0);
    solve();
    return 0;
}
