#include "TBankAccount.h"

#include <random>
#include <thread>

static std::mt19937& GetRng()
{
    static thread_local std::mt19937 rng
    {
    std::random_device{}()
    };
    return rng;
}

double TBankAccount::RandomInRange(double min, double max)
{
    std::uniform_real_distribution<double> dist(min, max);
    return dist(GetRng());
}

double TBankAccount::RandomBalanceFor(EBankAccountType t)
{
    switch (t)
    {
        case EBankAccountType::Checking:
        case EBankAccountType::Savings:
        case EBankAccountType::Pension: return RandomInRange(0.0, 1000.0);
        case EBankAccountType::Loan: return RandomInRange(-50000.0, -25000.0);
        case EBankAccountType::Credit: return RandomInRange(-1000.0, 0.0);
        default: return 0.0;
    }
}

TBankAccount::TBankAccount(const std::string &accNo, EBankAccountType type, const std::string &firstName
    , const std::string &lastName, time_t createdAt) : accountNumber(accNo), accountType(type), ownerFirstName(firstName)
, ownerLastName(lastName), creationTimestamp(createdAt), balance(RandomBalanceFor(type))
{
}


const std::string &TBankAccount::GetAccountNumber() const
{
    return accountNumber;
}
EBankAccountType TBankAccount::GetAccountType() const
{
    return accountType;
}
const std::string &TBankAccount::GetOwnerFirstName() const
{
    return ownerFirstName;
}
const std::string &TBankAccount::GetOwnerLastName() const
{
    return ownerLastName;
}

time_t TBankAccount::GetCreationTimestamp() const
{
    return creationTimestamp;
}
double TBankAccount::GetBalance() const
{
    return balance;
}




