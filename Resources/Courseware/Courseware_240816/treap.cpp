mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll ch[N][2],s[N],a[N],cnt[N],fa[N],val[N],tot,root,n,m,lastans=0,ans=0,flag;
ll newnode(ll w,ll faa){
	ll x=++tot;
	a[x]=w;val[x]=rng();
	cnt[x]=s[x]=1;
	fa[x]=faa;
	return x;
}
void refresh(ll x){	s[x]=s[ch[x][0]]+s[ch[x][1]]+cnt[x];}
void rotate(ll x){
	ll y=fa[x],z=fa[y];
	if(!z)root=x;
	ll k=(ch[y][1]==x);
	fa[ch[x][k^1]]=y;ch[y][k]=ch[x][k^1];
	fa[y]=x;ch[x][k^1]=y;
	fa[x]=z;ch[z][ch[z][1]==y]=x;
	refresh(y);refresh(x); 
}
void up(ll x){while(fa[x]&&val[fa[x]]>val[x])rotate(x);}
void insert(ll x,ll k){
	if(a[x]==k)cnt[x]++;
	else if(k<a[x]){
		if(!ch[x][0])ch[x][0]=newnode(k,x);
		else insert(ch[x][0],k);
	}
	else {
		if(!ch[x][1])ch[x][1]=newnode(k,x);
		else insert(ch[x][1],k);
	}
	refresh(x);
}
void Insert(ll x){flag=tot;insert(root,x);if(flag!=tot)up(tot);}
void del(ll x,ll k){
	if(a[x]==k)cnt[x]--;
	else if(k<a[x])del(ch[x][0],k);
	else del(ch[x][1],k);
	refresh(x);
}
ll rnk(ll x,ll k){
	if(!x)return 1;
	if(a[x]==k)return s[ch[x][0]]+1;
	if(k<a[x])return rnk(ch[x][0],k);
	return s[ch[x][0]]+cnt[x]+rnk(ch[x][1],k);
}
ll kth(ll x,ll k){
	if(s[ch[x][0]]<k&&k<=s[ch[x][0]]+cnt[x])return a[x];
	if(k<=s[ch[x][0]])return kth(ch[x][0],k);
	return kth(ch[x][1],k-s[ch[x][0]]-cnt[x]);
}
ll pre(ll x){return kth(root,rnk(root,x)-1);}
ll suf(ll x){return kth(root,rnk(root,x+1));}