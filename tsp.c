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
                InsertPos = tPos;
            }
        }
        addTownAfterTourPosition(t, InsertPos, tTown);
        pos = getNextTourPosition(tour, pos);
    }
    
    return t;
}


Tour *heuristic2(Tour *tour){
    //faire les asserts!
    int i=0, j=0;
    int tourSize = getTourSize(tour);
    double len=0, minLen=0;
    Tour *t = createEmptyTour();
    //t est le tour qu'on va retourner a l'utilisateur
    TourPosition *pos = getTourStartPosition(tour);
    //copie de la premiere ville
    Town *town = getTownAtPosition(tour, pos);
    Town *tStartTown = Towncpy(town);
    addTownAtTourEnd(t, tStartTown);
    //copie de la seconde ville
    pos = getNextTourPosition(t, pos);
    town = getTownAtPosition(tour, pos);
    Town *tSecondTown = Towncpy(town);
    addTownAtTourEnd(t, tSecondTown);
    //init de quelques variables
    //description needed
    TourPosition *tStartPos = getTourStartPosition(t);
    TourPosition *tSecondPos = getNextTourPosition(t, tStartPos);
    Town *tTown = NULL;
    Town *town2 = NULL;
    TourPosition *tPos = NULL, *tPos2 = NULL;
    TourPosition *InsertPos = NULL;
    pos = getNextTourPosition(tour, pos);
    for(i=2; i<tourSize; i++){
        town = getTownAtPosition(tour, pos);
        tSecondPos = getNextTourPosition(t, tStartPos);
        tSecondTown = getTownAtPosition(t, tSecondPos);
        tTown = Towncpy(town);
        minLen = distanceBetweenTowns(tStartTown, tTown) + distanceBetweenTowns(tTown, tSecondTown) - distanceBetweenTowns(tStartTown, tSecondTown);
        tPos = tStartPos;
        InsertPos = tStartPos;
        town = getTownAtPosition(t, tPos);
        for(j=0; j<i; j++){
            tPos2 = getNextTourPosition(t, tPos);
            if(tPos2 == NULL){
                town2 = tStartTown;
            }else{
                town2 = getTownAtPosition(t, tPos2);
            }
            len = distanceBetweenTowns(town, tTown) + distanceBetweenTowns(tTown, town2) - distanceBetweenTowns(town, town2);
            if( len < minLen){
                minLen = len;
                InsertPos = tPos;
            }
            tPos = tPos2;
            town = town2;
        }
        addTownAfterTourPosition(t, InsertPos, tTown);
        pos = getNextTourPosition(tour, pos);
    }
    
    return t;
}
