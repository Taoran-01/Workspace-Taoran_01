#include<bits/stdc++.h>
const int sz=1e6+10;
const int lgsz=std::__lg(sz)+1;
std::basic_string<int>graph[sz];
int f[sz][lgsz],dep[sz];
void dfs(int u,int fau){
    dep[u]=dep[fau]+1,f[u][0]=fau;
    for(int i=1;i<=std::__lg(dep[u]);i++)f[u][i]=f[f[u][i-1]][i-1];
    for(int v:graph[u]){
        if(v==fau)continue;
        dfs(v,u);
    }
}
int lca(int u,int v){
    if(dep[u]<dep[v])std::swap(u,v);
    while(dep[u]>dep[v])u=f[u][std::__lg(dep[u]-dep[v])];
    if(u==v)return u;
    for(int i=std::__lg(dep[u]);i>=0;i--)
        if(f[u][i]!=f[v][i])u=f[u][i],v=f[v][i];
    return f[u][0];
}
int main(){
	freopen("zom.in","r",stdin);
	freopen("zom.out","w",stdout);
	std::ios::sync_with_stdio(0),std::cin.tie(0);
    int n,q;
    std::cin>>n>>q;
    for(int i=1,u,v;i<n;i++)std::cin>>u>>v,graph[u]+=v,graph[v]+=u;
    dfs(1,0);
    while(q--){
        int op,u,v;
        std::cin>>op>>u>>v;
        if(op==2)std::cout<<lca(u,v)<<"\n";
        else{
            dep[u]=dep[v]+1,f[u][0]=v;
            for(int i=1;i<=std::__lg(dep[u]);i++)f[u][i]=f[f[u][i-1]][i-1];
        }
    }
    return 0;
}
