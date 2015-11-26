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

const int MN = 22;
int N;
typedef vector<int> vint;
string sup[MN], dis[MN];
int react[MN];

int main() {
    FILEIO("jungle");

	cin >> N;
	for (int i=1; i<=N; i++) {
		cin >> react[i];
	}

	for (int i=1; i<=N; i++) {
		string t;
		cin >> t;
		int len = t.length();
		for (int j=len-1; j>=0; j--) {
			sup[i] += t[j];
		}
	}
	const int MX = 1000000;
	int now = 1;
	for (int i=1; i<=MX; i++) {

		if (not sup[now].length()) {
			i --;
			now ++;
			now = (now > N ? now - N : now);
			continue;
		}

		char c = sup[now].back();
		sup[now].pop_back();
		dis[now] += c;

		for (int j=1; j<=N; j++) {
			if (j == now) continue;
			if (dis[j].back() == c) {
				int rnow = react[now],
					rj = react[j];
				bool flag = (rnow < rj);
				if (flag) {
					sup[j] = dis[now] + dis[j] + sup[j];
				} else {
					sup[now] = dis[j] + dis[now] + sup[now];
				}
				dis[now] = "";
				dis[j] = "";
				break;
			}
		}
		//cout << sup[now] << ' ' << dis[now] << endl;

		for (int j=1; j<=N; j++) {
			if (sup[j].length() == 0 and dis[j].length() == 0) {
				cout << "Player " << j << " wins after " << i << " moves." << endl;
				return 0;
			}
		}

		bool drflag = true;
		for (int j=1; j<=N; j++) {
			if (sup[j].length()) {
				drflag = false;
				break;
			}
		}
		if (drflag) {
			cout << "Draw after " << i << " moves." << endl;
			return 0;
		}

		now ++;
		now = (now > N ? now - N : now);
	}

	cout << "Abandoned after 1000000 moves." << endl;


    return 0;
}

