#include<bits/stdc++.h>
using namespace std;

#define _x first
#define _y second
typedef pair<double, double> pdd;

pdd operator + (const pdd p1, const pdd p2){
	return pdd(p1._x + p2._x, p1._y + p2._y);
}
pdd operator - (const pdd p1, const pdd p2){
	return pdd(p1._x - p2._x, p1._y - p2._y);
}

pdd operator * (const double c, const pdd p){
	return pdd(p._x * c, p._y * c);
}
pdd operator - (const pdd p){
	return (-1.0) * p;
}
double operator * (const pdd p1, const pdd p2){
	return p1._x * p2._x + p1._y * p2._y;
}
double operator % (const pdd p1, const pdd p2){
	return p1._x * p2._y - p2._x * p1._y;
}
