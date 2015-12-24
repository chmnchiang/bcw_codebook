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
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
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

string nxt(string s)
{
	string s2 = "";
	for(auto c: s)
		s2.PB(c == '0' ? '1' : '0');
	reverse(ALL(s2));
	return s2 + s;
}

string calc(string s)
{
	reverse(ALL(s));
	int N = s.size();
	s[0] += 1;
	for(int i=0; i<N; i++)
	{
		if(s[i] > '9')
		{
			if(i == N-1) s.PB('0');
			s[i] -= 10;
			s[i+1] += 1;
		}
	}
	N = s.size();

	if(N%2 == 0)
	{
		int H = N / 2;
		while(1)
		{
			bool fail = false;
			for(int i=H-1; i>=0; i--)
			{
				if(s[i] == s[N-i-1])
				{
					s[i]++;
					while(s[i] > '9')
					{
						s[i] -= 10;
						i++;
						if(i >= N)
						{
							string geng = "";
							for(int j=0; j<N/2; j++)
								geng.PB('0');
							geng.PB('1');
							return nxt(geng);
						}
						s[i]++;
					}
					if(i >= H) return nxt(s.substr(H));
					for(int j=i-1; j>=0; j--)
						s[j] = (s[N-j-1] == '0' ? '1' : '0');
					fail = true;
					break;
				}
			}
			if(!fail) break;
		}

		return s;
	}
	else
	{
		string geng = "";
		for(int i=0; i<N/2; i++)
			geng.PB('0');
		geng.PB('1');
		return nxt(geng);
	}
}

int main() {
	IOS;
	FILEIO("anti");

	string s;
	while(cin>>s && s != "0")
	{
		string ans = calc(s);
		reverse(ALL(ans));
		cout<<ans<<endl;
	}

    return 0;
}
