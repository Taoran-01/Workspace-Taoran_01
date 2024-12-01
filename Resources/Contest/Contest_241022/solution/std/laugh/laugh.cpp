#include<bits/stdc++.h>
using namespace std;
namespace gza{
	#define int long long
	#define pb push_back
	#define MT int TTT=R;while(TTT--)
	#define pc putchar
	#define R read()
	#define fo(i,a,b) for(int i=a;i<=b;i++)
	#define rep(i,a,b) for(int i=a;i>=b;i--)
	#define m1(a,b) memset(a,b,sizeof a)
	namespace IO
	{
		inline int read()
		{
		    int x=0;
		    char ch=getchar();
		    bool f=0;
		    while(!isdigit(ch)){if(ch=='-') f=1;ch=getchar();}
		    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
		    if(f) x=-x;
		    return x;    
		}
		template<typename T> inline void write(T x)
		{
		    if(x<0) pc('-'),x=-x;
		    if(x>9) write(x/10);
		    pc(x%10+'0');
		}
	};
	namespace math
	{
		inline int gcd(int a,int b)
		{
			int az=__builtin_ctz(a),bz=__builtin_ctz(b),z=(az>bz)?bz:az,t;
		    b>>=bz;
		    while(a) a>>=az,t=a-b,b=a,az=__builtin_ctz(t<0?-t:t),a=t<0?-t:t;
		    return b<<z;
		}
		inline int qmi(int a,int b,int p)
		{
			int res=1;
			while(b)
			{
				if(b&1) res=res*a%p;
				a=a*a%p;
				b>>=1;
			}
			return res;
		}
		const int MAXN=2e6+10;
		int my_fac[MAXN],my_inv[MAXN];
		void init_binom(int mod)
		{
			my_fac[0]=1;fo(i,1,min(MAXN,mod)-1) my_fac[i]=my_fac[i-1]*i%mod;
			my_inv[min(MAXN,mod)-1]=qmi(my_fac[min(MAXN,mod)-1],mod-2,mod);rep(i,min(MAXN,mod)-2,0) my_inv[i]=my_inv[i+1]*(i+1)%mod;
		}
		int binom(int a,int b,int mod)
		{
			return my_fac[a]*my_inv[b]%mod*my_inv[a-b]%mod;
		}
	};
	using namespace IO;
	using namespace math;
	
	const int N=310,mod=998244353;
	int m,a1,q;
	int a[N],b[N];
	int d[N][N];
	void main(){
		freopen("laugh.in","r",stdin);
		freopen("laugh.out","w",stdout);
		init_binom(mod);
		m=R,a1=R,q=R;
		fo(i,0,m) a[i]=R;
		fo(j,0,m)
		{
			fo(i,j,m) d[j+1][i+1]=q*(((i-j)%2!=0)?mod-binom(i,j,mod):binom(i,j,mod))%mod;
			(d[j+1][j+1]+=mod-1)%=mod;
			d[j+1][m+2]=a[j];
		}
		int n=m+1;
		fo(i,1,n)
		{
			if(!d[i][i])
			{
				int maxi=0;
				for(int j=i+1;j<=n&&!maxi;j++) if(d[j][i]) maxi=j;
				if(!maxi) continue;
				fo(j,i,n+1) swap(d[i][j],d[maxi][j]);
			}
			fo(j,i+1,n)
			{
				int tmp=d[j][i];	
				if(tmp)
				{
					fo(k,i,n+1)
						d[j][k]=(d[j][k]*d[i][i]%mod-d[i][k]*tmp%mod+mod)%mod;
				}
			}
		}
		rep(i,n,1)
		{
			fo(j,i+1,n) d[i][n+1]=(d[i][n+1]-b[j]*d[i][j]%mod+mod)%mod;
			b[i]=d[i][n+1]*qmi(d[i][i],mod-2,mod)%mod;
		}
		int sum=0;
		fo(i,1,n) (sum+=b[i])%=mod;
		write((a1+sum)%mod*qmi(q,mod-2,mod)%mod),puts("");
		fo(i,1,n) write((mod-b[i])%mod),pc(' ');
	}
}
signed main(){
	
	gza::main();
}
