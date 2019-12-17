import java.io.*;
import java.util.ArrayList;

public class Lab8_C {
    public static void main(String[] args) throws IOException {
        Reader in = new Reader();
        PrintWriter out = new PrintWriter(System.out);
        int city_number = in.nextInt();
        int road_number = in.nextInt();
        int from, to, weight;
        boolean[] status = new boolean[2 * city_number + 1];
        int[] queue = new int[2 * city_number + 1];
        int front = 0;
        int rear = 0;
        int res = 0;
        int temp;
        boolean flag = false;


        ArrayList<ArrayList<Integer>> adjacent_list = new ArrayList<>();
        for (int i = 0; i < 2 * city_number + 1; ++i) {
            adjacent_list.add(new ArrayList<Integer>());
            status[i] = true;
        }
        for (int i = 0; i < road_number; ++i) {
            from = in.nextInt();
            to = in.nextInt();
            weight = in.nextInt();
            if (weight == 1) {
                adjacent_list.get(from).add(to);
            }
            else {
                adjacent_list.get(from + city_number).add(to);
                adjacent_list.get(from).add(from + city_number);
            }
        }
        if (city_number == 1) {
            out.println(0);
            return;
        }
        queue[rear++] = 1;
        temp = rear;
        while (front != rear) {
            ++res;
            while (front != temp) {
                for (int i = 0; i < adjacent_list.get(queue[front]).size(); ++i) {
                    if (status[adjacent_list.get(queue[front]).get(i)]) {
                        status[adjacent_list.get(queue[front]).get(i)] = false;
                        if (adjacent_list.get(queue[front]).get(i) == city_number) {
                            flag = true;
                            break;
                        }
                        else {
                            queue[rear++] = adjacent_list.get(queue[front]).get(i);
                        }
                    }
                }
                if (flag) {
                    break;
                }
                ++front;
            }
            if (flag) {
                break;
            }
            temp = rear;
        }
        if (flag) {
            out.println(res);
        }
        else {
            out.println(-1);
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