package videoprokat;

import java.util.ArrayList;
import java.util.List;

/**
 * Реализация класса Rental.
 * Содержит конкретную реализацию всех методов абстрактного класса Rental.
 */
public class RentalReal extends Rental {

    /**
     * Конструктор по умолчанию.
     */
    public RentalReal() {
        this.items = new ArrayList<>();
    }

    /**
     * Конструктор с параметрами.
     */
    public RentalReal(int rentalId, Client client, List<VideoCarrier> items,
                      String rentalDate, String plannedReturnDate) {
        super(rentalId, client, new ArrayList<>(items), rentalDate, plannedReturnDate);
        this.items = new ArrayList<>(items);
    }

    @Override
    public int getRentalId() {
        return rentalId;
    }

    @Override
    public Client getClient() {
        return client;
    }

    @Override
    public List<VideoCarrier> getItems() {
        return items;
    }

    @Override
    public String getRentalDate() {
        return rentalDate;
    }

    @Override
    public String getPlannedReturnDate() {
        return plannedReturnDate;
    }

    @Override
    public double getDepositAmount() {
        return depositAmount;
    }

    @Override
    public double getRentalCost() {
        return rentalCost;
    }

    @Override
    public String getStatus() {
        return status;
    }

    @Override
    public void setCalculatedAmounts(FinancialCalculator calculator, int days) {
        if (calculator != null) {
            depositAmount = calculator.calculateDeposit(items);
            rentalCost = calculator.calculateRentalCost(items, days);
        }
    }

    @Override
    public double closeRental(double overdueFine) {
        status = "closed";
        return rentalCost + overdueFine;
    }

    /**
     * Деконструктор (финализатор).
     * Вызывается перед удалением объекта сборщиком мусора.
     */
    @Override
    protected void finalize() throws Throwable {
        try {
            if (items != null) {
                items.clear();
            }
        } finally {
            super.finalize();
        }
    }
}
