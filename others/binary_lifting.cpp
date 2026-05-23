int jump[N][logN];             //n個點 最多跳logn步
void init(int now, int nxt) {  //now走1步可以走到nxt
  jump[now][0] = nxt;
}
int jump[N][logN];
for(int i = 1; i <= log2(N); i++){ // 從跳 2^1 次枚舉到跳 2^logn 次
	for(int now = 1; now <= N; now++){
		jump[now][i] = jump[jump[now][i - 1]][i - 1];
	}
}
int query(int x,int k){
	int i = log2(k);
	while(k){
		if((1<<i) <= k){
			x = jump[x][i];
			k -= (1<<i);
		}
		i--;
	}
	return x; // 最後跳到的地方就是答案
}

// 樹上倍增
int anc[N][logN];
void dfs(int now, int fa) { // 現在的點、父節點
	anc[now][0] = fa;       // now 的 0 倍祖先是 fa
	for(auto i : g[now]){
		if(i == fa) continue;
		dfs(i, now);
	}
}
