#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define F first
#define S second
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
template<typename A, typename B>
ostream& operator <<(ostream &s, const pair<A,B> &p) {
  return s<<"("<<p.first<<","<<p.second<<")";
}
template<typename T>
ostream& operator <<(ostream &s, const vector<T> &c) {
  s<<"[ ";
  for (auto it : c) s << it << " ";
  s<<"]";
  return s;
}
// Let's Fight!

const int MAXN = 514;
const double PI = acos(-1);

int N;
int arr[MAXN];

double get_angle(int lb, int rb, int piv, double R, bool inv)
{
  double angle = 0;
  for(int i=lb; i<rb; i++)
  {
    double a = 2 * asin(arr[i] / (2 * R));
    if(i == piv && inv)
      a = 2 * PI - a;
    angle += a;
  }
  return angle;
}

double get_area(int lb, int rb, int piv)
{
  int tot_len = 0;
  for(int i=lb; i<rb; i++)
    if(i != piv)
      tot_len += arr[i];
  if(tot_len <= arr[piv])
    return 0;

  double crit_angle = get_angle(lb, rb, piv, arr[piv] / 2., false);
  bool inv = (crit_angle < 2 * PI);

  double lR = arr[piv] / 2., rR = 1e9;
  for(int i=0; i<80; i++)
  {
    double mR = (lR + rR) / 2;
    double total_angle = get_angle(lb, rb, piv, mR, inv);
    if(inv ^ (total_angle >= 2 * PI))
      lR = mR;
    else
      rR = mR;
  }

  double area = 0;
  for(int i=lb; i<rb; i++)
  {
    double h = sqrt(lR * lR - arr[i] * arr[i] / 4.);
    double a = arr[i] * h / 2.;
    if(i == piv && inv)
      a = -a;
    area += a;
  }

  //for(int i=lb; i<rb; i++) cout<<arr[i]<<" ";
  //cout<<" INV "<<inv<<" RADIUS "<<lR<<" AREA "<<area<<endl;

  return area;
}

double calc(int lb, int rb)
{
  if(lb == rb) return 0;
  int piv = lb;
  for(int i=lb; i<rb; i++)
    if(arr[i] > arr[piv])
      piv = i;

  double ans = get_area(lb, rb, piv);
  ans = max(ans, calc(lb, piv) + calc(piv+1, rb));

  return ans;
}

int main() {
  IOS;

  int t = 0;
  while(cin>>N && N)
  {
    t++;
    for(int i=0; i<N; i++)
      cin>>arr[i];

    double ans = calc(0, N);
    cout<<"Case "<<t<<": "<<fixed<<setprecision(10)<<ans<<endl;
  }

  return 0;
}
