import java.io.*;
import java.util.*;
import java.math.*;

class Main {
	public static final BigInteger TWO = BigInteger.valueOf(2);
	
	public static boolean isPerfectSquare(BigInteger x) {
		BigInteger l = BigInteger.ZERO, r = x;
        while (l.compareTo(r) < 0) {
            BigInteger mid = l.add(r).divide(TWO);
        	int midv = mid.multiply(mid).compareTo(x);
            if (midv == 0) return true;
            if (midv < 0) l = mid.add(BigInteger.ONE);
            else r = mid.subtract(BigInteger.ONE);
        }
        return l.multiply(l).compareTo(x) == 0;
	}
	
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		int T = cin.nextInt();
		for (int t = 0; t < T; ++t) {
			BigInteger n = cin.nextBigInteger();
			boolean a = isPerfectSquare(n);
			boolean b;
			if (n.mod(TWO).compareTo(BigInteger.ZERO) == 0) {
				b = isPerfectSquare(n.divide(TWO)) && isPerfectSquare(n.subtract(BigInteger.ONE));
			} else {
				b = isPerfectSquare(n) && isPerfectSquare(n.subtract(BigInteger.ONE).divide(TWO));
			}
			if (a && b) System.out.println("Arena of Valor");
			else if (a && !b) System.out.println("Hearth Stone");
			else if (!a && b) System.out.println("Clash Royale");
			else System.out.println("League of Legends");
		}
	}
}
