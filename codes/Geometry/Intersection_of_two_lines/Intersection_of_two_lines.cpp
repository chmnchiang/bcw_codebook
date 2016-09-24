const double EPS = 1e-9;

pdd interPnt(pdd p1, pdd p2, pdd q1, pdd q2, bool &res){
	double f1 = cross(p2, q1, p1);
	double f2 = -cross(p2, q2, p1);
	double f = (f1 + f2);

	if(fabs(f) < EPS) {
		res = false;
		return {};
    }

	res = true;
	return (f2 / f) * q1 + (f1 / f) * q2;
}
