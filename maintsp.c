#include <stdio.h>
#include "tour.h"
#include "town.h"
#include "tsp.h"

int main(){
    Tour *tourCon = createTourFromFile("xy-belgium-towns.csv");
    Tour *tourJous = heuristic1(tourCon);
    return 0;
}
