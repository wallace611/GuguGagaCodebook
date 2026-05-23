// dp[i][j] represents the probability of reaching sum j after i rolls
double dp[N+1][6*N+1];

// Initialize the first roll probability
for(int i = 1; i <= 6; ++i) {
	dp[1][i] = 1.0 / 6.0;
}

for(int i = 2; i <= n; ++i) {
	// Max sum after n rolls is 6*n (assuming n <= 100, max 600)
	for(int w = 1; w <= 600; ++w) {
		// Iterate through all 6 dice faces
		for(int j = 1; j <= 6; ++j) {
			if(w >= j) {
				dp[i][w] += dp[i-1][w-j];
			}
		}
		// Divide once per state to prevent precision errors
		dp[i][w] /= 6.0;
	}
}

double ans = 0.0;
for(int i = a; i <= b; ++i) {
	ans += dp[n][i];
}