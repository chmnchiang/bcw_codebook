#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define ALL(x) x.begin(),x.end()
#define IOS ios_base::sync_with_stdio(0);cin.tie(0)

typedef long long i64;
const int M = 258280327;
const int N = 354294;
const int Nh = 177147;
const int R = 105831709;
const int RR = 154163588; 
const int RN = 258279598;

int K, H;
i64 F[3][N], G[3][N];
i64 ans[N];
i64 temp[N];

void pre() {
    F[1][1] = 1;
    ans[1] = F[2][0] = F[2][1] = 1;
}

#define debug(a) for(int j=0; j<5; j++) { cout << a[j] << ' '; } cout << endl;
void fft(int n, i64 z, i64 *a, i64 *b) {
    if (n == 2) {
        a[0] = (b[0] + b[1]) % M;
        a[1] = (b[0] + b[1] * z) % M;
        return;
    }
    //if (n == 1) {
        //a[0] = b[0] % M;
        //return;
    //}

    int k = n / 3;
    for(int i=0; i<k; i++) {
        for(int j=0; j<3; j++) {
            temp[i+j*k] = b[i*3+j];
        }
    }
    
    for(int i=0; i<n; i++) {
        b[i] = temp[i];
    }
    
    i64 zzz = ((z*z)%M*z)%M;
    fft(k, zzz, a, b);
    fft(k, zzz, a+k, b+k);
    fft(k, zzz, a+k+k, b+k+k);

    i64 tz = 1;
    for(int i=0; i<n; i++) {
        int j = i%k;
        temp[i] = a[j];
        temp[i] += (a[k+j] * tz)%M; temp[i] %= M;
        temp[i] += ((a[k+k+j]*tz)%M * tz)%M; temp[i] %= M;
        tz = (tz*z)%M;
    }
    for(int i=0; i<n; i++) a[i] = temp[i];
    return;
}

int main() {
    freopen("dichromatic.in", "r", stdin);
    freopen("dichromatic.out", "w", stdout);
    pre();
    cin >> K >> H;
    for(int i=1; i<=H; i++) {
        //debug(F[2])
        fft(N, R, G[2], F[2]);
        //debug(G[2])
        for(int j=0; j<N; j++) {
            G[2][j] = G[2][j] * G[2][j];
            G[2][j] %= M;
        }
        fft(N, RR, F[0], G[2]);
        for(int j=Nh-1; j>0; j--) {
            F[2][j] = F[0][j] = (F[0][j-1] * RN)%M;
        }
        F[2][0] = F[0][0] = 0;
        for(int j=Nh; j<N; j++) F[0][j] = 0;
        //debug(F[0])

        fft(N, R, G[0], F[0]);
        for(int j=0; j<N; j++) {
            G[0][j] = G[0][j] * G[0][j];
            G[0][j] %= M;
        }
        fft(N, RR, F[1], G[0]);
        for(int j=Nh-1; j>0; j--) {
            F[1][j] = (F[1][j-1]*RN)%M;
        }
        for(int j=Nh; j<N; j++) F[1][j] = 0;
        F[1][0] = 0;
        //debug(F[1])

        for(int j=0; j<Nh; j++) {
            F[2][j] += F[1][j]; F[2][j] %= M;
            ans[j] += F[2][j]; ans[j] %= M;
        }
        for(int j=Nh; j<N; j++) F[2][j] = 0;
        //debug(F[2])
        //cout << 123 << endl;
    }

    for(int i=0; i<K; i++) {
        int t; cin >> t;
        cout << ans[t] << ' ';
    }
    cout << endl;

	return 0;
}

