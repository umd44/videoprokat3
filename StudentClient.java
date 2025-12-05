package videoprokat;

/**
 * Студентский клиент видеопроката.
 * Имеет специальные скидки и возможность льготного проката.
 * Наследует Client и реализует интерфейсы Discountable и Notifiable.
 */
public class StudentClient extends ClientReal implements Discountable, Notifiable {

    private String university;
    private String studentId;
    private String specialization;
    private int discountPercentage;
    private String email;
    private String preferredNotificationMethod;
    private boolean validStudent;

    /**
     * Конструктор студентского клиента.
     * @param clientId - идентификатор клиента
     * @param firstName - имя студента
     * @param lastName - фамилия студента
     * @param phoneNumber - номер телефона
     * @param university - название университета
     * @param studentId - студенческий номер
     * @param specialization - специальность
     * @param email - email студента
     */
    public StudentClient(int clientId, String firstName, String lastName,
                        String phoneNumber, String university, String studentId,
                        String specialization, String email) {
        super(clientId, firstName, lastName, phoneNumber);
        this.university = university;
        this.studentId = studentId;
        this.specialization = specialization;
        this.discountPercentage = 20; // Базовая скидка для студентов
        this.email = email;
        this.preferredNotificationMethod = "email";
        this.validStudent = true; // Предполагаем валидного студента при создании
    }

    /**
     * Получить процент скидки.
     * @return процент скидки
     */
    @Override
    public double getDiscountPercentage() {
        return validStudent ? discountPercentage : 0.0;
    }

    /**
     * Применить скидку к сумме.
     * @param amount - исходная сумма
     * @return сумма с учетом скидки
     */
    @Override
    public double applyDiscount(double amount) {
        if (!validStudent) {
            return amount; // Нет скидки, если студент не валиден
        }
        return amount * (1.0 - discountPercentage / 100.0);
    }

    /**
     * Отправить уведомление студенту.
     * @param message - сообщение уведомления
     */
    @Override
    public void sendNotification(String message) {
        if ("email".equals(preferredNotificationMethod)) {
            System.out.println("[STUDENT EMAIL to " + email + "] " + message);
        } else if ("sms".equals(preferredNotificationMethod)) {
            System.out.println("[STUDENT SMS to " + phoneNumber + "] " + message);
        } else {
            System.out.println("[STUDENT NOTIFICATION] " + message);
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
     * Получить название университета.
     * @return название университета
     */
    public String getUniversity() {
        return university;
    }

    /**
     * Получить студенческий номер.
     * @return студенческий номер
     */
    public String getStudentId() {
        return studentId;
    }

    /**
     * Получить специальность.
     * @return специальность
     */
    public String getSpecialization() {
        return specialization;
    }

    /**
     * Проверить, валиден ли студент (например, пока он обучается).
     * @return true, если студент валиден
     */
    public boolean isValidStudent() {
        return validStudent;
    }

    /**
     * Установить статус валидности студента.
     * @param valid - новый статус валидности
     */
    public void setValidStudent(boolean valid) {
        this.validStudent = valid;
        if (!valid) {
            System.out.println("Статус студента '" + firstName + " " + lastName + "' больше не валиден. Скидка удалена.");
        }
    }

    /**
     * Получить email студента.
     * @return email
     */
    public String getEmail() {
        return email;
    }

    /**
     * Установить email студента.
     * @param email - новый email
     */
    public void setEmail(String email) {
        this.email = email;
    }
}
