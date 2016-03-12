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

typedef long long ll;
const int MXN = 105;

int E;
ll M;
ll arr[MXN], brr[MXN];
ll comb[MXN][MXN];
string ip;

ll get_number(int &i) {
	ll s = 1, v = 0;
	if (ip[i] == '-') {
		s = -1;
		i++;
	}
	if (ip[i] == '+') i++;
	while (i < SZ(ip)) {
		if (!isdigit(ip[i])) break;
		v = v * 10 + ip[i] - '0';
		i++;
	}
	v *= s;
	return v;
}
void predo() {
	E = 0;
	FZ(arr);
	int i = 1;
	while (i < SZ(ip)) {
		if (ip[i] == ')') break;
//		cout << i << endl;
		if (ip[i] == '+' and ip[i+1] == 'n') {
			i += 2;
			if (ip[i] == '^') {
				i++;
				ll c = get_number(i);
				arr[c] += 1;
			} else {
				arr[1] += 1;
			}

		} else if (ip[i] == 'n') {
			i++;
			if (ip[i] == '^') {
				i++;
				ll c = get_number(i);
				arr[c] += 1;
			} else {
				arr[1] += 1;
			}
		} else if (ip[i] == '-' and ip[i+1] == 'n') {
			i += 2;
			if (ip[i] == '^') {
				i++;
				ll c = get_number(i);
				arr[c] -= 1;
			} else {
				arr[1] -= 1;
			}
		} else {
			int v = get_number(i);
			//cout << "PARSE " << v << endl;
			if (ip[i] == 'n') {
				i++;
				if (ip[i] == '^') {
					i++;
					ll c = get_number(i);
					arr[c] += v;
				} else {
					arr[1] += v;
				}
			} else {
				arr[0] += v;
			}
		}
	}
	E = 0;
	for (int j=100; j>=0; j--) {
		if (arr[j]) {
			E = j;
			break;
		}
	}
	i += 2;
	M = get_number(i);
	/*
	cout << "====\n";
	REP1(j,0,E) cout << arr[j] << " ";
	cout << endl;
	
	cout << "M = " << M << endl;
	*/
}
void make_comb()
{
	FZ(comb);
	comb[0][0] = 1 % M;
	for(int i=0; i<=E; i++)
	{
		comb[i][0] = comb[i][i] = 1 % M;
		for(int j=1; j<i; j++)
			comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % M;
	}
}
bool solve() {
	make_comb();

	for(int i=0; i<=E; i++)
	{
		arr[i] %= M;
		if(arr[i] < 0) arr[i] += M;
	}

	while(1)
	{
//		for(int i=E; i>=0; i--) cout<<arr[i]<<" ";cout<<endl;
		if(arr[0]) return false;

		for(int i=0; i<=E; i++)
			brr[i] = arr[i];
		FZ(arr);
		for(int i=E; i>0; i--)
		{
			for(int j=i-1; j>=0; j--)
			{
				arr[j] += brr[i] * comb[i][j];
				arr[j] %= M;
			}
		}
		E--;
		if(E < 0) break;
	}

	return true;
}
int main() {
	int t = 0;
	while (cin >> ip) {
		if (ip == ".") break;
		t++;
		predo();
		bool res = solve();
		cout<<"Case "<<t<<": ";
		if(res)
			cout<<"Always an integer"<<endl;
		else
			cout<<"Not always an integer"<<endl;
	}

    return 0;
}

