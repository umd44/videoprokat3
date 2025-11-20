package videoprokat;

/**
 * Исключение для невалидных данных клиента.
 */
public class InvalidClientException extends Exception {
    
    public InvalidClientException(String message) {
        super(message);
    }
    
    public InvalidClientException(String message, Throwable cause) {
        super(message, cause);
    }
}

