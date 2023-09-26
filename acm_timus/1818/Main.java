import java.util.*;
import java.io.*;
import java.math.*;
import java.math.BigInteger;


public class Main  {
    static final int maxSize = 2000 + 1;
    private static class myPair  {
        public BigInteger first;
        public BigInteger second;
        public myPair()  {
            first = BigInteger.ZERO;
            second = BigInteger.ZERO;
        }
        public myPair(BigInteger _first, BigInteger _second)  {
            first = _first;
            second = _second;
        }
    }

    private static myPair euclid(BigInteger a, BigInteger b)  {
        if(b == BigInteger.ZERO)  {
            return new myPair(BigInteger.ONE, BigInteger.ZERO);
        }
        BigInteger x, y;
        BigInteger remainder = a.mod(b);
        BigInteger quotient = a.divide(b);

        myPair rest = euclid(b, remainder);

        x = rest.second;
        y = rest.first;
        y = y.subtract(quotient.multiply(x));

        return new myPair(x, y);
    }
    public static void main(String[] args) throws FileNotFoundException, IOException {

        final var fin = new BufferedReader(new InputStreamReader(System.in));

        BigInteger n, n1;
        BigInteger[] a = new BigInteger[maxSize];
        BigInteger[] pows = new BigInteger[maxSize];
        BigInteger[] powsLess = new BigInteger[maxSize];

        pows[0] = BigInteger.ONE;
        powsLess[0] = BigInteger.ONE;

        n = nextLine(fin).nextBigInteger();
        n1 = n.subtract(BigInteger.ONE);
        int nInt = n.intValue();

        for(int i = 1;i <= nInt;i++)  {
            a[i] = fin.nextBigInteger();
        }

        for(int i = 1;i <= nInt;i++)  {
            pows[i] = pows[i - 1].multiply(n);
            powsLess[i] = powsLess[i - 1].multiply(n1);
        }
        BigInteger S = new BigInteger("0");
        for(int i = 1;i <= nInt;i++)  {
            S = S.add(a[i].multiply(pows[i - 1].multiply(powsLess[nInt + 1 - i])));
        }

        BigInteger A, B;
        A = powsLess[nInt];
        B = pows[nInt];

        myPair P = euclid(B, A);
        BigInteger B1 = P.first;

        BigInteger sHelper = S;
        sHelper = S.mod(A);
        sHelper = A.subtract(sHelper);

        BigInteger firstGuy = sHelper.multiply(B1);
        firstGuy = firstGuy.mod(A);
        firstGuy = firstGuy.add(A);
        firstGuy = firstGuy.mod(A);

        BigInteger lastGuy;

        lastGuy = firstGuy.multiply(pows[nInt]);
        lastGuy = lastGuy.add(S);
        lastGuy = lastGuy.divide(powsLess[nInt]);

        if(lastGuy == BigInteger.ZERO)
            lastGuy = pows[nInt];

        fout.println(lastGuy);

        fout.flush();

        if(DEBUG_MODE)  {
            fin.close();
            fout.close();
            ferr.close();
        }
    }
}