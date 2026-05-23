int getlca(int x, int y) {
	if (is_ancestor(x, y)) return x;     // 如果 u 為 v 的祖先則 lca 為 u
	if (is_ancestor(y, x)) return y;     // 如果 v 為 u 的祖先則 lca 為 u
	for (int i = logN; i >= 0; i--) {    // 判斷 2^logN, 2^(logN-1),...2^1, 2^0 倍祖先
		if (!is_ancestor(anc[x][i], y))  // 如果 2^i 倍祖先不是 v 的祖先
			x = anc[x][i];               // 則往上移動
	}
	return anc[x][0];  // 回傳此點的父節點即為答案
}