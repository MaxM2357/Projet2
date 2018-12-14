#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "town.h"
#include <stdlib.h>
#include <math.h>

struct Town_t {
    double xCoord, yCoord;
    char *Name;
};

Town *createTown(char *name, double x, double y){
    int size = 0;
    Town *t;
    t= malloc(sizeof(Town));
    if(t==NULL){
        exit(-1);
    }
    t->xCoord = x;
    t->yCoord = y;
    size = strlen(name)+1;
    t->Name = malloc(size*sizeof(char));
    if(t->Name==NULL){
        exit(-1);
    }
    strcpy(t->Name, name);
    
    return t;
}


double getTownX(Town *town){
    assert(town!=NULL);
    return town->xCoord;
    
}

double getTownY(Town *town){
    assert(town!=NULL);
    return town->yCoord;
}

const char *getTownName(Town *town){
    assert(town!=NULL);
    return town->Name;
}

double distanceBetweenTowns(Town *town1, Town *town2){
    double dist=0;
    
    dist = sqrt((((town2->xCoord) - (town1->xCoord))*((town2->xCoord) - (town1->xCoord))) + (((town2->yCoord)
               - (town1->yCoord))*((town2->yCoord) - (town1->yCoord))));
    
    
    return dist;
}

void freeTown(Town *town){
    assert(town!=NULL);
    
    free(town->Name);
    free(town);
}

















