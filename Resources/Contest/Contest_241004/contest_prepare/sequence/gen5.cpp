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
const ll Shu=3,Id[]={5,6,7};

ll n,a[N];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll random(ll l,ll r){return rng()%(r-l+1)+l;}
const ll Maxn=200000,Maxv=100;

int main(){
		
	for(ll i_=0;i_<Shu;i_++){
		char name[25];sprintf(name,"sequence%lld.in",Id[i_]);
		freopen(name,"w",stdout);
		
		n=random(Maxn-100,Maxn);
		
		for(ll i=1;i<=n;i++)a[i]=random(1,Maxv);
		
		printf("%lld\n",n);
		for(ll i=1;i<=n;i++)printf("%lld ",a[i]);putchar('\n');
		
	}
	
	return 0;
}/*







*/
