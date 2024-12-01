#include <iostream>
#include <vector>
#include "testlib.h"

using namespace std;

long long s;
int n, m;

const int maxn = 16;
int a[maxn][maxn];
const int maxCMatrix = 1e9;
const long long maxCS = 1e18;

int check(InStream& in) {
    string res;
    res = upperCase(in.readWord());
    if (res == "NO") {
        return 0;
    }
    if (res == "YES") {
        
    } else {
        return -1;
    }
    int k;
    k = in.readInt(0, n + m, "k");
    vector<int> cols(m, 1);
    vector<int> rows(n, 1);
    for (int i = 0; i < k; ++i) {
        int type;
        type = in.readInt(1, 2, "type");
        int id;
        if (type == 1) {
            id = in.readInt(1, n, "rowId");
        } else {
            id = in.readInt(1, m, "colId");
        }
        --id;
        if (type == 1) {
            if (rows[id] != 1) {
                return -1;
            }
            rows[id] = 0;
        } else {
            if (cols[id] != 1) {
                return -1;
            }
            cols[id] = 0;
        }
    }
    long long result = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            result += a[i][j] * rows[i] * cols[j];
        }
    }
    if (result != s) {
        return -1;
    }
    return 1;
}

int32_t main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    n = inf.readInt(1, maxn, "n");
    m = inf.readInt(1, maxn, "m");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            a[i][j] = inf.readInt(0, maxCMatrix, "a[i][j]");
        }
    }
    s = inf.readLong(0, maxCS, "s");
    int jstatus = check(ans);
    int pstatus = check(ouf);
    if (jstatus == -1) {
        ouf.quitf(_fail, "jury has a wrong answer");
    }
    if (jstatus == 0 && pstatus == 1) {
        ouf.quitf(_fail, "jury has not found the answer, but participant has");
    }
    if (jstatus == pstatus) {
        ouf.quitf(_ok, "good job!");
    }
    if (pstatus == 0) {
        ouf.quitf(_wa, "jury has found the answer, but participant has not");
    }
    ouf.quitf(_wa, "wrong sum");
}
