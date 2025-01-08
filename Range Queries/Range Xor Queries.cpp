Approach: Segment Tree

Complexity:
Time Complexity:
Build Segment Tree: O(n)
Query Operation: O(logn) per query
Total for q queries: O(n+qlogn)

Space Complexity:
Segment Tree Storage: O(4n)
Total Space: O(n)

#include <iostream>
#include <vector>
using namespace std;
 
// Function to build the segment tree
void buildSegmentTree(vector<long long>& tree, vector<int>& arr, int node, int start, int end) {
    if (start == end) {
        // Leaf node
        tree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        int leftChild = 2 * node + 1;
        int rightChild = 2 * node + 2;
 
        // Build the left and right children
        buildSegmentTree(tree, arr, leftChild, start, mid);
        buildSegmentTree(tree, arr, rightChild, mid + 1, end);
 
        // Internal node stores the XOR of its children
        tree[node] = tree[leftChild] ^ tree[rightChild];
    }
}
 
// Function to query the XOR sum in range [l, r]
long long querySegmentTree(vector<long long>& tree, int node, int start, int end, int l, int r) {
    if (r < start || l > end) {
        // Completely outside the range, return 0 (neutral element for XOR)
        return 0;
    }
 
    if (l <= start && end <= r) {
        // Completely inside the range
        return tree[node];
    }
 
    // Partially inside and partially outside
    int mid = (start + end) / 2;
    int leftChild = 2 * node + 1;
    int rightChild = 2 * node + 2;
 
    long long leftXOR = querySegmentTree(tree, leftChild, start, mid, l, r);
    long long rightXOR = querySegmentTree(tree, rightChild, mid + 1, end, l, r);
 
    return leftXOR ^ rightXOR;
}
 
int main() {
    int n, q;
    cin >> n >> q;
 
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
 
  
    vector<long long> segmentTree(4 * n);
 
 
    buildSegmentTree(segmentTree, arr, 0, 0, n - 1);
 
    
    while (q--) {
        int a, b;
        cin >> a >> b;
 
        a--; // Convert to 0-based indexing
        b--;
 
        cout << querySegmentTree(segmentTree, 0, 0, n - 1, a, b) << endl;
    }
 
    return 0;
}
