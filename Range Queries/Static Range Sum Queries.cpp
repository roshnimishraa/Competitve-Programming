Queries: Each query asks, What is the sum of numbers from index a to index b?

#include <iostream>
#include <vector>
using namespace std;
#define ll long long

int main() {
    ll n, q;
    cin >> n >> q; 

    vector<ll> arr(n + 1, 0); 
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

   vector<ll> prefixSum(n+1,0);
   for(int i=1;i<=n;i++)
   {
       prefixSum[i] = prefixSum[i-1]+arr[i];
   }
    while (q--) {
        ll a, b;
        cin >> a >> b; 
   ll ans = prefixSum[b] - prefixSum[a-1];
        cout << ans << endl;
    }

    return 0;
}


Approach 2: Segment Tree

Time Complexity:
Build: O(n) (each element contributes to O(logn) operations, summing up to O(n))
Query: O(logn) per query, as the tree height is logn.
    
Space Complexity: O(4n)
    
#include<iostream>
using namespace std;
#include<bits/stdc++.h>
#define ll long long
 
void buildSegmentTree(vector<ll> &segmentTree, vector<ll> &arr, ll node, ll low, ll high)
{
    if(low == high)
    {
        segmentTree[node] = arr[low];
    }
    else{
        ll mid = (low + high)/2;
        ll leftChild = 2*node + 1;
        ll rightChild = 2*node + 2;
        
        buildSegmentTree(segmentTree, arr, leftChild, low, mid);
        buildSegmentTree(segmentTree, arr, rightChild, mid+1, high);
        
        segmentTree[node] = segmentTree[leftChild] + segmentTree[rightChild];
        
    }
}
 
ll querySegment(vector<ll> &tree, ll node, ll start, ll end, ll l, ll r)
{
 if(r < start || l>end)
 {
     return 0;
 }
 
 if(l<=start && end<=r)
 {
     return tree[node];
 }
 
   ll mid = (start + end)/2;
   ll leftChild = 2*node + 1;
   ll rightChild = 2*node + 2;
   
   ll leftSum = querySegment(tree, leftChild, start, mid, l, r);
   ll rightSum = querySegment(tree, rightChild, mid+1, end, l, r);
        
return leftSum + rightSum;
}
 
int main()
{
    ll n,q;
    cin>>n>>q;
    vector<ll> arr(n);
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    vector<ll> segmentTree(4*n);
    buildSegmentTree(segmentTree, arr, 0, 0, n-1);
    
    while(q--)
    {
        ll a,b;
        cin>>a>>b;
        a--;  // Convert to 0-based indexing
        b--;
        
    cout<<querySegment(segmentTree, 0, 0, n-1, a, b)<<endl;
    }
    return 0;
}

