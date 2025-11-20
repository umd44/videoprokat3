package videoprokat;

/**
 * Исключение для отсутствующего элемента в каталоге.
 */
public class ItemNotFoundException extends Exception {
    
    private final int itemNumber;
    
    public ItemNotFoundException(String message, int itemNumber) {
        super(message);
        this.itemNumber = itemNumber;
    }
    
    public int getItemNumber() {
        return itemNumber;
    }
}

