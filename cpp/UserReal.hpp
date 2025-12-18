#pragma once
#include "User.hpp"
#include <string>
#include <vector>
#include <map>

/**
 * Реализация класса User.
 * Содержит конкретную реализацию всех методов абстрактного класса User.
 */
class UserReal : public User
{
private:
    static std::map<std::string, std::vector<std::string>> initRolePermissions();

    static const std::map<std::string, std::vector<std::string>> ROLE_PERMISSIONS;

public:
    /**
     * Конструктор по умолчанию.
     */
    UserReal();

    /**
     * Конструктор с параметрами.
     */
    UserReal(int userId, const std::string& username, const std::string& password, 
             const std::string& role, const std::string& fullName);

    virtual ~UserReal();

    int getUserId() override;
    std::string getUsername() override;
    std::string getPassword() override;
    std::string getRole() override;
    std::string getFullName() override;
    bool isActive() override;
    bool checkPassword(const std::string& password) override;
    bool hasPermission(const std::string& permission) override;
    void setActive(bool active) override;
};



