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
const ll Shu=6,Id[]={3,4,9,10,17,18};
const char Prob[50]="count";
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll random(ll l,ll r){return rng()%(r-l+1)+l;}

const ll Maxn[15]={20,20,1000,1000,_Max,_Max};
const ll Mk[15]={2,3,2,3,2,3};

map <ll,ll> c;
ll T,n,m,t;


int main(){
	for(ll i_=0;i_<Shu;i_++){
		char name[25];sprintf(name,"%s%lld.in",Prob,Id[i_]);
		freopen(name,"w",stdout);
		T=10;printf("%lld\n",T);
		for(ll _t=1;_t<=T;_t++){
			if(Maxn[i_]<=20)n=random(Maxn[i_]-4,Maxn[i_]);
			else if(Maxn[i_]<=1000)n=random(Maxn[i_]-100,Maxn[i_]);
			else n=random(Maxn[i_]/2,Maxn[i_]);
			
			if(Maxn[i_]<=20)m=random(Maxn[i_]-4,Maxn[i_]);
			else if(Maxn[i_]<=1000)m=random(Maxn[i_]-100,Maxn[i_]);
			else m=random(Maxn[i_]/2,Maxn[i_]);
			
			t=0;
			printf("%lld %lld %lld %lld\n",n,m,Mk[i_],t);
			
			
			
		}
		
		
	}
	
	return 0;
}/*







*/
