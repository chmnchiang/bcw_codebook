#include <bits/stdc++.h>
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define T third
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
	freopen(name".in", "r", stdin); \
	freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

using namespace std;

typedef pair<int, int> pii;

int N;

struct Bigint{
	static const int bL = 1000;
	static const int bM = 10000;
	int v[bL],l;
	Bigint() : l(0) {
		memset(v, 0, sizeof(v));
	}
	void n(){
		for(;l;l--) if(v[l-1]) return;
	}
	Bigint(long long a){
		for(l=0;a;v[l++]=a%bM,a/=bM);
	}
	Bigint(const char *a){
		l=0;
		int t=0,i=strlen(a),q=1;
		int ls=0;
		while(i>ls){
			t+=(a[--i]-'0')*q;
			if((q*=10)>=bM) {
				v[l++]=t; t=0; q=1;
			}
		}
		if(t) v[l++]=t;
	}
	void print() const {
		if(l==0){ putchar('0');return; }
		printf("%d",v[l-1]);
		for(int i=l-2;i>=0;i--) printf("%.4d",v[i]);
	}
	int cp3(const Bigint &b)const {
		if(l!=b.l) return l>b.l?1:-1;
		for(int i=l-1;i>=0;i--)
			if(v[i]!=b.v[i])
				return v[i]>b.v[i]?1:-1;
		return 0;
	}
	bool operator < (const Bigint &b)const{ return cp3(b)==-1; }
	bool operator == (const Bigint &b)const{ return cp3(b)==0; }
	bool operator > (const Bigint &b)const{ return cp3(b)==1; }
	Bigint operator - () const {
		Bigint r = (*this);
		return r;
	}
	Bigint operator + (const Bigint &b) const {
		Bigint r;
		r.l=max(l,b.l);
		for(int i=0;i<r.l;i++) {
			r.v[i]+=v[i]+b.v[i];
			if(r.v[i]>=bM) {
				r.v[i+1]+=r.v[i]/bM;
				r.v[i]%=bM;
			}
		}
		if(r.v[r.l]) r.l++;
		return r;
	}
	Bigint operator - (const Bigint &b) const {
		if((*this)<b) return -(b-(*this));
		Bigint r;
		r.l=l;
		for(int i=0;i<l;i++) {
			r.v[i]+=v[i];
			if(i<b.l) r.v[i]-=b.v[i];
			if(r.v[i]<0) {
				r.v[i]+=bM;
				r.v[i+1]--;
			}
		}
		r.n();
		return r;
	}
	Bigint operator * (const Bigint &b) {
		Bigint r;
		r.l=l+b.l;
		for(int i=0;i<l;i++) {
			for(int j=0;j<b.l;j++) {
				r.v[i+j]+=v[i]*b.v[j];
				if(r.v[i+j]>=bM) {
					r.v[i+j+1]+=r.v[i+j]/bM;
					r.v[i+j]%=bM;
				}
			}
		}
		r.n();
		return r;
	}
};

void mulint(Bigint& a, int b) {
	assert(b <= 10000);
	for (int i=0; i<10; i++)
		a.v[a.l+i] = 0;
	for (int i=0; i<a.l; i++)
		a.v[i] *= b;
	for (int i=0; i<a.l+5; i++) {
		a.v[i+1] += a.v[i] / Bigint::bM;
		a.v[i] %= Bigint::bM;
	}
	int l = a.l;
	for (int i=0; i<10; i++)
		if (a.v[l + i]) a.l = l+i+1;
}

struct LargeInt
{
	Bigint val;
	int npow;

	LargeInt()
	{
	}

	LargeInt(int x)
	{
		val = x;
		npow = 0;
	}

	LargeInt(int x, int y)
	{
		val = x;
		npow = y;
	}

	LargeInt(Bigint x)
	{
		val = x;
		npow = 0;
	}
};

struct tii
{
	int first;
	int second;
	int third;

	tii()
	{
	}

	tii(int i, int j, int k)
	{
		F = i;
		S = j;
		T = k;
	}

	bool operator<(const tii &x) const
	{
		if(F != x.F)return F < x.F;
		if(S != x.S)return S < x.S;
		return T < x.T;
	}
};

LargeInt np(int x)
{
	return LargeInt(1, x);
}

LargeInt& operator+=(LargeInt &a, LargeInt &b)
{
	int mp = min(a.npow, b.npow);
	while(a.npow > mp)
		a.npow--, mulint(a.val, N);
	while(b.npow > mp)
		b.npow--, mulint(b.val, N);
	//plusBigint(a.val, b.val);
	a.val = a.val + b.val;
	return a;
}

LargeInt operator*(LargeInt a, LargeInt b)
{
	LargeInt li;
	li.npow = a.npow + b.npow;
	li.val = a.val * b.val;
	return li;
}

void calc(LargeInt &s, int i, int j, int l, int r, int k)
{
	if(r-l==1) 
	{
		//cout<<i<<" "<<j<<" "<<l<<" "<<r<<" "<<k<<endl;
		s.npow += N-k-1;
		return;
	}
	int m = (l + r) / 2;
	if(j < m)
		mulint(s.val, N-i), calc(s, i, j, l, m, k+1);
	else if(j == m)
		calc(s, i, j, m, r, k);
	else
		mulint(s.val, i), calc(s, i, j, m, r, k+1);
}

int main() {
	FILEIO("binary");

	cin>>N;

	LargeInt tmp = 0;
	LargeInt res = 1;
	for(int i=1; i<=N; i++)
	{
		for(int j=0; j<N; j++)
		{
			res.npow = 0;
			res.val.l = 1;
			res.val.v[0] = 1;
			calc(res, i, j, 0, N, 0);
			
			if(i==1&&j==0) tmp = res;
			else tmp += res;
		}
	}

	while(tmp.npow > 0)
		tmp.npow--, mulint(tmp.val, N);

	tmp.val.print();
	cout<<endl;

	return 0;
}

