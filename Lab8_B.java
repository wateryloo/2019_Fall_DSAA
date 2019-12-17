import java.io.*;

public class Lab8_B {
    public static void main(String[] args) throws IOException {
        Reader in = new Reader();
        PrintWriter out = new PrintWriter(System.out);
        int testcase_number = in.nextInt();
        while (testcase_number-- > 0) {
            int N = in.nextInt();
            int M = in.nextInt();
            int K = in.nextInt();
            int[][] monsters = new int[K][3];
            int[][] map = new int[K + 2][K + 2];
            for (int index_of_monsters = 0; index_of_monsters < K; ++index_of_monsters) {
                monsters[index_of_monsters][0] = in.nextInt();
                monsters[index_of_monsters][1] = in.nextInt();
                monsters[index_of_monsters][2] = in.nextInt();
                if (monsters[index_of_monsters][2] >= monsters[index_of_monsters][0]) {
                    map[0][index_of_monsters + 1] = 1;
                    map[index_of_monsters + 1][0] = 1;
                }
                else if (monsters[index_of_monsters][2] >= M - monsters[index_of_monsters][1]) {
                    map[0][index_of_monsters + 1] = 1;
                    map[index_of_monsters + 1][0] = 1;
                }
                if (monsters[index_of_monsters][2] >= N - monsters[index_of_monsters][0]) {
                    map[K + 1][index_of_monsters + 1] = 1;
                    map[index_of_monsters + 1][K + 1] = 1;
                }
                else if (monsters[index_of_monsters][2] >= monsters[index_of_monsters][1]) {
                    map[K + 1][index_of_monsters + 1] = 1;
                    map[index_of_monsters + 1][K + 1] = 1;
                }
            }
            for (int index_1 = 0; index_1 < K - 1; ++index_1) {
                for (int index_2 = index_1; index_2 < K; ++index_2) {
                    int distance1 = (monsters[index_1][2] + monsters[index_2][2]) *
                                    (monsters[index_1][2] + monsters[index_2][2]);
                    int distance2 = ((monsters[index_1][0] - monsters[index_2][0]) *
                                    (monsters[index_1][0] - monsters[index_2][0])) +
                                    ((monsters[index_1][1] - monsters[index_2][1]) *
                                    (monsters[index_1][1] - monsters[index_2][1]));
                    if (distance1 >= distance2) {
                        map[index_1 + 1][index_2 + 1] = 1;
                        map[index_2 + 1][index_1 + 1] = 1;
                    }
                }
            }
            int[] queue = new int[K + 2];
            int[] status = new int[K + 2];
            int front = 0;
            int rear = 0;
            queue[rear++] = 0;
            status[0] = 1;
            boolean flag = false;
            OUT:while (front != rear) {
                for (int i = 0; i < K + 2; ++i) {
                    if (map[queue[front]][i] == 1 &&
                        status[i] == 0) {
                        queue[rear] = i;
                        if (queue[rear] == K + 1) {
                            out.println("No");
                            flag = true;
                            break OUT;
                        }
                        status[i] = 1;
                        ++rear;
                    }
                }
                ++front;
            }
            if (!flag) {
                out.println("Yes");
            }
        }
        in.close();
        out.close();
    }


    static class Reader
    {
        final private int BUFFER_SIZE = 1 << 16;
        private DataInputStream din;
        private byte[] buffer;
        private int bufferPointer, bytesRead;

        public Reader()
        {
            din = new DataInputStream(System.in);
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }

        public Reader(String file_name) throws IOException
        {
            din = new DataInputStream(new FileInputStream(file_name));
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }

        public String readLine() throws IOException
        {
            byte[] buf = new byte[64]; // line length
            int cnt = 0, c;
            while ((c = read()) != -1)
            {
                if (c == '\n')
                    break;
                buf[cnt++] = (byte) c;
            }
            return new String(buf, 0, cnt);
        }

        public int nextInt() throws IOException
        {
            int ret = 0;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg)
                c = read();
            do
            {
                ret = ret * 10 + c - '0';
            }  while ((c = read()) >= '0' && c <= '9');

            if (neg)
                return -ret;
            return ret;
        }

        public long nextLong() throws IOException
        {
            long ret = 0;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg)
                c = read();
            do {
                ret = ret * 10 + c - '0';
            }
            while ((c = read()) >= '0' && c <= '9');
            if (neg)
                return -ret;
            return ret;
        }

        public double nextDouble() throws IOException
        {
            double ret = 0, div = 1;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg)
                c = read();

            do {
                ret = ret * 10 + c - '0';
            }
            while ((c = read()) >= '0' && c <= '9');

            if (c == '.')
            {
                while ((c = read()) >= '0' && c <= '9')
                {
                    ret += (c - '0') / (div *= 10);
                }
            }

            if (neg)
                return -ret;
            return ret;
        }

        private void fillBuffer() throws IOException
        {
            bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
            if (bytesRead == -1)
                buffer[0] = -1;
        }

        private byte read() throws IOException
        {
            if (bufferPointer == bytesRead)
                fillBuffer();
            return buffer[bufferPointer++];
        }

        public void close() throws IOException
        {
            if (din == null)
                return;
            din.close();
        }
    }

}