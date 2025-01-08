Approach : Segment Tree

Time Complexity: 
Build: O(n) 
Query: O(logn) per query Total for q queries: O(n+qlogn) 
Overall: O(n+qlogn)

Space Complexity: 
Segment tree storage: O(4n) ~ O(n)

  
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
        ll leftChild = 2*node+1;
        ll rightChild = 2*node+2;
        
        buildSegmentTree(segmentTree, arr, leftChild, low, mid);
        buildSegmentTree(segmentTree, arr, rightChild, mid+1, high);
        
        segmentTree[node] = min(segmentTree[leftChild], segmentTree[rightChild]);
    }
}

ll querySegmentTree(vector<ll> &tree, ll node, ll start, ll end, ll l, ll r)
{
    if(r<start || l>end)
    {
        return INT_MAX;
    }
    if(l<=start && end<=r)
    {
        return tree[node];
    }
    
    ll mid = (start + end)/2;
    ll leftChild = 2*node + 1;
    ll rightChild = 2*node + 2;
    
    ll leftMin = querySegmentTree(tree, leftChild, start, mid, l, r);
    ll rightMin = querySegmentTree(tree, rightChild, mid+1, end, l, r);
    
    return min(leftMin, rightMin);
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
         a--;
         b--; //0-based indexing
         cout<<querySegmentTree(segmentTree, 0, 0, n-1, a, b)<<endl;
    }
    return 0;
}
