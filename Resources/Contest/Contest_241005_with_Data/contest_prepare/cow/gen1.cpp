#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector> 
#include <random>
#include <chrono>
#define ll long long
#define _Max 1000000000
#define N 500010
using namespace std;
const ll Shu=11,Id[]={1,2,12,13,14,15,16,17,18,19,20};
const char Prob[50]="cow";
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll random(ll l,ll r){return rng()%(r-l+1)+l;}

const ll Maxq[15]={5000,5000,100000,100000,100000,100000,100000,100000,300000,300000,300000};
struct node{
	ll x,y;
}a[N];
ll q,cnt,c[N];

int main(){
	for(ll i_=0;i_<Shu;i_++){
		char name[25];sprintf(name,"%s%lld.in",Prob,Id[i_]);
		freopen(name,"w",stdout);
		
		cnt=0;
		q=random(Maxq[i_]-100,Maxq[i_]);
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
		for(ll i=1;i<=cnt;i++)printf("%lld %lld\n",a[i].x,a[i].y);
		
		
		
		
		
	}
	
	return 0;
}/*





*/
