#ifndef SIMPLESEARCH_FCOMPAREACCOUNT_H
#define SIMPLESEARCH_FCOMPAREACCOUNT_H
#include "TBankAccount.h"

using FCompareAccount = bool (*)(TBankAccount* account, void* searchKey);


#endif //SIMPLESEARCH_FCOMPAREACCOUNT_H