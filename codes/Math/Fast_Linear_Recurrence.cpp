ll n,m,dp[N+N];
void pre_dp(){
	dp[0]= 1;
	ll bdr = min(m+m,n);
	for(ll i=1; i<=bdr; i++)
		for(ll j=i-1; j>=max(0ll,i-m); j--)
			dp[i]= add(dp[i],dp[j]);
}
vector<ll> Mul(const vector<ll>& v1,const vector<ll>& v2){
	int sz1 = (int)v1.size();
	int sz2 = (int)v2.size();
	assert(sz1 == m and sz2 == m);
	vector<ll> _v(m+m);
	for(int i=0; i<m+m; i++) _v[i]= 0;
	// expand
	for(int i=0; i<sz1; i++)
		for(int j=0; j<sz2; j++)
			_v[i+j+1]= add(_v[i+j+1],mul(v1[i],v2[j]));
	// shrink
	for(int i=0; i<m; i++)
		for(int j=1; j<=m; j++)
			_v[i + j]= add(_v[i + j],_v[i]);
	for(int i=0; i<m; i++)
		_v[i]= _v[i + m];
	_v.resize(m);
	return _v;
}
vector<ll> I,A;
ll solve(){
	pre_dp();
	if(n <= m+m)return dp[n];
	I.resize(m);
	A.resize(m);
	for(int i=0; i<m; i++) I[i]=A[i]=1;
	// dp[n]= /Sum_{i=0}^{m-1} A_i * dp[n - i - 1]
	ll dlt = (n - m) / m;
	ll rdlt = dlt * m;
	while(dlt){
		if(dlt & 1ll) I = Mul(I,A);
		A = Mul(A,A);
		dlt >>= 1;
	}
	ll ans = 0;
	for(int i=0; i<m; i++)
		ans = add(ans,mul(I[i],dp[n-i-1-rdlt]));
  return ans;
}
