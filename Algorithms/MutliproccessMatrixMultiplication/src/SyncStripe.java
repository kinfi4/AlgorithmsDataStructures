import java.util.ArrayList;

public class SyncStripe {
    private final int[][] matrix;
    public ArrayList<Integer> blockedRows = new ArrayList<>();

    public synchronized int[] blockRow(int idx) {
//        System.out.println(Thread.currentThread().getName() + " wanna block " + idx + "  " + this.blockedRows);

        while(this.rowIsBlocked(idx)) {
            try {
                wait();
            } catch (InterruptedException ignored) {}
        }

        this.blockedRows.add(idx);

        return this.matrix[idx];
    }

    public synchronized void freeRow(int idx) {
//        System.out.println(Thread.currentThread().getName() + " remove " + idx);

        this.blockedRows.remove((Integer) idx);
        notifyAll();
    }

    public synchronized boolean rowIsBlocked(int idx) {
        return this.blockedRows.contains(idx);
    }

    SyncStripe(int[][] matrix) {
        this.matrix = matrix;
    }
}
