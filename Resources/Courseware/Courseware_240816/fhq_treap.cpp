mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll random(ll l,ll r){return rng()%(r-l+1)+l;}
int n,m,root=0,ls[N],rs[N],rd[N],a[N],s[N],cnt=0,last_ans=0,ans=0;
void refresh(int x){s[x]=s[ls[x]]+s[rs[x]]+1;}
int newnode(int v){
    int x=++cnt;
    s[x]=1;rd[x]=random(-1e9,1e9);a[x]=v;
    return x;
}
void spl(int p,int v,int &x,int &y){
    if(!p){x=y=0;return ;}
    if(a[p]<=v)spl(rs[p],v,rs[x=p],y);
    else spl(ls[p],v,x,ls[y=p]);
    refresh(p);
}
int merge(int x,int y){
    if(!x||!y)return x|y;
    if(rd[x]<rd[y])return rs[x]=merge(rs[x],y),refresh(x),x;
    return ls[y]=merge(x,ls[y]),refresh(y),y;
}
void insert(int v){
    int x=0,y=0;
    spl(root,v,x,y);root=merge(merge(x,newnode(v)),y);
}
void del(int v){
    int x=0,y=0,z=0;
    spl(root,v-1,x,y);spl(y,v,y,z);
    root=merge(merge(x,merge(ls[y],rs[y])),z);
}
int kth(int k){
    int p=root;
    while(1){
        if(k<=s[ls[p]])p=ls[p];
        else if(k==s[ls[p]]+1)return a[p];
        else k-=s[ls[p]]+1,p=rs[p];
    }
}
int rnk(int v){
    int x=0,y=0,ans;
    spl(root,v-1,x,y);ans=s[x]+1;
    return root=merge(x,y),ans;
}
int pre(int x){return kth(rnk(x)-1);}
int suc(int x){return kth(rnk(x+1));}