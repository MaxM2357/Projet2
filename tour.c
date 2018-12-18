#include "town.h"
#include "tour.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//fonction de debugage
#define DEBUG(message) fprintf(stderr, "Debug (%s): ligne %d, fonction [%s], fichier [%s]\n", message, __LINE__, __FUNCTION__,__FILE__)

static TourPosition *getTourLastPosition(Tour *tour);

struct Tour_t{
    TourPosition *position;
    unsigned int size;
    
};

struct TourPosition_t{
    Town *town;
    TourPosition *suivant;
};

Tour *createEmptyTour(){
    Tour *tour;
    tour = malloc(sizeof(Tour));
    if(tour == NULL){
        exit(-1);
    }else{
        tour->position = NULL;
        tour->size = 0;
    }
    return tour;
}



Tour *createTourFromFile(char *filename){
    assert(filename != NULL);
    
    Town *town;
    Tour *tour;
    FILE *fp;
    char str[100], name[100], *token;
    double x,y;
    
    tour = createEmptyTour();
    fp = fopen(filename,"r");
        
        if (fp != NULL){
            while( fgets(str, 100, fp) != NULL){
                token = strtok(str,",");
                strcpy(name,token);
                token = strtok(NULL,",");
                x = atof(token);
                token = strtok(NULL,"\n");
                y = atof(token);
                town = createTown(name, x, y);
                
                addTownAtTourEnd(tour, town);
                
            }
            
        }else{
            printf("Impossible d'ouvrir le fichier\n");
            exit(-1);
        }
        
        return tour;
    
}


void freeTour(Tour *tour, int n){
    TourPosition *pos, *next;
    pos = tour->position;
    
    if(n==0){
        while(pos != NULL){
            next = pos->suivant;
            free(pos);
            pos = next;
        }
        free(tour);
    }else{
        while(pos != NULL){
            next = pos->suivant;
            freeTown(pos->town);
            free(pos);
            pos = next;
        }
        free(tour);
    }
    
}

void addTownAtTourEnd(Tour *tour, Town *town){
    assert(tour != NULL && town != NULL);

    TourPosition *nouvelle, *last;
    
    last = getTourLastPosition(tour);
    nouvelle = malloc(sizeof(TourPosition));
    
    if (nouvelle == NULL){
        exit(-1);
    }
    
    nouvelle->town = town;
    nouvelle->suivant = NULL;
    if(tour->position==NULL){
        tour->position = nouvelle;
    }else{
        last->suivant = nouvelle;
    }
}

void addTownAfterTourPosition(Tour *tour, TourPosition *pos, Town *town){
    assert(tour != NULL && pos != NULL && town != NULL);

    TourPosition *nouvelle;
    nouvelle = malloc(sizeof(TourPosition));
    if (nouvelle == NULL){
        exit(-1);
    }
    nouvelle->town = town;
    nouvelle->suivant = pos->suivant;
    pos->suivant = nouvelle;
    return;
}


TourPosition *getTourStartPosition(Tour *tour){
    assert(tour != NULL);
    
    return tour->position;
    
}

TourPosition *getTourLastPosition(Tour *tour){
    assert(tour != NULL);

    TourPosition *pos;
    pos = tour->position;
    if(pos == NULL)
        return NULL;
    while(pos->suivant != NULL){
        pos = pos->suivant;
    }
    return pos;
}

TourPosition *getNextTourPosition(Tour *tour, TourPosition *pos){
    assert(tour != NULL && pos != NULL);
    return pos->suivant;
}

Town *getTownAtPosition(Tour *tour, TourPosition *pos){
    assert(tour != NULL && pos != NULL);
    return pos->town;
}

int getTourSize(Tour *tour){
    assert(tour != NULL);
    TourPosition *pos;
    pos = tour->position;
    if(pos == NULL)
        return 0;
    int sizeTour=1;
    while(pos->suivant != NULL){
        pos = pos->suivant;
        sizeTour++;
    }
    return sizeTour;
}

double getTourLength(Tour *tour){
    assert(tour != NULL);
    double length = 0;
    TourPosition *pos,*suiv;
    pos = tour->position;
    while(pos->suivant != NULL){
        suiv= pos->suivant;
        length += distanceBetweenTowns(pos->town, suiv->town);
        pos = pos->suivant;
    }
    suiv = tour->position;
    length += distanceBetweenTowns(pos->town, suiv->town);
    return length;
}






















