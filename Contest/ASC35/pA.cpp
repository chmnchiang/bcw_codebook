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

const int MX = 105;

typedef pair<int,int> pii;

struct Event {
	int a, b;
	pii t1, t2;
}event[MX];

int trash;
int N, A, B, a[10], b[10], L;
int ansA[10], ansB[10], seg[105], st[10];
int ans;
int dp[1<<10][10];
vector<int> E[10][1<<10];

void build_edge() {
	for (int k=1; k<=8; k++) {
		int n=1<<k;
		for (int i=0; i<n; i++) {
			for (int j=1; j<=i; j++) {
				if ((i&j) == j) {
					E[k][i].PB(j);
				}
			}
		}
	}
}
void parse(char s[], int &h1, int &m1, pii &s1, int &h2, int &m2, pii &s2) {
	h1 = (s[0]-'0')*10+(s[1]-'0');
	m1 = (s[3]-'0')*10+(s[4]-'0');
	s1 = {s[5]-'A', s[6]-'A'};
	h2 = (s[8]-'0')*10+(s[9]-'0');
	m2 = (s[11]-'0')*10+(s[12]-'0');
	s2 = {s[13]-'A', s[14]-'A'};
}

int go(int n, int k, vector<int> &v1, vector<int> &v2, int state, int nk) {
	if (nk >= k) return 1;
	int &res = dp[state][nk];
	if (res != -1) return res;
	res = 0;
	for (auto v : E[n][state]) {
		int sum = 0;
		for (int i=0; i<n; i++) {
			if (v & (1<<i)) {
				sum += v1[i];
			}
			if (sum > v2[nk]) break;
		}
		if (sum == v2[nk] && go(n, k, v1, v2, state-v, nk+1)) {
			res = 1;
			break;
		}
	}
	return res;
}

void checkAmbiguous(vector<int> v1, vector<int> v2) {
	if (SZ(v1) < SZ(v2)) return;
	sort(ALL(v1));
	sort(ALL(v2));
	//cout << v1 << endl;
	//cout << v2 << endl;
	int n = SZ(v1);
	int k = SZ(v2);
	for (int i=0; i<(1<<n); i++)
		for (int j=0; j<k; j++)
			dp[i][j] = -1;
	if (go(n, k, v1, v2, (1<<n)-1, 0)) ans = 2;
}

bool check(int per[]) {
	int base[10] = {0}, tmpB[10] = {0};
	for (int i=1; i<A; i++) {
		tmpB[i] = tmpB[i-1] + a[per[i-1]];
	}
	for (int i=0; i<A; i++) {
		base[per[i]] = tmpB[i];
	}
	FMO(st);
	for (int i=0; i<L; i++) {
		int aa = event[i].a;
		int bb = event[i].b;
		pii t1 = event[i].t1;
		pii t2 = event[i].t2;
		
		int h1 = t1.F + base[aa];
		int h2 = h1 - t2.F;
		if (h1 >= base[aa] + a[aa]) return false;
		if (h2 < 0) return false;

		if (st[bb] == -1) {
			st[bb] = h2;
		} else if (st[bb] != h2) {
			return false;
		}
		if (st[bb] + b[bb] > N) return false;
	}
	FZ(seg);	
	vector<int> v1;
	for (int i=0; i<B; i++) {
		if (st[i] != -1) {
			for (int j=0; j<b[i]; j++) {
				if (seg[st[i]+j]) return false;
				seg[st[i]+j] = 1;
			}
		} else {
			v1.PB(b[i]);
		}
	}
	vector<int> v2, st2;
	int cnt = !seg[0];
	for (int i=1; i<N; i++) {
		if (seg[i] == 1) {
			if (cnt > 0) {
				v2.PB(cnt);
				st2.PB(i-cnt);
			}
			cnt = 0;
		} else {
			cnt++;
		}
	}
	if (cnt) {
		v2.PB(cnt);
		st2.PB(N-cnt);
	}
	if (SZ(v1) != SZ(v2)) {
		checkAmbiguous(v1, v2);
		return false;
	}
	vector<int> sortv2;
	sortv2 = v2;
	sort(ALL(v1));
	sort(ALL(sortv2));
	int flg = 0;
	for (int i=0; i<SZ(v1); i++) {
		if (v1[i] != sortv2[i]) return false;
		if (i && v1[i] == v1[i-1]) {
			// ambiguous
			flg = 1;
		}
	}
	if (flg) {
		ans = 2;
		return false;
	}

	for (int i=0; i<A; i++) {
		ansA[i] = per[i];
	}
	
	vector<pii> tmp;
	for (int i=0; i<B; i++) {
		if (st[i] != -1) {
			tmp.PB({st[i], i});
		} else {
			for (int j=0; j<SZ(st2); j++) {
				if (b[i] == v2[j]) {
					tmp.PB({st2[j], i});
					break;
				}
			}
		}
	}
	
	sort(ALL(tmp));
	for (int i=0; i<B; i++) {
		ansB[i] = tmp[i].S;
	}

	return true;
}

int main() {
	build_edge();
	FILEIO("ampm");
	while (~scanf("%d", &N)) {
		trash = scanf("%d", &A);
		N = 0;
		for (int i=0; i<A; i++) {
			trash = scanf("%d", &a[i]);
			N += a[i];
		}
		trash = scanf("%d", &B);
		for (int i=0; i<B; i++)
			trash = scanf("%d", &b[i]);
		trash = scanf("%d", &L);
		ans = 0;
		for (int i=0, h1, m1, h2, m2; i<L; i++) {
			pii s1, s2;
			char str[105];
			trash = scanf("%s", str);
			parse(str, h1, m1, s1, h2, m2, s2);
//			printf("%d %d %d%d %d %d %d%d\n", h1, m1, s1.F,s1.S, h2, m2, s2.F,s2.S);
			if (s1.F > s2.F) {
				swap(s1, s2);
				swap(h1, h2);
				swap(m1, m2);
			}
			event[i] = {s1.S, s2.S, {h1, m1}, {h2, m2}};
			if (m1 != m2) {
				ans = -1;
			}
		}
		if (ans != -1) {
			int per[10];
			for (int i=0; i<A; i++) per[i] = i;
			do {
				if (check(per)) ans++;
				if (ans >= 2) break;
			} while (next_permutation(per, per+A));
		}
		if (ans <= 0) {
			printf("Inconsistent\n");
		} else if (ans == 1) {
			printf("Alde system:");
			for (int i=0; i<A; i++)
				printf(" %d", ansA[i] + 1);
			puts("");
			printf("Baran system:");
			for (int i=0; i<B; i++)
				printf(" %d", ansB[i] + 1);
			puts("");
		} else {
			printf("Ambiguous\n");
		}
	}


	return 0;
}
