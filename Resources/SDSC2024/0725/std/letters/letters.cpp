#include<algorithm>
#include<cstring>
#include<cstdio>
#define ll long long
const ll mod=1e9+7;
const int M=2e6;
#define qwq M+7
inline void Mod(ll &x){
    if(x>=mod)x-=mod;
    if(x<0)x+=mod;
}
inline void update(ll &x,ll y){
    x+=y;Mod(x);
}
inline ll mpow(ll x,ll k){
    ll ans=1;
    for(;k;k=k>>1,x=x*x%mod){
        if(k&1)ans=ans*x%mod;
    }
    return ans;
}
ll fac[qwq],invfac[qwq];
ll p2[qwq],pk[qwq];
ll inv[qwq];
const int nM=2000;
ll Ak[nM<<1|7][nM+7];
ll Ck[nM<<1|7][nM+7];
int k;
inline void init(){
    fac[0]=1;
    p2[0]=1;pk[0]=1;
    for(int i=1;i<=M;++i){
        p2[i]=p2[i-1]<<1;Mod(p2[i]);
        pk[i]=pk[i-1]*k%mod;
        fac[i]=fac[i-1]*i%mod;
    }
    invfac[M]=mpow(fac[M],mod-2);
    for(int i=M-1;i>=0;--i){
        invfac[i]=invfac[i+1]*(i+1)%mod;
    }
    for(int i=1;i<=M;++i){
        inv[i]=invfac[i]*fac[i-1]%mod;
    }
    for(int i=0;i<=(nM<<1);++i){
        Ak[i][0]=1;
    }
    for(int j=1;j<=nM;++j){
        for(int i=0;i<=(nM<<1);++i){
            Ak[i][j]=Ak[i][j-1]*(k-i-j+1)%mod;
        }
    }
    for(int i=0;i<=(nM<<1);++i){
        for(int j=0;j<=nM;++j){
            Ck[i][j]=Ak[i][j]*invfac[j]%mod;
        }
    }
    return ;
}

inline ll A(int n,int m){
    if(m>n)return 0;
    if(n<0||m<0)return 0;
    if(n<=M){
        return fac[n]*invfac[n-m]%mod;
    }
    else {
        printf("?????\n");
        exit(0);
        return 0;
    }
    // ll ans=1;
    // for(int i=0;i<m;++i){
    //     ans=ans*(n-i)%mod;
    // }
    // return ans;
}
inline ll C(int n,int m){
    if(n<0||m<0)return 0;
    return A(n,m)*invfac[m]%mod;
}
ll ans;
int n,m;
inline void calc(ll cnt,int len){
    ll w=0;
    ll t=1;
    for(int j=m;j<=n;j+=m-len,t=-t){
        update(w,1ll*t*(n-j+1)%mod*pk[n-j]%mod);
        if(len==0)break;
    }
    ans=(ans+cnt*w)%mod;
}
inline ll f(int dk,int m){
    ll F=0;
    for(int i=0;i<=(m>>1);++i){
        ll sum=Ck[dk][i]*Ck[dk+i][m-(i<<1)]%mod*fac[m]%mod*mpow(p2[i],mod-2)%mod;
        update(F,sum);
    }
    return F;
}
int main(){
    freopen("letters.in","r",stdin);
    freopen("letters.out","w",stdout);
    scanf("%d%d%d",&n,&m,&k);
    init();
    ll cntall=f(0,m);
    // printf("ans:%lld\n",cntall);
    for(int len=1;len<=(m>>1);++len){
        ll wans=Ck[0][len]*f(len,m-(len<<1))%mod;
        wans=wans*fac[len]%mod;
        cntall+=mod-wans;Mod(cntall);
        calc(wans,len);
    }
    // printf("now ans:%lld\n",cntall);
    calc(cntall,0);
    printf("%lld\n",ans);
    return 0;
}