struct node{
	ll x,y;
	friend bool operator<(node a,node b){return a.x*b.y<b.x*a.y;}
};
node max(node a,node b){return a<b?b:a;}
struct node1{node a;ll ans;}t[N<<2];
ll n,m;
void build(ll x,ll l,ll r){
	if(l==r){t[x].a.y=l;return ;}
	ll mid=(l+r)>>1;
	build(x<<1,l,mid);build(x<<1|1,mid+1,r);
	t[x].a=max(t[x<<1].a,t[x<<1|1].a);
}
ll solve(node w,ll x,ll l,ll r){
	if(l==r)return w<t[x].a;
	if(t[x].a<w)return 0;
	ll mid=(l+r)>>1;
	if(w<t[x<<1].a)return solve(w,x<<1,l,mid)+t[x].ans-t[x<<1].ans;
	return solve(w,x<<1|1,mid+1,r);
}
void change(ll x,ll l,ll r,ll L,ll y){
	if(l==r){t[x].a.x=y;t[x].ans=1;return ;}
	ll mid=(l+r)>>1;
	if(mid>=L)change(x<<1,l,mid,L,y);
	else change(x<<1|1,mid+1,r,L,y);
	t[x].a=max(t[x<<1].a,t[x<<1|1].a);
	t[x].ans=t[x<<1].ans+solve(t[x<<1].a,x<<1|1,mid+1,r);
}