#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e18;
const int MAXN = 100005;
const int LOG = 19;

struct Edge {
	int u, v, w;
	bool in_mst;
	// Sort edges by weight in ascending order
	bool operator<(const Edge& other) const {
		return w < other.w;
	}
};

// DSU for Kruskal's Algorithm
struct DSU {
	vector<int> fa;
	DSU(int n) {
		fa.resize(n + 1);
		for (int i = 1; i <= n; ++i) fa[i] = i;
	}
	int find(int x) {
		return fa[x] == x ? x : fa[x] = find(fa[x]);
	}
	bool merge(int x, int y) {
		int fx = find(x), fy = find(y);
		if (fx == fy) return false;
		fa[fy] = fx;
		return true;
	}
};

int n, m;
vector<Edge> edges;
vector<pair<int, int>> adj[MAXN]; // Tree formed by MST edges

// Binary Lifting Tables
int depth[MAXN];
int up[MAXN][LOG];
long long max1_edge[MAXN][LOG]; // max1_edge: The maximum edge weight on the path
long long max2_edge[MAXN][LOG]; // max2_edge: The STRICTLY second maximum edge weight

// Helper function to update the top 2 distinct maximums from a set of values
void update_max(long long& m1, long long& m2, long long val) {
	if (val > m1) {
		m2 = m1;
		m1 = val;
	} else if (val < m1 && val > m2) {
		m2 = val;
	}
}

// DFS to initialize depth and 0-th ancestor (parent)
void dfs(int u, int p, int w, int d) {
	depth[u] = d;
	up[u][0] = p;
	max1_edge[u][0] = w;
	max2_edge[u][0] = -INF;

	// Build the binary lifting tables
	for (int i = 1; i < LOG; ++i) {
		int ancestor = up[u][i - 1];
		up[u][i] = up[ancestor][i - 1];
		
		long long m1 = -INF, m2 = -INF;
		// Merge the top 2 max edges from the lower half and upper half
		update_max(m1, m2, max1_edge[u][i - 1]);
		update_max(m1, m2, max2_edge[u][i - 1]);
		update_max(m1, m2, max1_edge[ancestor][i - 1]);
		update_max(m1, m2, max2_edge[ancestor][i - 1]);
		
		max1_edge[u][i] = m1;
		max2_edge[u][i] = m2;
	}

	// Traverse children
	for (auto& edge : adj[u]) {
		int v = edge.first;
		int weight = edge.second;
		if (v != p) {
			dfs(v, u, weight, d + 1);
		}
	}
}

// Function to query the max and strict second max edges on the path between u and v
pair<long long, long long> query_path(int u, int v) {
	long long res_m1 = -INF, res_m2 = -INF;
	
	// Ensure u is deeper than v
	if (depth[u] < depth[v]) swap(u, v);
	
	// Equalize depths
	for (int i = LOG - 1; i >= 0; --i) {
		if (depth[u] - (1 << i) >= depth[v]) {
			update_max(res_m1, res_m2, max1_edge[u][i]);
			update_max(res_m1, res_m2, max2_edge[u][i]);
			u = up[u][i];
		}
	}
	
	if (u == v) return {res_m1, res_m2};
	
	// Climb together to find LCA
	for (int i = LOG - 1; i >= 0; --i) {
		if (up[u][i] != up[v][i]) {
			update_max(res_m1, res_m2, max1_edge[u][i]);
			update_max(res_m1, res_m2, max2_edge[u][i]);
			update_max(res_m1, res_m2, max1_edge[v][i]);
			update_max(res_m1, res_m2, max2_edge[v][i]);
			u = up[u][i];
			v = up[v][i];
		}
	}
	
	// Process the last step to LCA
	update_max(res_m1, res_m2, max1_edge[u][0]);
	update_max(res_m1, res_m2, max2_edge[v][0]);
	
	return {res_m1, res_m2};
}

void solve() {
	// 1. Find Minimum Spanning Tree (MST) using Kruskal
	sort(edges.begin(), edges.end());
	DSU dsu(n);
	long long mst_weight = 0;
	int edge_cnt = 0;

	for (auto& e : edges) {
		e.in_mst = false;
		if (dsu.merge(e.u, e.v)) {
			e.in_mst = true;
			mst_weight += e.w;
			edge_cnt++;
			adj[e.u].push_back({e.v, e.w});
			adj[e.v].push_back({e.u, e.w});
		}
	}

	// Check if MST is possible
	if (edge_cnt != n - 1) {
		// cout << "No Spanning Tree" << "\n";
		return;
	}

	// 2. Precompute LCA and max edges tables
	dfs(1, 1, 0, 0);

	// 3. Find the Second MST
	long long strictly_second_mst = INF;
	long long non_strictly_second_mst = INF;

	for (const auto& e : edges) {
		if (e.in_mst) continue; // Only consider edges NOT in the MST
		
		pair<long long, long long> path_max = query_path(e.u, e.v);
		long long m1 = path_max.first;
		long long m2 = path_max.second;

		// DIFFERENCE 1: Non-Strictly Second MST
		// We can ALWAYS replace the max edge (m1) because the new edge e.w is guaranteed to be >= m1
		non_strictly_second_mst = min(non_strictly_second_mst, mst_weight - m1 + e.w);

		// DIFFERENCE 2: Strictly Second MST
		// We must ensure the new total weight is STRICTLY greater than the original MST weight
		if (e.w > m1) {
			strictly_second_mst = min(strictly_second_mst, mst_weight - m1 + e.w);
		} else if (e.w == m1 && m2 != -INF) {
			strictly_second_mst = min(strictly_second_mst, mst_weight - m2 + e.w);
		}
	}

	// Output the results based on your needs
	// cout << "MST: " << mst_weight << "\n";
	// cout << "Non-Strict: " << non_strictly_second_mst << "\n";
	// cout << "Strict: " << strictly_second_mst << "\n";
}