//bcw0x1bd2 {{{
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
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
	freopen(name".in", "r", stdin); \
freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

void RI() {}

template<typename... T>
void RI( int& head, T&... tail ) {
	scanf("%d",&head);
	RI(tail...);
}

mt19937 rng(0x5EED);
int randint(int lb, int ub) {
	return uniform_int_distribution<int>(lb, ub)(rng);
}
// Let's Fight! }}}

typedef pair<int,int> pii;

struct Monster{
	Monster () {}
	Monster (int _id, int _hp, int _x, int _lst){
		lst = _lst;
		id = _id;
		hp = _hp;
		x = _x;
	}
	int lst,id,hp,x;
};
map<int,pair<int,string>> ans;
int h;
char curMap[105];

int calc(){
	int ret = 0;
	vector<Monster> vec;
	for (int t=1; t<=500; t++){
		if (t > 10 && vec.empty()) break;
		for (auto &it : vec){
			// move
			int delay = 1;
			for (int i=0; i<10; i++){
				if (curMap[i] == 'S' && it.x - i < 5 && it.x >= i) delay++;
			}
			if (it.lst + delay == t){
				it.x++;
				it.lst = t;
			}
		}
		for (int i=0; i<(int)vec.size(); i++){
			if (vec[i].x >= 10){
				swap(vec[i],vec.back());
				vec.pop_back();
				i--;
			}
		}
		if (t <= 10)
			vec.PB(Monster(t,h,0,t));
		//attack
		for (int i=0; i<10; i++){
			if (curMap[i] == 'G'){
				int aid = -1;
				for (int j=0; j<(int)vec.size(); j++){
					if (i == vec[j].x){
						if (aid == -1 || vec[j].id < vec[aid].id)
							aid = j;
					}
				}
				if (aid != -1){
					vec[aid].hp -= 1;
					if (vec[aid].hp <= 0){
						ret++;
						swap(vec[aid],vec.back());
						vec.pop_back();
					}
				}
			} else if (curMap[i] == 'R'){
				if (t % 3 == 0){
					for (int j=0; j<(int)vec.size(); j++){
						if (vec[j].x == i){
							vec[j].hp -= 4;
							if (vec[j].hp <= 0){
								ret++;
								swap(vec[j],vec.back());
								vec.pop_back();
								j--;
							}
						}
					}
				}
			}
		}
	}
	return ret;
}
void DFS(int pos, int cost, int s){
	if (ans.count(10) && cost > ans[10].F){
		return ;
	}
	if (pos == 10){
		int k = calc();
		for (int i=1; i<=k; i++){
			if (!ans.count(i)){
				ans[i] = MP(cost,string(curMap));
			} else {
				string str = string(curMap);
				if (ans[i].F > cost || (ans[i].F == cost && ans[i].S > str)){
					ans[i] = MP(cost,str);
				}
			}
		}
		return ;
	}
	curMap[pos] = '.';
	DFS(pos+1,cost,s);
	curMap[pos] = 'G';
	DFS(pos+1,cost+3,s);
	curMap[pos] = 'R';
	DFS(pos+1,cost+10,s);
	curMap[pos] = 'S';
	DFS(pos+1,cost+5,s+1);
}

int main(){
	IOS;
	FILEIO("defend");
	for (h=1; h<=30; h++){
		ans.clear();
		DFS(0,0,0);
		int lstC = 0;
		vector<string> vec;
		for (int i=10; i>=1; i--){
			if (ans.count(i)){
				if (ans[i].F != lstC){
					char str[105];
					sprintf(str,"$%d -> kill %d with %s\\n", ans[i].F, i, ans[i].S.c_str());
					vec.PB(string(str));
				}
				lstC = ans[i].F;
			}
		}
		reverse(vec.begin(),vec.end());
		string s;
		for (auto it : vec)
			s = s + it;
		cout << "ans[" << h << "] = \"" << s << "\";" << endl;
	}
	return 0;
}

