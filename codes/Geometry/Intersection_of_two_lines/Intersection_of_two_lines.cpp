#include<bits/stdc++.h>

using namespace std;
const double EPS = 1e-9;

pdd interPnt(pdd p1, pdd p2, pdd q1, pdd q2){
	double f1 = (p2 - p1) % (q1 - p1);
	double f2 = (p2 - p1) % (p1 - q2);
	double f = (f1 + f2);

	if(fabs(f) < EPS) return pdd(nan(""), nan(""));

	return (f2 / f) * q1 + (f1 / f) * q2;
}
