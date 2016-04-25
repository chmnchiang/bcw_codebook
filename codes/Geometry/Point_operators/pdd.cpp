#include<bits/stdc++.h>

using namespace std;

#define x first
#define y second

typedef double dou;
struct pdd : pair<dou, dou> {
    using pair<dou, dou>::pair;
    #define C ,
    #define F(a,b,c,d) c a (const b &p) const { return d; }
    #define op(a) operator a
    #define O(a,b,c,d) c op(a) (const b &p) const { return d; } \
                       void op(a##=) (const b &p) { (*this)=(*this) a p; }
    explicit pdd(double a) : pdd(cos(a), sin(a)) {}
    O(+    , pdd, pdd, {x+p.x C y+p.y})
    O(-    , pdd, pdd, {x-p.x C y-p.y})
    O(*    , dou, pdd, {x*p C y*p}    )
    O(/    , dou, pdd, {x/p C y/p}    )
    F(op(*), pdd, dou, x*p.x+y*p.y    )
    F(cross, pdd, dou, x*p.y-y*p.x    )
    F(rot  , dou, pdd, {x*cos(p)-y*sin(p) C x*sin(p)+y*cos(p)})
    dou abs() { return hypot(x, y); }
    dou arg() { return atan2(y, x); }
};

template<typename T1, typename T2>
ostream& operator << (ostream &o, const pair<T1, T2> &pair) {
    return o << "(" << pair.x << ", " << pair.y << ")";
}

int main(){
    pdd p = {1, 2};
    cout << p << endl;
    cout << p.abs() << endl;
    p += p;
    cout << p << p.abs() << endl;
    pdd q = {2, 3};
    cout << p*q << endl;
    cout << p.cross(q) << endl;
    cout << p << endl;
    cout << p.rot(acos(-1)/2) << endl;
    q *= 2;
    cout << q << endl;
}

