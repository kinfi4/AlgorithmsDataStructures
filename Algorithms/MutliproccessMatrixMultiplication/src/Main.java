import javax.print.attribute.standard.PrinterMakeAndModel;
import java.time.Duration;
import java.time.Instant;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Main {
    public static void main(String[] args) {
        makeCalculations();
    }

    public static void makeCalculations() {
        int[] sizes = new int[] { 500, 1000, 2000 };

        for (int size : sizes) {
            for (int threadsNumber : new int[] {100, 250, 500}) {
                ArrayList<Long> syncMultiplicationTimes = new ArrayList<>();
                ArrayList<Long> foxMultiplicationTimes = new ArrayList<>();
                ArrayList<Long> stripeMultiplicationTimes = new ArrayList<>();

                for (int i = 0; i < 10; i++) {
                    int[][] A = _generateRandomMatrix(size, size);
                    int[][] B = _generateRandomMatrix(size, size);

                    Instant start = Instant.now();
                    int[][] C = matrixMultiplication(A, B);
                    Instant end = Instant.now();
                    Duration timeElapsed = Duration.between(start, end);
                    syncMultiplicationTimes.add(timeElapsed.toMillis());
                    System.out.print("Sync multiplication: " + timeElapsed.toMillis());

                    start = Instant.now();
                    int[][] C3 = stripeMatrixMultiplication(A, B, threadsNumber);
                    end = Instant.now();
                    timeElapsed = Duration.between(start, end);
                    stripeMultiplicationTimes.add(timeElapsed.toMillis());
                    System.out.print("  Stripe multiplication: " + timeElapsed.toMillis());

                    start = Instant.now();
                    int[][] C2 = foxMatrixMultiplication(A, B, threadsNumber);
                    end = Instant.now();
                    timeElapsed = Duration.between(start, end);
                    foxMultiplicationTimes.add(timeElapsed.toMillis());
                    System.out.println("  FOX multiplication: " + timeElapsed.toMillis());

                    System.out.println("==============================================");
                }

                System.out.println("THREADS COUNT: " + threadsNumber + " MATRIX SIZE: " + size);
                System.out.println("Sync: " + syncMultiplicationTimes.stream().mapToDouble(d -> d).average());
                System.out.println("Stripe: " + stripeMultiplicationTimes.stream().mapToDouble(d -> d).average());
                System.out.println("Fox: " + foxMultiplicationTimes.stream().mapToDouble(d -> d).average());

                System.out.println("-----------------------------------------");
                System.out.println("\n");
            }

            System.out.println("\n\n");
            System.out.println("EXPERIMENT FOR MATRIX SIZE " + size + " IS OVER!! \n\n");

        }
    }

    public static int[][] foxMatrixMultiplication(int[][] matrix1, int[][] matrix2, int threadsNumber) {
        if(matrix1.length != matrix1[0].length || matrix2.length != matrix2[0].length || matrix1.length != matrix2.length) {
            throw new RuntimeException("Matrix must be squared!");
        }

        int size = matrix1.length;

        if(size % threadsNumber != 0) {
            throw new RuntimeException("Block size is invalid for this matrix!");
        }

        int[][] resultMatrix = new int[size][size];
        List<Thread> threads = new ArrayList<>();

        int gridSize = (int) Math.sqrt(threadsNumber);

        int[][][][] leftBlocks = _divideMatrix(matrix1, gridSize);
        int[][][][] rightBlocks = _divideMatrix(matrix2, gridSize);

        SyncFox sync = new SyncFox(leftBlocks, rightBlocks);

        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                Thread thread = new FoxMultiplicationThread(i, j, gridSize, sync, resultMatrix);

                threads.add(thread);
                thread.start();
            }
        }

        for (Thread th : threads) {
            try{
                th.join();
            } catch (InterruptedException ignored) {}
        }

        return resultMatrix;
    }

    public static int[][] stripeMatrixMultiplication(int[][] matrix1, int[][] matrix2, int threadsNumber) {
        int[][] resultMatrix = new int[matrix1.length][matrix2[0].length];
        List<Thread> threads = new ArrayList<>();

        SyncStripe sync = new SyncStripe(matrix2);

        int rowsPerThread = matrix1.length / threadsNumber;
        rowsPerThread = Math.max(rowsPerThread, 1);

        for (int i = 0; i < matrix1.length; i += rowsPerThread) {
            ArrayList<int[]> rowsToCalculate = new ArrayList<>();
            ArrayList<Integer> indexesToCalculate = new ArrayList<>();

            int theLastIndex = Math.min(i + rowsPerThread, matrix1.length);
            for (int j = i; j < theLastIndex; j++) {
                rowsToCalculate.add(matrix1[j]);
                indexesToCalculate.add(j);
            }

            Thread thread = new StripeMultiplicationThread(sync, rowsToCalculate, i, indexesToCalculate, resultMatrix);

            threads.add(thread);
            thread.start();
        }

        for (Thread th : threads) {
            try{
                th.join();
            } catch (InterruptedException ignored) {}
        }


        return resultMatrix;
    }

    public static int[][] matrixMultiplication(int[][] matrix1, int[][] matrix2) {
        int matrix1Height = matrix1.length;
        int matrix1Width = matrix1[0].length;

        int matrix2Height = matrix2.length;
        int matrix2Width = matrix2[0].length;

        int[][] resultMatrix = new int[matrix1Height][matrix2Width];

        if(matrix1Width != matrix2Height) {
            throw new RuntimeException("Matrix's have invalid sizes!");
        }

        for (int row = 0; row < matrix1Height; row++) {
            for (int i = 0; i < matrix2Width; i++) {
                int sum = 0;

                for (int k = 0; k < matrix1Width; k++) {
                    sum += matrix1[row][k] * matrix2[k][i];
                }

                resultMatrix[row][i] = sum;
            }
        }

        return resultMatrix;
    }

    public static int[][] _generateRandomMatrix(int n, int m) {
        Random random = new Random();
        int[][] resultMatrix = new int[n][m];

        for (int i = 0; i < n; i++) {
            for (int k = 0; k < m; k++) {
                resultMatrix[i][k] = random.nextInt(5);
            }
        }

        return resultMatrix;
    }

    public static boolean _checkMatrixAreEqual(int[][] mat1, int[][] mat2) {
        if (mat1.length != mat2.length || mat1[0].length != mat2[0].length) {
            return false;
        }

        for (int i = 0; i < mat1.length; i++) {
            for (int j = 0; j < mat1[0].length; j++) {
                if(mat1[i][j] != mat2[i][j]) {
                    return false;
                }
            }
        }

        return true;
    }

    public static void _printMatrix(int[][] matrix) {
        for (int[] ints : matrix) {
            for (int j = 0; j < matrix[0].length; j++) {
                System.out.print(ints[j] + " ");
            }
            System.out.println();
        }

        System.out.println("==================================");
    }

    private static int[][][][] _divideMatrix(int[][] matrix, int gridSize) {
        int blockSize = matrix.length / gridSize;
        int[][][][] blocks = new int[gridSize][gridSize][blockSize][blockSize];

        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                for (int k = 0; k < blockSize; k++) {
                    System.arraycopy(matrix[i * blockSize + k], j * blockSize, blocks[i][j][k], 0, blockSize);
                }
            }
        }

        return blocks;
    }
}
