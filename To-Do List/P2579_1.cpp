#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define LL long long int
using namespace std;
const int maxn=55,INF=2000000000,P=10000;
inline int read(){
	int out=0,flag=1;char c=getchar();
	while(c<48||c>57) {if(c=='-') flag=-1;c=getchar();}
	while(c>=48&&c<=57){out=out*10+c-48;c=getchar();}
	return out*flag;
}
struct Matrix{
	LL s[maxn][maxn],n,m;
	Matrix() {n=m=0;memset(s,0,sizeof(s));}
}d[20],Q;
inline Matrix operator *(const Matrix& a,const Matrix& b){
	Matrix c;
	if(a.m!=b.n) return c;
	c.n=a.n;c.m=b.m;
	for(int i=1;i<=c.n;i++)
		for(int j=1;j<=c.m;j++)
			for(int k=1;k<=a.n;k++)
				c.s[i][j]=(c.s[i][j]+a.s[i][k]*b.s[k][j])%P;
	return c;
}
Matrix qpow(Matrix a,LL b){
	Matrix ans;
	ans.n=ans.m=a.n;
	for(int i=1;i<=ans.n;i++) ans.s[i][i]=1;
	for(;b;b>>=1,a=a*a) if(b&1) ans=ans*a;
	return ans;
}
int N,M,S,E,K,ban[20][maxn],G[maxn][maxn];
void init(){
	N=read();M=read();S=read()+1;E=read()+1;K=read();
	int a,b;
	while(M--){
		a=read()+1;
		b=read()+1;
		G[a][b]=G[b][a]=1;
	}
	int q=read(),rnd,u;
	while(q--){
		rnd=read();
		for(int i=0;i<rnd;i++){
			u=read()+1;
			for(int j=i;j<12;j+=rnd)
				ban[j][u]=true;
		}
	}
	Q.n=Q.m=N;
	for(int i=1;i<=N;i++) Q.s[i][i]=1;
	for(int i=0;i<12;i++){
		d[i].n=d[i].m=N;
		for(int j=1;j<=N;j++)
			for(int k=1;k<=N;k++){
				d[i].s[j][k]=(G[j][k]&&!ban[i][k]);
			}
	}
	for(int i=1;i<12;i++) Q=Q*d[i];
	Q=Q*d[0];
}
void solve(){
	int t=K-(K/12)*12;
	Matrix ans;ans.n=ans.m=N;
	for(int i=1;i<=N;i++) ans.s[i][i]=1;
	ans=ans*qpow(Q,K/12);
	for(int i=1;i<=t;i++) ans=ans*d[i];
	cout<<ans.s[S][E]<<endl;
}
int main(){
	freopen("P2579.in", "r", stdin);
	init();
	/*for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++) cout<<G[i][j]<<' ';
		cout<<endl;
	}
	for(int t=0;t<12;t++){
		cout<<endl<<endl;
		for(int i=1;i<=N;i++){
			for(int j=1;j<=N;j++) cout<<d[t].s[i][j]<<' ';
			cout<<endl;
		}
	}*/
	solve();
	return 0;
}
