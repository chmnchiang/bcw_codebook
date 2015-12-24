#include<bits/stdc++.h>

using namespace std;

int N, M;


void meteor(int a, int b, int k){

	//cout << a << ' ' << b << ' ' << k << endl;

	if( a == N ){
		cout << "y" << b+k+1;
		return ;
	}else if( b == M ){
		cout << "x" << a+k+1;
		return ;
	}
	if( k == 0 ){
		if( a != 0 || b != 0 ) cout << '(' ;

		cout << "x" << a+1 << "&y" << b+1;

		if( a != 0 || b != 0 ) cout << ')' ;
		return;
	}

	if( a != 0 || b != 0 ) cout << '(' ;

	meteor( a+1, b , k-1 );
	cout << '|' ; 
	meteor( a, b+1 , k-1 );
		
	if( a != 0 || b != 0 ) cout << ')' ;

}

int main(){

	freopen("merge.in", "r", stdin);
	freopen("merge.out", "w", stdout);

	cin >> N >> M ;

	for(int i=0; i<M+N; i++){

		for(int j = 0; j <= i; j++){

			int xx = j, yy = i - j;

			if( j != 0 ) cout << '|' ;

			cout << '(';
			if( xx >= N ){
				cout << 'y' << yy + 1; 
			}else if ( yy >= M ){
				cout << 'x' << xx + 1; 
			}else{
				cout << 'x' << xx + 1 << "&y" << yy + 1 ;
			}

			cout << ')';
		}
		cout << endl;
	}

}
