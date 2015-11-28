/*
Lucas’ Theorem:
	For non-negative integer n,m and prime P,
	C(m,n) mod P = C(m/M,n/M) * C(m%M,n%M) mod P
	= mult_i ( C(m_i,n_i) )
	where m_i is the i-th digit of m in base P.
--
Sum of Two Squares Thm (Legendre)
	For a given positive integer N, let
	D1 = (# of positive integers d dividing N that d=1(mod 4))
	D3 = (# of positive integers d dividing N that d=3(mod 4))
	then N can be written as a sum of two squares in exactly
	R(N) = 4(D1-D3) ways.
--
Difference of D1-D3 Thm
	let N = 2^t * [p1^e1 * ... * pr^er] * [q1^f1 * ... * qs^fs]
							  <- mod 4 = 1 prime ->   <- mod 4 = 3 prime ->
	then D1 - D3 = (e1+1)(e2+1)...(er+1) ... if (fi)s all even
									0 ... if any fi is odd
*/
