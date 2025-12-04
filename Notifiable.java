package videoprokat;

/**
 * Интерфейс для объектов, которым можно отправлять уведомления.
 * Демонстрирует использование интерфейсов в Java.
 */
public interface Notifiable {
    
    /**
     * Отправить уведомление.
     */
    void sendNotification(String message);
    
    /**
     * Получить предпочитаемый метод уведомления.
     */
    String getPreferredNotificationMethod();
}
