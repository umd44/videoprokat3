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
        try {
            validateRentalInput(client, items, days);
            List<VideoCarrier> safeItems = new ArrayList<>(items);
            Rental rental = new RentalReal(nextId++, client, safeItems, rentalDate, plannedReturnDate);
            rental.setCalculatedAmounts(calculator, days);
            for (VideoCarrier item : safeItems) {
                if (item == null) {
                    throw new IllegalArgumentException("Обнаружен пустой носитель в списке аренды");
                }
                item.markAsRented();
            }
            activeRentals.add(rental);
            return rental;
        } catch (IllegalArgumentException e) {
            throw new RentalOperationException("Не удалось создать аренду: " + e.getMessage(), e);
        } catch (RuntimeException e) {
            throw new RentalOperationException("Внутренняя ошибка при создании аренды", e);
        }
    }

    @Override
    public double processReturn(Rental rental, int overdueDays) {
        try {
            if (rental == null) {
                throw new IllegalArgumentException("Аренда не найдена");
            }
            if (overdueDays < 0) {
                throw new IllegalArgumentException("Просрочка не может быть отрицательной");
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
        } catch (IllegalArgumentException e) {
            throw new RentalOperationException("Ошибка при обработке возврата: " + e.getMessage(), e);
        } catch (RuntimeException e) {
            throw new RentalOperationException("Внутренняя ошибка при обработке возврата", e);
        }
    }

    private void validateRentalInput(Client client, List<VideoCarrier> items, int days) {
        if (client == null) {
            throw new IllegalArgumentException("Клиент не задан");
        }
        if (items == null || items.isEmpty()) {
            throw new IllegalArgumentException("Список носителей пуст");
        }
        if (days <= 0) {
            throw new IllegalArgumentException("Количество дней должно быть положительным");
        }
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
