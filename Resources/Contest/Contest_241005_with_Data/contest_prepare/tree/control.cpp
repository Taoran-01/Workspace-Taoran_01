#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define ll long long
#define N 500010
using namespace std;
ll read(){
	char cc;
	while(1){cc=getchar();if((cc>='0'&&cc<='9')||cc=='-')break;}
	ll sum=0,flag=1;
	cc=='-'?flag=-1:sum=(cc^48);
	while(1){cc=getchar();if(!(cc>='0'&&cc<='9'))break;sum=(sum<<1)+(sum<<3)+(cc^48);}
	return sum*flag;
}
void write(ll x){
	if(!x)putchar('0');
	if(x<0){x=-x;putchar('-');}
	ll cc[25],cntt=0;
	while(x){cc[++cntt]=x%10;x/=10;}
	for(ll i=cntt;i>=1;i--)putchar(cc[i]+'0');
	putchar('\n');
}
const ll Shu_gen=7,Shu_test=20,Shu_sample=1;
const char Prob[20]="tree";
char name[500];
void gen(){
	printf("---generate start\n");
	for(ll i=1;i<=Shu_gen;i++){
		sprintf(name,"g++ gen%lld.cpp -o gen%lld.exe -std=c++14 -Wl,--stack=1000000000000",i,i);
		system(name);
		sprintf(name,"gen%lld.exe",i);
		system(name);
		printf("finish generate %lld\n",i);
	}
	printf("---generate end\n");
}
void run(){
	printf("---run start\n");
	sprintf(name,"g++ %s.cpp -o %s.exe -std=c++14 -Wl,--stack=1000000000000",Prob,Prob);
	system(name);
	for(ll i=1;i<=Shu_test;i++){
		sprintf(name,"%s.exe < %s%lld.in > %s%lld.ans",Prob,Prob,i,Prob,i);
		system(name);
		printf("finish solve test %lld\n",i);
	}
	printf("---run end\n");
}
void gen_sample(){
	printf("---generate sample start\n");
	for(ll i=1;i<=Shu_sample;i++){
		sprintf(name,"g++ _gen%lld.cpp -o _gen%lld.exe -std=c++14 -Wl,--stack=1000000000000",i,i);
		system(name);
		sprintf(name,"_gen%lld.exe",i);
		system(name);
		printf("finish generate %lld\n",i);
	}
	printf("---generate sample end\n");
}
void run_sample(){
	printf("---run sample start\n");
	sprintf(name,"g++ %s.cpp -o %s.exe -std=c++14 -Wl,--stack=1000000000000",Prob,Prob);
	system(name);
	for(ll i=1;i<=Shu_sample+1;i++){
		sprintf(name,"%s.exe < ex_%s%lld.in > ex_%s%lld.ans",Prob,Prob,i,Prob,i);
		system(name);
		printf("finish solve test %lld\n",i);
	}
	printf("---run sample end\n");
}
int main(){
	gen();
	run();
//	gen_sample();
//	run_sample();
	
	return 0;
}/*







*/
