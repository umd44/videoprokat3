package videoprokat;

/**
 * Реализация класса Client.
 * Содержит конкретную реализацию всех методов абстрактного класса Client.
 */
public class ClientReal extends Client {

    /**
     * Конструктор по умолчанию.
     */
    public ClientReal() {
        super();
    }

    /**
     * Конструктор с параметрами.
     */
    public ClientReal(int clientId, String firstName, String lastName, String phoneNumber) {
        super(clientId, firstName, lastName, phoneNumber);
    }

    @Override
    public int getClientId() {
        return clientId;
    }

    @Override
    public String getFirstName() {
        return firstName;
    }

    @Override
    public String getLastName() {
        return lastName;
    }

    @Override
    public String getPhoneNumber() {
        return phoneNumber;
    }

    @Override
    public double getDepositBalance() {
        return depositBalance;
    }

    @Override
    public boolean isBlacklisted() {
        return blacklisted;
    }

    @Override
    public void addToDeposit(double amount) {
        if (amount > 0.0) {
            depositBalance += amount;
        }
    }

    @Override
    public boolean blockDepositFunds(double amount) {
        if (amount <= 0.0) {
            return false;
        }
        if (depositBalance >= amount) {
            depositBalance -= amount;
            return true;
        }
        return false;
    }

    @Override
    public void unblockDepositFunds(double amount) {
        if (amount > 0.0) {
            depositBalance += amount;
        }
    }

    @Override
    public void setBlacklisted(boolean value) {
        blacklisted = value;
    }

    @Override
    public String getMiddleName() {
        return middleName;
    }

    @Override
    public String getEmail() {
        return email;
    }

    @Override
    public String getPassportSeries() {
        return passportSeries;
    }

    @Override
    public String getPassportNumber() {
        return passportNumber;
    }

    @Override
    public String getAddress() {
        return address;
    }

    @Override
    public String getBirthDate() {
        return birthDate;
    }

    @Override
    public String getRegistrationDate() {
        return registrationDate;
    }

    @Override
    public String getBlacklistReason() {
        return blacklistReason;
    }

    @Override
    public int getBonusPoints() {
        return bonusPoints;
    }

    @Override
    public String getStatus() {
        return status;
    }

    @Override
    public void setMiddleName(String middleName) {
        this.middleName = middleName;
    }

    @Override
    public void setEmail(String email) {
        this.email = email;
    }

    @Override
    public void setPassport(String series, String number) {
        this.passportSeries = series;
        this.passportNumber = number;
    }

    @Override
    public void setAddress(String address) {
        this.address = address;
    }

    @Override
    public void setBirthDate(String birthDate) {
        this.birthDate = birthDate;
    }

    @Override
    public void setRegistrationDate(String registrationDate) {
        this.registrationDate = registrationDate;
    }

    @Override
    public void setBlacklistReason(String reason) {
        this.blacklistReason = reason;
    }

    @Override
    public void addBonusPoints(int points) {
        if (points > 0) {
            this.bonusPoints += points;
        }
    }

    @Override
    public boolean useBonusPoints(int points) {
        if (points > 0 && this.bonusPoints >= points) {
            this.bonusPoints -= points;
            return true;
        }
        return false;
    }

    @Override
    public void setStatus(String status) {
        this.status = status;
    }

    /**
     * Деконструктор (финализатор).
     * Вызывается перед удалением объекта сборщиком мусора.
     */
    @Override
    protected void finalize() throws Throwable {
        try {
            // Освобождение ресурсов (если необходимо)
        } finally {
            super.finalize();
        }
    }
}
