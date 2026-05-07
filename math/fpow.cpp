int fpow(int x, int n, int mod) {
    int res = 1;
    while (n) {
        if (n & 1) res = res * x % mod; 
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}