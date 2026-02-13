import org.ejml.simple.SimpleMatrix;

public class MatrixSumExample {
    public static void main(String[] args) {
        // 1. Define your data (2x2 matrices)
        double[][] dataA = {
            {1, 2},
            {3, 4}
        };
        
        double[][] dataB = {
            {5, 6},
            {7, 8}
        };

        // 2. Create SimpleMatrix objects
        SimpleMatrix A = new SimpleMatrix(dataA);
        SimpleMatrix B = new SimpleMatrix(dataB);

        // 3. Perform the addition
        // Mathematically: C = A + B
        SimpleMatrix C = A.plus(B);

        // 4. Print the result
        System.out.println("Matrix A:");
        A.print();
        
        System.out.println("Matrix B:");
        B.print();
        
        System.out.println("Result (A + B):");
        C.print();
    }
}
