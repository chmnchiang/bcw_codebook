typedef long long LL;
const int MAXN = 100010;
struct Coord{
	LL x, y;
	Coord operator - (Coord ag) const{
		Coord res;
		res.x = x - ag.x;
		res.y = y - ag.y;
		return res;
	}
}sum[MAXN], pnt[MAXN], ans, calc;

inline bool cross(Coord a, Coord b, Coord c){
	return (c.y - a.y) * (c.x - b.x) > (c.x - a.x) * (c.y - b.y);
}

int main(){
	int n, l, np, st, ed, now;
	scanf("%d %d\n", &n, &l);
	sum[0].x = sum[0].y = np = st = ed = 0;
	for (int i = 1, v; i <= n; i++){
		scanf("%d", &v);
		sum[i].y = sum[i - 1].y + v;
		sum[i].x = i;
	}
	ans.x = now = 1;
	ans.y = -1;
	for (int i = 0; i <= n - l; i++){
		while (np > 1 && cross(pnt[np - 2], pnt[np - 1], sum[i]))
			np--;
		if (np < now && np != 0) now = np;
		pnt[np++] = sum[i];
		while (now < np && !cross(pnt[now - 1], pnt[now], sum[i + l]))
			now++;
		calc = sum[i + l] - pnt[now - 1];
		if (ans.y * calc.x < ans.x * calc.y){
			ans = calc;
			st = pnt[now - 1].x;
			ed = i + l;
		}
	}
	double res = (sum[ed].y-sum[st].y)/(sum[ed].x-sum[st].x);
	printf("%f\n", res);
	return 0;
}
