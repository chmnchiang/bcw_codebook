#include <bits/stdc++.h>
using namespace std;

int N, P, ip[15];

int main() {
	while (cin >> N >> P) {
		int a, b;
		vector<int> vec;
		a = b = 0;
		int s = 0;
		for (int i=0; i<N; i++) { 
			cin >> ip[i];
		}
		if (ip[P] > 300) {
			cout << "0 0\n";
			continue;
		}
		b = s = ip[P];
		a = 1;
		for (int i=0; i<N; i++) {
			if (i == P) continue;
			vec.push_back(ip[i]);
		}
		sort(begin(vec), end(vec));
		for (int i=0; i<N-1; i++) {
			s += vec[i];
			if (s > 300) break;
			b += s;
			a++;
		}
		cout << a << " " << b << endl;
	}

	return 0;
}

