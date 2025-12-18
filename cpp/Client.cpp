#include "Client.hpp"

Client::Client()
    : clientId(0),
      depositBalance(0.0),
      blacklisted(false),
      bonusPoints(0),
      status("Active")
{
}

Client::Client(int clientId, const std::string& firstName, const std::string& lastName, const std::string& phoneNumber)
    : clientId(clientId),
      firstName(firstName),
      lastName(lastName),
      middleName(""),
      phoneNumber(phoneNumber),
      email(""),
      passportSeries(""),
      passportNumber(""),
      address(""),
      birthDate(""),
      registrationDate(""),
      depositBalance(0.0),
      blacklisted(false),
      blacklistReason(""),
      bonusPoints(0),
      status("Active")
{
}
