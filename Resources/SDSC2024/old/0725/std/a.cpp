#include<algorithm>
#include<cstring>
#include<cstdio>
#define ll long long
#define qwq 2000007
inline int read(){
    char c=getchar();
    int x=0;
    for(;c<'0'||c>'9';c=getchar());
    for(;c<='9'&&c>='0';c=getchar())x=(x<<1)+(x<<3)+c-'0';
    return x;
}
int n,m;
struct Edge{
    int a,b;
    int v;
}e[qwq];
ll ans;
int fa[qwq],siz[qwq];
bool cmp(Edge x,Edge y){
    return x.v<y.v;
}
inline int get_fa(int x){
    if(fa[x]==x)return x;
    return fa[x]=get_fa(fa[x]);
}
inline void add_fa(int x,int y){
    x=get_fa(x),y=get_fa(y);
    if(siz[x]>siz[y])std::swap(x,y);
    fa[x]=y;siz[y]+=siz[x];
    return ;
}
int main(){
    freopen("risk.in","r",stdin);
    freopen("risk.out","w",stdout);
    n=read();m=read();
    for(int i=1;i<=m;++i){
        // scanf("%d%d%d",&e[i].a,&e[i].b,&e[i].v);
        e[i].a=read(),e[i].b=read(),e[i].v=read();
    }
    std::sort(e+1,e+m+1,cmp);
    for(int i=1;i<=n;++i)fa[i]=i,siz[i]=1;
    int count=0;
    for(int i=1;i<=m;++i){
        if(get_fa(e[i].a)!=get_fa(e[i].b))add_fa(e[i].a,e[i].b),ans+=e[i].v,++count;
    }
    printf("%lld\n",ans);
    return 0;
}