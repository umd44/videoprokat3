#include "VideoCarrier.hpp"

VideoCarrier::VideoCarrier()
    : inventoryNumber(0),
      releaseYear(0),
      rentalPricePerDay(0.0),
      fullPrice(0.0),
      status("available"),
      totalRentals(0),
      ageRating("0+")
{
}

VideoCarrier::VideoCarrier(int inventoryNumber, const std::string& title, const std::string& carrierType, const std::string& genre,
                           double rentalPricePerDay, double fullPrice)
    : inventoryNumber(inventoryNumber),
      title(title),
      carrierType(carrierType),
      genre(genre),
      releaseYear(0),
      director(""),
      ageRating("0+"),
      description(""),
      rentalPricePerDay(rentalPricePerDay),
      fullPrice(fullPrice),
      status("available"),
      totalRentals(0)
{
}
