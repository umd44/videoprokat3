package videoprokat;

/**
 * Исключение уровня бизнес-логики для операций аренды.
 */
public class RentalOperationException extends RuntimeException {

    public RentalOperationException(String message) {
        super(message);
    }

    public RentalOperationException(String message, Throwable cause) {
        super(message, cause);
    }
}

