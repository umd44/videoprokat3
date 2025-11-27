package videoprokat;

import java.util.List;

/**
 * Абстрактный класс, описывающий аренду.
 * Содержит базовую структуру и методы для работы с арендой.
 */
public abstract class Rental {

    protected int rentalId;
    protected Client client;
    protected List<VideoCarrier> items;
    protected String rentalDate;
    protected String plannedReturnDate;
    protected double depositAmount;
    protected double rentalCost;
    protected String status;

    /**
     * Конструктор по умолчанию.
     * Инициализирует все поля значениями по умолчанию.
     */
    protected Rental() {
        this.rentalId = 0;
        this.client = null;
        this.items = null;
        this.rentalDate = "";
        this.plannedReturnDate = "";
        this.depositAmount = 0.0;
        this.rentalCost = 0.0;
        this.status = "active";
    }

    /**
     * Конструктор с параметрами.
     */
    protected Rental(int rentalId, Client client, List<VideoCarrier> items,
                     String rentalDate, String plannedReturnDate) {
        this.rentalId = rentalId;
        this.client = client;
        this.items = items;
        this.rentalDate = rentalDate;
        this.plannedReturnDate = plannedReturnDate;
        this.depositAmount = 0.0;
        this.rentalCost = 0.0;
        this.status = "active";
    }

    /**
     * Получить идентификатор аренды.
     */
    public abstract int getRentalId();

    /**
     * Получить клиента.
     */
    public abstract Client getClient();

    /**
     * Получить список носителей.
     */
    public abstract List<VideoCarrier> getItems();

    /**
     * Получить дату выдачи.
     */
    public abstract String getRentalDate();

    /**
     * Получить плановую дату возврата.
     */
    public abstract String getPlannedReturnDate();

    /**
     * Получить сумму залога.
     */
    public abstract double getDepositAmount();

    /**
     * Получить стоимость аренды.
     */
    public abstract double getRentalCost();

    /**
     * Получить статус аренды.
     */
    public abstract String getStatus();

    /**
     * Установить рассчитанные суммы с помощью калькулятора.
     */
    public abstract void setCalculatedAmounts(FinancialCalculator calculator, int days);

    /**
     * Закрыть аренду и вернуть итоговую сумму к оплате.
     */
    public abstract double closeRental(double overdueFine);
}