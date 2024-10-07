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


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll random(ll l,ll r){return rng()%(r-l+1)+l;}
	

ll q;

int main(){
	q=50000;
	printf("%lld\n",q);
	while(q--){
		ll x,y;
		x=random(1,10000);
		y=random(1,_Max);
		printf("%lld %lld\n",x,y);
	}
	
	
	
	
	
	return 0;
}/*



*/
