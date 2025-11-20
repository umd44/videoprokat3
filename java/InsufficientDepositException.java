package videoprokat;

/**
 * Исключение для недостаточного депозита.
 */
public class InsufficientDepositException extends Exception {
    
    private final double requiredAmount;
    private final double availableAmount;
    
    public InsufficientDepositException(String message, double requiredAmount, double availableAmount) {
        super(message);
        this.requiredAmount = requiredAmount;
        this.availableAmount = availableAmount;
    }
    
    public double getRequiredAmount() {
        return requiredAmount;
    }
    
    public double getAvailableAmount() {
        return availableAmount;
    }
}

