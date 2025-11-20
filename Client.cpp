#include "Client.hpp"
#include "VideoRentalException.hpp"

// Статические счетчики для автоматической генерации ID
int Client::s_nextClientId = 1;
int Client::s_totalClientsCount = 0;

// Конструктор по умолчанию - создает пустого клиента
Client::Client()
    : m_clientId(0), m_depositBalance(0.0), m_isBlacklisted(false)
{
    s_totalClientsCount++;
}

// Основной конструктор с данными клиента
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
    s_totalClientsCount++;
    
    // Если ID не указан, генерируем автоматически
    if (m_clientId == 0) {
        m_clientId = s_nextClientId++;
    } else {
        // Обновляем счетчик, чтобы избежать конфликтов
        if (clientId >= s_nextClientId) {
            s_nextClientId = clientId + 1;
        }
    }
}

// Конструктор копирования - создает копию клиента с новым ID
Client::Client(const Client& other)
    : m_clientId(s_nextClientId++),
      m_firstName(other.m_firstName),
      m_lastName(other.m_lastName),
      m_phoneNumber(other.m_phoneNumber),
      m_depositBalance(other.m_depositBalance),
      m_isBlacklisted(other.m_isBlacklisted)
{
    s_totalClientsCount++;
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

void Client::blockDepositFundsOrThrow(double amount)
{
    if (amount <= 0.0) {
        throw InvalidDataException("amount", "сумма должна быть положительной");
    }
    
    if (m_depositBalance < amount) {
        throw InsufficientFundsException(amount, m_depositBalance);
    }
    
    m_depositBalance -= amount;
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

Client& Client::addToDepositChain(double amount)
{
    if (amount > 0.0) {
        m_depositBalance += amount;
    }
    return *this;
}

Client& Client::setBlacklistedChain(bool value)
{
    m_isBlacklisted = value;
    return *this;
}

Client& Client::setFirstName(const std::string& firstName)
{
    this->m_firstName = firstName;
    return *this;
}

Client& Client::setLastName(const std::string& lastName)
{
    this->m_lastName = lastName;
    return *this;
}

bool Client::operator!=(const Client& other) const
{
    return m_clientId != other.m_clientId;
}

Client& Client::operator+=(double amount)
{
    if (amount > 0.0) {
        m_depositBalance += amount;
    }
    return *this;
}

int Client::getNextClientId()
{
    return s_nextClientId;
}

int Client::getTotalClientsCount()
{
    return s_totalClientsCount;
}

void Client::resetClientCounter()
{
    s_nextClientId = 1;
    s_totalClientsCount = 0;
}
