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
  T abs(){
    return sqrt(abs2());
  }
  T abs2(){
    return x*x + y*y;
  }
};
