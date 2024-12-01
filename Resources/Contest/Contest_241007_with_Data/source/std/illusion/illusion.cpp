#include<iostream>
#include<cstring>
#include<vector>
#define lowbit(x) x&(-x)
#define bug cout<<"florr\n";
using namespace std;
const int N=1e6+5;
vector<int> v[N];
int T,q,n=1,cnt;
int op[N],u[N],x[N];
int l[N],r[N];
int dfs(int u){
	l[u]=++cnt;
	for(auto ver:v[u]){
		dfs(ver);
	}
	r[u]=cnt;
}
long long t[N],ans[N];
void update(int x,int num) {
    while(x<=n){
        t[x]+=num;
        x+=lowbit(x);
    }
}
long long query(int x) {
    long long ans=0;
    while(x){
        ans+=t[x];
        x-=lowbit(x);
    }
    return ans;
}
int main(){
	freopen("illusion.in","r",stdin);
	freopen("illusion.out","w",stdout);
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>q;
		for(int i=1;i<=q;i++){
			cin>>op[i]>>u[i];
			if(op[i]==2) cin>>x[i];
			else v[u[i]].push_back(++n);
		}
		dfs(1);
		int c=0;
		for(int i=q;i;i--){
			if(op[i]==1){
				ans[n-c]=query(l[n-c]);
				c++;
			}
			else{
				update(r[u[i]]+1,-x[i]);
				update(l[u[i]],x[i]);
			}
		}
		ans[1]=query(1);
		for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
		cout<<"\n";
		for(int i=1;i<=n;i++) v[i].clear();
		for(int i=1;i<=n;i++) t[i]=0;
		n=1;
		cnt=0;
	}
	return 0;
}
