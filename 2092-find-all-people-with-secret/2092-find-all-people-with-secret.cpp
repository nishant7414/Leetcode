class DSU {
    public:
        vector<int> parent, size;
        DSU (int n) {
            parent.resize(n);
            size.resize(n, 1);

            for (int i = 0; i < n; i++) {
                parent[i] = i;
                size[i] = 1;
            }
        }

        int findUPar (int node) {
            if (parent[node] == node) {
                return node;
            }

            return parent[node] = findUPar(parent[node]);
        }

        void unionBySize (int u, int v) {
            int ulp_u = findUPar(u);
            int ulp_v = findUPar(v);

            if (ulp_u == ulp_v) {
                return;
            }

            if (size[ulp_u] >= size[ulp_v]) {
                parent[ulp_v] = ulp_u;
                size[ulp_u] += size[ulp_v];
            } else {
                parent[ulp_u] = ulp_v;
                size[ulp_v] += size[ulp_u];
            }
        }

        void resetNode (int node) {
            parent[node] = node;
            size[node] = 1;
        }
};

class Solution {
public:
    typedef pair<int, int> P;
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        map<int, vector<pair<int, int>>> mp;
        for (vector<int>& meeting: meetings) {
            int u = meeting[0], v = meeting[1], t = meeting[2];
            mp[t].push_back({u, v});
        }

        DSU dsu(n);
        dsu.unionBySize(0, firstPerson);
        for (auto &timeMeeting: mp) {

            for (auto &p: timeMeeting.second) {
                int u = p.first, v = p.second;
                dsu.unionBySize(u, v);
            }

            for (auto &p: timeMeeting.second) {
                int u = p.first, v = p.second;
                if (dsu.findUPar(u) != dsu.findUPar(0) && 
                        dsu.findUPar(v) != dsu.findUPar(0)) {
                            
                    dsu.resetNode(u);
                    dsu.resetNode(v);
                }
            }

        }

        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (dsu.findUPar(i) == dsu.findUPar(0)) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};