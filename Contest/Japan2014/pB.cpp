#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

string str;
int num;

vector<int> vec;
vector<char> op;

void parse() {
	int v = 0;
	for (auto c : str) {
		if (c == '+' || c == '*') {
			vec.PB(v);
			v = 0;
			op.PB(c);
		} else {
			v = v * 10 + c - '0';
		}
	}
	vec.PB(v);
}

bool calc1() {
	int ret = vec[0];
	for (int i=1; i<SZ(vec); i++) {
		if (op[i-1] == '+') {
			ret = ret + vec[i];
		} else {
			ret = ret * vec[i];
		}
	}
	return ret == num;
}
bool calc2() {
	vector<int> p;
	int mul = vec[0];
	for (int i=1; i<SZ(vec); i++) {
		if (op[i-1] == '+') {
			p.PB(mul);
			mul = vec[i];
		} else {
			mul *= vec[i];
		}
	}
	p.PB(mul);
	int ret=0;
	for (auto it : p)
		ret += it;
	return ret == num;
}

int main() {
	cin >> str;
	cin >> num;
	parse();
	int flag1 = calc1();
	int flag2 = calc2();
	if (flag1 && flag2) puts("U");
	else if (flag1) puts("L");
	else if (flag2) puts("M");
	else puts("I");

    return 0;
}

