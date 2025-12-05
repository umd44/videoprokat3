package videoprokat;

/**
 * Корпоративный клиент видеопроката.
 * Имеет корпоративные скидки на основе размера компании.
 * Наследует Client и реализует интерфейс Discountable.
 */
public class CorporateClient extends ClientReal implements Discountable {

    private String companyName;
    private String taxNumber;
    private int employeeCount;
    private double corporateDiscount;
    private String contactPerson;

    /**
     * Конструктор корпоративного клиента.
     * @param clientId - идентификатор клиента
     * @param firstName - имя контактного лица
     * @param lastName - фамилия контактного лица
     * @param phoneNumber - номер телефона
     * @param companyName - название компании
     * @param taxNumber - налоговый номер
     * @param employeeCount - количество сотрудников
     */
    public CorporateClient(int clientId, String firstName, String lastName,
                          String phoneNumber, String companyName, String taxNumber,
                          int employeeCount) {
        super(clientId, firstName, lastName, phoneNumber);
        this.companyName = companyName;
        this.taxNumber = taxNumber;
        this.employeeCount = employeeCount;
        this.contactPerson = firstName + " " + lastName;
        this.corporateDiscount = calculateCorporateDiscount();
    }

    /**
     * Рассчитать корпоративную скидку на основе размера компании.
     * @return процент скидки
     */
    protected double calculateCorporateDiscount() {
        if (employeeCount > 500) return 35.0;
        if (employeeCount > 200) return 30.0;
        if (employeeCount > 100) return 25.0;
        if (employeeCount > 50) return 20.0;
        if (employeeCount > 10) return 15.0;
        return 10.0;
    }

    /**
     * Получить процент скидки.
     * @return процент скидки
     */
    @Override
    public double getDiscountPercentage() {
        return corporateDiscount;
    }

    /**
     * Применить скидку к сумме.
     * @param amount - исходная сумма
     * @return сумма с учетом скидки
     */
    @Override
    public double applyDiscount(double amount) {
        return amount * (1.0 - corporateDiscount / 100.0);
    }

    /**
     * Получить название компании.
     * @return название компании
     */
    public String getCompanyName() {
        return companyName;
    }

    /**
     * Получить налоговый номер.
     * @return налоговый номер
     */
    public String getTaxNumber() {
        return taxNumber;
    }

    /**
     * Получить количество сотрудников.
     * @return количество сотрудников
     */
    public int getEmployeeCount() {
        return employeeCount;
    }

    /**
     * Обновить количество сотрудников и пересчитать скидку.
     * @param newEmployeeCount - новое количество сотрудников
     */
    public void updateEmployeeCount(int newEmployeeCount) {
        this.employeeCount = newEmployeeCount;
        this.corporateDiscount = calculateCorporateDiscount();
    }

    /**
     * Получить контактное лицо.
     * @return имя контактного лица
     */
    public String getContactPerson() {
        return contactPerson;
    }
}
