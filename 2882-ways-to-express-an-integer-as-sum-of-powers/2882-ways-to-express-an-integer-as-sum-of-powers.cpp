int const M = 1e9+7;
class Solution {
private:    
    vector<vector<int>> memo = vector(301, vector<int> (301, -1));
    int func(int n, int sum, int x, int num){
        if(sum == n){return 1;}
        int tmp=pow(num, x);

        if(sum + tmp > n){return 0;}

        if(memo[num][sum] != -1){return memo[num][sum];} // added

        int take = func(n, sum + tmp, x, num+1);
        int notTake = func(n, sum, x, num+1);

        return memo[num][sum] = (take+notTake)%M; // updated
    }    
public:
    int numberOfWays(int n, int x) {
        return func(n,0,x,1);
    }
};