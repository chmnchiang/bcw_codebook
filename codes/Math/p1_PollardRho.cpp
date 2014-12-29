/* pollard rho */
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
	long long x,x2;
	if(!(n&1)) return 2;
	//x=x2=randll()%n;
	x=x2=2;
	while(1) {
		x=f(x,n); x2=f(f(x2,n),n);
		long long d=__gcd(abs(x-x2),n);
		if(d!=1&&d!=n) return d;
	}
}
