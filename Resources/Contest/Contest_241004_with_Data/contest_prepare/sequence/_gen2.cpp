#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector> 
#include <random>
#include <chrono>
#define ll long long
#define N 2000010
using namespace std;
const ll Shu=1,Id[]={3};

ll n,a[N];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll random(ll l,ll r){return rng()%(r-l+1)+l;}
const ll Maxn=2000000,Maxv=1000000000;

int main(){
		
	for(ll i_=0;i_<Shu;i_++){
		char name[25];sprintf(name,"ex_sequence%lld.in",Id[i_]);
		freopen(name,"w",stdout);
		
		n=random(Maxn-100,Maxn);
		
		for(ll i=1;i<=n;i++)a[i]=random(1,Maxv);
		shuffle(a+1,a+n+1,rng);
		
		printf("%lld\n",n);
		for(ll i=1;i<=n;i++)printf("%lld ",a[i]);putchar('\n');
		
	}
	
	return 0;
}/*







*/
