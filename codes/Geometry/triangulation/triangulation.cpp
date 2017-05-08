bool inCircle(pdd a, pdd b, pdd c, pdd d) {
    b = b - a;
    c = c - a;
    d = d - a;
    if (cross(b, c) < 0) swap(b, c);
    double m[3][3] = {
        {b.x, b.y, b*b},
        {c.x, c.y, c*c},
        {d.x, d.y, d*d}
    };

    double det = m[0][0] * (m[1][1]*m[2][2] - m[1][2]*m[2][1])
               + m[0][1] * (m[1][2]*m[2][0] - m[1][0]*m[2][2])
               + m[0][2] * (m[1][0]*m[2][1] - m[1][1]*m[2][0]);
    return det < 0;
}

bool intersect(pdd a, pdd b, pdd c, pdd d) {
    return cross(b, c, a) * cross(b, d, a) < 0 and
        cross(d, a, c) * cross(d, b, c) < 0;
}


const double EPS = 1e-12;
struct Triangulation {
    static const int MXN = 1e5+5;
    int N;
    vector<int> ord;
    vector<pdd> pts;
    set<int> E[MXN];
    vector<vector<int>> solve(vector<pdd> p) {
        N = SZ(p);
        ord.resize(N);
        for (int i=0; i<N; i++) {
            E[i].clear();
            ord[i] = i;
        }
        sort(ALL(ord), [&p](int i, int j) {
            return p[i] < p[j];
        });

        pts.resize(N);
        for (int i=0; i<N; i++) pts[i] = p[ord[i]];

        go(0, N);

        vector<vector<int>> res(N);
        for (int i=0; i<N; i++) {
            int o = ord[i];
            for (auto x: E[i]) {
                res[o].PB(ord[x]);
            }
        }
        return res;
    }

    void add_edge(int u, int v) {
        E[u].insert(v);
        E[v].insert(u);
    }

    void remove_edge(int u, int v) {
        E[u].erase(v);
        E[v].erase(u);
    }

    void go(int l, int r) {
        int n = r - l;

        if (n <= 3) {
            for (int i=l; i<r; i++)
                for (int j=i+1; j<r; j++) add_edge(i, j);
            return;
        }
        int md = (l+r)/2;

        go(l, md);
        go(md, r);

        int il = l, ir = r-1;
        while (1) {
            int nx = -1;
            for (auto i: E[il]) {
                double cs = cross(pts[il], pts[i], pts[ir]);
                if (cs > EPS ||
                    (abs(cs) < EPS and abs(pts[i]-pts[ir]) < abs(pts[il]-pts[ir]))) {
                    nx = i;
                    break;
                }
            }
            if (nx != -1) {
                il = nx;
                continue;
            }
            for (auto i: E[ir]) {
                double cs = cross(pts[ir], pts[i], pts[il]);
                if (cs < -EPS ||
                    (abs(cs) < EPS and abs(pts[i]-pts[il]) < abs(pts[ir]-pts[il]))) {
                    nx = i;
                    break;
                }
            }

            if (nx != -1) {
                ir = nx;
            } else break;
        }

        add_edge(il, ir);

        while (1) {
            int nx = -1;
            bool is2 = false;

            for (int i: E[il]) {
                if (cross(pts[il], pts[i], pts[ir]) < -EPS and
                    (nx == -1 or inCircle(pts[il], pts[ir], pts[nx], pts[i]))) nx = i;
            }

            for (int i: E[ir]) {
                if (cross(pts[ir], pts[i], pts[il]) > EPS and
                    (nx == -1 or inCircle(pts[il], pts[ir], pts[nx], pts[i]))) nx = i, is2 = 1;
            }


            if (nx == -1) break;

            int a = il, b = ir;
            if (is2) swap(a, b);

            for (auto i: E[a]) {
                if (intersect(pts[a], pts[i], pts[b], pts[nx])) {
                    remove_edge(a, i);
                }
            }
            if (is2) {
                add_edge(il, nx);
                ir = nx;
            } else {
                add_edge(ir, nx);
                il = nx;
            }
        }
    }
} tri;
