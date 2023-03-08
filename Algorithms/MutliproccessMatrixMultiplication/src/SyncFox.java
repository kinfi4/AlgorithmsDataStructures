import java.util.ArrayList;

public class SyncFox {
    private final int[][][][] listOfBlocksLeftMatrix;
    private final int[][][][] listOfBlocksRightMatrix;
    public ArrayList<int[]> blockedBlocksRightMatrix = new ArrayList<>();
    public ArrayList<int[]> blockedBlocksLeftMatrix = new ArrayList<>();

    public synchronized int[][][] getBlockPair(int leftX, int leftY, int rightX, int rightY) {
        while(this.blocksIsBlocked(leftX, leftY, rightX, rightY)) {
            try {
                wait();
            } catch (InterruptedException ignored) {}
        }

//        System.out.println(Thread.currentThread().getName()  + " blocks " + leftY + " " + leftX + " " + rightY + " " + rightX);

        this.blockedBlocksLeftMatrix.add(new int[] {leftX, leftY});
        this.blockedBlocksRightMatrix.add(new int[] {rightX, rightY});

        return new int[][][]{ this.listOfBlocksLeftMatrix[leftY][leftX], this.listOfBlocksRightMatrix[rightY][rightX] };
    }

    public synchronized void freeBlocks(int leftX, int leftY, int rightX, int rightY) {
//        System.out.println(Thread.currentThread().getName()  + " frees " + leftY + "  " + leftX + " " + rightY + " " + rightX);

        for (int[] blockIdxes: this.blockedBlocksLeftMatrix) {
            if(blockIdxes[0] == leftX || blockIdxes[1] == leftY) {
                this.blockedBlocksLeftMatrix.remove(blockIdxes);
                break;
            }
        }
        for (int[] blockIdxes: this.blockedBlocksRightMatrix) {
            if(blockIdxes[0] == rightX || blockIdxes[1] == rightY) {
                this.blockedBlocksRightMatrix.remove(blockIdxes);
                break;
            }
        }

        notifyAll();
    }

    public synchronized boolean blocksIsBlocked(int leftX, int leftY, int rightX, int rightY) {
        for (int[] blockIdxes: this.blockedBlocksLeftMatrix) {
            if(blockIdxes[0] == leftX || blockIdxes[1] == leftY) {
                return true;
            }
        }
        for (int[] blockIdxes: this.blockedBlocksRightMatrix) {
            if(blockIdxes[0] == rightX || blockIdxes[1] == rightY) {
                return true;
            }
        }

        return false;
    }

    SyncFox(int[][][][] listOfBlocksLeftMatrix, int[][][][] listOfBlocksRightMatrix) {
        this.listOfBlocksLeftMatrix = listOfBlocksLeftMatrix;
        this.listOfBlocksRightMatrix = listOfBlocksRightMatrix;
    }
}
