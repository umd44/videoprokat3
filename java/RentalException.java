package videoprokat;

/**
 * Исключение для ошибок при работе с арендой.
 */
public class RentalException extends Exception {
    
    public RentalException(String message) {
        super(message);
    }
    
    public RentalException(String message, Throwable cause) {
        super(message, cause);
    }
}

