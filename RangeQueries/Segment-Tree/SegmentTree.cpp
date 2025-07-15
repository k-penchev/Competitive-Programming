#include <iostream>
#include <vector>
using namespace std;

vector<int> segTree;

void buildSegmentTree(vector<int>& arr, int idx, int start, int end) {
    if (start == end) {
        segTree[idx] = arr[start];
    } else {
        int mid = (start + end) / 2;
        buildSegmentTree(arr, 2 * idx + 1, start, mid);
        buildSegmentTree(arr, 2 * idx + 2, mid + 1, end);
        segTree[idx] = max(segTree[2 * idx + 1] , segTree[2 * idx + 2]);
        //Minimum element: segTree[idx] = min(segTree[2 * idx + 1] , segTree[2 * idx + 2]);
        //Sum of left + right: segTree[idx] = segTree[2 * idx + 1] + segTree[2 * idx + 2];
    }
}

int querySegmentTree(int idx, int start, int end, int l, int r) {
    if (r < start || l > end) return INT_MIN; //INT_MAX
    if (l <= start && r >= end) return segTree[idx];
    int mid = (start + end) / 2;
    return max(querySegmentTree(2 * idx + 1, start, mid, l, r) , querySegmentTree(2 * idx + 2, mid + 1, end, l, r));
    //Minimum element: return min(querySegmentTree(2 * idx + 1, start, mid, l, r) , querySegmentTree(2 * idx + 2, mid + 1, end, l, r));
    //Sum of left + right: return querySegmentTree(2 * idx + 1, start, mid, l, r) + querySegmentTree(2 * idx + 2, mid + 1, end, l, r);
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    int n = arr.size();
    segTree.resize(4 * n);
    buildSegmentTree(arr, 0, 0, n - 1);

    int l = 0, r = 4; 
    cout << "Segment Tree Range Query: " << querySegmentTree(0, 0, n - 1, l, r) << endl;
    
    return 0;
}
