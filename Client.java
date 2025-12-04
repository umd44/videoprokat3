package videoprokat;

/**
 * Абстрактный класс, описывающий клиента видеопроката.
 * Содержит базовую структуру и методы для работы с клиентом.
 */
public abstract class Client {

    protected int clientId;
    protected String firstName;
    protected String lastName;
    protected String phoneNumber;
    protected double depositBalance;
    protected boolean blacklisted;

    /**
     * Конструктор по умолчанию.
     * Инициализирует все поля значениями по умолчанию.
     */
    protected Client() {
        this.clientId = 0;
        this.firstName = "";
        this.lastName = "";
        this.phoneNumber = "";
        this.depositBalance = 0.0;
        this.blacklisted = false;
    }

    /**
     * Конструктор с параметрами.
     */
    protected Client(int clientId, String firstName, String lastName, String phoneNumber) {
        this.clientId = clientId;
        this.firstName = firstName;
        this.lastName = lastName;
        this.phoneNumber = phoneNumber;
        this.depositBalance = 0.0;
        this.blacklisted = false;
    }

    /**
     * Получить идентификатор клиента.
     */
    public abstract int getClientId();

    /**
     * Получить имя клиента.
     */
    public abstract String getFirstName();

    /**
     * Получить фамилию клиента.
     */
    public abstract String getLastName();

    /**
     * Получить номер телефона клиента.
     */
    public abstract String getPhoneNumber();

    /**
     * Получить баланс депозита клиента.
     */
    public abstract double getDepositBalance();

    /**
     * Проверить, находится ли клиент в черном списке.
     */
    public abstract boolean isBlacklisted();

    /**
     * Пополнить депозит клиента.
     * Не абстрактный метод с реализацией по умолчанию для возможности переопределения.
     */
    public void addToDeposit(double amount) {
        if (amount > 0.0) {
            depositBalance += amount;
        }
    }

    /**
     * Заблокировать средства депозита.
     * Не абстрактный метод с реализацией по умолчанию для возможности переопределения.
     */
    public boolean blockDepositFunds(double amount) {
        if (amount <= 0.0) return false;
        if (depositBalance >= amount) {
            depositBalance -= amount;
            return true;
        }
        return false;
    }

    /**
     * Разблокировать средства депозита.
     */
    public abstract void unblockDepositFunds(double amount);

    /**
     * Установить статус черного списка.
     */
    public abstract void setBlacklisted(boolean value);
}