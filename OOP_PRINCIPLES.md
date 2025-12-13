# Реализация принципов ООП в проекте Видеопрокат

## Краткий справочник

Данный документ содержит краткое описание реализации трех основных принципов объектно-ориентированного программирования в проекте.

---

## 1. Инкапсуляция (Encapsulation)

### Определение
Сокрытие внутренней реализации и предоставление контролируемого доступа к данным через публичные методы.

### Реализация в проекте

#### Пример 1: Защита данных клиента
```java
public abstract class Client {
    protected double depositBalance;  // Защищенное поле
    
    // Контролируемое изменение с валидацией
    public abstract void addToDeposit(double amount);
    public abstract boolean blockDepositFunds(double amount);
}

public class ClientReal extends Client {
    @Override
    public void addToDeposit(double amount) {
        if (amount > 0.0) {  // Валидация
            depositBalance += amount;
        }
    }
}
```

#### Пример 2: Контроль бонусных баллов
```java
public class ClientReal extends Client {
    @Override
    public void addBonusPoints(int points) {
        if (points > 0) {  // Защита от негативных значений
            this.bonusPoints += points;
        }
    }
    
    @Override
    public boolean useBonusPoints(int points) {
        if (points > 0 && this.bonusPoints >= points) {
            this.bonusPoints -= points;
            return true;  // Успешное списание
        }
        return false;  // Недостаточно баллов
    }
}
```

### Преимущества
- ✅ Невозможно напрямую изменить критичные данные
- ✅ Все изменения проходят через валидацию
- ✅ Защита от некорректных состояний объекта
- ✅ Возможность изменить внутреннюю реализацию без влияния на внешний код

---

## 2. Наследование (Inheritance)

### Определение
Механизм создания новых классов на основе существующих с повторным использованием кода.

### Реализация в проекте

#### Иерархия классов
```
Абстрактные базовые классы:
├── User → UserReal
├── Client → ClientReal
├── VideoCarrier → VideoCarrierReal
├── Catalog → CatalogReal
├── Rental → RentalReal
├── RentalManager → RentalManagerReal
├── FinancialCalculator → FinancialCalculatorReal
└── ReportGenerator → ReportGeneratorReal
```

#### Пример: Наследование VideoCarrier
```java
// Базовый класс с общей функциональностью
public abstract class VideoCarrier {
    protected int inventoryNumber;
    protected String title;
    protected String status;
    
    protected VideoCarrier() {
        this.status = "available";  // Инициализация по умолчанию
    }
    
    public abstract boolean isAvailable();
    public abstract void markAsRented();
}

// Конкретная реализация наследует все поля и методы
public class VideoCarrierReal extends VideoCarrier {
    public VideoCarrierReal(int inventoryNumber, String title, ...) {
        super();  // Вызов конструктора родителя
        this.inventoryNumber = inventoryNumber;
        this.title = title;
    }
    
    @Override
    public boolean isAvailable() {
        return "available".equals(status);  // Доступ к полям родителя
    }
    
    @Override
    public void markAsRented() {
        status = "rented";
    }
}
```

### Преимущества
- ✅ Повторное использование кода базовых классов
- ✅ Единая структура данных для всех наследников
- ✅ Расширение функциональности без изменения базового класса
- ✅ Логическая группировка связанных классов

---

## 3. Полиморфизм (Polymorphism)

### Определение
Способность объектов разных классов реагировать на одни и те же методы по-разному через общий интерфейс.

### Реализация в проекте

#### Пример 1: Работа через абстрактные типы
```java
public class VideoprokatFinalDemo {
    public static void main(String[] args) {
        // Полиморфное присваивание
        Catalog catalog = new CatalogReal();
        Client client = new ClientReal(1, "Ivan", "Ivanov", "+7-123");
        VideoCarrier movie = new VideoCarrierReal(100, "Matrix", "DVD", "Sci-Fi", 50, 500);
        
        // Полиморфные вызовы - работают для любой реализации
        catalog.addItem(movie);
        VideoCarrier found = catalog.findItemByNumber(100);
        
        // Можно легко заменить реализацию
        RentalManager manager = new RentalManagerReal();
    }
}
```

#### Пример 2: Полиморфизм в коллекциях
```java
public class CatalogReal extends Catalog {
    @Override
    public List<VideoCarrier> getAvailableItems() {
        List<VideoCarrier> result = new ArrayList<>();
        for (VideoCarrier item : items) {
            // Полиморфный вызов - не важен конкретный тип
            if (item != null && item.isAvailable()) {
                result.add(item);
            }
        }
        return result;
    }
}
```

#### Пример 3: Разное поведение через один интерфейс
```java
public class RentalManagerReal extends RentalManager {
    @Override
    public double processReturnWithDamage(Rental rental, int overdueDays, 
                                           VideoCarrier damagedItem, 
                                           String damageType, 
                                           double compensation) {
        for (VideoCarrier item : rental.getItems()) {
            if (item == damagedItem) {
                // Один метод setStatus(), но разное поведение
                if ("critical".equalsIgnoreCase(damageType)) {
                    item.setStatus("written_off");
                } else if ("minor".equalsIgnoreCase(damageType)) {
                    item.setStatus("maintenance");
                } else {
                    item.markAsAvailable();
                }
            }
        }
        return rental.closeRental(fine + compensation);
    }
}
```

### Преимущества
- ✅ Единый интерфейс для разных реализаций
- ✅ Легко добавлять новые реализации
- ✅ Упрощение кода - не нужно знать конкретный тип
- ✅ Гибкость - можно менять реализацию в runtime

---

## Комбинированное использование всех трех принципов

```java
public void demonstrateOOP() {
    // ПОЛИМОРФИЗМ: работаем через абстрактные типы
    Client client = new ClientReal(1, "Ivan", "Petrov", "+7-123");
    Catalog catalog = new CatalogReal();
    RentalManager manager = new RentalManagerReal();
    
    // ИНКАПСУЛЯЦИЯ: контролируемое изменение данных
    client.addToDeposit(1000.0);
    double balance = client.getDepositBalance();
    
    // НАСЛЕДОВАНИЕ: используем функциональность базовых классов
    VideoCarrier movie = new VideoCarrierReal(100, "Matrix", "DVD", "Sci-Fi", 50, 500);
    movie.setReleaseYear(1999);
    movie.setDirector("Wachowski");
    
    catalog.addItem(movie);
    
    // ПОЛИМОРФИЗМ: работает независимо от реализации
    List<VideoCarrier> available = catalog.getAvailableItems();
    Rental rental = manager.createRental(client, available, 3, "2025-01-15", "2025-01-18");
}
```

---

## Сводная таблица

| Принцип | Где применяется | Ключевые слова | Примеры классов |
|---------|-----------------|----------------|-----------------|
| **Инкапсуляция** | Все классы | `protected`, `private`, геттеры/сеттеры | `Client`, `VideoCarrier`, `Rental` |
| **Наследование** | Все модули | `extends`, `super`, `@Override` | `ClientReal extends Client` |
| **Полиморфизм** | Вся система | абстрактные типы, переопределение методов | `Catalog catalog = new CatalogReal()` |

---

## Заключение

Все три принципа ООП тесно взаимосвязаны и работают вместе:

1. **Инкапсуляция** защищает данные и обеспечивает их целостность
2. **Наследование** позволяет создавать иерархии классов и повторно использовать код
3. **Полиморфизм** обеспечивает гибкость и расширяемость системы

Благодаря правильному применению этих принципов, система видеопроката получилась:
- **Надежной** - невозможно установить некорректное состояние
- **Расширяемой** - легко добавлять новую функциональность
- **Поддерживаемой** - код логически организован и понятен
- **Гибкой** - можно легко менять реализацию без влияния на другие части системы
