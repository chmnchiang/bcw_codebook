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
#define REP(i,n) for (int i=0; i<(n); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)
// Let's Fight!

#define assert(x) while(not (x));

struct Author {
	vector<string> vec;

	bool operator < (const Author &he) const {
		return vec < he.vec;
	}

	friend ostream& operator << (ostream &o, Author &a) {
		assert(SZ(a.vec));
		o << a.vec[0];
		int sz = SZ(a.vec);
		for (int i=1; i<sz; i++) {
			o << " " << a.vec[i][0] << ".";
		}
		return o;
	}
};

int ssstoi(string s) {
	int t = 0;
	for (int i=0; i<(int)s.length(); i++) {
		t *= 10;
		t += s[i] - '0';
	}
	return t;
}

struct Ref {
	string type;
	vector<Author> authors;
	string title, journal, publisher, year;
	string volume, number, pages;
	bool page_is_range;

	void print() {
		if (type == "article") {
			print_as_article();
		} else {
			print_as_book();
		}
	}

	void print_as_article() {
		print_authors();
		cout << " ";
		cout << title;
		cout << " // ";
		cout << journal;
		if (volume != "") {
			cout << ", " << volume;
		}
		if (number != "") {
			cout << " " << "(" << number << ")";
		}
		cout << " -- " << year;
		if (pages != "") {
			cout << " -- ";
			if (page_is_range) {
				cout << "pp. " << pages;
			} else {
				cout << "p. " << pages;
			}
		}
	}

	void print_authors() {
		cout << authors[0];
		int sz = SZ(authors);
		for (int i=1; i<sz; i++) {
			 cout << ", " << authors[i];
		}
	}

	void print_as_book() {
		print_authors();
		cout << " ";
		cout << title;
		if (volume != "") {
			cout << ", Vol. " << volume;
		}
		cout << " -- ";
		cout << publisher << ", " << year;
	}

	bool operator < (const Ref &he) const {
		
		return make_tuple(authors, title, ssstoi(volume)) < make_tuple(he.authors, he.title, ssstoi(he.volume));
	}
};


char c;
string next_token() {
	if (not c) {
		return "";
	}

	while (c == '\n' or c == '\t' or c == ' ') {
		c = getchar();
	}
	if (c == '@' or c == '{' or c == '}' or c == '=' or c == ',') {
		char tc = c;
		c = getchar();
		return string("") + tc;
	}

	if (c == '"') {
		c = getchar();
		string res = "";
		while (c != '"') {
			res += c;
			c = getchar();
		}
		c = getchar();
		return res;
	}

	string res = "";
	while (isalnum(c) or c == '_' or c == '-') {
		res += c;
		c = getchar();
	}
	return res;
}

vector<Ref> refs;
bool parse() {
	string s = next_token();
	if (s == "") {
		return false;
	}
	assert (s == "@");

	Ref ref;
	s = next_token();
	ref.type = s;
#define NT() { s = next_token(); /* cout << s << endl; usleep(30000); */ }
	NT();
	assert(s == "{");

	NT();
	while (true) {
		
#define MAG(_n) \
		if (s == #_n) { \
			NT(); \
			assert(s == "="); \
			NT(); \
			ref._n = s; \
		}\

		MAG(title);
		MAG(journal);
		MAG(year);
		MAG(volume);
		MAG(number);
		MAG(publisher);

		if (s == "author") {
			NT(); // =
			NT();
			istringstream is(s);
			string ts;
			vector<string> v;
			while (is >> ts) {
				if (ts == "and") {
					Author au;

					au.vec.PB(v.back());
					v.pop_back();
					for (auto x: v) {
						au.vec.PB(x);
					}

					ref.authors.PB(au);
					v.clear();
				} else {
					v.PB(ts);
				}
			}

			{
				Author au;

				au.vec.PB(v.back());
				v.pop_back();
				for (auto x: v) {
					au.vec.PB(x);
				}

				ref.authors.PB(au);
			}
			sort(ALL(ref.authors));
			//cout << ref.authors << endl;
		}

		if (s == "pages") {
			NT();
			NT();
			bool is_range = false;
			for (auto x: s) {
				if (x == '-') {
					is_range = true;
					break;
				}
			}

			ref.pages = s;
			ref.page_is_range = is_range;
			//cout << "R = " << is_range << endl;
		}

		//cout << "Parse fin" << endl;

		NT();
		if (s == "}") {
			refs.PB(ref);
			return true;
		}
		else NT();
	}

	return true;
}

int main() {
	FILEIO("bibtex");

	c = getchar();
	while (parse());

	sort(ALL(refs));
	//cout << SZ(refs[0].authors) << endl;
	//cout << (refs[0] < refs[2]) << endl;

	for (int i=0; i<SZ(refs); i++) {
		cout << "[" << i+1 << "] ";
		refs[i].print();
		cout << "\n";
	}


    return 0;
}
