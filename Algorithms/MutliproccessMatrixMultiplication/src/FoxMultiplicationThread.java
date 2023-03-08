public class FoxMultiplicationThread extends Thread {
    private final SyncFox sync;
    private final int i;
    private final int j;
    private final int blocksGridSize;
    private final int[][] resultMatrix;
    private final int blockSize;

    FoxMultiplicationThread(int i, int j, int blocksGridSize, SyncFox s, int[][] resultMatrix) {
        this.sync = s;
        this.i = i;
        this.j = j;
        this.blocksGridSize = blocksGridSize;
        this.resultMatrix = resultMatrix;
        this.blockSize = resultMatrix.length / blocksGridSize;
    }

    @Override
    public void run() {
        for (int k = 0; k < this.blocksGridSize; k++) {
            var blocks = this.sync.getBlockPair((this.i + k) % this.blocksGridSize, this.i, this.j, (this.i + k) % this.blocksGridSize);

            multiplyMatrices(blocks[0], blocks[1]);

            this.sync.freeBlocks((this.i + k) % this.blocksGridSize, this.i, this.j, (this.i + k) % this.blocksGridSize);
        }
    }

    private void multiplyMatrices(int[][] mat1, int[][] mat2) {
        for (int i = 0; i < mat1.length; i++) {
            for (int j = 0; j < mat2[0].length; j++) {
                for (int k = 0; k < mat2.length; k++) {
                    this.resultMatrix[this.i*this.blockSize + i][this.j*this.blockSize + j] += mat1[i][k] * mat2[k][j];
                }
            }
        }
    }

}
