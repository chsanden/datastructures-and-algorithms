#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <ctime>
#include "TLinkedList.h"
#include "TBankAccount.h"
#include "EBankAccountType.h"
#include "SearchSummary.h"

// -------------------- Helpers: random generators --------------------

static int RandInt(int lo, int hi) {            // inclusive
    return lo + (std::rand() % (hi - lo + 1));
}

static std::string RandomAccountNumber()
{
    // super-simple: NO + 11 random digits
    std::string s = "NO";
    for (int i = 0; i < 11; ++i) s += char('0' + RandInt(0, 9));
    return s;
}

// Any moment in 2024
static time_t RandomTimestamp2024()
{
    std::tm tm{};                 // zero-init
    tm.tm_year = 124;             // 2024 - 1900
    tm.tm_mon  = RandInt(0, 11);  // 0..11
    tm.tm_mday = RandInt(1, 28);  // safe day-of-month (avoid month length edge cases)
    tm.tm_hour = RandInt(0, 23);
    tm.tm_min  = RandInt(0, 59);
    tm.tm_sec  = RandInt(0, 59);
    tm.tm_isdst = -1;             // let C library figure it out
    return std::mktime(&tm);
}

static EBankAccountType RandomAccountType()
{
    return static_cast<EBankAccountType>(RandInt(0, 4)); // 5 enum values
}

// -------------------- Standalone search functions (Part 3) --------------------

TBankAccount* FindAccountByNumber(
    TBankAccount** accountArray, int arraySize,
    const std::string& accountNumber, SearchSummary& summary)
{
    using clock = std::chrono::steady_clock;
    auto t0 = clock::now();

    for (int i = 0; i < arraySize; ++i) {
        ++summary.comparisons;
        if (accountArray[i]->GetAccountNumber() == accountNumber) {
            auto dt = clock::now() - t0;
            summary.timeSpentMs = std::chrono::duration<double, std::milli>(dt).count();
            return accountArray[i];
        }
    }
    auto dt = clock::now() - t0;
    summary.timeSpentMs = std::chrono::duration<double, std::milli>(dt).count();
    return nullptr;
}

void PrintEveryAccountInDateRange(
    TBankAccount** accountArray, int arraySize,
    time_t fromDate, time_t toDate, SearchSummary& summary)
{
    using clock = std::chrono::steady_clock;
    auto t0 = clock::now();

    for (int i = 0; i < arraySize; ++i) {
        ++summary.comparisons;
        time_t created = accountArray[i]->GetCreationTimestamp();
        if (created >= fromDate && created <= toDate) {
            std::tm* t = std::localtime(&created);
            std::cout << "  " << accountArray[i]->GetAccountNumber()
            << " | " << accountArray[i]->GetOwnerFirstName()
            << ' ' << accountArray[i]->GetOwnerLastName()
            << " | created " << std::put_time(t, "%Y-%m-%d %H:%M:%S")
            << " | type " << ToString(accountArray[i]->GetAccountType())
            << " | balance " << accountArray[i]->GetBalance()
            << std::endl;
        }
    }

    auto dt = clock::now() - t0;
    summary.timeSpentMs = std::chrono::duration<double, std::milli>(dt).count();
}

// -------------------- Name reader (names given) --------------------

typedef bool (*FNameRead)(const std::string& firstName, const std::string& lastName);

// Globals only to satisfy the plain-C callback style used here
static TLinkedList<TBankAccount*>* gList = nullptr;
static std::vector<TBankAccount*>*  gVec  = nullptr;

static bool OnNameRead(const std::string& firstName, const std::string& lastName)
{
    // Create between 5 and 10 accounts per name
    int count = RandInt(5, 10);
    for (int i = 0; i < count; ++i) {
        const auto accNo   = RandomAccountNumber();
        const auto accType = RandomAccountType();
        const auto created = RandomTimestamp2024();

        // requires the 5-arg constructor overload
        auto* acc = new TBankAccount(accNo, accType, firstName, lastName, created);

        gList->PushBack(acc);
        gVec->push_back(acc);
    }
    return true; // return false if you ever want to stop early
}

static void readNamesFromFile(const std::string& filename, FNameRead cb)
{
    if (filename.empty()) return;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << '\n';
        return;
    }

    std::string line, first, last;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if (iss >> first >> last) {
            if (cb && !cb(first, last)) break;
        }
    }
    file.close();
}

// -------------------- Integrated callbacks for TLinkedList::Every --------------------

static bool MatchMonthJune2024(TBankAccount* acc, void* /*key*/)
{
    time_t ts = acc->GetCreationTimestamp();
    std::tm* t = std::localtime(&ts);
    return (t->tm_year == 124 && t->tm_mon == 5); // June (0-based month)
}

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // 1) Build primary list + a vector mirror (will become the dynamic array)
    TLinkedList<TBankAccount*> list(/*ownsData=*/true);
    std::vector<TBankAccount*> mirror;
    mirror.reserve(55000); // 5400 names × up to 10 accounts ≈ 54k (avoid re-alloc)

    gList = &list;
    gVec  = &mirror;

    // Read file and populate (file in same directory as executable)
    readNamesFromFile("Random_Name.txt", OnNameRead);

    // Ensure we met the >= 5000 requirement
    if (mirror.size() < 5000) {
        std::cerr << "Warning: only " << mirror.size()
                  << " accounts created; expected >= 5000.\n";
    }

    // Create the dynamic array copy (Part 3 requirement)
    const int N = static_cast<int>(mirror.size());
    auto** accountArray = new TBankAccount*[N];
    for (int i = 0; i < N; ++i) accountArray[i] = mirror[i];

    std::cout << "Populated " << list.Size() << " accounts.\n\n";

    // 2) Demonstrations & Analysis (Part 4.12a)

    // a) Find First: search for one near the end and one that does not exist
    {
        std::cout << "[Find() near the end]\n";
        SearchSummary s{};
        // Pick a target near the end (if we have enough accounts)
        const std::string target = (N >= 3) ? accountArray[N - 3]->GetAccountNumber()
                                            : accountArray[N - 1]->GetAccountNumber();
        TBankAccount* found = list.Find(
            /*onCompare:*/ [](TBankAccount* a, void* key){
                return a->GetAccountNumber() == *static_cast<std::string*>(key);
            },
            /*key:*/ const_cast<std::string*>(&target),
            /*summary:*/ &/*summary:*/ s);
        std::cout << "  Target: " << target << " | Comparisons: " << s.comparisons
                  << " | Time: " << s.timeSpentMs << " ms\n";

        std::cout << "[Find() non-existent]\n";
        SearchSummary s2{};
        std::string missing = "NO00000000000"; // extremely unlikely to exist
        TBankAccount* notFound = list.Find(
            [](TBankAccount* a, void* key){
                return a->GetAccountNumber() == *static_cast<std::string*>(key);
            },
            &missing, &s2);
        std::cout << "  Target: " << missing << " | Found? " << (notFound ? "Yes" : "No")
                  << " | Comparisons: " << s2.comparisons
                  << " | Time: " << s2.timeSpentMs << " ms\n\n";
    }

    // b) Find All (Integrated): Every() for accounts created in June 2024
    {
        std::cout << "[Every() - accounts created in June 2024]\n";
        SearchSummary s{};
        TLinkedList<TBankAccount*>* june = list.Every(MatchMonthJune2024, nullptr, &s);
        std::cout << "  Matches: " << june->Size()
                  << " | Comparisons: " << s.comparisons
                  << " | Time: " << s.timeSpentMs << " ms\n";
        // You could iterate and print a few:
        // (Avoid printing thousands to keep output sane.)
        delete june; // ownsData=false inside Every()
        std::cout << '\n';
    }

    // c) Find All (Standalone): first quarter of 2024
    {
        std::cout << "[Standalone search -- accounts created in Q1 2024]\n";

        // Q1 range: 2024-01-01 00:00:00 to 2024-03-31 23:59:59
        std::tm from{}; from.tm_year = 124; from.tm_mon = 0; from.tm_mday = 1;
        std::tm to  {}; to  .tm_year = 124; to  .tm_mon = 2; to  .tm_mday = 31; to.tm_hour = 23; to.tm_min = 59; to.tm_sec = 59;
        time_t tFrom = std::mktime(&from);
        time_t tTo   = std::mktime(&to);

        SearchSummary s{};
        PrintEveryAccountInDateRange(accountArray, N, tFrom, tTo, s);
        std::cout << "  Comparisons: " << s.comparisons
                  << " | Time: " << s.timeSpentMs << " ms\n\n";
    }

    // Cleanup dynamic array (the list owns the account objects)
    delete[] accountArray;

    std::cout << "Done.\n";
    return 0;
}

// --------------Analysis---------------
// The Find() function iterates sequentially through the linked list to compare the data field of each node
// until a match is found, or it gets a nullptr as return. This means that if the matching node is towards the very end
// of the list, then the complexity would be near-as-makes-no-difference O(n). Therefore the other edge case is that the
// matching node is found at the very start of the list, making the time complexity essentially O(1).
// Since we have no way to arbitrarily reorganise the list according to the search query, we have to account for the
// worst case time complexity, which in the case of linked lists is O(n)

// The Every() function displays polymorphic flexibility through callbacks - meaning one function can
// handle many search conditions. PrintEveryAccountInDateRange() is more specialised, which also makes it more readable
// in this case. This also means that it's search functionality is not as versatile as Every(), with the specialisation
// of the PrintEveryAcc....() function being tied to a single search criteria.