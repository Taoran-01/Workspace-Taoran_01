#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N=5e6+5,L=5e4,mod=998244353;
int n,m;
int cnt=0;
int f[N],dfn[N],fa[N],out[N],dep[N],c[N],d[N], mi[19][N],s[N];
vector<int>e[N];
int get(int x, int y) {return dfn[x] < dfn[y] ? x : y;}//返回dfs序更小的一个
//dfs序 
void dfs(int id, int f) {
	dep[id]=dep[f]+1;
  	mi[0][dfn[id] = ++cnt] = f;
	s[dfn[id]]=s[dfn[f]]+1;//前缀和 
  	for(int it : e[id]) if(it != f) dfs(it, id); 
  	out[id]=cnt;
}
//求lca 
int lca(int u, int v) {
  if(u == v) return u;
  if((u = dfn[u]) > (v = dfn[v])) swap(u, v);//选dfs序更小的
  int d = __lg(v - u++);//级数，u赋值为其儿子
  return get(mi[d][u], mi[d][v - (1 << d) + 1]);
}
//树状数组 
int lowbit(int i)
{
    return i&(-i);    
} 
void add(int x,int y)
{
    for(int i = x;i<=n;i+=lowbit(i))
    {
        c[i]+=y;
    }
}
int getsum(int x)
{
    int sum = 0;
    for(int i = x;i>0;i-=lowbit(i))
    {
        sum+=c[i];
    }
    return sum;
}
//并查集 
int find(int x){
	if(f[x]==x) return x;
	return f[x]=find(f[x]);
}
void merge(int x,int y){
	int u=find(x),v=find(y);
	if(u!=v) f[v]=u;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);
	cin>>n>>m;
	fa[1]=1;
	for(int i=2;i<=n;i++){
		int x;cin>>x;
		fa[i]=x;
		e[x].push_back(i);
	}
	for(int i=1;i<=n;i++) f[i]=i;
	dfs(1,0);
	//st表预处理,求lca 
	for(int i = 1; i <= __lg(n); i++)
    for(int j = 1; j + (1 << i) - 1 <= n; j++)
      mi[i][j] = get(mi[i - 1][j], mi[i - 1][j + (1 << i - 1)]);
    //对前缀和差分 
	for(int i=1;i<=n;i++){
      	add(i,s[i]-s[i-1]);
	}
	for(int i=1;i<=m;i++){
		int op,u,v;cin>>op>>u>>v;
		if(op==1){
			while(find(u)!=find(v)){
				if(dep[f[u]]<dep[f[v]]) swap(u,v);
				add(dfn[f[u]],-1);
				add(out[f[u]]+1,1);			
				merge(f[fa[f[u]]],f[u]);
				find(u);
				u=f[u];
			}			
		}
		else if(op==2){
			cout<<getsum(dfn[u])+getsum(dfn[v])-getsum(dfn[lca(u,v)])*2+1<<endl;
		}
	}
}


