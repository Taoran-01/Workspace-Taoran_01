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
#define N 5000010
using namespace std;
const ll Shu=1,Id[]={4};
const char Prob[50]="ex_insert";
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll random(ll l,ll r){return rng()%(r-l+1)+l;}

ll n,m,A,a[N];


const ll Maxn=5000000,Maxv=_Max;

int main(){
	for(ll i_=0;i_<Shu;i_++){
		char name[25];sprintf(name,"%s%lld.in",Prob,Id[i_]);
		freopen(name,"w",stdout);
		
		n=random(Maxn-1000,Maxn);
		m=random(n/3,(n*2)/3);
		for(ll i=1;i<=n+1;i++)a[i]=random(1,Maxv);
		sort(a+1,a+n+1+1);A=a[1];
		shuffle(a+2,a+n+1+1,rng);
		
		printf("%lld %lld %lld\n",n,m,A);
		for(ll i=2;i<=n+1;i++)printf("%lld ",a[i]);putchar('\n');
		
		
		
	}
	
	return 0;
}/*







*/
