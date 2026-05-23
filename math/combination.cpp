#define MXN 1'000'005
#define N 1'000'000
#define ll long long

ll fac[MXN], inv[MXN];
fac[0] = 1; // 0! = 1
for(int i = 1; i <= N; i++)    fac[i] = fac[i-1] * i % mod;
inv[N] = fpow(fac[N], mod-2); // 快速冪
for(int i = N-1; i >=0; i--)   inv[i] = inv[i+1] * (i+1) % mod;

ll C(int n,int k){
	return fac[n]*inv[k]%mod*inv[n-k]%mod;
}