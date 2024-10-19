#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector> 
#include <random>
#include <chrono>
#define ll long long
#define N 500010
using namespace std;
const ll Shu=5,Id[]={12,13,14,15,16};
const char Prob[50]="machine";
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll random(ll l,ll r){return rng()%(r-l+1)+l;}

struct node{
	ll l,r;
}a1[N],a2[N],a3[N];
ll cnt1=0,cnt2=0,cnt3=0;
ll n,q,m;
ll b[N],a[N],c[N];
const ll B=10000000;
const ll Maxn=50000,Maxq=50000;

bool check(){
	for(ll i=1;i<=cnt1;i++){
		ll l=a1[i].l,r=a1[i].r;
		if(a[r]-a[l-1])return 0;
	}
	for(ll i=1;i<=cnt2;i++){
		ll l=a2[i].l,r=a2[i].r;
		if(!(a[r]-a[l-1]))return 0;
	}
	return 1;
}
int main(){
	for(ll i_=0;i_<Shu;i_++){
		char name[25];sprintf(name,"%s%lld.in",Prob,Id[i_]);
		freopen(name,"w",stdout);
		
		while(1){
			n=random(Maxn-100,Maxn);q=random(Maxq-100,Maxq);
			m=50;while(1){
				for(ll i=1;i<=m;i++)b[i]=random(1,n);
				sort(b+1,b+m+1);
				ll fl=1;for(ll i=1;i<m;i++)if(b[i+1]-b[i]<=1)fl=0;
				if(fl)break;
			}
			b[m+1]=n+1;
			for(ll i=1;i<=n;i++)a[i]=0;for(ll i=1;i<=m;i++)a[b[i]]=1;
			for(ll i=1;i<=n;i++)a[i]+=a[i-1];
			cnt1=random(q/3,(q*2)/3);
			for(ll i=1;i<=cnt1;i++){
				ll id=random(1,m+1);
				ll l=b[id-1]+1,r=b[id]-1;
				if(random(0,1)){
					ll L,R;
					if(random(0,1)){L=l;R=random(l,r);}
					else {L=random(l,r);R=r;}
					a1[i]=(node){L,R};
				}
				else {
					ll L=random(l,r),R=random(l,r);
					if(L>R)swap(L,R);
					a1[i]=(node){L,R};
				}
			}
			cnt2=random((q-cnt1)/3,2*(q-cnt1)/3);
			for(ll i=1;i<=cnt2;i++){
				if(!random(0,3)){
					ll x1,x2;
					x1=random(1,m);x2=x1+1;
					ll l1=b[x1-1]+1,r1=b[x1]-1,l2=b[x2-1]+1,r2=b[x2]-1;
					ll L=random(l1,r1),R=random(l2,r2);
					a2[i]=(node){L,R};
				}
				else {
					ll x1,x2;
					while(1){
						x1=random(1,m);x2=random(2,m+1);
						if(x1<x2)break;
					}
					ll l1=b[x1-1]+1,r1=b[x1]-1,l2=b[x2-1]+1,r2=b[x2]-1;
					ll L=random(l1,r1),R=random(l2,r2);
					a2[i]=(node){L,R};
				}
				
			}
			cnt3=q-cnt1-cnt2;
			for(ll i=1;i<=cnt3;i++){
				if(random(0,1))a3[i].l=b[random(1,m)];
				else a3[i].l=random(1,n);
			}
			
			if(!check()){
				cerr<<"error\n";
				continue;
			}
			else {
				printf("%lld %lld\n",n,q);
				for(ll i=1;i<=cnt1;i++)c[i]=i;
				for(ll i=1;i<=cnt2;i++)c[i+cnt1]=i+B;
				for(ll i=1;i<=cnt3;i++)c[i+cnt1+cnt2]=i+B+B;
				shuffle(c+1,c+q+1,rng);
				for(ll i=1;i<=q;i++){
					ll x=c[i];
					if(x<B){
						printf("0 %lld %lld 0\n",a1[x].l,a1[x].r);
					}
					else if(B<x&&x<2*B){
						x-=B;
						printf("0 %lld %lld 1\n",a2[x].l,a2[x].r);
					}
					else {
						x-=2*B;
						printf("1 %lld\n",a3[x].l);
					}
				}
				break;
			}
			
			
		}
	}
	
	return 0;
}/*







*/
