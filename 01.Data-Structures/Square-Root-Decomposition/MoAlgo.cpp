#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Query {
    int l, r, idx;
};

int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    vector<Query> queries = {{1, 3, 0}, {0, 4, 1}};
    vector<int> answer(queries.size());

    int blockSize = sqrt(arr.size());
    sort(queries.begin(), queries.end(), [&](Query a, Query b) {
        int blockA = a.l / blockSize;
        int blockB = b.l / blockSize;
        return blockA == blockB ? a.r < b.r : blockA < blockB;
    });

    int curL = 0, curR = -1, curSum = 0;
    for (auto& q : queries) {
        while (curR < q.r) curSum += arr[++curR];
        while (curR > q.r) curSum -= arr[curR--];
        while (curL < q.l) curSum -= arr[curL++];
        while (curL > q.l) curSum += arr[--curL];
        answer[q.idx] = curSum;
    }

    for (int i = 0; i < answer.size(); ++i) {
        cout << "Mo's Algorithm Query " << i + 1 << ": " << answer[i] << endl;
    }
    return 0;
}
