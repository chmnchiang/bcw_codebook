#include<bits/stdc++.h>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

const int MAXN = 2666;

int W, H;
vector<string> vstr;
int arr[MAXN][MAXN];
int xa[MAXN], ya[MAXN], xb[MAXN], yb[MAXN];
int cnt;

int main()
{
  freopen("gridbaglayout.in", "r", stdin);
  freopen("gridbaglayout.out", "w", stdout);

  IOS;

  string tmps;
  while(getline(cin, tmps)) vstr.PB(tmps);

  for(int i=0; i<MAXN; i++)
    for(int j=0; j<MAXN; j++)
      arr[i][j] = -1;

  int pos = 2;
  int x = -1, y = -1, wid = 1, hei = 1;
  bool first = true;
  int lastrow = -1, rmcol = -1;
  while(pos < (int)vstr.size())
  {
    while(1)
    {
      string &s = vstr[pos];
      pos++;

      if(s[0] == 'c')
        break;
      else
      {
        char c = s[8];
        size_t eqpos = s.find('=');
        int val = -1;
        string ns = s.substr(eqpos + 2);
        ns = ns.substr(0, ns.size()-1);
        if(ns[0] != 'G')
          val = atoi(ns.c_str());
        if(c == 'x') x = val;
        else if(c == 'y') y = val;
        else if(c == 'w') wid = val;
        else if(c == 'h') hei = val;
      }
    }

    int row, col;
    if(x == -1 && y == -1)
    {
      if(first)
      {
        row = lastrow, col = -1;
        while(col == -1)
        {
          row++;
          for(int i=0; i<MAXN; i++)
          {
            if(arr[row][i] == -1)
            {
              col = i;
              break;
            }
          }
        }
      }
      else
      {
        row = lastrow, col = rmcol + 1;
        while(arr[row][col] != -1) col++;
      }
    }
    else if(x == -1 && y != -1)
    {
      row = y, col = 0;
      while(arr[row][col] != -1) col++;
    }
    else if(x != -1 && y == -1)
    {
      if(first)
      {
        row = lastrow + 1, col = x;
        while(arr[row][col] != -1) row++;
      }
      else
      {
        row = lastrow;
        col = x;
      }
    }
    else
    {
      row = y;
      col = x;
    }

    first = false;

    int xl = col + wid, yl = row + hei;
    if(wid == -1)
    {
      W = max(W, col+1);
      xl = MAXN;
      first = true;
    }
    else
    {
      W = max(W, xl);
    }
    if(hei == -1)
    {
      H = max(H, row+1);
      yl = MAXN;
    }
    else
    {
      H = max(H, yl);
    }

    for(int i=row; i<yl; i++)
      for(int j=col; j<xl; j++)
        arr[i][j] = cnt;

    xa[cnt] = col;
    ya[cnt] = row;
    xb[cnt] = xl - 1;
    yb[cnt] = yl - 1;
    cnt++;

    lastrow = row;
    rmcol = xl - 1;
  }

  for(int i=0; i<cnt; i++)
  {
    xb[i] = min(xb[i], W-1);
    yb[i] = min(yb[i], H-1);
  }

  cout<<H<<" "<<W<<endl;
  for(int i=0; i<cnt; i++)
    cout<<ya[i]<<" "<<xa[i]<<" "<<yb[i]<<" "<<xb[i]<<endl;

  return 0;
}
