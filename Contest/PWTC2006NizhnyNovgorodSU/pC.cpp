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

const int MAXN = 131072;
// (must be 2^k)

typedef long double ld;
typedef complex<ld> cplx;
const ld PI = acosl(-1);
const cplx I(0, 1);

cplx omega[MAXN+1];
void pre_fft()
{
  for(int i=0; i<=MAXN; i++)
    omega[i] = exp(i * 2 * PI / MAXN * I);
}

void fft(int n, cplx a[], bool inv=false)
{
  int basic = MAXN / n;
  int theta = basic;
  for (int m = n; m >= 2; m >>= 1) {
    int mh = m >> 1;
    for (int i = 0; i < mh; i++) {
      cplx w = omega[inv ? MAXN-(i*theta%MAXN) : i*theta%MAXN];
      for (int j = i; j < n; j += m) {
        int k = j + mh;
        cplx x = a[j] - a[k];
        a[j] += a[k];
        a[k] = w * x;
      }
    }
    theta = (theta * 2) % MAXN;
  }
  int i = 0;
  for (int j = 1; j < n - 1; j++) {
    for (int k = n >> 1; k > (i ^= k); k >>= 1);
    if (j < i) swap(a[i], a[j]);
  }
  if (inv)
    for (i = 0; i < n; i++)
      a[i] /= n;
}

string S1, S2;
int l1, l2;

int ans[5][5][MAXN];
cplx A[5][MAXN], B[5][MAXN];

cplx temp[MAXN];
void calc(int a, int b) {
	for (int i=0; i<MAXN; i++) {
		temp[i] = A[a][i] * B[b][i];
	}
	fft(MAXN, temp, true);
	for (int i=0; i<MAXN; i++) {
		ans[a][b][i] = round(temp[i].real());
	}

}

void calc() {
	pre_fft();
	l1 = SZ(S1);
	l2 = SZ(S2);
	for (int i=0; i<l1+l1; i++) {
		int j = i%l1;
		int t = S1[j]-'A';
		A[t][i] = 1.0;
	}

	for (int i=0; i<l2; i++) {
		int t = S2[l2-i-1]-'a';
		B[t][i] = 1.0;
	}

	for (int i=0; i<5; i++) {
		fft(MAXN, A[i]);
		fft(MAXN, B[i]);
	}

	for (int i=0; i<5; i++) {
		for (int j=0; j<5; j++) {
			calc(i, j);
		}
	}
	
	/*
	for (int a=0; a<5; a++)
		for (int b=0; b<5; b++) {
			cout << char('a' + a) << ' ' << char('A' + b) << ' ';
			for (int i=0; i<l1; i++) {
				cout << ans[a][b][i] << ' ';
			} cout << endl;
		}
		*/
	

	vector<int> perm = {0, 1, 2, 3, 4};
	int ra = 0;
	do {
		for (int i=l1; i<l1+l1; i++) {
			int t = 0;
			for (int j=0; j<5; j++) {
				t += ans[j][perm[j]][i];
				//cout << j << ' ' << perm[j] << ' ' << i << ' ' << ans[j][perm[j]][i] << endl;
				//cout << "T = " << t << endl;
			}
			ra = max(ra, t);
		}
	} while (next_permutation(ALL(perm)));
	cout << l1-ra << endl;
}

int main() {

	IOS;
	cin>>S1>>S2;

	calc();

	return 0;
}
