#ifndef UBikeHashTableIMP_h
#define UBikeHashTableIMP_h

#include "readonly/UBikeHashTableADT.h"

// std::array< UBikePtrList, 256 >
// typedef std::forward_list<UBike*> UBikePtrList;

//=================================================================
// the hash table for the ubikes owned by the ubike company
// overflow is handled by chaining
//=================================================================
class UBikeHashTableIMP : public UBikeHashTableADT
{
public:
    //=================================================================
    // add the ubike pointer to the hash table
    //=================================================================
    void addUBikePtr(UBike* ubptr);

    //=================================================================
    // find the ubike pointer in the hash table given ubike license
    // if toRemove is true, remove the the pointer from the hash table
    // return the ubike pointer that points to the ubike "license"
    //=================================================================
    UBike* findUBikePtr(std::string license, bool toRemove);

    //=================================================================
    // information
    //=================================================================
    //std::string toString() const;
};

#endif
