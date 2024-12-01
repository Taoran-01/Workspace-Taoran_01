#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector> 
#include <random>
#include <chrono>
#include <map> 
#define ll long long
#define _Max 1000000000
#define N 2000010
using namespace std;
const ll Shu=3,Id[]={9,10,11};
const char Prob[50]="tree";
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll random(ll l,ll r){return rng()%(r-l+1)+l;}

vector <ll> b[N];
map <pair<ll,ll> ,ll>b2;
const ll Maxn=200000;
ll T,n,m,b1[N][2],tot,c[N],cnt=0,dfn[N],s[N],root,tot1,p[N],a[N],fa[N],q[N],cnt1,g[N],cnt2,id[N],p1[N];

void add_edge(ll u,ll v){
	b[u].push_back(v);
	b[v].push_back(u);
	tot++;b1[tot][0]=u;b1[tot][1]=v;
	b2[make_pair(u,v)]=b2[make_pair(v,u)]=1;
}
void dfs(ll x,ll faa){
	s[x]=1;fa[x]=faa;
	dfn[x]=++tot1;id[tot1]=x;
	for(ll v:b[x])if(v!=faa){
		dfs(v,x);
		s[x]+=s[v];
	}
}



int main(){
	for(ll i_=0;i_<Shu;i_++){
		char name[25];sprintf(name,"%s%lld.in",Prob,Id[i_]);
		freopen(name,"w",stdout);
		
		T=3;
		printf("%lld\n",T);
		while(T--){
			n=random(Maxn-1000,Maxn);
			m=random(n*8/5-10000,n*8/5-100);
			for(ll i=1;i<=n;i++)b[i].clear();
			tot=0;b2.clear();
			
			for(ll i=2;i<=n;i++)add_edge(1,i);
			for(ll i=3;i<=m-n+1+2;i++)add_edge(2,i);
			
			
			
			for(ll i=1;i<=n;i++)p[i]=i;
			for(ll i=1;i<=m;i++)p1[i]=i;
			shuffle(p1+1,p1+n,rng);
			shuffle(p1+n,p1+m+1,rng);
			shuffle(p+1,p+n+1,rng);
			printf("%lld %lld\n",n,m);
			for(ll i=1;i<=m;i++)printf("%lld %lld\n",p[b1[p1[i]][0]],p[b1[p1[i]][1]]);
			
		}
		
		
		
		
	}
//	system("tree.exe < tree19.in > tree19.ans");
	return 0;
}/*




*/