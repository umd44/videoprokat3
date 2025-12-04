#include "PremiumClient.hpp"

PremiumClient::PremiumClient()
    : Client(),
      m_discountPercentage(10.0),
      m_loyaltyPoints(0)
{
}

PremiumClient::PremiumClient(int clientId,
                             const std::string& firstName,
                             const std::string& lastName,
                             const std::string& phoneNumber,
                             const std::string& email,
                             double discountPercentage)
    : Client(clientId, firstName, lastName, phoneNumber),
      m_discountPercentage(discountPercentage),
      m_loyaltyPoints(0),
      m_email(email)
{
    std::cout << "Создан премиум-клиент: " << firstName << " " << lastName 
              << " со скидкой " << discountPercentage << "%\n";
}

PremiumClient::~PremiumClient()
{
    std::cout << "Деструктор PremiumClient для " << m_firstName << "\n";
}

PremiumClient& PremiumClient::operator=(const Client& base)
{
    if (this != &base) {
        m_clientId = base.getClientId();
        m_firstName = base.getFirstName();
        m_lastName = base.getLastName();
        m_phoneNumber = base.getPhoneNumber();
        m_depositBalance = base.getDepositBalance();
        m_isBlacklisted = base.getIsBlacklisted();
        
        m_discountPercentage = 5.0;
        m_loyaltyPoints = 0;
        m_email = "";
        
        std::cout << "Присвоение базового Client производному PremiumClient\n";
    }
    return *this;
}

void PremiumClient::addToDeposit(double amount)
{
    Client::addToDeposit(amount);
    
    m_loyaltyPoints += static_cast<int>(amount / 20.0);
    std::cout << "Начислено " << static_cast<int>(amount / 20.0) 
              << " бонусных баллов (всего: " << m_loyaltyPoints << ")\n";
}

bool PremiumClient::blockDepositFunds(double amount)
{
    if (amount <= 0.0) return false;
    
    double discountedAmount = applyDiscount(amount);
    
    if (m_depositBalance >= discountedAmount) {
        m_depositBalance -= discountedAmount;
        std::cout << "Применена скидка " << m_discountPercentage 
                  << "%. Заблокировано: " << discountedAmount 
                  << " вместо " << amount << "\n";
        return true;
    }
    return false;
}

void PremiumClient::updateLoyalty(double rentalAmount)
{
    m_loyaltyPoints += static_cast<int>(rentalAmount / 10.0);
    if (m_loyaltyPoints > 1000 && m_discountPercentage < 20.0) {
        m_discountPercentage = 20.0;
        std::cout << "Скидка увеличена до 20%!\n";
    }
}

double PremiumClient::getDiscountPercentage() const
{
    return m_discountPercentage;
}

int PremiumClient::getLoyaltyPoints() const
{
    return m_loyaltyPoints;
}

const std::string& PremiumClient::getEmail() const
{
    return m_email;
}

double PremiumClient::applyDiscount(double amount) const
{
    return amount * (1.0 - m_discountPercentage / 100.0);
}

void PremiumClient::sendNotification(const std::string& message) const
{
    std::cout << "[EMAIL to " << m_email << "] " << message << "\n";
}
