struct Key {
	int first,second;
	Key () {}
	Key (int _x, int _y) : first(_x),  second(_y) {}
	bool operator == (const Key &b) const {
		return tie(F,S) == tie(b.F,b.S);
	}
};
struct KeyHasher {
	size_t operator()(const Key& k) const {
		return k.first + k.second*100000;
	}
};

typedef unordered_map<Key,int,KeyHasher> map_t;

int main(int argc, char** argv){
	map_t mp;
	for (int i=0; i<10; i++)
		mp[Key(i,0)] = i+1;
	for (int i=0; i<10; i++)
		printf("%d\n", mp[Key(i,0)]);

	return 0;
}

