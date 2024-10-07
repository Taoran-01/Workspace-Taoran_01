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
#define N 50010
using namespace std;
const ll Shu=1,Id[]={3};
const char Prob[50]="ex_bracket";
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll random(ll l,ll r){return rng()%(r-l+1)+l;}


ll T,n,a[N],cnt=0;


void gen(ll n){
	printf("%lld\n",n);
	for(ll i=1;i<=n;i++)putchar('(');
	putchar('\n');
}

int main(){
	for(ll i_=0;i_<Shu;i_++){
		char name[25];sprintf(name,"%s%lld.in",Prob,Id[i_]);
		freopen(name,"w",stdout);
		
		ll maxn=2000000,sumn=20000000;
		
		cnt=0;
		for(ll t=1;t<=100;t++){
			n=random(1,500);
			a[++cnt]=n;sumn-=n;
		}
		while(sumn>maxn){
			n=random(maxn-1000,maxn);
			a[++cnt]=n;sumn-=n;
		}
		a[++cnt]=sumn;
		shuffle(a+1,a+cnt+1,rng);
		
		printf("%lld\n",cnt);
		for(ll i=1;i<=cnt;i++)gen(a[i]);
		
		
		
		
	}
	
	return 0;
}/*


const ll Maxn[20]={500,500,5000,5000,5000,200000,200000,200000,200000,200000,2000000,2000000,2000000,2000000};
const ll Maxsumn[20]={2000,2000,20000,20000,20000,1000000,1000000,1000000,1000000,1000000,20000000,20000000,20000000,20000000};





*/
