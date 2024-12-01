ll a[N],cnt[N],ch[N][2],s[N],fa[N],tot=0,root,n,m,lastans=0,ans=0;
void refresh(ll x){	s[x]=s[ch[x][0]]+s[ch[x][1]]+cnt[x];}
ll getch(ll x){return ch[fa[x]][1]==x;}
void rotate(ll x){
	ll y=fa[x],z=fa[y];
	ll k=getch(x);
	fa[ch[x][k^1]]=y;ch[y][k]=ch[x][k^1];
	fa[y]=x;ch[x][k^1]=y;
	fa[x]=z;ch[z][ch[z][1]==y]=x;
	refresh(y);refresh(x);
}
void splay(ll x){
	for(ll y=fa[x];y;rotate(x),y=fa[x])if(fa[y])getch(x)==getch(y)?rotate(y):rotate(x);
	root=x;
}
void find(ll x){
	ll p=root;
	while(a[p]!=x&&ch[p][x>a[p]])p=ch[p][x>a[p]];
	splay(p);
}
ll newnode(ll w,ll faa){
	ll x=++tot;
	fa[x]=faa;a[x]=w;
	cnt[x]=s[x]=1;
	return x;
}
void insert(ll k){
	ll p=root,faa=0;
	while(p&&a[p]!=k)faa=p,p=ch[p][k>a[p]];
	if(!p){
		p=newnode(k,faa);
		ch[faa][k>a[faa]]=p;
	}
	else cnt[p]++;
	splay(p);
}
void del(ll k){
	find(k);
	if(a[root]!=k)return ;
	cnt[root]--;s[root]--;
}
ll rnk(ll k){
	insert(k);
	ll w=s[ch[root][0]]+1;
	del(k);
	return w;
}
ll kth(ll k){
	ll p=root;
	while(1){
		if(s[ch[p][0]]<k&&k<=s[ch[p][0]]+cnt[p]){splay(p);return a[p];}
		if(k<=s[ch[p][0]])p=ch[p][0];
		else {k-=s[ch[p][0]]+cnt[p];p=ch[p][1];}
	} 
}
ll pre(ll x){return kth(rnk(x)-1);}
ll suf(ll x){return kth(rnk(x+1));}