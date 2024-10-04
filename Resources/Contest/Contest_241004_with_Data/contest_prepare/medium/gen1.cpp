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

const char Prob[50]="medium";
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll random(ll l,ll r){return rng()%(r-l+1)+l;}

const ll Maxn[25]={0,8,13,100,1000,5000,5000,5000,50000,50000,50000,100000,100000,100000,500000,500000,500000,500000,500000,500000,500000},
Maxsumn[25]={0,100,100,1000,10000,50000,100000,100000,1000000,1000000,1000000,1000000,2000000,2000000,2000000,2000000,1400000,1600000,1800000,2000000,2000000},
Maxv[25]={0,_Max,_Max,_Max,_Max,_Max,1,_Max,_Max,1,_Max,_Max,1,_Max,_Max,_Max,_Max,_Max,_Max,1,_Max};

ll T,n,k,a[N];
ll updiv(ll n,ll m){return n/m+(n%m>0);}
int main(){
	for(ll i_=1;i_<=20;i_++){
		char name[25];sprintf(name,"%s%lld.in",Prob,i_);
		freopen(name,"w",stdout);
		
		ll sumn=Maxsumn[i_],maxn=Maxn[i_],maxv=Maxv[i_];
		T=updiv(sumn,maxn);
		printf("%lld\n",T);
		while(T--){
			n=maxn;if(n>sumn)n=sumn;
			sumn-=n;
			k=random(1,__lg(n));
			if(i_==8||i_==14)k=1;
			if(i_==15)k=random(50,n);
			printf("%lld %lld\n",n,k);
			for(ll i=1;i<=n;i++)a[i]=random(0,maxv);
			if(maxv==1)for(ll i=1;i<=n;i++)a[i]=(random(0,10)?0:1);
			for(ll i=1;i<=n;i++)printf("%lld ",a[i]);putchar('\n');
			
		}
	}
	
	return 0;
}/*







*/
