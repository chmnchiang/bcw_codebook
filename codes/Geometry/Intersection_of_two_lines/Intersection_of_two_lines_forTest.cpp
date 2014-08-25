#include<bits/stdc++.h>

using namespace std;

typedef pair<double, double> pdd;
const double EPS = 1e-9;

pdd operator + (const pdd p1, const pdd p2) {
	return pdd(p1.first + p2.first, p1.second + p2.second);
}

pdd operator - (const pdd p1, const pdd p2) {
	return pdd(p1.first - p2.first, p1.second - p2.second);
}
double operator % (const pdd p1, const pdd p2) {
	return p1.first * p2.second - p1.second * p2.first;
}
pdd operator * (const double c, const pdd p) {
	return pdd(c * p.first, c * p.second);
}

pdd interPnt(pdd p1, pdd p2, pdd q1, pdd q2){
	double f1 = (p2 - p1) % (q1 - p1);
	double f2 = (p2 - p1) % (p1 - q2);
	double f = (f1 + f2);

	if(fabs(f) < EPS) return pdd(nan(""), nan(""));

	return (f2 / f) * q1 + (f1 / f) * q2;
}

int main(){

	double x, y;
	while(cin >> x >> y){
		pdd p1, p2, p3, p4, pa;
		p1 = pdd(x, y);
		cin >> x >> y;
		p2 = pdd(x, y);
		cin >> x >> y;
		p3 = pdd(x, y);
		cin >> x >> y;
		p4 = pdd(x, y);
		pa = interPnt(p1, p2, p3, p4);
		cout << '(' << pa.first << ", " << pa.second << ')' << endl;
	}
}
