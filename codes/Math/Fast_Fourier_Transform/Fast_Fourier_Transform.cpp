typedef complex<double> cplx;
const int PI = acos(-1);
const cplx I(0, 1);
void fft(int n, cplx a[]) {
	double theta = 2 * PI / n;
	for (int m = n; m >= 2; m >>= 1) {
		int mh = m >> 1;
		for (int i = 0; i < mh; i++) {
			cplx w = exp(i*theta*I);
			for (int j = i; j < n; j += m) {
				int k = j + mh;
				cplx x = a[j] - a[k];
				a[j] += a[k];
				a[k] = w * x;
			}
		}
		theta *= 2;
	}
	int i = 0;
	for (int j = 1; j < n - 1; j++) {
		for (int k = n >> 1; k > (i ^= k); k >>= 1);
		if (j < i) swap(a[i], a[j]);
	}
}
