import org.ejml.simple.SimpleMatrix;

public class Main {

    private static final double EPS = 1e-10;

    static class Pivot {
        Pivot(double maxVal, int index) {
            this.maxVal = maxVal;
            this.index = index;
        }
        double maxVal;
        int index;
    }

    private Pivot findPivot(SimpleMatrix m, int currentRow, int pivotCol) {
        int rows = m.getNumRows();
        Pivot pivot = new Pivot(0.0, -1);
        for (int i = currentRow; i < rows; i++) {
            double currentVal = Math.abs(m.get(i, pivotCol));
            if (currentVal > pivot.maxVal && currentVal > EPS) {
                pivot.maxVal = currentVal;
                pivot.index = i;
            }
        }
        return pivot;
    }

    private void swapRows(SimpleMatrix m, int r1, int r2) {
        for (int col = 0; col < m.getNumCols(); col++) {
            double tmp = m.get(r1, col);
            m.set(r1, col, m.get(r2, col));
            m.set(r2, col, tmp);
        }
    }

    private void normalize(SimpleMatrix m, int currentRow, int pivotCol) {
        double divisor = m.get(currentRow, pivotCol);
        for (int col = 0; col < m.getNumCols(); col++) {
            double newValue = m.get(currentRow, col) / divisor;
            m.set(currentRow, col, newValue);
        }
    }

    private void eliminateBelow(SimpleMatrix m, int currentRow, int pivotCol) {
        for (int r = currentRow + 1; r < m.getNumRows(); r++) {
            double multiplier = m.get(r, pivotCol);
            for (int col = 0; col < m.getNumCols(); col++) {
                m.set(r, col, m.get(r, col) - multiplier * m.get(currentRow, col));
            }
        }
    }

    public void ref(SimpleMatrix m) {
        int rows = m.getNumRows();
        int cols = m.getNumCols();

        int currentRow = 0;
        int pivotCol = 0;

        while (currentRow < rows && pivotCol < cols) {
            Pivot pivot = findPivot(m, currentRow, pivotCol);
            if (pivot.index == -1) {
                ++pivotCol;
                continue;
            }
            swapRows(m, pivot.index, currentRow);
            normalize(m, currentRow, pivotCol);
            eliminateBelow(m, currentRow, pivotCol);
            ++currentRow;
            ++pivotCol;
        }
    }
}
