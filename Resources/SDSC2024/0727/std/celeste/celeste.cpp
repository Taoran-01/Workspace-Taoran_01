/*FreeTimeLove's code.
Love has a nasty habit of disappearing over night.*/
#include<bits/stdc++.h>
namespace FRTMLV{
#define ll long long
#define LD long double
#define i7 __int128
#define re return
#define con continue
using namespace std;
template<class T>inline bool ckmin(T &a,T b){re b<a?a=b,1:0;}
template<class T>inline bool ckmax(T &a,T b){re a<b?a=b,1:0;}
const int N=1e4+5;
inline int rd(){
	int ans=0,f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9')ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	re f?-ans:ans;
}
int n,f[N][N],a[N],ans[N];
int main(){
	freopen("celeste.in","r",stdin);
	freopen("celeste.out","w",stdout);
	n=rd();
	for(int i=1;i<=n;i++)a[i]=rd();
	for(int r=1;r<=n;r++){
		f[r][r]=f[r-1][r]=1;
		int p=r-1;
		for(int l=r-2;l>0;l--){
			if((ll)(r-l)*(a[r]-a[p])>(ll)(r-p)*(a[r]-a[l]))
				f[l][r]=min(f[l+1][p],f[l+1][p-1])+f[p][r],p=l;
			else f[l][r]=min(f[l][p],f[l][p-1])+f[p][r];
			ans[r-l+1]^=f[l][r];
		}
	}
	ans[1]=n&1,ans[2]=(n&1)^1;
	for(int i=1;i<=n;i++)printf("%d ",ans[i]);
	puts("");
	re 0;
}
/*

*/
}int main(){re FRTMLV::main();}
