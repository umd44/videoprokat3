#pragma once
#include <string>

class Client
{
public:
    Client();
    Client(int clientId,
           const std::string& firstName,
           const std::string& lastName,
           const std::string& phoneNumber);
    ~Client() = default;

    int getClientId() const;
    const std::string& getFirstName() const;
    const std::string& getLastName() const;
    const std::string& getPhoneNumber() const;
    double getDepositBalance() const;
    bool getIsBlacklisted() const;

    void addToDeposit(double amount);
    bool blockDepositFunds(double amount);
    void unblockDepositFunds(double amount);
    void setBlacklisted(bool value);

private:
    int m_clientId;
    std::string m_firstName;
    std::string m_lastName;
    std::string m_phoneNumber;
    double m_depositBalance;
    bool m_isBlacklisted;
};
