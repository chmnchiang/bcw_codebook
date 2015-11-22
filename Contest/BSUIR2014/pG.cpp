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

const int MXN = 1000005;

int N, mxCnt, pq[MXN], cnt[MXN];
int remain;
int pre = -1;

void print(int v) {
	cout << v;
	if (remain == 1) {
		cout << endl;
	} else {
		cout << " ";
	}
	if (pre == v) {
		exit(1);
	}
	assert(pre != v);
	pre = v;
	remain--;
}
void pop(int v) {
	int c = pq[v];
	pq[v]--;
	cnt[c]--;
	cnt[c-1]++;
	if (cnt[mxCnt] == 0) {
		mxCnt--;
	}
	print(v);
}

void go(int &x) {
	while (pq[x] == 0) {
		x++;
	}
}

int main() {
	IOS;
	cin >> N;
	for (int i=0, v; i<N; i++) {
		cin >> v;
		pq[v]++;
	}
	mxCnt = 0;
	for (int i=0; i<MXN; i++) {
		if (pq[i]) {
			cnt[pq[i]]++;
			mxCnt = max(mxCnt, pq[i]);
		}
	}
	if (mxCnt >= (N-mxCnt+2)) {
		cout << "-1\n";
		return 0;
	}
	remain = N;
	int alpha = -1;
	int a = 0, b = 0;
	while (remain) {
		if ((remain&1) && (mxCnt == remain/2+1)) {
			// x o x o x o x
			for (int i=0; i<MXN; i++) {
				if (mxCnt == pq[i]) {
					alpha = i;
					break;
				}
			}
			pop(alpha);	
			continue;
		} else if (mxCnt*2 == remain) {
			for (int i=0; i<MXN; i++) {
				if (mxCnt == pq[i]) {
					alpha = i;
					break;
				}
			}
			break;
		}
		go(a);
		if (b <= a) b = a+1;
		go(b);
		if (pre != a) {
			pop(a);
		} else {
			pop(b);
		}
	}
	if (alpha != -1) {
		N = 0;
		for (int i=0; i<MXN; i++) {
			if (i == alpha) continue;
			while (pq[i]) {
				cnt[N++] = i;
				pq[i]--;
			}
		}

		if (pre == alpha) {
			for (int i=0; i<N; i++) {
				print(cnt[i]);
				print(alpha);
			}
		} else {
			if (pre != cnt[0]){
				if (cnt[0] < alpha) {
					for (int i=0; i<N; i++) {
						print(cnt[i]);
						print(alpha);
					}
				} else {
					for (int i=0; i<N; i++) {
						print(alpha);
						print(cnt[i]);
					}
				}
			} else {
				if (N == 1) {
					print(alpha);
					print(cnt[0]);
				} else {
					int id = 0;
					for (int i=0; i<N; i++) {
						if (cnt[i] == cnt[0]) continue;
						id = i;
						break;
					}
					if (pre != cnt[id] && cnt[id] < alpha) {
						print(cnt[id]);
						print(alpha);
						for (int i=0; i<N; i++) {
							if (id == i) continue;
							print(cnt[i]);
							print(alpha);
						}
					} else {
						for (int i=0; i<N; i++) {
							print(alpha);
							print(cnt[i]);
						}
					}
				}
			}
		}
	}

	return 0;
}

