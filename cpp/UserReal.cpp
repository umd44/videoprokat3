#include "UserReal.hpp"
#include <algorithm>

std::map<std::string, std::vector<std::string>> UserReal::initRolePermissions()
{
    std::map<std::string, std::vector<std::string>> perms;

    std::vector<std::string> operatorPerms = {
        "search_items", "create_rental", "process_return", "view_clients", 
        "register_client", "accept_payment"
    };
    perms["Operator"] = operatorPerms;

    std::vector<std::string> seniorOperatorPerms = {
        "search_items", "create_rental", "process_return", "view_clients", 
        "register_client", "accept_payment", "edit_items", "edit_client_status", 
        "apply_discount", "view_financial_reports", "manage_fines"
    };
    perms["Senior Operator"] = seniorOperatorPerms;

    std::vector<std::string> adminPerms = {
        "search_items", "create_rental", "process_return", "view_clients", 
        "register_client", "accept_payment", "edit_items", "edit_client_status", 
        "apply_discount", "view_financial_reports", "manage_fines",
        "manage_users", "edit_dictionaries", "view_all_reports", 
        "system_settings", "writeoff_items"
    };
    perms["Administrator"] = adminPerms;

    return perms;
}

const std::map<std::string, std::vector<std::string>> UserReal::ROLE_PERMISSIONS = UserReal::initRolePermissions();

UserReal::UserReal()
    : User()
{
}

UserReal::UserReal(int userId, const std::string& username, const std::string& password, 
                   const std::string& role, const std::string& fullName)
    : User(userId, username, password, role, fullName)
{
}

UserReal::~UserReal()
{
}

int UserReal::getUserId()
{
    return userId;
}

std::string UserReal::getUsername()
{
    return username;
}

std::string UserReal::getRole()
{
    return role;
}

std::string UserReal::getFullName()
{
    return fullName;
}

bool UserReal::isActive()
{
    return active;
}

bool UserReal::checkPassword(const std::string& password)
{
    return this->password == password;
}

bool UserReal::hasPermission(const std::string& permission)
{
    auto it = ROLE_PERMISSIONS.find(role);
    if (it == ROLE_PERMISSIONS.end()) {
        return false;
    }
    const std::vector<std::string>& permissions = it->second;
    return std::find(permissions.begin(), permissions.end(), permission) != permissions.end();
}

void UserReal::setActive(bool active)
{
    this->active = active;
}

std::string UserReal::getPassword()
{
    return password;
}
