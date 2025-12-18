#pragma once
#include <string>

/**
 * Абстрактный класс, описывающий пользователя системы (оператора).
 * Содержит базовую структуру и методы для работы с пользователем.
 */
class User
{
protected:
    int userId;
    std::string username;
    std::string password;
    std::string role;
    std::string fullName;
    bool active;

    /**
     * Конструктор по умолчанию.
     */
    User();

    /**
     * Конструктор с параметрами.
     */
    User(int userId, const std::string& username, const std::string& password, 
         const std::string& role, const std::string& fullName);

public:
    virtual ~User() = default;

    /**
     * Получить ID пользователя.
     */
    virtual int getUserId() = 0;

    /**
     * Получить имя пользователя.
     */
    virtual std::string getUsername() = 0;

    /**
     * Получить пароль пользователя.
     */
    virtual std::string getPassword() = 0;

    /**
     * Получить роль пользователя.
     */
    virtual std::string getRole() = 0;

    /**
     * Получить полное имя пользователя.
     */
    virtual std::string getFullName() = 0;

    /**
     * Проверить активен ли пользователь.
     */
    virtual bool isActive() = 0;

    /**
     * Проверить пароль.
     */
    virtual bool checkPassword(const std::string& password) = 0;

    /**
     * Проверить, имеет ли пользователь право на операцию.
     */
    virtual bool hasPermission(const std::string& permission) = 0;

    /**
     * Установить активность пользователя.
     */
    virtual void setActive(bool active) = 0;
};



