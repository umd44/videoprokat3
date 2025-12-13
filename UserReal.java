package videoprokat;

import java.util.HashMap;
import java.util.Map;

/**
 * Реализация класса User.
 * Содержит конкретную реализацию всех методов абстрактного класса User.
 */
public class UserReal extends User {

    private static final Map<String, String[]> ROLE_PERMISSIONS = new HashMap<>();

    static {
        ROLE_PERMISSIONS.put("Operator", new String[]{
            "search_items", "create_rental", "process_return", "view_clients", "register_client", "accept_payment"
        });
        ROLE_PERMISSIONS.put("Senior Operator", new String[]{
            "search_items", "create_rental", "process_return", "view_clients", "register_client", "accept_payment",
            "edit_items", "edit_client_status", "apply_discount", "view_financial_reports", "manage_fines"
        });
        ROLE_PERMISSIONS.put("Administrator", new String[]{
            "search_items", "create_rental", "process_return", "view_clients", "register_client", "accept_payment",
            "edit_items", "edit_client_status", "apply_discount", "view_financial_reports", "manage_fines",
            "manage_users", "edit_dictionaries", "view_all_reports", "system_settings", "writeoff_items"
        });
    }

    /**
     * Конструктор по умолчанию.
     */
    public UserReal() {
        super();
    }

    /**
     * Конструктор с параметрами.
     */
    public UserReal(int userId, String username, String password, String role, String fullName) {
        super(userId, username, password, role, fullName);
    }

    @Override
    public int getUserId() {
        return userId;
    }

    @Override
    public String getUsername() {
        return username;
    }

    @Override
    public String getRole() {
        return role;
    }

    @Override
    public String getFullName() {
        return fullName;
    }

    @Override
    public boolean isActive() {
        return active;
    }

    @Override
    public boolean checkPassword(String password) {
        return this.password.equals(password);
    }

    @Override
    public boolean hasPermission(String permission) {
        String[] permissions = ROLE_PERMISSIONS.get(role);
        if (permissions == null) {
            return false;
        }
        for (String p : permissions) {
            if (p.equals(permission)) {
                return true;
            }
        }
        return false;
    }

    @Override
    public void setActive(boolean active) {
        this.active = active;
    }
}
