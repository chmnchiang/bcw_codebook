const int MAX = 1000;
int len;
char ip[MAX];
char op[MAX*2];
int zv[MAX*2];

int main(){

	cin >> ip;
	len = strlen(ip);

	int l2 = len*2 - 1;
	for(int i=0; i<l2; i++){
		if(i&1) op[i] = '@';
		else op[i] = ip[i/2];
	}
	int l=0, r=0;
	zv[0] = 1;

	for(int i=1; i<l2; i++){
		if( i > r ){
			l = r = i;
			while( l>0 && r<l2-1 && op[l-1] == op[r+1] ){
				l --;
				r ++;
			}
			zv[i] = (r-l+1);
		}else{
			int md = (l+r)/2;
			int j = md + md - i;
			zv[i] = zv[j];
			int q = zv[i] / 2;
			int nr = i + q;
			if( nr == r ){
				l = i + i - r;

				while( l>0 && r<l2-1 && op[l-1] == op[r+1] ){
					l --;
					r ++;
				}
				zv[i] = r - l + 1;
			}else if( nr > r ){
				zv[i] = (r - i) * 2 + 1;
			}
		}
	}

	return 0;
}

