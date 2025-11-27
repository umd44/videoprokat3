package videoprokat;

/**
 * Реализация класса Client.
 * Содержит конкретную реализацию всех методов абстрактного класса Client.
 */
public class ClientReal extends Client {

    /**
     * Количество созданных клиентов (демонстрация статического поля).
     */
    private static int totalClientsCreated = 0;

    /**
     * Конструктор по умолчанию.
     */
    public ClientReal() {
        super();
        totalClientsCreated++;
    }

    /**
     * Конструктор с параметрами.
     */
    public ClientReal(int clientId, String firstName, String lastName, String phoneNumber) {
        super(clientId, firstName, lastName, phoneNumber);
        totalClientsCreated++;
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

    /**
     * Возвращает количество созданных клиентов (статический метод).
     */
    public static int getTotalClientsCreated() {
        return totalClientsCreated;
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
