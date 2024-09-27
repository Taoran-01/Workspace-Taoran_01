#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")

#include<stdio.h>
#include<string.h>
#include<array>
using std::array;
using std::pair;

int dp[32][110592],s[32][110592];

const int P=(1<<30)-1;

inline int encode(array<char,6> lim,array<char,3> sign,array<char,3> is_max,array<char,3> b)
{
	int S=0;
	for(int i=0;i<6;i++) S=(S<<1)+lim[i];
	for(int i=0;i<3;i++) S=S*3+sign[i]+1;
	for(int i=0;i<3;i++) S=(S<<1)+is_max[i];
	for(int i=0;i<3;i++) S=(S<<1)+b[i];
	return S;
}
inline void print(array<char,6> lim,array<char,3> sign,array<char,3> is_max,array<char,3> b)
{
	for(int i=0;i<6;i++) putchar('0'+lim[i]),putchar(' ');
	putchar(',');
	for(int i=0;i<3;i++) sign[i]==-1?(putchar('-'),putchar('1')):(putchar(' '),putchar('0'+sign[i])),putchar(' ');
	putchar(',');
	for(int i=0;i<3;i++) putchar('0'+is_max[i]),putchar(' ');
	putchar(',');
	for(int i=0;i<3;i++) putchar('0'+b[i]),putchar(' ');
}
inline pair<int,int> dfs(int p,array<int,6> l,array<char,6> lim,array<char,3> sign,array<char,3> is_max,array<char,3> b)
{
	int S=encode(lim,sign,is_max,b);
	//printf("%d %d\n",p,S);
	if(dp[p][S]!=-1) return {dp[p][S],s[p][S]};
	dp[p][S]=s[p][S]=0;
	array<char,6> u;
	for(int i=0;i<6;i++) u[i]=lim[i]?(l[i]>>p&1):1;
	array<char,6> now;
	array<char,3> now_b;
	array<char,3> now_max;
	for(now[0]=0;now[0]<=u[0];now[0]++)
		for(now[1]=0;now[1]<=u[1];now[1]++)
			for(now[2]=0;now[2]<=u[2];now[2]++)
				for(now[3]=0;now[3]<=u[3];now[3]++)
					for(now[4]=0;now[4]<=u[4];now[4]++)
						for(now[5]=0;now[5]<=u[5];now[5]++)
							for(now_b[0]=0;now_b[0]<2;now_b[0]++)
								for(now_b[1]=0;now_b[1]<2;now_b[1]++)
									for(now_b[2]=0;now_b[2]<2;now_b[2]++)
									{
										array<char,3> r,now_sign=sign;
										int max_r=0;
										int flag=1;
										for(int i=0;i<3;i++)
										{
											int x=now[i],y=now[i+3],bh=b[i],bl=now_b[i];
											if(!now_sign[i]&&x!=y) now_sign[i]=x>y?1:-1;
											if(now_sign[i]==-1) x^=y^=x^=y;
											r[i]=x-y+(bh<<1)-bl;
											if(r[i]<0||r[i]>1){ flag=0;break; }
										}
										if(!flag) continue;
										for(int i=0;i<3;i++)
											if(is_max[i]&&r[i]>max_r) max_r=r[i];
										for(int i=0;i<3;i++) now_max[i]=is_max[i]&&r[i]==max_r;
										int c=(max_r^now[0]^now[1]^now[2]^now[3]^now[4]^now[5])<<p;
										array<char,6> now_lim;
										for(int i=0;i<6;i++) now_lim[i]=lim[i]&&now[i]==u[i];
										pair<int,int> f=p?dfs(p-1,l,now_lim,now_sign,now_max,now_b):pair<int,int>{!(now_b[0]||now_b[1]||now_b[2]),0};
										dp[p][S]=dp[p][S]+f.first&P,s[p][S]=s[p][S]+(long long)c*f.first+f.second&P;
									}
	return {dp[p][S],s[p][S]};
}

array<int,6> l;

int main()
{
	freopen("stars.in","r",stdin);
	freopen("stars.out","w",stdout);
	scanf("%d%d%d%d%d%d",&l[0],&l[1],&l[2],&l[3],&l[4],&l[5]);
	array<char,6> lim={1,1,1,1,1,1};
	array<char,3> sign={0,0,0},borrow={0,0,0},is_max={1,1,1};
	memset(dp,-1,sizeof(dp)),dfs(31,l,lim,sign,is_max,borrow);
	printf("%u\n",s[31][encode(lim,sign,is_max,borrow)]);
	return 0;
}