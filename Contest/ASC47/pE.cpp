#include<bits/stdc++.h>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<vector>
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
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

const int MX = 31;
const int prl[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};

int N;
int ans[MX][MX], best[MX][MX], build[MX][MX], tmp[MX][MX];

int cost(int arr[MX][MX]) {
	vector<int> vl;
	for(int i=0; i<N; i++) 
		for(int j=0; j<N; j++) vl.PB(arr[i][j]);

	sort(vl.begin(), vl.end());

	int cs = 0;
	for(int i=0; i<(int)vl.size(); i++) {
		int j = i+1;
		for(; j<(int)vl.size() && vl[j] == vl[i]; j++);
		cs = max(cs, j-i);
	}
	return cs;
}

void getArr(int sh, int num, int arr[MX][MX]) {
	for(int i=0; i<N; i++) 
		for(int j=0; j<N; j++) arr[i][j] = 0;
	for(int i=0; i<N; i++) {
		for(int j=0; j<num; j++) {
			int k = (i+j)%N;
			arr[i][k] = (1<<sh);
		}

	}
	return;
}

void swapRow(int a, int b, int arr[MX][MX]) {
	for(int i=0; i<N; i++) {
		swap(arr[a][i], arr[b][i]);
	}
}

void swapCol(int a, int b, int arr[MX][MX]) {
	for(int i=0; i<N; i++) {
		swap(arr[i][a], arr[i][b]);
	}
}

void randomShuffle(int arr[MX][MX]) {
	int t = N * 2;
	for(int i=0; i<t; i++) {
		int a = rand()%N, b = rand()%N;
		swapRow(a, b, arr);
	}
	for(int i=0; i<t; i++) {
		int a = rand()%N, b = rand()%N;
		swapCol(a, b, arr);
	}
}

void copy(int a[MX][MX], int b[MX][MX]) {
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++) a[i][j] = b[i][j];
}

void mul(int a[MX][MX], int b[MX][MX], int c[MX][MX]) {
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			a[i][j] = b[i][j] | c[i][j];
		}
	}
}

int main()
{
	FILEIO("elegant");
	
	srand(2);
	IOS;
	cin >> N;
	if (N==29) srand(413);
        else if (N>29) srand(1);
	int md = N>>1;


	for(int i=0; i<16; i++) {
		int bs = 101010;
		for(int j=0; j<1000; j++) {
			getArr(i, md, build);
			randomShuffle(build);
			mul(tmp, ans, build);

			int c = cost(tmp);

			if(c < bs) {
				copy(best, tmp);
				bs = c;
			}
		}
		copy(ans, best);
	}

	set<long long> st;

	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			long long outp = 1;
			double x = 0;
			for(int k=0; k<16; k++) {
				if(ans[i][j] & (1<<k)){
					outp *= prl[k];
					x += log10(prl[k]);
				}
			}
			st.insert(outp);
			if( x > 18 ) assert(false);
			cout << outp << ' ';
		}
		cout << endl;
	}
	
	return 0;
}
