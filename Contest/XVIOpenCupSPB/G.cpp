#pragma GCC optimize ("O2")
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

int ip[4][4];

int calc(vector<int> vec) {
	int n = SZ(vec);
	vector<int> vst(n);
	fill(ALL(vst),0);
	int res = n;

	REP(i,n) {
		if (vst[i]) continue;
		int j = i;
		while (!vst[j]) {
			vst[j] = 1;
			j = vec[j];
		}
		res--;
	}
	return res;
}
void swap_row(int i, int j) {
	cout<<char('a'+i)<<"-"<<char('a'+j)<<endl;
}
void swap_col(int i, int j) {
	cout<<(i+1)<<"-"<<(j+1)<<endl;
}
void swap_two(int i, int j) {
	char x1 = 'a'+i/4;
	int y1 = i%4+1;
	char x2 = 'a'+j/4;
	int y2 = j%4+1;

	cout<<x1<<y1<<"-"<<x2<<y2<<endl;
}
int main() {
	IOS;
	REP(i,4) REP(j,4) {
		cin>>ip[i][j];
		ip[i][j]--;
	}
	int bcost = 1000;
	vector<int> brow, bcol, bvec;

	vector<int> row = {0,1,2,3};
	do {
		vector<int> col = {0,1,2,3};
		do {
			vector<int> vec(16);
			REP(i,4) REP(j,4) {
				vec[i*4+j] = ip[row[i]][col[j]];
			}
			int tmp = calc(row) + calc(col) + calc(vec);
			if (tmp < bcost) {
				bcost = tmp;
				brow = row;
				bcol = col;
				bvec = vec;
			}
		} while (next_permutation(ALL(col)));
	} while (next_permutation(ALL(row)));

	assert(bcost != 1000);

	cout<<bcost<<endl;

	int at[16];
	{
		auto vec = brow;
		REP(i,4) vec[brow[i]] = i;
		REP(i,4) at[vec[i]] = i;
		REP(i,4) {
			if (i != vec[i]) {
				int j = at[i];
				swap_row(i,j);
				swap(vec[i], vec[j]);
				at[vec[i]] = i;
				at[vec[j]] = j;
			}
		}
		REP(i,4) assert(vec[i] == i);
	}
	{
		auto vec = bcol;
		REP(i,4) vec[bcol[i]] = i;
		REP(i,4) at[vec[i]] = i;
		REP(i,4) {
			if (i != vec[i]) {
				int j = at[i];
				swap_col(i,j);
				swap(vec[i], vec[j]);
				at[vec[i]] = i;
				at[vec[j]] = j;
			}
		}
		REP(i,4) assert(vec[i] == i);
	}
	{
		auto &vec = bvec;
		REP(i,16) at[vec[i]] = i;
		REP(i,16) {
			if (i != vec[i]) {
				int j = at[i];
				swap_two(i,j);
				swap(vec[i], vec[j]);
				at[vec[i]] = i;
				at[vec[j]] = j;
			}
		}
		REP(i,16) assert(vec[i] == i);
	}


	return 0;
}

