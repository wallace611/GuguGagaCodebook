vector<pair<int, int>> A(N);
sort(A.begin(), A.end());

// Insert start point at index 0 and end point at back
A.insert(A.begin(), pair<int, int>{1, 1}); 
A.push_back(pair<int, int>{n, m});

vector<int> dp(N + 5);

for(int i = 1; i <= N + 1; ++i) {
	// Calculate total valid permutations without obstacles
	dp[i] = cnt(0, i); 
	auto [x, y] = A[i];
	
	// Subtract combinations that pass through other obstacles
	for(int j = 1; j < i; ++j) {
		auto [xx, yy] = A[j];
		
		// Ensure obstacle j is strictly within the path to obstacle i
		if(xx <= x && yy <= y) {
				dp[i] -= cnt(j, i) * dp[j];
		}
	}
}
cout << dp[N+1];