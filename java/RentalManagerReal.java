package videoprokat;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * Реализация класса RentalManager.
 * Содержит конкретную реализацию всех методов абстрактного класса RentalManager.
 */
public class RentalManagerReal extends RentalManager {

    private static int nextId = 1;

    /**
     * Конструктор по умолчанию.
     * Инициализирует список активных аренд и калькулятор.
     */
    public RentalManagerReal() {
        this.activeRentals = new ArrayList<>();
        this.calculator = new FinancialCalculatorReal();
    }

    @Override
    public Rental createRental(Client client, List<VideoCarrier> items, int days,
                               String rentalDate, String plannedReturnDate) {
        if (client == null || items == null || items.isEmpty() || days <= 0) {
            return null;
        }
        List<VideoCarrier> safeItems = new ArrayList<>(items);
        Rental rental = new RentalReal(nextId++, client, safeItems, rentalDate, plannedReturnDate);
        rental.setCalculatedAmounts(calculator, days);
        for (VideoCarrier item : safeItems) {
            if (item != null) {
                item.markAsRented();
            }
        }
        activeRentals.add(rental);
        return rental;
    }

    public Rental createRentalWithException(Client client, List<VideoCarrier> items, int days,
                                            String rentalDate, String plannedReturnDate) throws RentalException {
        if (client == null) {
            throw new RentalException("Клиент не может быть null");
        }
        if (items == null || items.isEmpty()) {
            throw new RentalException("Список носителей не может быть пустым");
        }
        if (days <= 0) {
            throw new RentalException("Количество дней должно быть положительным: " + days);
        }
        
        for (VideoCarrier item : items) {
            if (item == null) {
                throw new RentalException("Элемент в списке не может быть null");
            }
            if (!item.isAvailable()) {
                throw new RentalException("Носитель " + item.getTitle() + " недоступен для аренды");
            }
        }
        
        try {
            List<VideoCarrier> safeItems = new ArrayList<>(items);
            Rental rental = new RentalReal(nextId++, client, safeItems, rentalDate, plannedReturnDate);
            rental.setCalculatedAmounts(calculator, days);
            for (VideoCarrier item : safeItems) {
                item.markAsRented();
            }
            activeRentals.add(rental);
            return rental;
        } catch (Exception e) {
            throw new RentalException("Ошибка при создании аренды: " + e.getMessage(), e);
        }
    }

    @Override
    public double processReturn(Rental rental, int overdueDays) {
        if (rental == null) {
            return 0.0;
        }
        double fine = calculator.calculateOverdueFine(overdueDays);
        for (VideoCarrier item : rental.getItems()) {
            if (item != null) {
                item.markAsAvailable();
            }
        }
        double total = rental.closeRental(fine);
        Iterator<Rental> iterator = activeRentals.iterator();
        while (iterator.hasNext()) {
            if (iterator.next() == rental) {
                iterator.remove();
                break;
            }
        }
        return total;
    }

    @Override
    public List<Rental> getOverdueRentals(String currentDate) {
        List<Rental> result = new ArrayList<>();
        for (Rental rental : activeRentals) {
            if (rental != null && "active".equals(rental.getStatus())) {
                result.add(rental);
            }
        }
        return result;
    }

    @Override
    public void close() {
        if (activeRentals != null) {
            activeRentals.clear();
        }
        calculator = null;
    }

    public static int getNextRentalId() {
        return nextId;
    }

    public static void resetRentalIdCounter() {
        nextId = 1;
    }

    /**
     * Деконструктор (финализатор).
     * Вызывается перед удалением объекта сборщиком мусора.
     */
    @Override
    protected void finalize() throws Throwable {
        try {
            close();
        } finally {
            super.finalize();
        }
    }
}
