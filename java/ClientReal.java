package videoprokat;

/**
 * Реализация класса Client.
 * Содержит конкретную реализацию всех методов абстрактного класса Client.
 */
public class ClientReal extends Client {

    // Счетчик созданных клиентов
    private static int totalClientsCreated = 0;

    // Максимальное количество клиентов
    public static final int MAX_CLIENTS = 10000;

    /**
     * Конструктор по умолчанию.
     */
    public ClientReal() {
        super();
        incrementClientCount();
    }

    public ClientReal(int clientId, String firstName, String lastName, String phoneNumber) {
        super(clientId, firstName, lastName, phoneNumber);
        incrementClientCount();
    }

    public ClientReal(int clientId) {
        this();
        this.clientId = clientId;
    }

    private static void incrementClientCount() {
        totalClientsCreated++;
    }

    public static int getTotalClientsCreated() {
        return totalClientsCreated;
    }

    public static boolean canCreateNewClient() {
        return totalClientsCreated < MAX_CLIENTS;
    }

    public static void resetClientCount() {
        totalClientsCreated = 0;
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
        if (amount <= 0.0) {
            return false;
        }
        if (depositBalance >= amount) {
            depositBalance -= amount;
            return true;
        }
        return false;
    }

    public void blockDepositFundsWithException(double amount) throws InsufficientDepositException {
        if (amount <= 0.0) {
            throw new IllegalArgumentException("Сумма должна быть положительной: " + amount);
        }
        if (depositBalance < amount) {
            throw new InsufficientDepositException(
                "Недостаточно средств на депозите. Требуется: " + amount + ", доступно: " + depositBalance,
                amount,
                depositBalance
            );
        }
        depositBalance -= amount;
    }

    public void validateClientData() throws InvalidClientException {
        if (firstName == null || firstName.trim().isEmpty()) {
            throw new InvalidClientException("Имя клиента не может быть пустым");
        }
        if (lastName == null || lastName.trim().isEmpty()) {
            throw new InvalidClientException("Фамилия клиента не может быть пустой");
        }
        if (phoneNumber == null || phoneNumber.trim().isEmpty()) {
            throw new InvalidClientException("Номер телефона не может быть пустым");
        }
        if (clientId <= 0) {
            throw new InvalidClientException("ID клиента должен быть положительным числом: " + clientId);
        }
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

    public ClientReal setFirstName(String firstName) {
        this.firstName = firstName;
        return this;
    }

    public ClientReal setLastName(String lastName) {
        this.lastName = lastName;
        return this;
    }

    public ClientReal setPhoneNumber(String phoneNumber) {
        this.phoneNumber = phoneNumber;
        return this;
    }

    public ClientReal addDeposit(double amount) {
        this.addToDeposit(amount);
        return this;
    }

    public boolean isSameAs(Client other) {
        if (other == null) {
            return false;
        }
        return this.clientId == other.getClientId();
    }

    public boolean isSameInstance(Client other) {
        return this == other;
    }

    /**
     * Деконструктор (финализатор).
     * Вызывается перед удалением объекта сборщиком мусора.
     */
    @Override
    protected void finalize() throws Throwable {
        try {
            // Освобождение ресурсов (если необходимо)
        } finally {
            super.finalize();
        }
    }
}
