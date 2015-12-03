// does not work when n is prime
long long modit(long long x,long long mod) {
	if(x>=mod) x-=mod;
	//if(x<0) x+=mod;
	return x;
}
long long mult(long long x,long long y,long long mod) {
	long long s=0,m=x%mod;
	while(y) {
		if(y&1) s=modit(s+m,mod);
		y>>=1;
		m=modit(m+m,mod);
	}
	return s;
}
long long f(long long x,long long mod) {
	return modit(mult(x,x,mod)+1,mod);
}
long long pollard_rho(long long n) {
	if(!(n&1)) return 2;
  while (true) {
    long long y=2, x=rand()%(n-1)+1, res=1;
    for (int sz=2; res==1; sz*=2) {
      for (int i=0; i<sz && res<=1; i++) {
        x = f(x, n);
        res = __gcd(abs(x-y), n);
      }
      y = x;
    }
    if (res!=0 && res!=n) return res;
  }
}
