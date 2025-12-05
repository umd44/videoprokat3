package videoprokat;

/**
 * Интерфейс для объектов, которые могут получать уведомления.
 * Определяет методы для отправки различных типов уведомлений.
 */
public interface Notifiable {
    /**
     * Отправить уведомление клиенту.
     * @param message - сообщение уведомления
     */
    void sendNotification(String message);

    /**
     * Получить предпочтительный способ уведомления.
     * @return способ уведомления (email, SMS, push и т.д.)
     */
    String getPreferredNotificationMethod();

    /**
     * Установить предпочтительный способ уведомления.
     * @param method - новый способ уведомления
     */
    void setPreferredNotificationMethod(String method);
}
