class Solution {
public:
    int countOperations(int num1, int num2) {
        long long a = num1, b = num2;
        int ops = 0;
        while (a > 0 && b > 0){
            if (a < b) std::swap(a, b);
            ops += a / b;
            a %= b;
        }
         return ops;
    }
};