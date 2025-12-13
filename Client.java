package videoprokat;

/**
 * Абстрактный класс, описывающий клиента видеопроката.
 * Содержит базовую структуру и методы для работы с клиентом.
 */
public abstract class Client {

    protected int clientId;
    protected String firstName;
    protected String lastName;
    protected String middleName;
    protected String phoneNumber;
    protected String email;
    protected String passportSeries;
    protected String passportNumber;
    protected String address;
    protected String birthDate;
    protected String registrationDate;
    protected double depositBalance;
    protected boolean blacklisted;
    protected String blacklistReason;
    protected int bonusPoints;
    protected String status;

    /**
     * Конструктор по умолчанию.
     * Инициализирует все поля значениями по умолчанию.
     */
    protected Client() {
        this.clientId = 0;
        this.firstName = "";
        this.lastName = "";
        this.middleName = "";
        this.phoneNumber = "";
        this.email = "";
        this.passportSeries = "";
        this.passportNumber = "";
        this.address = "";
        this.birthDate = "";
        this.registrationDate = "";
        this.depositBalance = 0.0;
        this.blacklisted = false;
        this.blacklistReason = "";
        this.bonusPoints = 0;
        this.status = "Active";
    }

    /**
     * Конструктор с параметрами.
     */
    protected Client(int clientId, String firstName, String lastName, String phoneNumber) {
        this.clientId = clientId;
        this.firstName = firstName;
        this.lastName = lastName;
        this.middleName = "";
        this.phoneNumber = phoneNumber;
        this.email = "";
        this.passportSeries = "";
        this.passportNumber = "";
        this.address = "";
        this.birthDate = "";
        this.registrationDate = "";
        this.depositBalance = 0.0;
        this.blacklisted = false;
        this.blacklistReason = "";
        this.bonusPoints = 0;
        this.status = "Active";
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
     */
    public abstract void addToDeposit(double amount);

    /**
     * Заблокировать средства депозита.
     */
    public abstract boolean blockDepositFunds(double amount);

    /**
     * Разблокировать средства депозита.
     */
    public abstract void unblockDepositFunds(double amount);

    /**
     * Установить статус черного списка.
     */
    public abstract void setBlacklisted(boolean value);

    /**
     * Получить отчество клиента.
     */
    public abstract String getMiddleName();

    /**
     * Получить email клиента.
     */
    public abstract String getEmail();

    /**
     * Получить серию паспорта клиента.
     */
    public abstract String getPassportSeries();

    /**
     * Получить номер паспорта клиента.
     */
    public abstract String getPassportNumber();

    /**
     * Получить адрес клиента.
     */
    public abstract String getAddress();

    /**
     * Получить дату рождения клиента.
     */
    public abstract String getBirthDate();

    /**
     * Получить дату регистрации клиента.
     */
    public abstract String getRegistrationDate();

    /**
     * Получить причину блокировки клиента.
     */
    public abstract String getBlacklistReason();

    /**
     * Получить количество бонусных баллов клиента.
     */
    public abstract int getBonusPoints();

    /**
     * Получить статус клиента.
     */
    public abstract String getStatus();

    /**
     * Установить отчество клиента.
     */
    public abstract void setMiddleName(String middleName);

    /**
     * Установить email клиента.
     */
    public abstract void setEmail(String email);

    /**
     * Установить серию и номер паспорта клиента.
     */
    public abstract void setPassport(String series, String number);

    /**
     * Установить адрес клиента.
     */
    public abstract void setAddress(String address);

    /**
     * Установить дату рождения клиента.
     */
    public abstract void setBirthDate(String birthDate);

    /**
     * Установить дату регистрации клиента.
     */
    public abstract void setRegistrationDate(String registrationDate);

    /**
     * Установить причину блокировки клиента.
     */
    public abstract void setBlacklistReason(String reason);

    /**
     * Начислить бонусные баллы клиенту.
     */
    public abstract void addBonusPoints(int points);

    /**
     * Списать бонусные баллы клиента.
     */
    public abstract boolean useBonusPoints(int points);

    /**
     * Установить статус клиента.
     */
    public abstract void setStatus(String status);
}