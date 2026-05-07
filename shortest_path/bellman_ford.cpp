struct edge {
    int v, w;
};
int s, n; // 起點 點數量
vector<edge> E[MXN];
vector<int> dis(MXN, INF), cnt(MXN), inq(MXN);
// cnt記錄最短路經過幾條邊
// inq記錄節點是否在queue裡面
queue<int> Q;
dis[s] = 0; Q.push(s); inq[s] = 1;
while (Q.size()) {
    int u = Q.front(); Q.pop();
    inq[u] = 0;
    for (auto [v, w] : E[u]) {
        if (dis[v] > dis[u] + w) {
            dis[v] = dis[u] + w;
            cnt[v] = cnt[u] + 1;
            if (cnt[v] >= n) {有負環}
            if (!inq[v]) Q.push(v), inq[v] = 1;
}}}