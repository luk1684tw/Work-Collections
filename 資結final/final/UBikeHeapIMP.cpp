#include "UBikeHeapIMP.h"

void UBikeHeapIMP::swap(const int a, const int b)
{
    std::swap((*this)[a], (*this)[b]);
    (*this)[a]->heapIndex = a;
    (*this)[b]->heapIndex = b;
}

void UBikeHeapIMP::sift_up(int i)
{
    while (i>1 && (*this)[i/2]->mileage > (*this)[i]->mileage) {
        this->swap(i/2, i);
        i /= 2;
    }
}

void UBikeHeapIMP::sift_down(int i)
{
    while (true) {
        int cur = (*this)[i]->mileage;
        int l = (2*i   <= this->number) ? (*this)[2*i]  ->mileage
                                        : cur+1;
        int r = (2*i+1 <= this->number) ? (*this)[2*i+1]->mileage
                                        : cur+1;
        if (cur <= l && cur <= r) return;

        if (l <= r) {
            this->swap(2*i, i);
            i = 2*i;
        } else {
            this->swap(2*i+1, i);
            i = 2*i+1;
        }
    }
}
void UBikeHeapIMP::addUBikePtr(UBike* ubptr)
{
    (*this)[++number] = ubptr;
    ubptr->heapIndex = number;
    sift_up(number);
}

UBike* UBikeHeapIMP::removeUBikePtr(int heapIndex)
{
    if (heapIndex > this->number) return nullptr;
    auto retval = (*this)[heapIndex];
    (*this)[heapIndex] = (*this)[number--];
    (*this)[heapIndex]->heapIndex = heapIndex;
    sift_up(heapIndex);
    sift_down(heapIndex);
    return retval;
}
