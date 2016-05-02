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

typedef double ld;

const int MAXW = 20;
const int MAXH = 10005;
const ld EPS = 1E-11;

int W, H;
ld U, D, L, R;
string arr[MAXH];

struct Vec
{
  ld v[MAXW];
  Vec(){FZ(v);}
};

struct Mat
{
  ld v[MAXW][MAXW];
  Mat(){FZ(v);}
};

ld operator*(const Vec &a, const Vec &b)
{
  ld res = 0;
  for(int i=0; i<W; i++)
    res += a.v[i] * b.v[i];
  return res;
}

Vec operator*(const Mat &m, const Vec &b)
{
  Vec vec;
  for(int i=0; i<W; i++)
  {
    vec.v[i] = 0;
    for(int j=0; j<W; j++)
      vec.v[i] += m.v[i][j] * b.v[j];
  }
  return vec;
}

Vec operator+(const Vec &a, const Vec &b)
{
  Vec vec;
  for(int i=0; i<W; i++)
    vec.v[i] = a.v[i] + b.v[i];
  return vec;
}

Mat operator*(const Mat &a, const Mat &b)
{
  Mat mat;
  for(int i=0; i<W; i++)
  {
    for(int j=0; j<W; j++)
    {
      mat.v[i][j] = 0;
      for(int k=0; k<W; k++)
        mat.v[i][j] += a.v[i][k] * b.v[k][j];
    }
  }
  return mat;
}

Mat operator+(const Mat &a, const Mat &b)
{
  Mat mat;
  for(int i=0; i<W; i++)
    for(int j=0; j<W; j++)
      mat.v[i][j] = a.v[i][j] + b.v[i][j];
  return mat;
}

Mat operator-(const Mat &a, const Mat &b)
{
  Mat mat;
  for(int i=0; i<W; i++)
    for(int j=0; j<W; j++)
      mat.v[i][j] = a.v[i][j] - b.v[i][j];
  return mat;
}

struct Layer
{
  Mat Ru, Tu, Rd, Td, A;
};

Mat pinv(Mat m);

Mat I;
Layer slay[MAXH], dlay[MAXH];
ld ans[MAXH][MAXW];
bool used[MAXW];

Mat pinv(Mat m)
{
  Mat res = I;

  FZ(used);
  for(int i=0; i<W; i++)
  {
    int piv = -1;
    for(int j=0; j<W; j++)
    {
      if(used[j]) continue;
      if(abs(m.v[j][i]) > EPS)
      {
        piv = j;
        break;
      }
    }
    if(piv == -1)
      continue;
    used[i] = true;
    swap(m.v[piv], m.v[i]);
    swap(res.v[piv], res.v[i]);

    ld rat = m.v[i][i];
    for(int j=0; j<W; j++)
    {
      m.v[i][j] /= rat;
      res.v[i][j] /= rat;
    }

    for(int j=0; j<W; j++)
    {
      if(j == i) continue;
      rat = m.v[j][i];
      for(int k=0; k<W; k++)
      {
        m.v[j][k] -= rat * m.v[i][k];
        res.v[j][k] -= rat * res.v[i][k];
      }
    }
  }

  for(int i=0; i<W; i++)
  {
    if(used[i]) continue;
    for(int j=0; j<W; j++)
      res.v[i][j] = 0;
  }

  return res;
}

Layer gen_layer(string s)
{
  Layer lay;
  Mat mat = I;
  for(int i=0; i<W; i++)
  {
    if(i==W-1 or s[i+1]=='X')
    {
      if(s[i] == '.')
        mat.v[i][i] -= R;
    }
    else if(s[i+1] == '.')
      mat.v[i][i+1] -= L;

    if(i==0 or s[i-1]=='X')
    {
      if(s[i] == '.')
        mat.v[i][i] -= L;
    }
    else if(s[i-1] == '.')
      mat.v[i][i-1] -= R;
  }

  Mat p = pinv(mat);

  for(int i=0; i<W; i++)
  {
    for(int j=0; j<W; j++)
    {
      if(s[i] == 'X')
      {
        lay.Ru.v[i][j] = lay.Rd.v[i][j] = (i == j);
        lay.Tu.v[i][j] = lay.Td.v[i][j] = lay.A.v[i][j] = 0;
      }
      else if(s[i] == 'T')
      {
        lay.Ru.v[i][j] = lay.Rd.v[i][j] = lay.Tu.v[i][j] = lay.Td.v[i][j] = 0;
        lay.A.v[i][j] = p.v[i][j];
      }
      else
      {
        lay.Ru.v[i][j] = lay.Td.v[i][j] = U * p.v[i][j];
        lay.Rd.v[i][j] = lay.Tu.v[i][j] = D * p.v[i][j];
      }
    }
  }

  return lay;
}

Layer merge_layer(const Layer &l1, const Layer &l2)
{
  Layer lay;

  Mat rr = pinv(I - l1.Rd * l2.Ru);

  lay.Ru = l1.Ru + l1.Td * l2.Ru * rr * l1.Tu;
  //lay.Tu = l2.Tu * rr * l1.Tu;
  //lay.Rd = l2.Rd + l2.Tu * rr * l1.Rd * l2.Td;
  //lay.Td = l1.Td * (I + l2.Ru * rr * l1.Rd) * l2.Td;

  return lay;
}

void calc()
{
  for(int i=0; i<W; i++)
    for(int j=0; j<W; j++)
      I.v[i][j] = (i == j);

  for(int i=0; i<H; i++)
    slay[i] = gen_layer(arr[i]);

  dlay[H].Ru = I;
  for(int i=H-1; i>=0; i--)
    dlay[i] = merge_layer(slay[i], dlay[i+1]);

  int num = 0;
  Vec vec;
  for(int i=0; i<W; i++)
  {
    if(arr[0][i] == '.')
    {
      num++;
      vec.v[i] = 1;
    }
  }
  for(int i=0; i<W; i++)
    vec.v[i] /= num;

  Mat mx = I - dlay[0].Ru;
  Mat totr = pinv(mx);
  vec = totr * vec;

  for(int i=0; i<H; i++)
  {
    Vec nvec = pinv(I - slay[i].Rd * dlay[i+1].Ru) * slay[i].Tu * vec;
    Vec res = slay[i].A * (vec + dlay[i+1].Ru * nvec);
    for(int j=0; j<W; j++)
      ans[i][j] = res.v[j];
    vec = nvec;
  }

  cout<<fixed<<setprecision(10);
  for(int i=0; i<H; i++)
    for(int j=0; j<W; j++)
      if(arr[i][j] == 'T')
        cout<<ans[i][j]<<"\n";
}

int main() {
  IOS;
  cin>>W>>H>>U>>D>>L>>R;
  U *= 0.01;
  D *= 0.01;
  L *= 0.01;
  R *= 0.01;
  for(int i=0; i<H; i++)
    cin>>arr[i];

  calc();

  return 0;
}
