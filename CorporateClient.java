package videoprokat;

/**
 * Корпоративный клиент - производный класс от Client.
 * Демонстрирует наследование от абстрактного класса и интерфейса.
 */
public class CorporateClient extends Client implements Discountable {
    
    private String companyName;
    private double corporateDiscount;
    private int employeeCount;
    
    public CorporateClient() {
        super();
        this.companyName = "";
        this.corporateDiscount = 15.0;
        this.employeeCount = 0;
    }
    
    /**
     * Конструктор с параметрами, вызывает конструктор базового класса.
     */
    public CorporateClient(int clientId, String firstName, String lastName,
                          String phoneNumber, String companyName, int employeeCount) {
        super(clientId, firstName, lastName, phoneNumber);
        this.companyName = companyName;
        this.employeeCount = employeeCount;
        this.corporateDiscount = calculateCorporateDiscount();
    }
    
    /**
     * Использует protected поля базового класса для расчета скидки.
     */
    protected double calculateCorporateDiscount() {
        if (employeeCount > 100) return 25.0;
        if (employeeCount > 50) return 20.0;
        if (employeeCount > 10) return 15.0;
        return 10.0;
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
    public void addToDeposit(double amount) {
        if (amount > 0.0) {
            depositBalance += amount;
        }
    }
    
    @Override
    public boolean blockDepositFunds(double amount) {
        if (amount <= 0.0) return false;
        if (depositBalance >= amount) {
            depositBalance -= amount;
            return true;
        }
        return false;
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
    
    public String getCompanyName() {
        return companyName;
    }
    
    @Override
    public double getDiscountPercentage() {
        return corporateDiscount;
    }
    
    @Override
    public double applyDiscount(double amount) {
        return amount * (1.0 - corporateDiscount / 100.0);
    }
    
    @Override
    public boolean isDiscountAvailable() {
        return !blacklisted && corporateDiscount > 0;
    }
}
