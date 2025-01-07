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
