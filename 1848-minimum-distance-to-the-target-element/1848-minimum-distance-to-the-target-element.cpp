class Solution {
public:
    int getMinDistance(vector<int>& nums, int target, int start) {
        int min_dist = INT_MAX;
        for (int i = 0; i < nums.size(); i++){
            if (nums[i] == target){
                min_dist = min(min_dist, abs(i - start));
            }
        }
        return min_dist;
    }
};