Approach: Segment Tree

Time Complexity:
Building the Segment Tree: O(n)
Update Operation: O(logn) per update
Range Query Operation: O(logn) per query
Total Time Complexity: O(n+qlogn)
    
Space Complexity:
Segment Tree Storage: O(4n)
Overall: O(n)

#include <iostream>
using namespace std;
#include<bits/stdc++.h>

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

        // Internal node stores the sum of its children
        tree[node] = min(tree[leftChild] , tree[rightChild]);
    }
}

// Function to update a value at position k
void updateSegmentTree(vector<long long>& tree, int node, int start, int end, int idx, int value) {
    if (start == end) {
        // Leaf node
        tree[node] = value;
    } else {
        int mid = (start + end) / 2;
        int leftChild = 2 * node + 1;
        int rightChild = 2 * node + 2;

        if (idx <= mid) {
            // Update in the left subtree
            updateSegmentTree(tree, leftChild, start, mid, idx, value);
        } else {
            // Update in the right subtree
            updateSegmentTree(tree, rightChild, mid + 1, end, idx, value);
        }

        // Recalculate the sum for the current node
        tree[node] = min(tree[leftChild] , tree[rightChild]);
    }
}

long long querySegmentTree(vector<long long>& tree, int node, int start, int end, int l, int r) {
    if (r < start || l > end) {
      
        return INT_MAX;
    }

    if (l <= start && end <= r) {
       return tree[node];
    }

   int mid = (start + end) / 2;
    int leftChild = 2 * node + 1;
    int rightChild = 2 * node + 2;

    long long leftMin = querySegmentTree(tree, leftChild, start, mid, l, r);
    long long RightMin = querySegmentTree(tree, rightChild, mid + 1, end, l, r);

    return min(leftMin, RightMin);
}

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Segment tree array (size 4*n is sufficient for storage)
    vector<long long> segmentTree(4 * n);

    // Build the segment tree
    buildSegmentTree(segmentTree, arr, 0, 0, n - 1);

    // Process queries
    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            // Update query: "1 k u"
            int k, u;
            cin >> k >> u;
            k--; // Convert to 0-based indexing
            updateSegmentTree(segmentTree, 0, 0, n - 1, k, u);
        } else if (type == 2) {
            // Range sum query: "2 a b"
            int a, b;
            cin >> a >> b;
            a--; b--; // Convert to 0-based indexing
            cout << querySegmentTree(segmentTree, 0, 0, n - 1, a, b) << endl;
        }
    }

    return 0;
}
