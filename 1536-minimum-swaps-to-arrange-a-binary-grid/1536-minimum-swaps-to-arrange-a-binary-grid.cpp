class Solution {

private:
    int getCurTrailingZeros(vector<int>&nums,const int &n){
        int zeros=0;
        for(int i=n-1;i>=0;--i){
            if(nums[i]==0){++zeros;}
            else{break;}
        }
        return zeros;
    }

public:
    int minSwaps(vector<vector<int>>& grid) {
        const int n = grid.size();
        int swaps = 0;
        for(int i=0;i<n;++i){
            bool flag=false;
            int curZeros = getCurTrailingZeros(grid[i],n);
            if(curZeros>=n-i-1){continue;}
            for(int j=i+1;j<n;++j){
                int zeros = getCurTrailingZeros(grid[j],n);
                if(zeros>=n-i-1){
                    flag=true;
                    for (int k=j; k>i;--k) {
                        ++swaps;
                        swap(grid[k], grid[k-1]);
                    }
                    break;
                }
            }
            if(!flag){return -1;}
        }
        return swaps;
    }
};