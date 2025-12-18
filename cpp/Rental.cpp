#include "Rental.hpp"
#include "Client.hpp"

Rental::Rental()
    : rentalId(0),
      client(nullptr),
      rentalDate(""),
      plannedReturnDate(""),
      depositAmount(0.0),
      rentalCost(0.0),
      status("active")
{
}

Rental::Rental(int rentalId, Client* client, const std::vector<VideoCarrier*>& items,
               const std::string& rentalDate, const std::string& plannedReturnDate)
    : rentalId(rentalId),
      client(client),
      items(items),
      rentalDate(rentalDate),
      plannedReturnDate(plannedReturnDate),
      depositAmount(0.0),
      rentalCost(0.0),
      status("active")
{
}
