#include<bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int MAX = 514;

int M, N, H;
int A[MAX], B[MAX];
char ans[MAX][MAX];
int us[MAX];

int main(){

	freopen("chip.in", "r", stdin);
	freopen("chip.out", "w", stdout);

	cin >> M >> N >> H ;

	for( int i = 0; i < M; i++)
		cin >> A[i];
	
	for( int i = 0; i < N; i++)
		cin >> B[i];

	int nus = 0;

	for( int i = 0; i < M; i++){
		
		int t = N - A[i] - nus;
		//cout << nus << endl;
		if( t < 0 ) goto jiz;

		vector<pii> arr;

		for(int j = 0; j < N; j++){

			if( us[j] > 0 || B[j] <= 0 ) continue;

			arr.push_back(make_pair(B[j], j));
		}

		if( (int)arr.size() < t ) goto jiz;

		sort( arr.begin(), arr.end(), greater<pii>() );

		for( int j = 0 ; j < t ; j++ ){
			int t = arr[j].second;
			us[t] = H;
			B[t] --;
		}

		nus = 0;
		
		for( int j = 0 ; j < N; j++ ){
			if( us[j] == 0 ) ans[i][j] = '*';
			else if( us[j] == 1 || us[j] == H ) ans[i][j] = '+';
			else ans[i][j] = '|';

			if( us[j] > 0 ) {
				us[j] --;
				if( us[j] > 0 ) nus ++;
			}
		}
	}

	for(int i = 0; i < N; i++){
		//cout << B[i] << ' ';
		if( B[i] != 0 ) goto jiz;
	}

	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
			cout << ans[i][j] ;
		}
		cout << endl;
	}

	return 0;

jiz:
	cout << "inconsistent" << endl;

}
