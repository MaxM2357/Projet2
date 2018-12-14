#include "tour.h"
#include "town.h"
#include <stdio.h>

int main(){
    Tour *tourBilllon = createEmptyTour();
    unsigned int size = getTourSize(tourBilllon);
    printf("%d \n", size);
    Town *chinatown = createTown("china", 34, 56);
    addTownAtTourEnd(tourBilllon, chinatown);
    size = getTourSize(tourBilllon);
    printf("%d \n", size);
    Tour *tourNiquet = createTourFromFile("xy-belgium-towns.csv");
    size = getTourSize(tourNiquet);
    printf("%d \n", size);
    freeTour(tourBilllon, 1);
    freeTour(tourNiquet, 1);
    return 1;
}
