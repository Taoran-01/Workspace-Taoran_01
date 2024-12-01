#include <bits/stdc++.h>

#define int long long

#define maxn 200005

#define INF LONG_LONG_MAX

using namespace std;

int n,q,K;

int ls[maxn],rs[maxn];

int f[maxn];

int a[maxn];

int mx[maxn],mi[maxn];

void update(int now){
	
	mx[now] = max(mx[now],a[now]);
	
	mi[now] = min(mi[now],a[now]);
	
	if(ls[now]){
		
		update(ls[now]);
		
		mx[now] = max(mx[now],mx[ls[now]]);
		
		mi[now] = min(mi[now],mi[ls[now]]);
		
	}
	
	if(rs[now]){
		
		update(rs[now]);
		
		mx[now] = max(mx[now],mx[rs[now]]);
		
		mi[now] = min(mi[now],mi[rs[now]]);
		
	}
	
}

int get_ans(int now){
	
	int ans = 0;
	
	if(((!ls[now]) || a[now] >= mx[ls[now]]) && ((!rs[now]) || a[now] <= mi[rs[now]])) ++ ans;
	
	if(ls[now]) ans += get_ans(ls[now]);
	
	if(rs[now]) ans += get_ans(rs[now]);
	
	return ans;
	
}

signed main(){
	
	ios::sync_with_stdio(0);
	
	cin.tie(0);
	
	cout.tie(0);
	
	cin >> n >> q >> K;
	
	for(int i = 1;i <= n;++ i){
		
		cin >> ls[i] >> rs[i];
		
		f[ls[i]] = f[rs[i]] = i;
		
	}
	
	for(int i = 1;i <= n;++ i){
		
		cin >> a[i];
		
		mx[i] = 0,mi[i] = INF;
		
	}
	
	if(n * q <= 30000000){
		
		update(1);
		
		while(q --){
			
			int pd,x;
			
			cin >> pd >> x;
			
			if(pd == 1){
				
				for(int i = 1;i <= n;++ i) mx[i] = 0,mi[i] = INF;
				
				int y;
				
				cin >> y;
				
				a[x] = y;
				
				update(1);
				
			} else {
				
				cout << get_ans(x) << "\n";
				
			}
			
		}
		
	}
	
	return 0;
	
}
/*
  6 5 0
  2 3
  4 0
  5 6
  0 0
  0 0
  0 0
  4 1 3 2 2 5
  2 2
  1 3 3
  1 2 2
  1 3 5
  2 1
 */
