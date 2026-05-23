using ld = long double;
ld dp[1005][1005];

// Initialize: when only white mice remain, princess wins 100%
for (int i = 1; i <= w; i++) dp[i][0] = 1;
// Initialize: when only black mice remain, princess wins 0%
for (int i = 1; i <= b; i++) dp[0][i] = 0;

for (int i = 1; i <= w; i++) {
	for (int j = 1; j <= b; j++) {
		auto &cur = dp[i][j];
		
		// Case 1: Princess catches a white mouse immediately
		cur += (ld)i / (i + j);
		
		// Probability that both princess and dragon catch a black mouse
		ld x = (ld)j / (i + j) * (j - 1) / (i + j - 1);
		
		// Case 2: A black mouse escapes after they both catch black mice
		if (j >= 3) {
			cur += x * (j - 2) / (i + j - 2) * dp[i][j-3];
		}
		
		// Case 3: A white mouse escapes after they both catch black mice
		if (j >= 2) {
			cur += x * i / (i + j - 2) * dp[i-1][j-2];
		}
	}
}