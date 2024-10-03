#include<bits/stdc++.h>
using namespace std;
inline long long read(){
	long long res=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')res=res*10+ch-48,ch=getchar();
	return res*f;
}
const int N=1e5+6;
long long ans;
long long t,n,m,val[N],dis[N],dis1[N],s,p,qq;
vector<int>e[N],E[N];
vector<int>w[N],W[N];
struct card{
	long long c,d;
}ca[N];
struct node{
	long long dis,pos;
	bool operator < (const node & a) const{
		return a.dis<dis;
	}
};
int ad[N];
void adde(int u,int v,long long l){
	e[u].push_back(v);
	w[u].push_back(l);
}
void adde1(int u,int v,long long l){
	E[v].push_back(u);
	W[v].push_back(l);
}
bool cmp(card a,card b){
	return a.d>b.d;
}
int vis[N];
void dij(int s){
	priority_queue<node>q;
	for (int i=1;i<=n;++i) dis[i]=1e17;
	q.push((node){0,s});
	dis[s]=0;
	while (!q.empty()){
		node tmp=q.top();
		q.pop();
		long long x=tmp.dis,d=tmp.pos;
		if (vis[d]) continue;
		vis[d]=1;
		for (int i=0;i<e[d].size();++i){
			int v=e[d][i];
			if (dis[v]>dis[d]+w[d][i]){
				dis[v]=dis[d]+w[d][i];
				if (!vis[v]){
					q.push((node){dis[v],v});
				}
			}
		}
	}
}
void dij1(){
	priority_queue<node>q;
	for (int i=1;i<=n;++i) dis1[i]=1e17,vis[i]=0;
	for (int i=1;i<=qq;++i){
		q.push((node){0,ad[i]});
		dis1[ad[i]]=0;
	}
	while (!q.empty()){
		node tmp=q.top();
		q.pop();
		long long x=tmp.dis,d=tmp.pos;
		if (vis[d]) continue;
		vis[d]=1;
		for (int i=0;i<E[d].size();++i){
			int v=E[d][i];
			if (dis1[v]>dis1[d]+W[d][i]){
				dis1[v]=dis1[d]+W[d][i];
				if (!vis[v]){
					q.push((node){dis1[v],v});
				}
			}
		}
	}
}
bool cmp1(long long a,long long b){
	return a>b;
}
priority_queue<long long,vector<long long>,greater<long long>> q;
int main(){
	n=read(),m=read();
	for (int i=1;i<=m;++i){
		long long u,v,l;
		u=read(),v=read(),l=read();
		adde(u,v,l);
		adde1(u,v,l);
	}
	t=read();
	for (int i=1;i<=t;++i){
		val[i]=read();
	}
	sort(val+1,val+1+n,cmp1);
	s=read(),p=read(),qq=read();
	for (int i=1;i<=p;++i){
		ca[i].c=read(),ca[i].d=read();
	}
	sort(ca+1,ca+p+1,cmp);
	for (int i=1;i<=qq;++i){
		ad[i]=read();
	}
	dij(s);
	dij1();
	int top=1,flg=0;
	for (int i=1;i<=p;++i){
		int v=ca[i].c;
		if (ca[i].d>=val[top]){
			q.push(dis[v]+dis1[v]);
		}
		else if(!q.empty()){
			ans+=q.top();
			q.pop();
			++top;
			--i;
			++flg;
			if (flg==t) break;
		}
	}
	while (flg!=t){
		ans+=q.top();
		++flg;
		q.pop();
	}
	cout<<ans;
	return 0;
}
