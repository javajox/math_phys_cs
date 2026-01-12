public class Main {

    public double cosAB(double a, double b) {
	double cos_a = Math.cos(a);
    	double cos_b = Math.cos(b);
	double sin_a = Math.sin(a);
	double sin_b = Math.sin(b);

	return cos_a * cos_b - sin_a * sin_b;
    }	    

    public static void main(String[] args) {
	Main main = new Main();    
        System.out.println("cosAB(0, 0) = " + main.cosAB(0,0));
    }
}
