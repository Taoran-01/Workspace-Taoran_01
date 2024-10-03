const db alpha=0.7123456789;
ll n,m,lastans=0,ans=0;
ll root,tot=0,a[N],cnt[N],s[N],sz[N],sd[N],lc[N],rc[N],q[N],hh;
void refresh(ll x){
	s[x]=s[lc[x]]+s[rc[x]]+1;
	sz[x]=sz[lc[x]]+sz[rc[x]]+cnt[x];
	sd[x]=sd[lc[x]]+sd[rc[x]]+(cnt[x]>=1);
}
void spread(ll x){if(!x)return ;spread(lc[x]);if(cnt[x])q[++hh]=x;spread(rc[x]);}
ll build(ll l,ll r){
	if(l>r)return 0;
	if(l==r){lc[q[l]]=rc[q[l]]=0;refresh(q[l]);return q[l];}
	ll mid=(l+r)>>1;
	lc[q[mid]]=build(l,mid-1);rc[q[mid]]=build(mid+1,r);
	refresh(q[mid]);
	return q[mid];
}
void rebuild(ll &x){hh=0;spread(x);x=build(1,hh);}
ll bad(ll x){return sz[x]&&(alpha*s[x]<=max(s[lc[x]],s[rc[x]])||sd[x]<=alpha*s[x]);}
void insert(ll &x,ll k){
	if(!x){x=++tot;a[x]=k;cnt[x]=1;refresh(x);return ;}
	if(k==a[x])cnt[x]++;
	else if(k<a[x])insert(lc[x],k);
	else insert(rc[x],k);
	refresh(x);
	if(bad(x))rebuild(x);
}
void del(ll &x,ll k){
	if(k==a[x])cnt[x]--;
	else if(k<a[x])del(lc[x],k);
	else del(rc[x],k);
	refresh(x);
	if(bad(x))rebuild(x);
}
ll rnk(ll x,ll k){
	if(!x)return 1;
	if(a[x]==k)return sz[lc[x]]+1;
	if(k<a[x])return rnk(lc[x],k);
	return sz[lc[x]]+cnt[x]+rnk(rc[x],k);
}
ll kth(ll x,ll k){
	if(!x)return -1;
	if(sz[lc[x]]<k&&k<=sz[lc[x]]+cnt[x])return a[x];
	if(k<=sz[lc[x]])return kth(lc[x],k);
	return kth(rc[x],k-sz[lc[x]]-cnt[x]);
}
ll pre(ll k){return kth(root,rnk(root,k)-1);}
ll suf(ll k){return kth(root,rnk(root,k+1));}