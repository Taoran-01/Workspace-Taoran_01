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
#define N 500010
using namespace std;
const ll Shu=1,Id[]={4};
const char Prob[50]="ex_cow";
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll random(ll l,ll r){return rng()%(r-l+1)+l;}

struct node{
	ll x,y;
}a[N];
ll q,cnt,c[N];

map<ll,ll> e;
ll tot=0;
vector <ll> b[N];
ll cmp(ll a,ll b){return a>b;}
int main(){
	for(ll i_=0;i_<Shu;i_++){
		char name[25];sprintf(name,"%s%lld.in",Prob,Id[i_]);
		freopen(name,"w",stdout);
		
		for(ll i=1;i<=tot;i++)b[i].clear();
		cnt=0;tot=0;
		q=random(100000-100,100000);
		printf("%lld\n",q);
		while(q){
			ll siz=random(1e7,1e9);
			ll pos=random(1,1e14-siz);
			ll shu=random(60,100);
			ll shuq=random(900,1100);
			shuq=min(shuq,q);
			q-=shuq;
			for(ll i=1;i<=shu;i++)c[i]=random(1,siz)+pos;
			while(shuq--){
				ll x=c[random(1,shu)],y=random(1,siz/10);
				a[++cnt]=(node){x,y};
			}
		}
		shuffle(a+1,a+cnt+1,rng);
		for(ll i=1;i<=cnt;i++){
			ll x=a[i].x;if(!e[x])e[x]=++tot;
			b[e[x]].push_back(a[i].y);
		}
		for(ll i=1;i<=tot;i++)sort(b[i].begin(),b[i].end(),cmp);
		for(ll i=1;i<=cnt;i++){
			ll x=a[i].x;
			printf("%lld %lld\n",x,b[e[x]].back());
			b[e[x]].pop_back();
		}
		
		
		
	}
	
	return 0;
}/*





*/
