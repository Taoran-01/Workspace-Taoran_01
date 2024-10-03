#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define lll __int128
map <lll,int> ma;
const int N=(1<<20)+5,M=105;
int a[22];
int nxt[60005][10],cnt=0;
ll dp[60005][M];
bool cmp(int a,int b){
	return a>b;
}
vector <int> divide(lll tmp){
	vector <int> now;now.clear();
	while (tmp) now.emplace_back(tmp%10),tmp/=10;
	return now;
}
char n[22];
int main(){
	freopen ("fnt.in","r",stdin);
	freopen ("fnt.out","w",stdout);
	int m,l=0;
	//ll n;
	scanf ("%s",n+1);
	l=strlen(n+1);
	scanf ("%d",&m);
	for (int i=1;i<=l;i++) a[i]=n[i]-'0';
	ma[0]=++cnt;
	for (int s=0;s<(1<<l);s++){
		vector <int> now;now.clear();
		for (int i=1;i<=l;i++)
			if (s&(1<<(i-1))) now.emplace_back(a[i]);
		sort(now.begin(),now.end(),cmp);
		lll tmp=0;
		for (int i=0;i<now.size();i++)
			tmp=tmp*10+now[i];
		if (!ma[tmp]) ma[tmp]=++cnt;
	}
	map <lll,int> :: iterator it;
	for (it=ma.begin();it!=ma.end();it++){
		lll now=(*it).first;
		for (int j=0;j<=9;j++){
			vector <int> to=divide(now);
			to.emplace_back(j);
			sort(to.begin(),to.end(),cmp);
			lll tmp=0;
			for (int i=0;i<to.size();i++)
				tmp=tmp*10+to[i];
			if (ma.find(tmp)!=ma.end())
				nxt[(*it).second][j]=ma[tmp];
		}
	}
	dp[1][0]=1;
	for (int i=1;i<=cnt;i++)
		for (int s=0;s<m;s++)
			for (int j=(i==1);j<=9;j++)
				if (nxt[i][j]) dp[nxt[i][j]][(s*10+j)%m]+=dp[i][s];
	ll ans=(m==1?dp[cnt][0]:0);
	for (int s=1;s<m;s++)
		if (__gcd(s,m)==1) ans+=dp[cnt][s];
	printf ("%lld",ans);
	return 0;
}

