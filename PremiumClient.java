package videoprokat;

/**
 * Премиальный клиент - производный класс от Client.
 * Демонстрирует:
 * - Наследование от абстрактного класса
 * - Множественное наследование (абстрактный класс + интерфейсы)
 * - Использование protected полей базового класса
 * - Перегрузку методов с вызовом базового класса
 * - Вызов конструктора базового класса с параметрами
 */
public class PremiumClient extends Client implements Discountable, Notifiable {
    
    private double discountPercentage;
    private int loyaltyPoints;
    private String email;
    private String preferredNotificationMethod;
    
    public PremiumClient() {
        super();
        this.discountPercentage = 10.0;
        this.loyaltyPoints = 0;
        this.email = "";
        this.preferredNotificationMethod = "email";
    }
    
    /**
     * Конструктор с параметрами.
     * Демонстрирует вызов конструктора базового класса с параметрами.
     */
    public PremiumClient(int clientId, String firstName, String lastName, 
                        String phoneNumber, String email, double discountPercentage) {
        super(clientId, firstName, lastName, phoneNumber);
        this.discountPercentage = discountPercentage;
        this.loyaltyPoints = 0;
        this.email = email;
        this.preferredNotificationMethod = "email";
    }
    
    /**
     * Демонстрирует использование protected полей базового класса.
     */
    protected void updateLoyalty(double rentalAmount) {
        loyaltyPoints += (int)(rentalAmount / 10.0);
        if (loyaltyPoints > 1000 && discountPercentage < 20.0) {
            discountPercentage = 20.0;
        }
    }
    
    /**
     * Перегрузка метода базового класса С ВЫЗОВОМ базового метода.
     * Добавляет начисление бонусных баллов к стандартной функциональности.
     */
    @Override
    public void addToDeposit(double amount) {
        super.addToDeposit(amount);
        loyaltyPoints += (int)(amount / 20.0);
        System.out.println("Начислено " + (int)(amount / 20.0) + " бонусных баллов");
    }
    
    /**
     * Перегрузка метода базового класса БЕЗ ВЫЗОВА базового метода.
     * Полностью переопределяет логику блокировки для премиум-клиентов.
     */
    @Override
    public boolean blockDepositFunds(double amount) {
        if (amount <= 0.0) return false;
        double discountedAmount = applyDiscount(amount);
        if (depositBalance >= discountedAmount) {
            depositBalance -= discountedAmount;
            System.out.println("Применена скидка " + discountPercentage + "%. Заблокировано: " + discountedAmount);
            return true;
        }
        return false;
    }
    
    @Override
    public int getClientId() {
        return clientId;
    }
    
    @Override
    public String getFirstName() {
        return firstName;
    }
    
    @Override
    public String getLastName() {
        return lastName;
    }
    
    @Override
    public String getPhoneNumber() {
        return phoneNumber;
    }
    
    @Override
    public double getDepositBalance() {
        return depositBalance;
    }
    
    @Override
    public boolean isBlacklisted() {
        return blacklisted;
    }
    
    @Override
    public void unblockDepositFunds(double amount) {
        if (amount > 0.0) {
            depositBalance += amount;
        }
    }
    
    @Override
    public void setBlacklisted(boolean value) {
        blacklisted = value;
    }
    
    public int getLoyaltyPoints() {
        return loyaltyPoints;
    }
    
    public String getEmail() {
        return email;
    }
    
    @Override
    public double getDiscountPercentage() {
        return discountPercentage;
    }
    
    @Override
    public double applyDiscount(double amount) {
        return amount * (1.0 - discountPercentage / 100.0);
    }
    
    @Override
    public boolean isDiscountAvailable() {
        return !blacklisted && discountPercentage > 0;
    }
    
    @Override
    public void sendNotification(String message) {
        System.out.println("[" + preferredNotificationMethod.toUpperCase() + " to " 
                         + email + "] " + message);
    }
    
    @Override
    public String getPreferredNotificationMethod() {
        return preferredNotificationMethod;
    }
}
