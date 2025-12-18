package videoprokat;

/**
 * Абстрактный класс, описывающий пользователя системы (оператора).
 * Содержит базовую структуру и методы для работы с пользователем.
 */
public abstract class User {

    protected int userId;
    protected String username;
    protected String password;
    protected String role;
    protected String fullName;
    protected boolean active;

    /**
     * Конструктор по умолчанию.
     */
    protected User() {
        this.userId = 0;
        this.username = "";
        this.password = "";
        this.role = "Operator";
        this.fullName = "";
        this.active = true;
    }

    /**
     * Конструктор с параметрами.
     */
    protected User(int userId, String username, String password, String role, String fullName) {
        this.userId = userId;
        this.username = username;
        this.password = password;
        this.role = role;
        this.fullName = fullName;
        this.active = true;
    }

    /**
     * Получить ID пользователя.
     */
    public abstract int getUserId();

    /**
     * Получить имя пользователя.
     */
    public abstract String getUsername();

    /**
     * Получить роль пользователя.
     */
    public abstract String getRole();

    /**
     * Получить полное имя пользователя.
     */
    public abstract String getFullName();

    /**
     * Получить пароль пользователя (используется для сохранения в файл).
     */
    public abstract String getPassword();

    /**
     * Проверить активен ли пользователь.
     */
    public abstract boolean isActive();

    /**
     * Проверить пароль.
     */
    public abstract boolean checkPassword(String password);

    /**
     * Проверить, имеет ли пользователь право на операцию.
     */
    public abstract boolean hasPermission(String permission);

    /**
     * Установить активность пользователя.
     */
    public abstract void setActive(boolean active);
}
