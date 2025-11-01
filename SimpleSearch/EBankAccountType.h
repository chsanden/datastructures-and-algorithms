#ifndef SIMPLESEARCH_EBANKACCOUNTTYPE_H
#define SIMPLESEARCH_EBANKACCOUNTTYPE_H


enum class EBankAccountType {
    Checking,
    Savings,
    Credit,
    Pension,
    Loan
};
inline const char* ToString(EBankAccountType t)
{
    switch (t) {
            case EBankAccountType::Checking: return "Checking";
            case EBankAccountType::Savings: return "Savings";
            case EBankAccountType::Credit: return "Credit";
            case EBankAccountType::Pension: return "Pension";
            case EBankAccountType::Loan: return "Loan";
            default: return "Unknown";
    }
}

#endif //SIMPLESEARCH_EBANKACCOUNTTYPE_H

