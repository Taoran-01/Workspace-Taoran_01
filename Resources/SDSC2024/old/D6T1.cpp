
// Ctrl+Alt+N
// by my friend iPhoneSX

// 这是一道交互题，QYC出的

#include"q.h"
#include<stdio.h>
using namespace std;
bool check(int x,int n){
	for(int i=2;i<=n;i++){
		if(Q(1,i,x)==1){
			return 1;
		}
	}
	return 0;
}
int solve(int n){
	if(n==1){
		return 1;
	}
	else if(n==2){
		if(C(1,2)==1){
			return 1;
		}
		else{
			return 2;
		}
	}
	else{
		int l=1,r=n-1;
		while(l<r){
			int mid=(l+r+1)/2;
			if(check(mid,n)){
				l=mid;
			}
			else{
				r=mid-1;
			}
		}
		int pos=0,op=0;
		for(int i=2;i<=n;i++){
			if(Q(1,i,l)){
				pos=i;
				break;
			}
		}
		for(int i=1;i<=n;i++){
			if(Q(pos,i,n-1)){
				op=i;
				break;
			}
		}
		if(C(pos,op)==1){
			return pos;
		}
		else{
			return op;
		}
	}
}


