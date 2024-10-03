#include<bits/stdc++.h>
using namespace std;

int main(){
    long long n, ans=0;
    cin >> n;
    for(int d = 0; d < 63; ++d) {
        long long D = ((1LL<<d)-1)*2 - 1;
        long long l = 1, r = n * 2, x = 0;
        while (l <= r) {
            long double mid = (l + r) / 2;
            long double tmp = mid * (mid + D);
            if (tmp == n * 2) {
                x = mid;
                break;
            }
            else if (tmp < n * 2) {
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }
        if((x&1) && x * (x+D) == n*2) {
            cout<<(ans = x*(1LL<<d))<<" ";
        }
	}
    if(ans == 0) cout<<-1;
    return 0;
}