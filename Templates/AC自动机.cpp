#include <cmath>
#include <ctime>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

char buf[1<<20], *p1, *p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)

inline ll read() {
	ll x=0, f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}

/*
输入一个匹配串s和m个模式串t，询问每个t出现过的次数。
*/

void getstr(char* s, int &len) {
	for (int pt=1; s[pt]; ++pt) s[pt]=0;
	char ch=getchar(); len=0;
	while (ch<'a'||ch>'z') ch=getchar();
	while (ch>='a'&&ch<='z') s[++len]=ch, ch=getchar();
}

#define N 8000010
#define c s[i]-'a'
#define v trie[u].son[i]
#define Fail trie[u].fail
int m, len, cnt;
int vis[N], rev[N], indeg[N];
char s[N];
queue<int> q;

struct trie_node {
	int son[30], fail, exist, ans;
} trie[N];

void insert(int num) {
	int u=1;
	for (int i=0; i<len; ++i) {
		if (!trie[u].son[c]) trie[u].son[c]=++cnt;
		u=trie[u].son[c];
	}
	if (!trie[u].exist) trie[u].exist=num;
	rev[num]=trie[u].exist;
	return;
}

void getfail() {
	for (int i=0; i<26; ++i) trie[0].son[i]=1;
	q.push(1), trie[1].fail=0;
	while (!q.empty()) {
		int u=q.front(); q.pop();
		for (int i=0; i<26; ++i) {
			if (!v) {v=trie[Fail].son[i]; continue;}
			trie[v].fail=trie[Fail].son[i];
			++indeg[trie[Fail].son[i]];
			q.push(v);
		}
	}
}

void topo() {
	for (int i=1; i<=cnt; ++i) {
		if (!indeg[i]) q.push(i);
	}
	while (!q.empty()) {
		int u=q.front(); q.pop();
		vis[trie[u].exist]=trie[u].ans;
		trie[Fail].ans+=trie[u].ans;
		if (!(--indeg[Fail])) q.push(Fail);
	}
}

void query() {
	int u=1;
	for (int i=0; i<len; ++i) {
		u=trie[u].son[c], ++trie[u].ans;
	}
}

int main() {
	m=read(), cnt=1;
	for (int i=1; i<=m; ++i) getstr(s-1, len), insert(i);
	getfail(), getstr(s-1, len), query(), topo();
	for (int i=1; i<=m; ++i) printf("%d\n", vis[rev[i]]);
	return 0;
}
