package videoprokat;

/**
 * ВИП клиент видеопроката.
 * Специальный статус с максимальными привилегиями и персональным обслуживанием.
 * Наследует Client и реализует интерфейсы Discountable и Notifiable.
 */
public class VIPClient extends ClientReal implements Discountable, Notifiable {

    private String vipTier; // platinum, gold, silver
    private double loyaltyMultiplier;
    private String personalManagerName;
    private String email;
    private String phoneNumberForNotification;
    private String preferredNotificationMethod;
    private int priorityLevel; // 1 = highest, 3 = lowest
    private double accumulatedCashback;

    /**
     * Конструктор ВИП клиента.
     * @param clientId - идентификатор клиента
     * @param firstName - имя клиента
     * @param lastName - фамилия клиента
     * @param phoneNumber - номер телефона
     * @param vipTier - уровень ВИП (platinum, gold, silver)
     * @param email - email адрес
     * @param personalManagerName - имя персонального менеджера
     */
    public VIPClient(int clientId, String firstName, String lastName, String phoneNumber,
                     String vipTier, String email, String personalManagerName) {
        super(clientId, firstName, lastName, phoneNumber);
        this.vipTier = vipTier;
        this.personalManagerName = personalManagerName;
        this.email = email;
        this.phoneNumberForNotification = phoneNumber;
        this.preferredNotificationMethod = "email";
        this.accumulatedCashback = 0.0;
        this.loyaltyMultiplier = calculateLoyaltyMultiplier(vipTier);
        this.priorityLevel = calculatePriorityLevel(vipTier);
    }

    /**
     * Рассчитать множитель лояльности на основе уровня ВИП.
     * @param tier - уровень ВИП
     * @return множитель лояльности
     */
    private double calculateLoyaltyMultiplier(String tier) {
        switch (tier) {
            case "platinum": return 3.0;
            case "gold": return 2.0;
            case "silver": return 1.5;
            default: return 1.0;
        }
    }

    /**
     * Рассчитать приоритет на основе уровня ВИП.
     * @param tier - уровень ВИП
     * @return приоритет (1 = высший)
     */
    private int calculatePriorityLevel(String tier) {
        switch (tier) {
            case "platinum": return 1;
            case "gold": return 2;
            case "silver": return 3;
            default: return 4;
        }
    }

    /**
     * Получить процент скидки для ВИП клиента.
     * @return процент скидки
     */
    @Override
    public double getDiscountPercentage() {
        switch (vipTier) {
            case "platinum": return 40.0;
            case "gold": return 30.0;
            case "silver": return 20.0;
            default: return 10.0;
        }
    }

    /**
     * Применить скидку к сумме с накоплением кэшбека.
     * @param amount - исходная сумма
     * @return сумма с учетом скидки
     */
    @Override
    public double applyDiscount(double amount) {
        double discount = getDiscountPercentage();
        double discountedAmount = amount * (1.0 - discount / 100.0);
        
        // Накопление кэшбека (2% от скидки)
        double cashbackAmount = (amount - discountedAmount) * 0.02 * loyaltyMultiplier;
        accumulatedCashback += cashbackAmount;
        
        return discountedAmount;
    }

    /**
     * Отправить уведомление ВИП клиенту.
     * @param message - сообщение уведомления
     */
    @Override
    public void sendNotification(String message) {
        String prefix = "[VIP " + vipTier.toUpperCase() + " ";
        if ("email".equals(preferredNotificationMethod)) {
            System.out.println(prefix + "EMAIL to " + email + "] " + message);
        } else if ("sms".equals(preferredNotificationMethod)) {
            System.out.println(prefix + "SMS to " + phoneNumberForNotification + "] " + message);
        } else if ("phone".equals(preferredNotificationMethod)) {
            System.out.println(prefix + "CALL to " + phoneNumberForNotification + "] " + message);
        } else {
            System.out.println(prefix + "NOTIFICATION] " + message);
        }
    }

    /**
     * Получить предпочтительный способ уведомления.
     * @return способ уведомления
     */
    @Override
    public String getPreferredNotificationMethod() {
        return preferredNotificationMethod;
    }

    /**
     * Установить предпочтительный способ уведомления.
     * @param method - новый способ уведомления
     */
    @Override
    public void setPreferredNotificationMethod(String method) {
        if ("email".equals(method) || "sms".equals(method) || "phone".equals(method)) {
            this.preferredNotificationMethod = method;
        }
    }

    /**
     * Получить уровень ВИП.
     * @return уровень ВИП
     */
    public String getVipTier() {
        return vipTier;
    }

    /**
     * Получить имя персонального менеджера.
     * @return имя менеджера
     */
    public String getPersonalManagerName() {
        return personalManagerName;
    }

    /**
     * Получить уровень приоритета (1 = высший).
     * @return уровень приоритета
     */
    public int getPriorityLevel() {
        return priorityLevel;
    }

    /**
     * Получить накопленный кэшбек.
     * @return сумма кэшбека
     */
    public double getAccumulatedCashback() {
        return accumulatedCashback;
    }

    /**
     * Использовать накопленный кэшбек.
     * @param amount - сумма кэшбека для использования
     * @return действительно использованная сумма
     */
    public double useCashback(double amount) {
        if (amount <= accumulatedCashback) {
            accumulatedCashback -= amount;
            return amount;
        }
        double usedAmount = accumulatedCashback;
        accumulatedCashback = 0.0;
        return usedAmount;
    }

    /**
     * Повысить уровень ВИП.
     * @param newTier - новый уровень ВИП
     */
    public void upgradeTier(String newTier) {
        if ("platinum".equals(newTier) || "gold".equals(newTier) || "silver".equals(newTier)) {
            this.vipTier = newTier;
            this.loyaltyMultiplier = calculateLoyaltyMultiplier(newTier);
            this.priorityLevel = calculatePriorityLevel(newTier);
            System.out.println("Клиент " + firstName + " " + lastName + " повышен до уровня: " + newTier);
        }
    }

    /**
     * Получить информацию о ВИП клиенте.
     * @return строка с информацией
     */
    @Override
    public String toString() {
        return "VIPClient{" +
                "name='" + firstName + " " + lastName + '\'' +
                ", vipTier='" + vipTier + '\'' +
                ", discount=" + getDiscountPercentage() + "%" +
                ", cashback=" + accumulatedCashback +
                ", manager='" + personalManagerName + '\'' +
                '}';
    }
}
