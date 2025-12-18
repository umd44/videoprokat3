#pragma once
#include <string>

/**
 * Абстрактный класс, описывающий видеоноситель (диск/кассета).
 * Содержит базовую структуру и методы для работы с видеоносителем.
 */
class VideoCarrier
{
protected:
    int inventoryNumber;
    std::string title;
    std::string carrierType;
    std::string genre;
    int releaseYear;
    std::string director;
    std::string ageRating;
    std::string description;
    double rentalPricePerDay;
    double fullPrice;
    std::string status;
    int totalRentals;

    /**
     * Конструктор по умолчанию.
     * Инициализирует все поля значениями по умолчанию.
     */
    VideoCarrier();

    /**
     * Конструктор с параметрами.
     */
    VideoCarrier(int inventoryNumber, const std::string& title, const std::string& carrierType, const std::string& genre,
                 double rentalPricePerDay, double fullPrice);

public:
    virtual ~VideoCarrier() = default;

    /**
     * Получить инвентарный номер.
     */
    virtual int getInventoryNumber() = 0;

    /**
     * Получить название фильма.
     */
    virtual std::string getTitle() = 0;

    /**
     * Получить тип носителя.
     */
    virtual std::string getCarrierType() = 0;

    /**
     * Получить жанр.
     */
    virtual std::string getGenre() = 0;

    /**
     * Получить цену аренды за день.
     */
    virtual double getRentalPricePerDay() = 0;

    /**
     * Получить полную стоимость.
     */
    virtual double getFullPrice() = 0;

    /**
     * Получить статус носителя.
     */
    virtual std::string getStatus() = 0;

    /**
     * Проверить, доступен ли носитель для аренды.
     */
    virtual bool isAvailable() = 0;

    /**
     * Пометить носитель как арендованный.
     */
    virtual void markAsRented() = 0;

    /**
     * Пометить носитель как доступный.
     */
    virtual void markAsAvailable() = 0;

    /**
     * Получить год выпуска.
     */
    virtual int getReleaseYear() = 0;

    /**
     * Получить режиссера/разработчика.
     */
    virtual std::string getDirector() = 0;

    /**
     * Получить возрастной рейтинг.
     */
    virtual std::string getAgeRating() = 0;

    /**
     * Получить описание.
     */
    virtual std::string getDescription() = 0;

    /**
     * Получить количество аренд.
     */
    virtual int getTotalRentals() = 0;

    /**
     * Установить год выпуска.
     */
    virtual void setReleaseYear(int year) = 0;

    /**
     * Установить режиссера/разработчика.
     */
    virtual void setDirector(const std::string& director) = 0;

    /**
     * Установить возрастной рейтинг.
     */
    virtual void setAgeRating(const std::string& ageRating) = 0;

    /**
     * Установить описание.
     */
    virtual void setDescription(const std::string& description) = 0;

    /**
     * Увеличить счетчик аренд.
     */
    virtual void incrementRentals() = 0;

    /**
     * Установить статус носителя.
     */
    virtual void setStatus(const std::string& status) = 0;
};
