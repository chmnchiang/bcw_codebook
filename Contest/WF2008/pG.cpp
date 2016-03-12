#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define F first
#define S second
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
#define REP(i,x) for (int i=0; i<(x); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
template<typename A, typename B>
ostream& operator <<(ostream &s, const pair<A,B> &p) {
    return s<<"("<<p.first<<","<<p.second<<")";
}
template<typename T>
ostream& operator <<(ostream &s, const vector<T> &c) {
    s<<"[ ";
    for (auto it : c) s << it << " ";
    s<<"]";
    return s;
}
// Let's Fight!

typedef long double ld;

const int MAXN = 25;
const ld EPS = 1E-12;
const ld EPS2 = 1E-8;
const ld INF = 1E6;

int N;
ld arr[MAXN], brr[MAXN], crr[MAXN];
ld C;
ld A1, A0, B1, B0;

ld aa[3][3], bb[3];

void gauss()
{
	for(int i=0; i<3; i++)
	{
		int piv = -1;
		for(int j=i; j<3; j++)
			if(abs(aa[j][i]) > EPS)
				piv = j;
		swap(aa[piv], aa[i]);
		swap(bb[piv], bb[i]);

		ld r = aa[i][i];
		for(int j=0; j<3; j++)
			aa[i][j] /= r;
		bb[i] /= r;
		for(int j=0; j<3; j++)
		{
			if(j == i) continue;
			ld rat = aa[j][i];
			for(int k=0; k<3; k++)
				aa[j][k] -= aa[i][k] * rat;
			bb[j] -= bb[i] * rat;
		}
	}
}

ld eval_poly(ld x)
{
	ld res = 0;
	ld cur = 1;
	for(int i=0; i<=2*N+1; i++)
	{
		res += cur * crr[i];
		cur *= x;
	}

	return res;
}

ld eval_side(ld h, ld m, ld lb)
{
	for(int i=0; i<=N; i++)
		brr[i] = arr[i];
	brr[0] += m * C - h;
	brr[1] -= m;
	FZ(crr);
	for(int i=0; i<=2*N; i++)
	{
		ld r = 0;
		for(int j=0; j<=i; j++)
			r += brr[j] * brr[i-j];
		crr[i+1] = r / (i+1);
	}

	ld mx = max(lb, C), mn = min(lb, C);
	return eval_poly(mx) - eval_poly(mn);
}

ld eval(ld h, ld l, ld r)
{
	return eval_side(h, l, -1) + eval_side(h, r, 1);
}

ld randf(ld x)
{
	ld r = rand() / (ld)RAND_MAX;
	return x * (2 * r - 1);
}

ld min_l(ld h)
{
	ld lb = -INF, rb = INF;
	for(int i=0; i<200; i++)
	{
		ld m1 = (lb*2+rb)/3, m2 = (lb+rb*2)/3;
		ld c1 = eval_side(h, m1, -1);
		ld c2 = eval_side(h, m2, -1);
		if(c1 < c2)
			rb = m2;
		else
			lb = m1;
	}

	return rb;
}

ld min_r(ld h)
{
	ld lb = -INF, rb = INF;
	for(int i=0; i<200; i++)
	{
		ld m1 = (lb*2+rb)/3, m2 = (lb+rb*2)/3;
		ld c1 = eval_side(h, m1, 1);
		ld c2 = eval_side(h, m2, 1);
		if(c1 < c2)
			rb = m2;
		else
			lb = m1;
	}

	return rb;
}

ld eval_h(ld h)
{
	ld ml = min_l(h), mr = min_r(h);
	return eval(h, ml, mr);
}

ld min_hlr()
{
	ld lb = -5, rb = 5;
	for(int i=0; i<200; i++)
	{
		ld m1 = (lb*2+rb)/3, m2 = (lb+rb*2)/3;
		ld c1 = eval_h(m1);
		ld c2 = eval_h(m2);
		if(c1 < c2)
			rb = m2;
		else
			lb = m1;
	}

	return rb;
}

void CCLemon()
{
	FZ(crr);
	for(int i=0; i<=N; i++)
		crr[i+1] = arr[i] / (i+1);
	bb[0] = -2 * (eval_poly(1) - eval_poly(-1));
	bb[1] = -2 * C * (eval_poly(1) - eval_poly(C));
	bb[2] = -2 * C * (eval_poly(C) - eval_poly(-1));
	FZ(crr);
	for(int i=0; i<=N; i++)
		crr[i+2] = arr[i] / (i+2);
	bb[1] += 2 * (eval_poly(1) - eval_poly(C));
	bb[2] += 2 * (eval_poly(C) - eval_poly(-1));

	aa[0][0] = 4;
	aa[0][1] = -pow(1-C, 2);
	aa[0][2] = pow(1+C, 2);
	aa[1][0] = -pow(1-C, 2);
	aa[1][1] = 2./3.*pow(1-C, 3);
	aa[1][2] = 0;
	aa[2][0] = pow(1+C, 2);
	aa[2][1] = 0;
	aa[2][2] = 2./3.*pow(1+C, 3);
}

void calc()
{
/*	ld h = min_hlr();
	h = CCLemon();
	ld l = min_l(h);
	ld r = min_r(h);*/

/*	A1 = (h-l) / (C+1);
	A0 = h - A1 * C;
	B1 = (h-r) / (C-1);
	B0 = h - B1 * C;
	*/

	CCLemon();
	gauss();
	ld h = -bb[0], l = bb[2], r = bb[1];

	A1 = l;
	A0 = h - C * l;
	B1 = r;
	B0 = h - C * r;

//	cout<<l<<" "<<h<<" "<<r<<endl;
}

double xorg(ld x)
{
	return x;
	if(x < 0) return x - EPS2;
	else return x + EPS2;
}

int main() {
	IOS;

	int t = 0;
	while(cin>>N && N)
	{
		t++;
		double x;
		for(int i=N; i>=0; i--)
		{
			cin>>x;
			arr[i] = x;
		}
		cin>>x;
		C = x;

		calc();
		cout<<fixed<<setprecision(3);
		cout<<"Case "<<t<<": "<<xorg(A1)<<" "<<xorg(A0)<<" "<<xorg(B1)<<" "<<xorg(B0)<<endl;
	}
    return 0;
}

