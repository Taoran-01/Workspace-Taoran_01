#include<bits/stdc++.h>
#include"testlib.h" 
using namespace std;
int a[505][505];
int main(int argc,char*argv[]){
	registerTestlibCmd(argc,argv);
	cin.tie(0)->sync_with_stdio(0);
	int n=inf.readInt(),x=ouf.readInt();
	if(x<1||x>500)quitf(_wa,"x is out of range");
	for(int i=1;i<x;i++)
		for(int j=i+1;j<=x;j++){
			int t=ouf.readInt();
			if(t!=0&&t!=1)quitf(_wa,"The element in upper triangular adjacency matrix is not in {0,1}.");
			a[i][j]=a[j][i]=t;
		}
	int cnt=0;
	for(int i=1;i<x;i++)
		for(int j=i+1;j<x;j++)
			for(int k=j+1;k<=x;k++)
				cnt+=(a[i][j]&&a[i][k]&&a[j][k]);
	if(cnt!=n)quitf(_wa,"Wrong Answer.%d vaild triads found but %d expected.",cnt,n);
	quitf(_ok,"ok");
	return 0;
}
