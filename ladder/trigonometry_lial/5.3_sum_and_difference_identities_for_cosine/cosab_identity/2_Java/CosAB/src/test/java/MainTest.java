import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;

public class MainTest {

    @Test
    void testCosAB_When_A_Is_0_and_B_Is_O() {
        Main main = new Main();
        assertEquals(1, main.cosAB(0, 0));
    }
	
    @Test
    void testCosAB_When_A_Is_Pi_and_B_Is_Pi() {
	Main main = new Main();
	assertEquals(1, main.cosAB(Math.PI, Math.PI));
    }

}
