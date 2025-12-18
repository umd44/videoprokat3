#include "User.hpp"

User::User()
    : userId(0),
      username(""),
      password(""),
      role("Operator"),
      fullName(""),
      active(true)
{
}

User::User(int userId, const std::string& username, const std::string& password, 
           const std::string& role, const std::string& fullName)
    : userId(userId),
      username(username),
      password(password),
      role(role),
      fullName(fullName),
      active(true)
{
}



