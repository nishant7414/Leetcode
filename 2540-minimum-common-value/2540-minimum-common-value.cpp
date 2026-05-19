class Solution {
public:
    int getCommon(vector<int>& nums1, vector<int>& nums2) {
        for(int x:nums1){
            auto it = lower_bound(nums2.begin(),nums2.end(),x);
            if(it!=nums2.end() &&  *it==x)return x;
        }
        return -1;
    }
};