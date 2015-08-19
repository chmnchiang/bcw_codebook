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
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

const int MX = 101010;
int N;
int A[MX];
bool us[MX][3], mem[MX][3];
vector<int> ans;

bool dp(int i, int f) {
    if (i == N+1) return true;
    if (us[i][f]) {
        return mem[i][f];
    }
    us[i][f] = true;
    if (f == 1) {
        if (dp(i+1, 1) and A[i] < i) return mem[i][f] = true;
        else if (dp(i+1, 2) and A[i] < i and 
                    (i == N or A[i] < A[i+1])) {
            return mem[i][f] = true;
        }
    } else if (f == 2) {
        if (dp(i+1, 1) and A[i] > i) return mem[i][f] = true;
        else if (dp(i+1, 2) and A[i] > i
                    and (i == N or A[i+1] > i+1)) {
            return mem[i][f] = true;
        }
    }
    return mem[i][f] = false;
}

void go(int i, int f) {
    if (i == N+1) return;
    ans.PB((i-1)*2 + f);
    if (f == 1) {
        if (dp(i+1, 1) and A[i] < i) return go(i+1, 1);
        else if (dp(i+1, 2) and A[i] < i and 
                    (i == N or A[i] < A[i+1])) {
            return go(i+1, 2);
        }
    } else if (f == 2) {
        if (dp(i+1, 1) and A[i] > i) return go(i+1, 1);
        else if (dp(i+1, 2) and A[i] > i
                    and (i == N or A[i+1] > i+1)) {
            return go(i+1, 2);
        }
    }
    return;
}

int main() {
    FILEIO("restore");

    cin >> N;
    for(int i=1; i<=N; i++) {
        cin >> A[i];
    }

    bool f1 = dp(1, 1), f2 = dp(1, 2);
    if (f1 or f2) {
        if (f1) go(1, 1);
        else go(1, 2);
        sort(ALL(ans));
        vector<int> z;
        int ida = 0;
        for (int i=1; i<=N+N; i++) {
            while (ida < N and ans[ida] < i) ida ++;
            if (ida >= N or ans[ida] != i) z.PB(i);
        }

        int idz = 0, idf = 0;
        for (int i=1; i<=N+N; i++) {
            if (ans[idf] == i){
                cout << i << ' ';
                idf ++;
            } else {
                cout << z[A[idz+1]-1] << ' ';
                idz ++;
            }
        }
        cout << endl;
    } else {
        cout << -1 << endl;
    }

  return 0;
}
