for(int i = 1; i <= n;++i){
    for(int w = W; w >= 0;--w)
        dp[w] = max(w - c[i] >= 0 ? dp[w - c[i]] + v[i] : 0, dp[w]);

// Backtracing
for(int i = 1; i <= n;++i){
    for(int w = 0; w <= W;++w) {
     //dp[i][w] 考慮前 i 個物品且負重上限為 w 的答案。
        int a = w - c[i] >= 0 ? dp[i - 1][w - c[i]] + v[i] : 0;
        int b = dp[i-1][w];
        if(a > b){
            dp[i][w] = a;
            R[i][w] = w-c[i];
        }else{
            dp[i][w] = b;
            R[i][w] = w;
        }   
    }
}

int i = n, w = W;
vector<int> ans;
while(i){
    if(w != R[i][w]) ans.push_back(i); //不一樣代表有取
    w = R[i][w];
    --i;
}