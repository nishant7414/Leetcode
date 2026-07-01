class Solution {
public:
    using u16 = uint16_t;
    using u32 = uint32_t;
    inline static constexpr u32 dx[4]{0u, -1u, 1u, 0u};
    inline static constexpr u32 dy[4]{-1u, 0u, 0u, 1u};
    inline static u32 q[400 * 400 + 1];
    inline static u16 g[401][401];

    [[gnu::always_inline]] static u32 pack(u32 x, u32 y) noexcept {
        return (x << 16) | y;
    }

    [[gnu::always_inline]] static pair<u32, u32> unpack(u32 p) noexcept {
        return {p >> 16, p & 0xFFFF};
    }

    inline static constexpr u32 kInf = 0xFFFFu >> 1;

    static auto maximumSafenessFactor(const vector<vector<int>>& ggg) noexcept {
        auto& gg = reinterpret_cast<const vector<vector<u32>>&>(ggg);
        const u32 h = gg.size(), w = gg.front().size();
        [[assume(h<401)]];
        [[assume(w<401)]];

        u32 qe = 0;
        for (u32 y = 0; y != h; ++y) {
            #pragma GCC unroll
            for (u32 x = 0; x != w; ++x) {
                bool b = gg[y][x];
                g[y][x] = kInf & -!b;
                q[qe] = pack(x, y);
                qe += b;
            }
        }

        for (u32 qb = 0; qb != qe;) {
            for (u32 stop = qe; qb != stop; ++qb) {
                auto [x, y] = unpack(q[qb]);
                #pragma GCC unroll 4
                for (u32 t = 0; t != 4; ++t) {
                    u32 nx = min(x + dx[t], w);
                    u32 ny = min(y + dy[t], h);
                    bool b = (nx != w) & (ny != h) & (g[ny][nx] == kInf);
                    g[ny][nx] = ((g[y][x] + 1) & -b) | (g[ny][nx] & -!b);
                    q[qe] = pack(nx, ny);
                    qe += b;
                }
            }
        }

        qe = 0;
        q[qe++] = pack(0, 0);
        u16 ans = min(g[0][0], g[h - 1][w - 1]);

        constexpr auto cmp = less{};
        constexpr auto proj = [](u32 xy) noexcept -> u32 {
            auto [x, y] = unpack(xy);
            return ((g[y][x] & kInf) << 18) | (y << 9) | x;
        };

        g[0][0] |= 1u << 15;

        const u32 target = pack(w - 1, h - 1);
        while (ans != 0 && qe != 0 && q[0] != target) {
            ranges::pop_heap(q, q + qe, cmp, proj);
            u32 qe2 = qe--;

            {
                auto [x, y] = unpack(q[qe]);
                ans = min(ans, g[y][x] &= kInf);
            }

            for (u32 i = qe; i != qe2; ++i) {
                auto [x, y] = unpack(q[i]);
                if (q[i] == target)
                    return ans;
                if (g[y][x] >> 15)
                    continue;
                g[y][x] |= (1u << 15);

                if ((g[y][x] & kInf) < ans) {
                    q[qe++] = pack(x, y);
                    ranges::push_heap(q, q + qe, cmp, proj);
                    continue;
                }

                ans = min<u16>(ans, g[y][x] & kInf);

                #pragma GCC unroll 4
                for (u32 t = 0; t != 4; ++t) {
                    u32 nx = min(x + dx[t], w);
                    u32 ny = min(y + dy[t], h);
                    bool b = (nx == w) | (ny == h) | (g[ny][nx] >> 15);
                    q[qe2] = pack(nx, ny);
                    qe2 += !b;
                }
            }
        }

        return ans;
    }
};