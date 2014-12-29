int P=605028353,root=3,MAXNUM=262144;
// Remember coefficient are mod P
/*
p=a*2^n+1
n		2^n 				p 						a 		root
5		32 					97 						3 		5
6		64 					193 					3 		5
7		128					257					  2 		3
8		256 				257 					1 		3
9		512 				7681 					15 		17
10 	1024 				12289 				12 		11
11 	2048 				12289 				6 		11
12 	4096 				12289 				3 		11
13 	8192 				40961 				5			3
14 	16384				65537 				4 		3
15 	32768 			65537 				2 		3
16 	65536 			65537 				1 		3
17 	131072 			786433 				6 		10
18 	262144 			786433 				3 		10 (605028353, 2308, 3)
19 	524288 			5767169 			11 		3
20 	1048576		 	7340033 			7 		3
21 	2097152			23068673 			11 		3
22 	4194304 		104857601 		25 		3
23 	8388608		 	167772161 		20 		3
24 	16777216 		167772161 		10 		3
25 	33554432 		167772161 		5 		3 (1107296257, 33, 10)
26 	67108864 		469762049 		7 		3
27 	134217728 	2013265921 		15 		31
*/
int bigmod(long long a,int b){
	if(b==0)return 1;
	return (bigmod((a*a)%P,b/2)*(b%2?a:1ll))%P;
}
int inv(int a,int b){
	if(a==1)return 1;
	return (((long long)(a-inv(b%a,a))*b+1)/a)%b;
}
std::vector<long long> ps(MAXNUM);
std::vector<int> rev(MAXNUM);
struct poly{
	std::vector<unsigned int> co;
	int n;//polynomial degree = n
	poly(int d){n=d;co.resize(n+1,0);}
	void trans2(int NN){
		int r=0,st,N;
		unsigned int a,b;
		while((1<<r)<(NN>>1))++r;
		for(N=2;N<=NN;N<<=1,--r){
			for(st=0;st<NN;st+=N){
				int i,ss=st+(N>>1);
				for(i=(N>>1)-1;i>=0;--i){
					a=co[st+i]; b=(ps[i<<r]*co[ss+i])%P;
					co[st+i]=a+b; if(co[st+i]>=P)co[st+i]-=P;
					co[ss+i]=a+P-b; if(co[ss+i]>=P)co[ss+i]-=P;
				}
			}
		}
	}
	void trans1(int NN){
		int r=0,st,N;
		unsigned int a,b;
		for(N=NN;N>1;N>>=1,++r){
			for(st=0;st<NN;st+=N){
				int i,ss=st+(N>>1);
				for(i=(N>>1)-1;i>=0;--i){
					a=co[st+i]; b=co[ss+i];
					co[st+i]=a+b; if(co[st+i]>=P)co[st+i]-=P;
					co[ss+i]=((a+P-b)*ps[i<<r])%P;
				}
			}
		}
	}
	poly operator*(const poly& _b)const{
		poly a=*this,b=_b;
		int k=n+b.n,i,N=1;
		while(N<=k)N*=2;
		a.co.resize(N,0); b.co.resize(N,0);
		int r=bigmod(root,(P-1)/N),Ni=inv(N,P);
		ps[0]=1;
		for(i=1;i<N;++i)ps[i]=(ps[i-1]*r)%P;
		a.trans1(N);b.trans1(N);
		for(i=0;i<N;++i)a.co[i]=((long long)a.co[i]*b.co[i])%P
			;
		r=inv(r,P);
		for(i=1;i<N/2;++i)std::swap(ps[i],ps[N-i]);
		a.trans2(N);
		for(i=0;i<N;++i)a.co[i]=((long long)a.co[i]*Ni)%P;
		a.n=n+_b.n; return a;
	}
};
