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
const int N=1e6+5;
inline int rd(){
	int ans=0,f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9')ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	re f?-ans:ans;
}
int n,K,f[21][N],la[21][21],cnt[21];
int main(){
	int Cnt=0;
	freopen("amnesia.in","r",stdin);
	freopen("amnesia.out","w",stdout);
//	freopen("amnesia7_1.in","r",stdin);
//	freopen("amnesia7_1.out","w",stdout);
//	n=rd(),K=1;
	n=rd(),K=rd();
	memset(f,0x3f,sizeof f); 
//	for(int i=0;i<=K;i++)f[i][0]=-1;
	for(int i=0;i<=K;i++)f[i][0]=0;
	for(int i=1;i<=n;i++){
		int x=rd();
		for(int j=K;j>=0;j--){
			if(x>f[j][cnt[j]]){
				f[j][++cnt[j]]=x;
				la[j][j]=cnt[j];
			}
			else{
				int l=1,r=cnt[j],mid;
				while(l<r){
//					++Cnt;
					mid=(l+r)>>1;
					if(f[j][mid]<x)l=mid+1;
					else r=mid;
				}
				ckmin(f[j][l],x);
				la[j][j]=l;
			}
			for(int x=0;x<j;x++){
				int p=la[j-1][x];
				ckmax(cnt[j],p+1);
				ckmin(f[j][p+1],f[j-1][p]+1);
				la[j][x]=p+1;
			}
		}
	}
	int ans=cnt[0];
	for(int i=1;i<=K;i++)ckmax(ans,cnt[i]);
	printf("%d\n",ans);
//	printf("Cnt:%d\n",Cnt);
	re 0;
}
/*
4 2
11 12 1 2


11 12 13 14 15 5 4 3 2 1


15
1 2 1 2 1 1 2 2 3 2 2 3 3 2 4 

5
1 2 1 2 1
*/
}int main(){re FRTMLV::main();}
