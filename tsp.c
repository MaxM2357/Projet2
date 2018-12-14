#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "town.h"
#include "tour.h"
#include "tsp.h"

//fonction de debugage
#define DEBUG(message) fprintf(stderr, "Debug (%s): ligne %d, fonction [%s], fichier [%s]\n", message, __LINE__, __FUNCTION__,__FILE__)

static Town *Towncpy(Town *src){
    double x = getTownX(src);
    double y = getTownY(src);
    const char *name = getTownName(src);
    Town *dest = createTown(name, x, y);
    return dest;
}

Tour *heuristic1(Tour *tour){
    //faire les asserts!
    int i=0, j=0;
    int tourSize = getTourSize(tour);
    double dist=0;
    Tour *t = createEmptyTour();
    //t est le tour qu'on va retourner a l'utilisateur
    TourPosition *pos = getTourStartPosition(tour);
    Town *town = getTownAtPosition(tour, pos);
    Town *tStartTown = Towncpy(town);
    addTownAtTourEnd(t, tStartTown);
    TourPosition *tStartPos = getTourStartPosition(t);
    Town *tTown = NULL;
    TourPosition *tPos = NULL;
    TourPosition *InsertPos = NULL;
    pos = getNextTourPosition(tour, pos);
    for(i=1; i<tourSize; i++){
        town = getTownAtPosition(tour, pos);
        tTown = Towncpy(town);
        dist = distanceBetweenTowns(tStartTown, tTown);
        tPos = tStartPos;
        InsertPos = tStartPos;
        for(j=0; j<i-1; j++){
            tPos = getNextTourPosition(t, tPos);
            town = getTownAtPosition(t, tPos);
            if( distanceBetweenTowns(town, tTown) < dist){
                dist = distanceBetweenTowns(town, tTown);
                printf("%lf\n", dist);
                InsertPos = tPos;
            }
        }
        printf("******\nChoosen: %lf\n******\n", dist);
        addTownAfterTourPosition(t, InsertPos, tTown);
        pos = getNextTourPosition(tour, pos);
    }
    
    return t;
}
