const int MAX = 300;
const double EPS = 1e-8;

double mat[MAX][MAX];
void Gauss(int n) {
	for(int i=0; i<n; i++) {
		bool ok = 0;
		for(int j=i; j<n; j++) {
			if(fabs(mat[j][i]) > EPS) {
				swap(mat[j], mat[i]);
				ok = 1;
				break;
			}
		}
		if(!ok) continue;

		double fs = mat[i][i];
		for(int j=i+1; j<n; j++) {
			double r = mat[j][i] / fs;
			for(int k=i; k<n; k++) {
				mat[j][k] -= mat[i][k] * r;
			}
		}
	}
}

