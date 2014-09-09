long long power(long long x,long long p,long long mod){
	long long s=1,m=x;
	while(p) {
		if(p&1) s=mult(s,m,mod);
		p>>=1;
		m=mult(m,m,mod);
	}
	return s;
}
bool witness(long long a,long long n,long long u,int t){
	long long x=power(a,u,n);
	for(int i=0;i<t;i++) {
		long long nx=mult(x,x,n);
		if(nx==1&&x!=1&&x!=n-1) return 1;
		x=nx;
	}
	return x!=1;
}
bool miller_rabin(long long n,int s=100) {
	// iterate s times of witness on n
	// return 1 if prime, 0 otherwise
	if(n<2) return 0;
	if(!(n&1)) return n==2;
	long long u=n-1;
	int t=0;
	// n-1 = u*2^t
	while(u&1) {
		u>>=1;
		t++;
	}
	while(s--) {
		long long a=randll()%(n-1)+1;
		if(witness(a,n,u,t)) return 0;
	}
	return 1;
}
