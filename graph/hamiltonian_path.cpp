// 圖中有 n 個點，詢問是否能走過所有點且每個點僅經過一次。需要記錄經過了哪些點，以及停留在哪個點。
// Initialize: each node can reach itself
for(int i = 0; i < n; ++i) {
    dp[(1<<i)][i] = true;
}

// Iterate through all subsets
for(int s = 1; s < (1<<n); ++s) {
  for(int j = 0; j < n; ++j) {
    // Continue if vertex j is not in state s
    if(s & (1<<j)) continue;
    
    // Iterate all endpoints in state s
    for(int i = 0; i < n; ++i) {
      // s must pass through i
      if(!(s & (1<<i))) continue;
      
      // If there is a directed edge from i to j
      if(edge[i][j]) {
          dp[s | (1<<j)][j] |= dp[s][i];
      }
    }
  }
}

bool ans = false;
for(int i = 0; i < n; ++i) ans |= dp[(1<<n)-1][i];