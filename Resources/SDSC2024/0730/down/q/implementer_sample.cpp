#include"q.h"
#include<stdio.h>

static int a[1000002];

bool Q(const int i,const int j,const int k){ return (a[i]-a[j])%k==0; }
bool C(const int i,const int j){ static int cnt=0; if(cnt) printf("o bro you have used too many C\n"); return cnt++,a[i]<a[j]; }

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    printf("Yours: %d\n",solve(n));
    for(int i=1;i<=n;i++) if(a[i]==1) printf("Real : %d\n");
    return 0;
}