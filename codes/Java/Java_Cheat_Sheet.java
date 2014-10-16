/* Compile: javac %
 * Run: java [Class name] */
import java.util.*;
import java.lang.*;
import java.math.*;

class Main {
	public static void main (String[] args) {
		System.out.print(1);
		System.out.print(2);
		System.out.println("Hello World");
		System.out.printf("%.2f", 0.12345);
		
		Scanner	sc = new Scanner(System.in);
		System.out.println(sc.nextLine()); //gets()
		System.out.println(sc.next()); //scanf("%s")
		System.out.println(sc.nextInt());
		System.out.println(sc.nextDouble());
		while(sc.hasNext()) { //EOF
			int a = sc.nextInt();
			System.out.println(a);
		}

		int[] a = {1,2,3};
		int[][] b = {{1,2},{3,4,5}};
		double[] c = new double[90];
		System.out.print(b[0][1]);
		System.out.print(b[1][2]);

		int[] d = {5,2,1,3,4};
		Integer[] e = {6,3,4,1,2};
		Arrays.sort(d);
		Arrays.sort(e, new MyCom());
		for(int i=0; i<d.length; i++) {
			System.out.print(d[i]);
		}
		for(int i=0; i<e.length; i++) {
			System.out.print(e[i]);
		}

		Set<String> s = new HashSet<String>(); //or TreeSet
		s.add("123");
		s.add("234");
		System.out.println(s);
		System.out.println(s.contains("123"));
		Map<String, Integer> m = new TreeMap<String, Integer>();
		m.put("haha", 123);
		m.put("hehe", 234);
		System.out.println(m);

		BigInteger b1 = new BigInteger("-1231237182379123712");
		BigInteger b2 = BigInteger.valueOf(234);

		System.out.println(b1.add(b2));
		System.out.println(b1.mod(b2));

		int z = Integer.parseInt("-123");
		System.out.println(z);

		System.out.println(Math.PI);
		System.out.println(Math.sin(1));
	}

	static class MyCom implements Comparator<Integer> {
		public int compare(Integer i1, Integer i2) {
			return i2 - i1;
		}
	}
}
