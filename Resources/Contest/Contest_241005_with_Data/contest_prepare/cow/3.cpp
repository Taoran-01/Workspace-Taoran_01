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
	



int main(){
	for(ll t=1;;t++){
		system("2.exe > data.in");
		system("1.exe < data.in > ans.out");
		system("cow.exe < data.in > data.out");
		if(system("fc data.out ans.out"))return 0;
		printf("Ac %lld\n",t);
	}
	
	
	
	return 0;
}/*



*/
