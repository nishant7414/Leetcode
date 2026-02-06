class Solution {
public:
    
    int solve(vector<int>&prices, int day, int transactionsLeft, vector<vector<int>> &Memo){
        
        if(day == prices.size()){
            return 0;
        }
        
        if(transactionsLeft == 0){
            return 0;
        }
        
        int &ans = Memo[day][transactionsLeft]; 
        
        if(ans != -1){ // if problem has already been solved 
            return ans;
        }
        
        // choice 1
        // no transaction today
        int ans1 = solve(prices, day + 1, transactionsLeft, Memo);
        
        
        // choice 2
        // doing the possible transaction today     
        int ans2 = 0;
        bool buy = (transactionsLeft % 2 == 0);
        
        if(buy == true){ // buy
            ans2 = -prices[day] + solve(prices, day + 1, transactionsLeft - 1, Memo);
        }else{ // sell
            ans2 = prices[day] + solve(prices, day + 1, transactionsLeft - 1, Memo);
        }
        
        return ans = max(ans1, ans2); // store ans in memo before returning
        
        
    }
    
    
    int maxProfit(vector<int>& prices) {
        
        vector<vector<int>> Memo(prices.size(), vector<int>(5, -1));
        int ans = solve(prices, 0, 4, Memo);
        return ans;
        
    }
};