import org.ejml.simple.SimpleMatrix;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class TestMain {

    private static final double EPSILON = 1e-9;

    private final Main main = new Main();

    /**
     * Verifies the matrix is in Row Echelon Form:
     * 1. Each pivot (leading entry in a row) is 1.0
     * 2. Each pivot is to the right of the pivot in the row above
     * 3. All entries below a pivot are 0
     */
    private void assertIsREF(SimpleMatrix m) {
        int rows = m.getNumRows();
        int cols = m.getNumCols();
        int lastPivotCol = -1;

        for (int r = 0; r < rows; r++) {
            int pivotCol = -1;
            for (int c = 0; c < cols; c++) {
                if (Math.abs(m.get(r, c)) > EPSILON) {
                    pivotCol = c;
                    break;
                }
            }
            if (pivotCol == -1) {
                // Zero row — all remaining rows must also be zero
                for (int rr = r + 1; rr < rows; rr++) {
                    for (int c = 0; c < cols; c++) {
                        assertEquals(0.0, m.get(rr, c), EPSILON,
                                "Non-zero row found below a zero row at (" + rr + "," + c + ")");
                    }
                }
                break;
            }
            // Pivot must be 1.0
            assertEquals(1.0, m.get(r, pivotCol), EPSILON,
                    "Pivot at (" + r + "," + pivotCol + ") should be 1.0");
            // Pivot must be strictly to the right of the previous pivot
            assertTrue(pivotCol > lastPivotCol,
                    "Pivot at row " + r + " (col " + pivotCol + ") is not to the right of previous pivot (col " + lastPivotCol + ")");
            // All entries below the pivot must be 0
            for (int rr = r + 1; rr < rows; rr++) {
                assertEquals(0.0, m.get(rr, pivotCol), EPSILON,
                        "Entry below pivot at (" + rr + "," + pivotCol + ") should be zero");
            }
            lastPivotCol = pivotCol;
        }
    }

    @Test
    void testNullInputThrowsException() {
        assertThrows(NullPointerException.class, () -> main.ref(null));
    }

    @Test
    void test1x1Matrix() {
        SimpleMatrix m = new SimpleMatrix(new double[][]{{5.0}});
        main.ref(m);
        assertEquals(1.0, m.get(0, 0), EPSILON, "Single element should be normalized to 1");
    }

    @Test
    void test2x2IdentityMatrix() {
        SimpleMatrix m = new SimpleMatrix(new double[][]{
                {1, 0},
                {0, 1}
        });
        main.ref(m);
        assertIsREF(m);
        assertEquals(1.0, m.get(0, 0), EPSILON);
        assertEquals(0.0, m.get(0, 1), EPSILON);
        assertEquals(0.0, m.get(1, 0), EPSILON);
        assertEquals(1.0, m.get(1, 1), EPSILON);
    }

    @Test
    void test2x2SimpleMatrix() {
        SimpleMatrix m = new SimpleMatrix(new double[][]{
                {2, 4},
                {1, 3}
        });
        main.ref(m);
        assertIsREF(m);
    }

    @Test
    void test3x3RegularMatrix() {
        SimpleMatrix m = new SimpleMatrix(new double[][]{
                {2, 1, -1},
                {-3, -1, 2},
                {-2, 1, 2}
        });
        main.ref(m);
        assertIsREF(m);

        // First pivot
        assertEquals(1.0, m.get(0, 0), EPSILON);
        // Below first pivot
        assertEquals(0.0, m.get(1, 0), EPSILON);
        assertEquals(0.0, m.get(2, 0), EPSILON);
        // Second pivot
        assertEquals(1.0, m.get(1, 1), EPSILON);
        // Below second pivot
        assertEquals(0.0, m.get(2, 1), EPSILON);
        // Third pivot
        assertEquals(1.0, m.get(2, 2), EPSILON);
    }

    @Test
    void test3x3MatrixWithZeroPivotColumn() {
        SimpleMatrix m = new SimpleMatrix(new double[][]{
                {0, 2, 4},
                {0, 3, 9},
                {0, 1, 5}
        });
        main.ref(m);
        assertIsREF(m);

        // Column 0 is all zeros, so pivots should start at column 1
        assertEquals(0.0, m.get(0, 0), EPSILON);
        assertEquals(1.0, m.get(0, 1), EPSILON);
        assertEquals(0.0, m.get(1, 1), EPSILON);
        assertEquals(1.0, m.get(1, 2), EPSILON);
    }

    @Test
    void test3x3ZeroMatrix() {
        SimpleMatrix m = new SimpleMatrix(new double[][]{
                {0, 0, 0},
                {0, 0, 0},
                {0, 0, 0}
        });
        main.ref(m);

        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                assertEquals(0.0, m.get(r, c), EPSILON, "All entries should remain zero");
            }
        }
    }

    @Test
    void testPartialPivoting() {
        // Row with smaller value on top — should be swapped with the larger one
        SimpleMatrix m = new SimpleMatrix(new double[][]{
                {1, 2},
                {4, 5}
        });
        main.ref(m);
        assertIsREF(m);

        // Largest absolute value in col 0 is 4, so row swap should occur
        assertEquals(1.0, m.get(0, 0), EPSILON);
        assertEquals(0.0, m.get(1, 0), EPSILON);
    }

    @Test
    void testWideMatrix2x4() {
        SimpleMatrix m = new SimpleMatrix(new double[][]{
                {1, 2, 3, 4},
                {5, 6, 7, 8}
        });
        main.ref(m);
        assertIsREF(m);

        assertEquals(1.0, m.get(0, 0), EPSILON);
        assertEquals(0.0, m.get(1, 0), EPSILON);
        assertEquals(1.0, m.get(1, 1), EPSILON);
    }

    @Test
    void testTallMatrix4x2() {
        SimpleMatrix m = new SimpleMatrix(new double[][]{
                {3, 6},
                {1, 4},
                {2, 8},
                {5, 10}
        });
        main.ref(m);
        assertIsREF(m);

        // All entries below pivots should be zero
        for (int r = 2; r < 4; r++) {
            for (int c = 0; c < 2; c++) {
                assertEquals(0.0, m.get(r, c), EPSILON,
                        "Entry at (" + r + "," + c + ") should be zero");
            }
        }
    }

    @Test
    void testAlreadyInRowEchelonForm() {
        SimpleMatrix m = new SimpleMatrix(new double[][]{
                {1, 3, 5},
                {0, 1, 2},
                {0, 0, 1}
        });
        main.ref(m);
        assertIsREF(m);

        assertEquals(1.0, m.get(0, 0), EPSILON);
        assertEquals(1.0, m.get(1, 1), EPSILON);
        assertEquals(1.0, m.get(2, 2), EPSILON);
    }

    @Test
    void testNormalizationProducesPivotOfOne() {
        SimpleMatrix m = new SimpleMatrix(new double[][]{
                {10, 20, 30},
                {0, 5, 15},
                {0, 0, 3}
        });
        main.ref(m);
        assertIsREF(m);

        assertEquals(1.0, m.get(0, 0), EPSILON);
        assertEquals(1.0, m.get(1, 1), EPSILON);
        assertEquals(1.0, m.get(2, 2), EPSILON);
    }

    @Test
    void testSingleRowMatrix() {
        SimpleMatrix m = new SimpleMatrix(new double[][]{{3, 6, 9}});
        main.ref(m);

        assertEquals(1.0, m.get(0, 0), EPSILON, "Single row pivot should be normalized to 1");
        assertEquals(2.0, m.get(0, 1), EPSILON);
        assertEquals(3.0, m.get(0, 2), EPSILON);
    }

    @Test
    void testSingleColumnMatrix() {
        SimpleMatrix m = new SimpleMatrix(new double[][]{
                {3},
                {6},
                {9}
        });
        main.ref(m);
        assertIsREF(m);

        assertEquals(1.0, m.get(0, 0), EPSILON);
        assertEquals(0.0, m.get(1, 0), EPSILON);
        assertEquals(0.0, m.get(2, 0), EPSILON);
    }

    @Test
    void testNegativeValues() {
        SimpleMatrix m = new SimpleMatrix(new double[][]{
                {-2, -4, -6},
                {-1, -3, -5},
                {-3, -7, -8}
        });
        main.ref(m);
        assertIsREF(m);
    }

    @Test
    void testLinearlyDependentRows() {
        SimpleMatrix m = new SimpleMatrix(new double[][]{
                {1, 2, 3},
                {2, 4, 6},
                {3, 6, 9}
        });
        main.ref(m);
        assertIsREF(m);

        // All rows are multiples of each other → rank 1
        // Rows 1 and 2 should become all zeros
        for (int c = 0; c < 3; c++) {
            assertEquals(0.0, m.get(1, c), EPSILON, "Row 1 should be all zeros");
            assertEquals(0.0, m.get(2, c), EPSILON, "Row 2 should be all zeros");
        }
    }

    @Test
    void testMixedZeroAndNonZeroRows() {
        SimpleMatrix m = new SimpleMatrix(new double[][]{
                {0, 0, 0},
                {1, 2, 3},
                {0, 0, 0}
        });
        main.ref(m);
        assertIsREF(m);

        // Non-zero row should float to the top
        assertEquals(1.0, m.get(0, 0), EPSILON);
    }
}
