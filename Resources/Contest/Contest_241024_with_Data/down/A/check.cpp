#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;

inline int readAndCheckAnswer(InStream &in, int m,
                              const vector<string> &plane) {
  int n = plane.size();
  vector<string> ans(n);
  ans[0] = in.readLine("Impossible|[.X]{6}", "row[1]");
  if (ans[0] == "Impossible") {
    return -1;
  }
  for (int i = 1; i < n; i++)
    ans[i] = in.readLine("[.X]{6}", "row[" + to_string(i + 1) + "]");

  int diff = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 6; j++) {
        if (plane[i][j] == '.' && ans[i][j] == 'X')
            diff++;
        if (plane[i][j] == 'X' && ans[i][j] == '.')
            in.quitf(_wa, "Remove original passenger %d in %d row", j + 1, i + 1);
        if (ans[i][j] != ans[i][5 - j])
            in.quitf(_wa, "Non symetric place %d in %d row", j + 1, i + 1);
    }
  }
  if (diff != m)
    in.quitf(_wa, "Added passengers number is not equal to m");

  return 1;
}

int main(int argc, char *argv[]) {
  registerTestlibCmd(argc, argv);

  int n = inf.readInt(1, MAXN, "n");
  inf.readSpace();
  int m = inf.readInt(0, 6 * MAXN, "m");
  inf.readEoln();
  vector<string> plane(n);
  for (int i = 0; i < n; i++)
    plane[i] = inf.readLine("[.X]{6}", "row[" + to_string(i + 1) + "]");

  int jans = readAndCheckAnswer(ans, m, plane);
  int pans = readAndCheckAnswer(ouf, m, plane);

  if (jans == pans)
    quitf(_ok, "n=%d, m=%d", n, m);
  else if (jans == -1)
    quitf(_fail, "Participant found answer, but jury not");
  else
    quitf(_wa, "Jury found answer, but participant not");
}
