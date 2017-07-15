#include "UBikeSystemIMP.h"
#include <iostream>
using namespace std;
void UBikeSystemIMP::InitDistTable(std::string MapFile)
{
    // init and caculate all done in this func
    priceTable.calcAllPairsShortestPath(MapFile);
}

void UBikeSystemIMP::NewBike(std::string classType, std::string license, int mile, std::string station)
{

    auto ubptr = new UBike();
    ubptr->isRented = false;
    ubptr->mileage = mile;
    ubptr->license = license;
    ubptr->station = station;
    ubptr->classType = classType;
    ubHashTable.addUBikePtr(ubptr);
    ubStations[station][classType].addUBikePtr(ubptr);
    //cout <<"newbike " << ubptr->license << " " << ubptr->station << " " << ubptr->classType << "\n";
}

void UBikeSystemIMP::JunkIt(std::string license)
{
    auto ubptr = ubHashTable.findUBikePtr(license, false);
    if (ubptr == nullptr) return;
    if (ubptr->isRented) return;
    ubHashTable.findUBikePtr(license, true);
    ubStations[ubptr->station][ubptr->classType].removeUBikePtr(ubptr->heapIndex);
    //cout << "junk " << ubptr->license << " " << ubptr->station << " " << ubptr->classType << "\n";
    delete ubptr;
}


void UBikeSystemIMP::Rent(std::string classType, std::string station)
{
    auto ubptr = ubStations[station][classType].removeUBikePtr(1);
    if (ubptr == nullptr) return;   // no available ubike
    ubStations[station]["Rented"].addUBikePtr(ubptr);
    ubptr->isRented = true;
    //cout << "rent " << ubptr->license << " " << ubptr->station << " " << ubptr->classType << "\n";
}

void UBikeSystemIMP::Return(std::string station, std::string license, int returnMile)
{
    auto ubptr = ubHashTable.findUBikePtr(license, false);
    if (ubptr == nullptr) return;
    if (ubptr->isRented == false) return;
    this->net += priceTable.calcPrice(returnMile-ubptr->mileage, ubptr->classType, ubptr->station, station);
    ubStations[ubptr->station]["Rented"].removeUBikePtr(ubptr->heapIndex);
    ubptr->mileage = returnMile;
    ubptr->isRented = false;
    ubStations[ubptr->station][ubptr->classType].addUBikePtr(ubptr);
    //cout << "return " << ubptr->license << " " << ubptr->station << " " << ubptr->classType << " " << ubptr->heapIndex <<"\n";
    //cout << "benefit : " << net << "\n";
}

void UBikeSystemIMP::Trans(std::string station, std::string license)
{
    auto ubptr = ubHashTable.findUBikePtr(license, false);
    if (ubptr == nullptr) return;
    if (ubptr->isRented == true) return;
    ubStations[ubptr->station][ubptr->classType].removeUBikePtr(ubptr->heapIndex);
    ubStations[station][ubptr->classType].addUBikePtr(ubptr);
    ubptr->station = station;
    //cout << "trans " << ubptr->license << " " << ubptr->station << " " << ubptr->classType << "\n";
}

void UBikeSystemIMP::ShutDown()
{
    for (int i=0; i<256; ++i) {
        auto &&lst = ubHashTable[i];
        for (auto it=lst.begin(); it!=lst.end(); ++it) {
            auto ubptr = *it;
            ubStations[ubptr->station][ubptr->classType].removeUBikePtr(ubptr->heapIndex);
            ubStations[ubptr->station]["Rented"].removeUBikePtr(ubptr->heapIndex);
            delete *it;
        }
        lst.clear();
    }
}
