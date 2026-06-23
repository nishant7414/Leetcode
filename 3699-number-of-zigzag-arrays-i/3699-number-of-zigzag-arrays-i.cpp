constexpr int P=1e9+7, N=2000;
using ll=long long;
// dp[x]=count of such seqs s[i]=x where x in [0,.., m-1] with m=r-l+1
static ll dp[N]; 
class Solution {
public:
    static int zigZagArrays(int n, int l, int r) {
        const int m=r-l+1;
        fill_n(dp, m, 1);
        for(int i=1; i<n; i++){
            const bool dir=i&1;
            ll Sum=0;
            const int i0=(-dir & m-1), iN=(-!dir & m+1)-1, step=1-(dir<<1);
            for(int j=i0; j!=iN; j+=step){
                ll x=dp[j];              
                dp[j]=Sum;              
                Sum=(Sum+x)%P;
            }
        }
        return 2*reduce(dp, dp+m, 0LL)%P;
    }
};
auto init = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();