#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

const int MX = 17;
const int MXF = (1<<17);

const int perc[4] = {0, 1, 2, 6};
const int per[4][6][3] = {
	{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
	{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
	{{0, 1, 0}, {1, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
	{{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}}
};

int N, K, M, P;
string ip[MX];
string lf[MX];
string mem[(1<<MX)][17][7];
bool us[MXF][17][7];

bool us2[20][20][20][20];
bool mem2[20][20][20][20];
bool dp2(int st, int ps, int ed, int pe) {
	if (us2[st][ps][ed][pe]) return mem2[st][ps][ed][pe];

	us2[st][ps][ed][pe] = true;
	string ord = ip[ed];
	reverse(ord.begin(), ord.end());
	
	string q = "";
	for (int k=0; k<M; k++) {
		q += lf[ed][per[M][pe][k]];
	}

	string rord = ord + q;
	//cout << "rord = " << rord << endl;

	int zo[20] = {};
	for (int k=0; k<N; k++) {
		zo[rord[k]-'A'] = k;
	}

	bool can = true;
	for (int k=0; k<K-1; k++) {
		if (zo[ip[st][k]-'A'] > zo[ip[st][k+1]-'A']) {
			can = false;
			break;
		}
	}

	if (not can) return mem2[st][ps][ed][pe] = false;;

	for (int k=0; k<M-1; k++) {
		if (zo[lf[st][per[M][ps][k]]-'A'] > zo[lf[st][per[M][ps][k+1]]-'A']) {
			can = false;
			break;
		}
	}

	if (not can) return mem2[st][ps][ed][pe] = false;;
	return mem2[st][ps][ed][pe] = true;;
}

string dp(int fg, int st, int p) {
	if (not (fg & (1<<st))) return "!";

	int cnt = __builtin_popcount(fg);
	char c = st + 'A';
	if (cnt == 1) {
		//cout << "Fin = " << (c) << endl;
		return string("") + c;
	}

	if (us[fg][st][p]) return mem[fg][st][p];

	us[fg][st][p] = true;
	string ans = "!";
	for (int i=0; i<N; i++) {
		if (not ((1<<i) & fg)) continue;
		if (st == i) continue;

		string ord = ip[i];
		reverse(ord.begin(), ord.end());

		for (int j=0; j<P; j++) {

			if (not dp2(st, p, i, j)) continue;

			string a = dp(fg^(1<<st), i, j);
			if (a == "!") continue;
			else {
				if (ans == "!") {
					//cout << a << endl;
					ans = a + c;
				} else if (ans > (a+c)) {
					ans = (a+c);
				}
			}
		}
	}
	//cout << "Ans = " << ans << endl;

	return (mem[fg][st][p] = ans);
}

int main() {
	IOS;
	cin >> N >> K;
	M = N - K;
	P = perc[M];

	for (int i=0; i<N; i++) {
		cin >> ip[i];

		bool fd[20] = {};

		for (int j=0; j<K; j++) {
			fd[ip[i][j]-'A'] = true;
		}


		for (int j=0; j<N; j++) {
			if (not fd[j]) lf[i] += char('A'+j);
		}
	}

	//while(1);

	string ans = "ZZZZZZZ";

	int fg = (1<<N)-1;
	for (int i=0; i<N; i++) {
		for (int j=0; j<P; j++) {
			string a = dp(fg, i, j);
			if (a == "!") continue;
			ans = min(ans, dp(fg, i, j));
		}
	}
	cout << ans << endl;
	return 0;
}

