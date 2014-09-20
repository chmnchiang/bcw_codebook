struct Point{
  typedef double T;
  T x, y;

  Point() : x(0), y(0) {}
  Point(T _x, T _y) : x(_x), y(_y) {}

  bool operator < (const Point &b) const{
    return tie(x,y) < tie(b.x,b.y);
  }
  bool operator == (const Point &b) const{
    return tie(x,y) == tie(b.x,b.y);
  }
  Point operator + (const Point &b) const{
    return Point(x+b.x, y+b.y);
  }
  Point operator - (const Point &b) const{
    return Point(x-b.x, y-b.y);
  }
  T operator * (const Point &b) const{
    return x*b.x + y*b.y;
  }
  T operator % (const Point &b) const{
    return x*b.y - y*b.x;
  }
  Point operator * (const T &b) const{
    return Point(x*b, y*b);
  }
  T len(){
    return sqrt(len2());
  }
  T len2(){
    return x*x + y*y;
  }
};

const int MAXN = 1000100;
struct Mcc{
  // return pair of center and r^2
  int n;
  Point p[MAXN],cen;
  double r2;
  
  void init(int _n, Point _p[]){
    n = _n;
    memcpy(p,_p,sizeof(Point)*n);
  }
  double sqr(double a){ return a*a; }
  Point center(Point p0, Point p1, Point p2) {
    Point a = p1-p0;
    Point b = p2-p0;
    double c1=a.len2()*0.5;
    double c2=b.len2()*0.5;
    double d = a % b;
    double x = p0.x + (c1 * b.y - c2 * a.y) / d;
    double y = p0.y + (a.x * c2 - b.x * c1) / d;
    return Point(x,y);
  }

  pair<Point,double> solve(){
    random_shuffle(p,p+n);
    r2=0;
    for (int i=0; i<n; i++){
      if ((cen-p[i]).len2() <= r2) continue;
      cen = p[i];
      r2 = 0;
      for (int j=0; j<i; j++){
        if ((cen-p[j]).len2() <= r2) continue;
        cen = Point((p[i].x+p[j].x)*0.5, (p[i].y+p[j].y)*0.5);
        r2 = (cen-p[j]).len2();
        for (int k=0; k<j; k++){
          if ((cen-p[k]).len2() <= r2) continue;
          cen = center(p[i],p[j],p[k]);
          r2 = (cen-p[k]).len2();
        }
      }
    }
    return _MP(cen,r2);
  }
}mcc;
