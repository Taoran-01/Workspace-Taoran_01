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
const ll Shu=2,Id[]={19,20};
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
			m=random(n*8/5-1000,n*8/5);
			for(ll i=1;i<=n;i++)b[i].clear();
			tot=0;b2.clear();
			
			ll shu=n;cnt=0;
			while(shu){
				ll x;
				if(shu<100)x=shu;
				else x=random(1,(shu)/10);
				
				a[++cnt]=random(shu-x+1,shu);
				for(ll i=shu-x+1;i<shu;i++)add_edge(i,i+1);
				shu-=x;
			}
			
			for(ll i=2;i<=cnt;i++)add_edge(a[i],a[random(1,i-1)]);
			
			root=random(1,n);
			tot1=0;
			dfs(root,0);
			
			ll pos;
			while(1){
				pos=random(1,n);if(pos==root)continue;
				ll sum=n-s[pos];
				cnt1=0;q[++cnt1]=pos;while(fa[q[cnt1]]!=root){
					q[cnt1+1]=fa[q[cnt1]];
					cnt1++;sum+=n-s[q[cnt1]];
				}
				if(sum<(m-n+1)*2)continue;
				break;
			}
			
			for(ll t=n;t<=m;t++){
				ll x,y;
				while(1){
					x=q[random(1,cnt1)];
					y=random(1,n-s[x]);
					if(y<=dfn[x]-1)y=id[y];
					else {
						y-=(dfn[x]-1);
						y=id[dfn[x]+s[x]+y-1];
					}
					if(x==y)continue;
					if(b2[make_pair(x,y)])continue;
					add_edge(x,y);break;
				}
			}
			
			
			
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
