class Solution:
    def new21Game(self, n: int, k: int, maxPts: int) -> float:
        if k == 0 or k - 1 + maxPts <= n:
            return 1.0
        if n < k:
            return 0.0

        dp = [0.0] * (n + 1)
        for i in range(k, n + 1):
            dp[i] = 1.0

        # window = sum(dp[k .. min(n, k+maxPts-1)])
        right0 = min(n, k + maxPts - 1)
        window = sum(dp[k: right0 + 1])

        for i in range(k - 1, -1, -1):
            dp[i] = window / maxPts
            # slide window for next i-1: add dp[i], remove dp[i+maxPts] if in range
            window += dp[i]
            if i + maxPts <= n:
                window -= dp[i + maxPts]

        return dp[0]