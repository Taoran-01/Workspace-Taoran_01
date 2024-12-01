#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#define ll long long
#define N 2000010
using namespace std;
int read(){
	char cc;
	while(1){cc=getchar();if((cc>='0'&&cc<='9')||cc=='-')break;}
	int sum=0,flag=1;
	cc=='-'?flag=-1:sum=(cc^48);
	while(1){cc=getchar();if(!(cc>='0'&&cc<='9'))break;sum=(sum<<1)+(sum<<3)+(cc^48);}
	return sum*flag;
}
vector <int> b[N],c[N];
int n,m,a[N],s[N],dfn[N],cnt,e[N][2],tot,fa[N],q[N],hh,d[N];
void add(int l,int r,int w){a[l]+=w;a[r+1]-=w;}
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void dfs(int x,int faa){
	dfn[x]=++cnt;
	for(int v:b[x])if(v!=faa){
		d[v]=d[x]+1;dfs(v,x);
		s[x]+=s[v];
	}
}
int askfa(int x,int y){return dfn[x]<=dfn[y]&&dfn[y]<=dfn[x]+s[x]-1;}
void dfs2(int x,int faa){
	q[++hh]=x;for(int dep:c[x])add(dfn[q[dep]],dfn[q[dep]]+s[q[dep]]-1,-1);
	for(int v:b[x])if(v!=faa)dfs2(v,x);hh--;
}
int main(){
	int T=read();while(T--){
	n=read();m=read();cnt=tot=0;
	for(int i=1;i<=n;i++){b[i].clear();c[i].clear();fa[i]=i;a[i]=0;s[i]=1;}
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		int fx=find(u),fy=find(v);
		if(fx!=fy){
			fa[fx]=fy;
			b[u].push_back(v);
			b[v].push_back(u);
		}
		else {tot++;e[tot][0]=u;e[tot][1]=v;}
	}
	d[1]=1;dfs(1,0);
	for(int i=1;i<=tot;i++){
		int x=e[i][0],y=e[i][1];
		if(askfa(x,y)){add(dfn[y],dfn[y]+s[y]-1,1);c[y].push_back(d[x]+1);a[1]++;}
		else if(askfa(y,x)){add(dfn[x],dfn[x]+s[x]-1,1);c[x].push_back(d[y]+1);a[1]++;}
		else {add(dfn[x],dfn[x]+s[x]-1,1);add(dfn[y],dfn[y]+s[y]-1,1);}
	}
	hh=0;dfs2(1,0);
	for(int i=1;i<=n;i++)a[i]+=a[i-1];
	for(int i=1;i<=n;i++)putchar((a[dfn[i]]==tot)+'0');putchar('\n');
	}return 0;
}
