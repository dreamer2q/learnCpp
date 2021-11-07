#include "algorithm"
#include "iostream"
#include "vector"

using namespace std;

struct Edge {
    int start;
    int end;
    int weight;
    explicit Edge() = default;
    explicit Edge(int start, int end, int weight) {
        this->start = start;
        this->end = end;
        this->weight = weight;
    }
};

bool cmp(const Edge &a, const Edge &b) {
    return (a.weight < b.weight);
}

class DisjointSet {
   private:
    vector<int> parent;

   public:
    void init(int n) {
        this->parent = vector<int>(n + 1);
        for (int &t : parent)
            t = -1;
    }
    int findRoot(int x) {
        while (parent[x] != -1) {
            x = parent[x];
        }
        return x;
    }
    bool merge(int x, int y) {
        int x_root = findRoot(x);
        int y_root = findRoot(y);
        if (x_root == y_root)
            return false;
        else {
            parent[x_root] = y_root;
        }
        return true;
    }
};

int main() {
    int n;
    while (cin >> n) {
        vector<Edge> edges;
        vector<int> parent(n + 1);
        DisjointSet disjointSet;
        disjointSet.init(n + 1);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                int weight;
                cin >> weight;
                if (j > i) edges.emplace_back(Edge(i, j, weight));
            }
        }
        int builtNum;
        cin >> builtNum;
        while (builtNum--) {
            int start, end;
            cin >> start >> end;
            disjointSet.merge(start, end);
        }
        sort(edges.begin(), edges.end(), cmp);
        int res = 0;
        for (auto &edge : edges) {
            int startRoot = disjointSet.findRoot(edge.start);
            int endRoot = disjointSet.findRoot(edge.end);
            if (startRoot != endRoot) {
                res += edge.weight;
                disjointSet.merge(startRoot, endRoot);
            }
        }
        cout << res << endl;
    }
    return 0;
}