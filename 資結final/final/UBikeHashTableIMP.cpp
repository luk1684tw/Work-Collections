#include "UBikeHashTableIMP.h"
#include <string>

int hash_func(std::string license)
{
    int x[5];
    for (int i=0; i<5; ++i) {
        x[i] = (license[i]<'A') ? license[i]-'0' : license[i]-'A'+10;
    }
    int s = x[0];
    for (int i=1; i<5; ++i) {
        s = 29 * s + x[i];
    }

    // use s's 6th to 13th bits
    // in sum, 8-bits(0-255)
    s = s >> 5;
    int exp2 = 1;
    int retval = 0;
    for (int i=0; i<8; ++i) {
        retval += (s%2) * exp2;
        s = s >> 1;
        exp2 *= 2;

    }

    return retval;
}

void UBikeHashTableIMP::addUBikePtr(UBike* ubptr)
{
    int index = hash_func(ubptr->license);
    // assume no duplicated ubike
    (*this)[index].push_front(ubptr);
}

UBike* UBikeHashTableIMP::findUBikePtr(std::string license, bool toRemove)
{
    int index = hash_func(license);
    auto& lst = (*this)[index];
    auto it = lst.begin();
    while (it != lst.end()) {
        if ((*it)->license == license) break;
        ++it;
    }
    if (it == lst.end()) return nullptr;
    auto retval = *it;
    // not found

    // remove and return nullptr
    if (toRemove) {
        lst.remove(*it);
        return nullptr;
    }
    return (*it);
    if (toRemove) lst.remove(retval);
    return retval;
}
