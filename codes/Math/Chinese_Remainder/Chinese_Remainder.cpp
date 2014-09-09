int pfn; // number of distinct prime factors
int pf[MAXNUM]; // prime factor powers
int rem[MAXNUM]; // corresponding remainder
int pm[MAXNUM];
inline void generate_primes() {
	int i,j;
	pnum=1;
	prime[0]=2;
	for(i=3;i<MAXVAL;i+=2) {
		if(nprime[i]) continue;
		prime[pnum++]=i;
		for(j=i*i;j<MAXVAL;j+=i) nprime[j]=1;
	}
}
inline int inverse(int x,int p) {
	int q,tmp,a=x,b=p;
	int a0=1,a1=0,b0=0,b1=1;
	while(b) {
		q=a/b; tmp=b; b=a-b*q; a=tmp;
		tmp=b0; b0=a0-b0*q; a0=tmp;
		tmp=b1; b1=a1-b1*q; a1=tmp;
	}
	return a0;
}
inline void decompose_mod() {
	int i,p,t=mod;
	pfn=0;
	for(i=0;i<pnum&&prime[i]<=t;i++) {
		p=prime[i];
		if(t%p==0) {
			pf[pfn]=1;
			while(t%p==0) {
				t/=p;
				pf[pfn]*=p;
			}
			pfn++;
		}
	}
	if(t>1) pf[pfn++]=t;
}
inline int chinese_remainder() {
	int i,m,s=0;
	for(i=0;i<pfn;i++) {
		m=mod/pf[i];
		pm[i]=(long long)m*inverse(m,pf[i])%mod;
		s=(s+(long long)pm[i]*rem[i])%mod;
	}
	return s;
}
\end{lstlisting}

\subsection{Miller Rabin}
\begin{lstlisting}
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
