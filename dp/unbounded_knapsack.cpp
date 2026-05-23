for(int w = 0; w <= W; ++w)
	for(int i = 1; i <= n; ++i)
		dp[w] = max(dp[w], w-c[i] >= 0 ? dp[w-c[i]] + v[i] : 0);