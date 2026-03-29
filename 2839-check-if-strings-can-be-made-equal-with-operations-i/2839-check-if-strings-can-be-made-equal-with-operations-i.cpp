class Solution {
public:
    bool canBeEqual(string s1, string s2) {
        if(s1==s2)return true;

        //since s1 and s2 is of length=4
        //there are only 3 valid cases

        //case 1: swap index 0 & 2
        swap(s1[0], s1[2]); 
        if(s1==s2)return true; 
        swap(s1[0], s1[2]); //revert back

        //case 2: swap index 1 & 3
        swap(s1[1], s1[3]); 
        if(s1==s2)return true;

        //case 3: swap both (0&2 and 1&3)
        //1&3 is already swapped above
        swap(s1[0], s1[2]);

        return s1==s2;
    }   
};