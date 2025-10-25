#include "Client.hpp"

Client::Client()
    : m_clientId(0), m_depositBalance(0.0), m_isBlacklisted(false)
{
}

Client::Client(int clientId,
               const std::string& firstName,
               const std::string& lastName,
               const std::string& phoneNumber)
    : m_clientId(clientId),
      m_firstName(firstName),
      m_lastName(lastName),
      m_phoneNumber(phoneNumber),
      m_depositBalance(0.0),
      m_isBlacklisted(false)
{
}

int Client::getClientId() const { return m_clientId; }
const std::string& Client::getFirstName() const { return m_firstName; }
const std::string& Client::getLastName() const { return m_lastName; }
const std::string& Client::getPhoneNumber() const { return m_phoneNumber; }

double Client::getDepositBalance() const { return m_depositBalance; }
bool Client::getIsBlacklisted() const { return m_isBlacklisted; }

void Client::addToDeposit(double amount)
{
    if (amount > 0.0) {
        m_depositBalance += amount;
    }
}

bool Client::blockDepositFunds(double amount)
{
    if (amount <= 0.0) return false;
    if (m_depositBalance >= amount) {
        m_depositBalance -= amount;
        return true;
    }
    return false;
}

void Client::unblockDepositFunds(double amount)
{
    if (amount > 0.0) {
        m_depositBalance += amount;
    }
}

void Client::setBlacklisted(bool value)
{
    m_isBlacklisted = value;
}
