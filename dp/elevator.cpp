#define pp pair<int,int>
#define ff first
#define ss second
pp dp[(1<<20)]; //2^20
void solve(){
	int n,x;
	cin >> n >> x;
	vector<int> w(n);
	for(auto &c:w) cin >> c;
    //初始化: 電梯最多搭 n 次，所以開 n+1 當 inf
	for(int s = 0; s < (1<<n);++s) dp[s].ff = n+1;
    // s 為集合
	dp[0].ss = x, dp[0].ff = 0; 
    //沒人上電梯 讓空集合電梯目前的負重是 x，
    //所以空集這台電梯就搭不上去，這樣下一個人上電梯一定會搭到下一班
	for(int s = 1; s < (1<<n);++s){ //窮舉全部狀態
		for(int i = 0; i < n;++i){
			if(!(s & (1 << i))) continue; 
            // i 為此集合 s 最後上電梯的人 所以必須落在集合 s 內
			int pv = s ^ (1 << i); // i 沒搭的狀態
			auto [a,b] = dp[pv];
            
			if(b + w[i] > x) b = w[i],++a; // i 搭不上最後一班，得多一班
			else b += w[i]; //搭的上去
            
			if(a < dp[s].ff) dp[s] = pp{a,b}; //次數少先取
			else if(a == dp[s].ff) dp[s].ss = min(dp[s].ss,b); //次數一樣，取最小的負重
		}
	}
	cout << dp[(1<<n)-1].ff << '\n';
}