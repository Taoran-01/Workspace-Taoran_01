#include <bits/stdc++.h>
using namespace std;

int ccost(int i, int j, int k){
    int d = abs(i-j);
    return k?d:1;
}

int main(){
    freopen ("go.in","r",stdin);
	freopen ("go.out","w",stdout);
    int T;
    cin >> T;
    while(T--){
        string s; int k;
        cin >> k >> s;
        int l = s.length();
        int b = count(s.begin(), s.end(), 'B');
        int w = l - b;
        long long cost1 = 0, cost2 = 0;
        queue<int> q;
        char qtype = 0;
        if(abs(b-w) > 1) { cout << "-1" << endl; continue; }
        if(b >= w){ // BWBW...
            for(int i = 0; i < l; i++){
                if(i%2){ // except W
                    if(s[i] == 'B') {
                        if(qtype == 'W'){
                            int x = q.front();
                            q.pop();
                            cost1 += ccost(i, x, k);
                            if(q.empty()) qtype = 0;
                        }
                        else {
                            q.push(i);
                            qtype = 'B';
                        }
                    }
                } else { // except B
                    if(s[i] == 'W') {
                        if(qtype == 'B'){
                            int x = q.front();
                            q.pop();
                            cost1 += ccost(i, x, k);
                            if(q.empty()) qtype = 0;
                        }
                        else {
                            q.push(i);
                            qtype = 'W';
                        }
                    }
                }
            }
        }
        else cost1 = INT_MAX;

        if(w >= b){ // WBWB...
            for(int i = 0; i < l; i++){
                if(i%2 == 0){ // except W
                    if(s[i] == 'B') {
                        if(qtype == 'W'){
                            int x = q.front();
                            q.pop();
                            cost2 += ccost(i, x, k);
                            if(q.empty()) qtype = 0;
                        }
                        else {
                            q.push(i);
                            qtype = 'B';
                        }
                    }
                } else { // except B
                    if(s[i] == 'W') {
                        if(qtype == 'B'){
                            int x = q.front();
                            q.pop();
                            cost2 += ccost(i, x, k);
                            if(q.empty()) qtype = 0;
                        }
                        else {
                            q.push(i);
                            qtype = 'W';
                        }
                    }
                }
            }
        }
        else cost2 = INT_MAX;
        cout << min(cost1, cost2) << endl;
    }
}
