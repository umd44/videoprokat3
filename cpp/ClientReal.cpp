#include "ClientReal.hpp"

ClientReal::ClientReal()
    : Client()
{
}

ClientReal::ClientReal(int clientId, const std::string& firstName, const std::string& lastName, const std::string& phoneNumber)
    : Client(clientId, firstName, lastName, phoneNumber)
{
}

ClientReal::~ClientReal()
{
}

int ClientReal::getClientId()
{
    return clientId;
}

std::string ClientReal::getFirstName()
{
    return firstName;
}

std::string ClientReal::getLastName()
{
    return lastName;
}

std::string ClientReal::getPhoneNumber()
{
    return phoneNumber;
}

double ClientReal::getDepositBalance()
{
    return depositBalance;
}

bool ClientReal::isBlacklisted()
{
    return blacklisted;
}

void ClientReal::addToDeposit(double amount)
{
    if (amount > 0.0) {
        depositBalance += amount;
    }
}

bool ClientReal::blockDepositFunds(double amount)
{
    if (amount <= 0.0) {
        return false;
    }
    if (depositBalance >= amount) {
        depositBalance -= amount;
        return true;
    }
    return false;
}

void ClientReal::unblockDepositFunds(double amount)
{
    if (amount > 0.0) {
        depositBalance += amount;
    }
}

void ClientReal::setBlacklisted(bool value)
{
    blacklisted = value;
}

std::string ClientReal::getMiddleName()
{
    return middleName;
}

std::string ClientReal::getEmail()
{
    return email;
}

std::string ClientReal::getPassportSeries()
{
    return passportSeries;
}

std::string ClientReal::getPassportNumber()
{
    return passportNumber;
}

std::string ClientReal::getAddress()
{
    return address;
}

std::string ClientReal::getBirthDate()
{
    return birthDate;
}

std::string ClientReal::getRegistrationDate()
{
    return registrationDate;
}

std::string ClientReal::getBlacklistReason()
{
    return blacklistReason;
}

int ClientReal::getBonusPoints()
{
    return bonusPoints;
}

std::string ClientReal::getStatus()
{
    return status;
}

void ClientReal::setMiddleName(const std::string& middleName)
{
    this->middleName = middleName;
}

void ClientReal::setEmail(const std::string& email)
{
    this->email = email;
}

void ClientReal::setPassport(const std::string& series, const std::string& number)
{
    this->passportSeries = series;
    this->passportNumber = number;
}

void ClientReal::setAddress(const std::string& address)
{
    this->address = address;
}

void ClientReal::setBirthDate(const std::string& birthDate)
{
    this->birthDate = birthDate;
}

void ClientReal::setRegistrationDate(const std::string& registrationDate)
{
    this->registrationDate = registrationDate;
}

void ClientReal::setBlacklistReason(const std::string& reason)
{
    this->blacklistReason = reason;
}

void ClientReal::addBonusPoints(int points)
{
    if (points > 0) {
        this->bonusPoints += points;
    }
}

bool ClientReal::useBonusPoints(int points)
{
    if (points > 0 && this->bonusPoints >= points) {
        this->bonusPoints -= points;
        return true;
    }
    return false;
}

void ClientReal::setStatus(const std::string& status)
{
    this->status = status;
}



