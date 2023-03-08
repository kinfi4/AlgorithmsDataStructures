import java.util.ArrayList;

public class StripeMultiplicationThread extends Thread {
    private final ArrayList<int[]> leftRows;
    private final ArrayList<Integer> threadIdxes;
    private int currentRightRowIndex;
    private final int[][] resultMatrix;
    private final SyncStripe syncObj;
    private final int leftRowLength;

    StripeMultiplicationThread(SyncStripe sync, ArrayList<int[]> leftRows, int currentRightRowIndex, ArrayList<Integer> threadIdxes, int[][] resultMatrix) {
        this.syncObj = sync;
        this.leftRows = leftRows;
        this.leftRowLength = this.leftRows.get(0).length;
        this.currentRightRowIndex = (currentRightRowIndex) % this.leftRowLength;
        this.threadIdxes = threadIdxes;
        this.resultMatrix = resultMatrix;
    }

    @Override
    public void run() {
        for (int j = 0; j < this.leftRows.size(); j++) {
            int[] leftRow = this.leftRows.get(j);
            int threadIdx = this.threadIdxes.get(j);

            int rowsCalculated = 0;
            while (rowsCalculated < this.leftRowLength) {
                int[] rightRow = this.syncObj.blockRow(this.currentRightRowIndex);

                for (int i = 0; i < rightRow.length; i++) {
                    this.resultMatrix[threadIdx][i] += rightRow[i]*leftRow[this.currentRightRowIndex];
                }

                rowsCalculated += 1;
                int prevRightRowIndex = this.currentRightRowIndex;
                this.currentRightRowIndex = (this.currentRightRowIndex + 1) % leftRow.length;

                this.syncObj.freeRow(prevRightRowIndex);
            }

        }
    }
}
