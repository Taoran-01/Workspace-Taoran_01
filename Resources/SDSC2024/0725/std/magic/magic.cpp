#include<algorithm>
#include<cstring>
#include<cstdio>
#define ll long long
#define qwq 1000007
const int inf=320051113;
inline int read(){
    char c=getchar();
    int x=0;
    for(;c<'0'||c>'9';c=getchar());
    for(;c<='9'&&c>='0';c=getchar())x=(x<<1)+(x<<3)+c-'0';
    return x;
}
int n,m,k;
struct Work{
    int x,y;
}w[qwq];
int dp[qwq];
int main(){
    freopen("magic.in","r",stdin);
    freopen("magic.out","w",stdout);
    // scanf("%d%d%d",&n,&m,&k);
    n=read(),m=read(),k=read();
    for(int i=1;i<=m;++i){
        // scanf("%d%d",&w[i].x,&w[i].y);
        w[i].x=read(),w[i].y=read();
    }
    for(int i=1;i<=n;++i)dp[i]=inf;
    dp[k]=0;
    for(int i=1;i<=m;++i){
        int a=std::min(dp[w[i].x],dp[w[i].y])+1;
        std::swap(dp[w[i].x],dp[w[i].y]);
        dp[w[i].x]=std::min(dp[w[i].x],a);
        dp[w[i].y]=std::min(dp[w[i].y],a);
    }
    for(int i=1;i<=n;++i){
        if(dp[i]==inf)printf("%d ",-1);
        else printf("%d ",dp[i]);
    }
    putchar('\n');
    return 0;
}