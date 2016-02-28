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
#define endl "\n"
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
#define REP(i,x) for(int i=0;i<(x);i++)
#define REP1(i,a,b) for (int i=(a);i<=(b);i++)
// Let's Fight!
const int MX = 101010;


struct Person {
	int d, m, y;
	int dep, id;
	string name;
	bool leave;
	int gid;

	bool operator < (const Person he) const {
		return make_tuple(y, m, d, dep, id) > 
			   make_tuple(he.y, he.m, he.d, he.dep, he.id) ;
	}

	friend ostream& operator << (ostream &o, Person &p) {
		o << p.name;
		return o;
	}
};

vector<Person> people;
vector<int> depPerId[MX];

typedef priority_queue<Person> PQ;
int N;
PQ depPq[MX], offPq;
map<int, int> depId;
int totDep;

int getDep(int a) {
	if (depId.find(a) == depId.end()) {
		depId[a] = totDep++;
	}
	return depId[a];
}

string prtOff() {
	while (offPq.size()) {
		auto p = offPq.top();
		int gid = p.gid;
		if (people[gid].leave) {
			offPq.pop();
		} else {
			return p.name;
		}
	}
	return "Vacant";
}

string prtDep(int dep) {
	auto &pq = depPq[dep];
	while (pq.size()) {
		auto p = pq.top();
		int gid = p.gid;
		if (people[gid].leave) {
			pq.pop();
		} else {
			return p.name;
		}
	}
	return "Vacant";
}

void in() {
	int dep; cin >> dep;
	dep = getDep(dep);
	string name; cin >> name;
	string date; cin >> date;
#define MAG(a) (date[a] - '0')
	int d = MAG(0)*10+MAG(1);
	int m = MAG(3)*10+MAG(4);
	int y = MAG(6)*1000+MAG(7)*100+MAG(8)*10+MAG(9);

	int gid = people.size();
	Person p = {d, m, y, dep, (int)depPerId[dep].size(), name, false, gid};
	depPerId[dep].PB(gid);
	//cout << "+ " << name << ' ' << gid << endl;
	people.PB(p);
	depPq[dep].push(p);
	offPq.push(p);

	cout << prtOff() << " " << prtDep(dep) << endl;
}

void out() {
	int dep, id;
	cin >> dep >> id;
	id--;
	dep = getDep(dep);
	int gid = depPerId[dep][id];
//	cout << depPerId[dep] << endl;
//	cout << gid << endl;
	people[gid].leave = true;
//	cout << people[gid].name << endl;
//	cout << people << endl;
	
	cout << prtOff() << " " << prtDep(dep) << endl;
}

int main() {
	IOS;

	cin >> N;
	for (int i=0; i<N; i++) {
		int t; cin >> t;
		if (t == 1) {
			in();
		} else if (t == -1) {
			out();
		}
	}
	
	return 0;
}

