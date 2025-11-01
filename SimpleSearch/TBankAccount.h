#ifndef SIMPLESEARCH_TBANKACCOUNT_H
#define SIMPLESEARCH_TBANKACCOUNT_H
#include <string>
#include <ctime>
#include "EBankAccountType.h"


class TBankAccount {
private:
    std::string accountNumber;
    EBankAccountType accountType;
    std::string ownerFirstName;
    std::string ownerLastName;
    time_t creationTimestamp;
    double balance;

    double RandomInRange(double min, double max);
    double RandomBalanceFor(EBankAccountType t);

    public:
    TBankAccount(const std::string& accNo, EBankAccountType type, const std::string& firstName, const std::string& lastName, time_t createdAt);

    ~TBankAccount() = default;

    [[nodiscard]] const std::string& GetAccountNumber() const;
    [[nodiscard]] EBankAccountType GetAccountType() const;
    [[nodiscard]] const std::string& GetOwnerFirstName() const;
    [[nodiscard]] const std::string& GetOwnerLastName() const;

    [[nodiscard]] time_t GetCreationTimestamp() const;
    [[nodiscard]] double GetBalance() const;


};


#endif //SIMPLESEARCH_TBANKACCOUNT_H