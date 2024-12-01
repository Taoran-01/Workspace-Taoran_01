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
const ll Shu=4,Id[]={5,6,7,8};
const char Prob[50]="count";
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll random(ll l,ll r){return rng()%(r-l+1)+l;}
const ll Mk[10]={2,2,3,3};

map <pair<ll,ll> ,ll> c;
ll T,n,m,t,cnt;
struct node{
	ll x,y;
}a[N];

void gen_single(){
	ll x,y;
	while(1){
		x=random(1,n);y=random(1,m);
		if(c.find(make_pair(x,y))==c.end()){
			c[make_pair(x,y)]=1;t--;
			a[++cnt]=(node){x,y};
			return ;
		}
	}
}
int main(){
	for(ll i_=0;i_<Shu;i_++){
		char name[25];sprintf(name,"%s%lld.in",Prob,Id[i_]);
		freopen(name,"w",stdout);
		T=10;printf("%lld\n",T);
		for(ll _t=1;_t<=T;_t++){
			n=random(16,20);
			m=random(16,20);
			t=random(200,n*m-10);
			printf("%lld %lld %lld %lld\n",n,m,Mk[i_],t);
			
			
			c.clear();cnt=0;
			
			while(t){
				gen_single();
			}
			shuffle(a+1,a+cnt+1,rng);
			for(ll i=1;i<=cnt;i++)printf("%lld %lld\n",a[i].x,a[i].y);
			
			
		}
		
		
	}
	
	return 0;
}/*







*/
