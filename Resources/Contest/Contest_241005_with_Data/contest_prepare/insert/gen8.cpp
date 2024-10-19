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
const ll Shu=1,Id[]={12};
const char Prob[50]="insert";
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll random(ll l,ll r){return rng()%(r-l+1)+l;}

ll n,m,A,a[N];


const ll Maxn=500000,Maxv=_Max;

int main(){
	for(ll i_=0;i_<Shu;i_++){
		char name[25];sprintf(name,"%s%lld.in",Prob,Id[i_]);
		freopen(name,"w",stdout);
		
		n=random(Maxn-1000,Maxn);
		m=1;
		A=random(1,Maxv);
		for(ll i=1;i<=n;i++)a[i]=random(1,Maxv);
		
		printf("%lld %lld %lld\n",n,m,A);
		for(ll i=1;i<=n;i++)printf("%lld ",a[i]);putchar('\n');
		
		
		
	}
	
	return 0;
}/*







*/
