import static org.junit.jupiter.api.Assertions.assertEquals;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;


public class StackTest {
    private Stack stack; // Objeto da classe Stack a ser testado

    @BeforeEach
    public void setUp() {
        stack = new Stack(); // Inicializa uma nova pilha antes de cada teste
    }

    @AfterEach
    public void tearDown() {
        stack = null; // Define a pilha como null após cada teste
    }

    @Test
    public void testPush() {
        stack.push("A");
        assertEquals("A", stack.top()); // Verifica se o elemento "A" foi adicionado corretamente no topo da pilha
    }

    @Test
    public void testPop() {
        stack.push("A");
        stack.push("B");
        stack.pop();
        assertEquals("A", stack.top()); // Verifica se o elemento "B" foi removido corretamente da pilha
    }

    @Test
    public void testEmpty() {
        assertTrue(stack.empty()); // Verifica se a pilha está vazia inicialmente
        stack.push("A");
        assertFalse(stack.empty()); // Verifica se a pilha não está vazia após adicionar um elemento
    }

    @Test
    public void testLength() {
        assertEquals(0, stack.length()); // Verifica se o comprimento da pilha é 0 inicialmente
        stack.push("A");
        stack.push("B");
        assertEquals(2, stack.length()); // Verifica se o comprimento da pilha é 2 após adicionar dois elementos
    }
}
