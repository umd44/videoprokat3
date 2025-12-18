#pragma once
#include "Client.hpp"

/**
 * Реализация класса Client.
 * Содержит конкретную реализацию всех методов абстрактного класса Client.
 */
class ClientReal : public Client
{
public:
    /**
     * Конструктор по умолчанию.
     */
    ClientReal();

    /**
     * Конструктор с параметрами.
     */
    ClientReal(int clientId, const std::string& firstName, const std::string& lastName, const std::string& phoneNumber);

    virtual ~ClientReal();

    int getClientId() override;
    std::string getFirstName() override;
    std::string getLastName() override;
    std::string getPhoneNumber() override;
    double getDepositBalance() override;
    bool isBlacklisted() override;
    void addToDeposit(double amount) override;
    bool blockDepositFunds(double amount) override;
    void unblockDepositFunds(double amount) override;
    void setBlacklisted(bool value) override;
    std::string getMiddleName() override;
    std::string getEmail() override;
    std::string getPassportSeries() override;
    std::string getPassportNumber() override;
    std::string getAddress() override;
    std::string getBirthDate() override;
    std::string getRegistrationDate() override;
    std::string getBlacklistReason() override;
    int getBonusPoints() override;
    std::string getStatus() override;
    void setMiddleName(const std::string& middleName) override;
    void setEmail(const std::string& email) override;
    void setPassport(const std::string& series, const std::string& number) override;
    void setAddress(const std::string& address) override;
    void setBirthDate(const std::string& birthDate) override;
    void setRegistrationDate(const std::string& registrationDate) override;
    void setBlacklistReason(const std::string& reason) override;
    void addBonusPoints(int points) override;
    bool useBonusPoints(int points) override;
    void setStatus(const std::string& status) override;
};



