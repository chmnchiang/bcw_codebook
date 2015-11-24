#include <bits/stdc++.h>
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
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

typedef long long i64;
typedef pair<i64, int> pii;
const int MX = 101010;
const int MC = 11;
int N, M, C;
i64 arrive[MX]; 
int cargo[MX], weight[MX];
int speed[MX];
vector<int> can[MX];
int statusShip[MX];
int statusCrane[MX];
int lastIdle[MX];

struct event {
	i64 t;
	int type; // 2 = ship come, 0 = crane finish, 1 = crane idle
	int data; // ship or crane id

	bool operator < (const event &he) const {
		return tie(t, type, data) >= tie(he.t, he.type, he.data);
	}
};

priority_queue<event> events;
priority_queue<pii, vector<pii>, greater<pii>> idle[MC];
priority_queue<pii, vector<pii>, greater<pii>> wait[MC];

int answer[MX];

int main() {
	IOS;
	FILEIO("seaport");

	cin >> N >> M >> C;

	for (int i=0; i<N; i++) {
		cin >> arrive[i] >> cargo[i] >> weight[i];
	}

	for (int i=0; i<M; i++) {
		int t;
		cin >> speed[i] >> t;
		//cout << i << ' ' << t << endl;
		for (int j=0; j<t; j++) {
			int a; cin >> a; can[i].PB(a);
		//	cout << a << endl;
		}
	}

	for (int i=0; i<N; i++) {
		events.push({arrive[i], 2, i});
	}

	for (int i=0; i<M; i++) {
		for (auto x: can[i]) {
			idle[x].push({0, i});
			lastIdle[x] = 0;
			//cout << "idle push = " << x << ' ' << i << endl;
		}
	}

	auto go = [&](int cr, int sh, i64 t) {
		//cout << cr << ' ' << sh << ' ' << t << endl;
		statusShip[sh] = 1;
		statusCrane[cr] = 1;

		answer[sh] = cr;

		i64 finishTime = t + (0LL + weight[sh] + speed[cr] - 1)/speed[cr];
		events.push({finishTime, 0, cr});
	};

	while (not events.empty()) {
		event e = events.top(); events.pop();
		i64 t = e.t;
		//cout << "Event = " << e.t << ' ' << e.type << endl;

		if (e.type == 0) {
			int crane = e.data;
			vector<int> &cans = can[crane];

			pii z = {12345678901234567LL, -1};
			bool have = false;
			for (auto x: cans) {
				auto &ls = wait[x];
				while ( (not ls.empty())
						and (statusShip[ls.top().S] != 2) ) {
					ls.pop();
				}

				if (not ls.empty()) {
					z = min(z, ls.top());
					have = true;
				}
			}

			if (not have) {
				statusCrane[crane] = 0;
				lastIdle[crane] = t;
				for (auto x: cans) {
					idle[x].push({t, crane});
				}
			} else {
				int ship = z.S;
				go(crane, ship, t);
			}
		}

		if (e.type == 2) {
			int ship = e.data;
			int c = cargo[ship];
			auto &ls = idle[c];
			while ( (not ls.empty()) 
					and (statusCrane[ls.top().S] == 1 or lastIdle[ls.top().S] != ls.top().F) ) {
				//cout << "Pop = " << ls.top().S << endl;
				ls.pop();
			}


			if (ls.empty()) {
				statusShip[ship] = 2;
				wait[c].push({t, ship});
			} else {
				pii pr = ls.top(); ls.pop();
				int crane = pr.S;
				//cout << "Crane = " << crane << ' ' << ship << ' ' << c  << endl;
				
				go(crane, ship, t);
			}
		}
	}

	for (int i=0; i<N; i++) {
		cout << answer[i]+1 << '\n';
	}

	return 0;
}

