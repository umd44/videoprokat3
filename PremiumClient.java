package videoprokat;

/**
 * Премиальный клиент видеопроката.
 * Имеет систему лояльности, скидки и уведомления.
 * Наследует Client и реализует интерфейсы Discountable и Notifiable.
 */
public class PremiumClient extends ClientReal implements Discountable, Notifiable {

    private double discountPercentage;
    private int loyaltyPoints;
    private String email;
    private String phoneNumberForNotification;
    private String preferredNotificationMethod;

    /**
     * Конструктор премиального клиента.
     * @param clientId - идентификатор клиента
     * @param firstName - имя клиента
     * @param lastName - фамилия клиента
     * @param phoneNumber - номер телефона
     * @param email - email адрес
     * @param discountPercentage - процент скидки для премиального клиента
     */
    public PremiumClient(int clientId, String firstName, String lastName,
                        String phoneNumber, String email, double discountPercentage) {
        super(clientId, firstName, lastName, phoneNumber);
        this.discountPercentage = discountPercentage;
        this.loyaltyPoints = 0;
        this.email = email;
        this.phoneNumberForNotification = phoneNumber;
        this.preferredNotificationMethod = "email";
    }

    /**
     * Получить процент скидки.
     * @return процент скидки
     */
    @Override
    public double getDiscountPercentage() {
        return discountPercentage;
    }

    /**
     * Применить скидку к сумме.
     * @param amount - исходная сумма
     * @return сумма с учетом скидки
     */
    @Override
    public double applyDiscount(double amount) {
        double discountedAmount = amount * (1.0 - discountPercentage / 100.0);
        // Добавляем бонусные баллы лояльности (1 балл за каждые 10 единиц скидки)
        int bonusPoints = (int)((amount - discountedAmount) / 10);
        loyaltyPoints += bonusPoints;
        return discountedAmount;
    }

    /**
     * Отправить уведомление клиенту.
     * @param message - сообщение уведомления
     */
    @Override
    public void sendNotification(String message) {
        if ("email".equals(preferredNotificationMethod)) {
            System.out.println("[EMAIL to " + email + "] " + message);
        } else if ("sms".equals(preferredNotificationMethod)) {
            System.out.println("[SMS to " + phoneNumberForNotification + "] " + message);
        } else {
            System.out.println("[NOTIFICATION] " + message);
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
        if ("email".equals(method) || "sms".equals(method)) {
            this.preferredNotificationMethod = method;
        }
    }

    /**
     * Получить количество баллов лояльности.
     * @return количество баллов
     */
    public int getLoyaltyPoints() {
        return loyaltyPoints;
    }

    /**
     * Добавить баллы лояльности.
     * @param points - количество баллов для добавления
     */
    public void addLoyaltyPoints(int points) {
        loyaltyPoints += points;
    }

    /**
     * Использовать баллы лояльности для дополнительной скидки.
     * @param pointsToUse - количество баллов для использования
     * @return дополнительная скидка в рублях
     */
    public double useLoyaltyPoints(int pointsToUse) {
        if (pointsToUse <= loyaltyPoints) {
            loyaltyPoints -= pointsToUse;
            return pointsToUse * 0.1; // 0.1 рубля за каждый балл
        }
        return 0.0;
    }

    /**
     * Получить email адрес.
     * @return email
     */
    public String getEmail() {
        return email;
    }

    /**
     * Установить email адрес.
     * @param email - новый email
     */
    public void setEmail(String email) {
        this.email = email;
    }
}
