#include "PriceTableIMP.h"
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include<limits>
using namespace std;
// Add your code here
void PriceTableIMP::calcAllPairsShortestPath(std::string mapFile)
{
     // init the this->distTable

    for(int i=0;i<StationNum;i++) for(int j=0;j<StationNum;j++)
    {
        const std::string &sti = StationNames[i];
        const std::string &stj = StationNames[j];
        this->distTable[sti][stj] =
            (i == j) ? 0 : 10000000;
    }

    // fill the discount road into disTable
    std::fstream mf;
    mf.open(mapFile);
    std::string src, dst;
    int weight;
    while (mf >> src >> dst >> weight) {
        this->distTable[src][dst] = min(distTable[src][dst],weight);
        this->distTable[dst][src] = min(distTable[dst][src],weight);
    }

    // all pair shortest path
    auto &&A = this->distTable;
    for (int i=0; i<StationNum; ++i) {
        for (int j=0; j<StationNum; ++j) {
            for (int k=0; k<StationNum; ++k) {
                //if (i == j) continue;
                const std::string &sti = StationNames[i];
                const std::string &stj = StationNames[j];
                const std::string &stk = StationNames[k];
                A[sti][stj] = std::min(A[sti][stj], A[sti][stk] + A[stk][stj]);
                A[stj][sti] = std::min(A[stj][sti], A[stj][stk] + A[stk][sti]);
            }

        }
    }
    mf.close();
}
int PriceTableIMP::calcPrice(int milageDiff, std::string bClass,std::string from, std::string toStation)
{
   int distance;
   distance = distTable[from][toStation];
   if(milageDiff > distance)
   {
      return oriRates.at(bClass)*milageDiff;
   }
   else
   {
      return dscntRates.at(bClass)*milageDiff;
   }
}
