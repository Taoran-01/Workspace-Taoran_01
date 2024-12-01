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
const ll Shu=7,Id[]={19,20,21,22,23,24,25};
const char Prob[50]="count";
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll random(ll l,ll r){return rng()%(r-l+1)+l;}
const ll Lk[10]={2,2,2,3,3,3,2};
const ll Rk[10]={2,2,2,3,3,3,3};

map <pair<ll,ll> ,ll> c;
ll T,n,m,t,cnt;
struct node{
	ll x,y;
}a[N];

void gen_single(){
	ll x,y;
	while(1){
		if(random(0,1)){
			y=random(1,m);
			if(random(0,1))x=1;else x=n;
		}
		else {
			x=random(1,n);
			if(random(0,1))y=1;else y=m;
		}
		if(c.find(make_pair(x,y))==c.end()){
			c[make_pair(x,y)]=1;t--;
			a[++cnt]=(node){x,y};
			return ;
		}
	}
}
void gen_square(){
	ll n1=random(1,n-20);
	ll m1=random(1,m-20);
	ll n_=random(15,20);
	ll m_=random(15,20);
	ll k=random(10,min(t,n_*m_-10));
	while(k--){
		ll x,y,sum=0;
		while(1){
			x=n1+random(0,n_-1);
			y=m1+random(0,m_-1);
			if(c.find(make_pair(x,y))==c.end()){
				c[make_pair(x,y)]=1;t--;
				a[++cnt]=(node){x,y};
				break;
			}
		}
		sum++;if(sum>20)return ;
	}
}
int main(){
	for(ll i_=0;i_<Shu;i_++){
		char name[25];sprintf(name,"%s%lld.in",Prob,Id[i_]);
		freopen(name,"w",stdout);
		T=10;printf("%lld\n",T);
		for(ll _t=1;_t<=T;_t++){
			n=random(600000000,1000000000);
			m=random(600000000,1000000000);
			t=random(15000,20000);
			printf("%lld %lld %lld %lld\n",n,m,random(Lk[i_],Rk[i_]),t);
			
			
			c.clear();cnt=0;
			
			while(t){
				if(t>=20){
					if(random(0,10))gen_square();
					else gen_single();
				}
				else gen_single();
			}
			shuffle(a+1,a+cnt+1,rng);
			for(ll i=1;i<=cnt;i++)printf("%lld %lld\n",a[i].x,a[i].y);
			
			
		}
		
		
	}
	
	return 0;
}/*







*/
