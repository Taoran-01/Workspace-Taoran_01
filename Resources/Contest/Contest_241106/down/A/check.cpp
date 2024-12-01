#include "testlib.h"

using namespace std;

vector<int> primes;

void calc(int n) {
    vector<bool> used(n + 1);
    for (long long i = 2; i <= n; i++) {
        if (!used[i]) {
            primes.push_back((int)i);
            for (long long j = i * i; j <= n; j += i) {
                used[j] = true;
            }
        }
    }
}

const int MAX_N = 1'000'000;

void check(InStream& in, int n, const vector<int>& a) {
    auto v = in.readInts(n, 1, 2, "ans");

    vector<bool> A(MAX_N + 1), B(MAX_N + 1);

    for (int i = 0; i < n; i++) {
        if (v[i] == 1) {
            A[a[i]] = true;
        } else {
            B[a[i]] = true;
        }
    }

    for (int i = 0; i <= MAX_N; i++) {
        if (A[i]) {
            for (auto j : primes) {
                if (i * j > MAX_N) {
                    break;
                }
                if (A[i * j]) {
                    in.quitf(_wa, "Invalid pair of integers: %d and %d", i, i * j);
                }
            }
        }

        if (B[i]) {
            for (auto j : primes) {
                if (i * j > MAX_N) {
                    break;
                }
                if (B[i * j]) {
                    in.quitf(_wa, "Invalid pair of integers: %d and %d", i, i * j);
                }
            }
        }
    }
}


int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    auto a = inf.readInts(n);

    calc(MAX_N);

    check(ouf, n, a);
    check(ans, n, a);

    quitf(_ok, "OK");
    return 0;
}
