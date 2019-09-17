import java.util.Scanner;

public class Lab1_E {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        long[] eve = new long[2];
        long[] neko = new long[2];
        long[] move = new long[2];
        eve[0] = in.nextLong();
        eve[1] = in.nextLong();
        neko[0] = in.nextLong();
        neko[1] = in.nextLong();
        in.nextLine();
        in.nextLine();
        String sequence = in.nextLine();
        for (char c : sequence.toCharArray()) {
            switch (c) {
                case 'U':
                    ++move[1];
                    break;
                case 'D':
                    --move[1];
                    break;
                case 'L':
                    --move[0];
                    break;
                case 'R':
                    ++move[0];
                    break;
            }
        }
        long distance = Math.abs(neko[0] - eve[0]) + Math.abs(neko[1] - eve[1]);
        long left = 0;
        long right =200000000000001L;   // After I change right to this number , AC. But why?
        long mid = left + (right - left) / 2;
        long[] neko_t = neko.clone();
        while (left < right - 1) {
            mid = left + (right - left) / 2;
            long time = mid / (long)sequence.length();
            neko_t[0] = neko[0] + time * move[0];
            neko_t[1] = neko[1] + time * move[1];
            long t = mid % (long)sequence.length();
            for (int i = 0; i < t; ++i) {
                switch (sequence.charAt(i)) {
                    case 'U':
                        ++neko_t[1];
                        break;
                    case 'D':
                        --neko_t[1];
                        break;
                    case 'L':
                        --neko_t[0];
                        break;
                    case 'R':
                        ++neko_t[0];
                        break;
                }
            }
            distance = Math.abs(neko_t[0] - eve[0]) + Math.abs(neko_t[1] - eve[1]);
            if (distance <= mid)
                right = mid;
            else
                left = mid;
        }
//        distance = Math.abs(neko_t[0] - eve[0]) + Math.abs(neko_t[1] - eve[1]);
        long[] lmr = new long[3];
        lmr[0] = left;
        lmr[1] = mid;
        lmr[2] = right;
        for (long l : lmr) {
            long time = l / (long)sequence.length();
            neko_t[0] = neko[0] + time * move[0];
            neko_t[1] = neko[1] + time * move[1];
            long t = l % (long)sequence.length();
            for (int i = 0; i < t; ++i) {
                switch (sequence.charAt(i)) {
                    case 'U':
                        ++neko_t[1];
                        break;
                    case 'D':
                        --neko_t[1];
                        break;
                    case 'L':
                        --neko_t[0];
                        break;
                    case 'R':
                        ++neko_t[0];
                        break;
                }
            }
            distance = Math.abs(neko_t[0] - eve[0]) + Math.abs(neko_t[1] - eve[1]);
            if (l == distance || l - 1 == distance) {
                System.out.println(l);
                in.close();
                return;
            }
        }
        System.out.println(-1);
        in.close();
    }
}