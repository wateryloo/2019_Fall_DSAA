import java.io.*;
import java.util.ArrayList;

public class Lab8_D {

    public static void main(String[] args) throws IOException {
        Reader in = new Reader();
        PrintWriter out = new PrintWriter(System.out);
        int testcase_number = in.nextInt();
        int city_number;
        int road_number;
        int a;
        int b;
        int queue_1_front;
        int queue_1_rear;
        int queue_2_front;
        int queue_2_rear;
        boolean adding_on_queue_1;
        while (testcase_number > 0) {
            adding_on_queue_1 = false;
            queue_1_front = 0;
            queue_1_rear = 0;
            queue_2_front = 0;
            queue_2_rear = 0;
            --testcase_number;
            city_number = in.nextInt();
            road_number = in.nextInt();
            int[] queue_1 = new int[city_number];
            int[] queue_2 = new int[city_number];
            ArrayList<Integer>[] adjacent_list = new ArrayList[city_number + 1];
            boolean[] status = new boolean[city_number + 1];
            for (int i = 0; i < city_number + 1; ++i) {
                adjacent_list[i] = new ArrayList<Integer>();
                status[i] = true;
            }
            while (road_number-- > 0) {
                a = in.nextInt();
                b = in.nextInt();
                adjacent_list[a].add(b);
                adjacent_list[b].add(a);
            }
            queue_1[queue_1_rear++] = 1;
            status[1] = false;
            while (queue_1_front != queue_1_rear || queue_2_front != queue_2_rear) {
                if (adding_on_queue_1) {
                    while (queue_2_front != queue_2_rear) {
                        for (int i = 0; i < adjacent_list[queue_2[queue_2_front]].size(); ++i) {
                            if (status[adjacent_list[queue_2[queue_2_front]].get(i)]) {
                                queue_1[queue_1_rear++] =
                                        adjacent_list[queue_2[queue_2_front]].get(i);
                                status[adjacent_list[queue_2[queue_2_front]].get(i)] = false;
                            }
                        }
                        ++queue_2_front;
                    }
                    adding_on_queue_1 = false;
                }
                else {
                    while (queue_1_front != queue_1_rear) {
                        for (int i = 0; i < adjacent_list[queue_1[queue_1_front]].size(); ++i) {
                            if (status[adjacent_list[queue_1[queue_1_front]].get(i)]) {
                                queue_2[queue_2_rear++] =
                                        adjacent_list[queue_1[queue_1_front]].get(i);
                                status[adjacent_list[queue_1[queue_1_front]].get(i)] = false;
                            }
                        }
                        ++queue_1_front;
                    }
                    adding_on_queue_1 = true;
                }
            }
            if (queue_1_rear < queue_2_rear) {
                out.println(queue_1_rear);
                for (int i = 0; i < queue_1_rear; ++i) {
                    out.print(queue_1[i]);
                    out.print(' ');
                }
                out.println();
            }
            else {
                out.println(queue_2_rear);
                for (int i = 0; i < queue_2_rear; ++i) {
                    out.print(queue_2[i]);
                    out.print(' ');
                }
                out.println();
            }
        }
        in.close();
        out.close();
    }


    static class Reader {
        final private int BUFFER_SIZE = 1 << 16;
        private DataInputStream din;
        private byte[] buffer;
        private int bufferPointer, bytesRead;

        public Reader() {
            din = new DataInputStream(System.in);
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }

        public Reader(String file_name) throws IOException {
            din = new DataInputStream(new FileInputStream(file_name));
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }

        public String readLine() throws IOException {
            byte[] buf = new byte[64]; // line length
            int cnt = 0, c;
            while ((c = read()) != -1) {
                if (c == '\n')
                    break;
                buf[cnt++] = (byte) c;
            }
            return new String(buf, 0, cnt);
        }

        public int nextInt() throws IOException {
            int ret = 0;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg)
                c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');

            if (neg)
                return -ret;
            return ret;
        }

        public long nextLong() throws IOException {
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

        public double nextDouble() throws IOException {
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

            if (c == '.') {
                while ((c = read()) >= '0' && c <= '9') {
                    ret += (c - '0') / (div *= 10);
                }
            }

            if (neg)
                return -ret;
            return ret;
        }

        private void fillBuffer() throws IOException {
            bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
            if (bytesRead == -1)
                buffer[0] = -1;
        }

        private byte read() throws IOException {
            if (bufferPointer == bytesRead)
                fillBuffer();
            return buffer[bufferPointer++];
        }

        public void close() throws IOException {
            if (din == null)
                return;
            din.close();
        }
    }
}