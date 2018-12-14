#ifndef TOUR_H_
#define TOUR_H_

#include "town.h"

typedef struct Tour_t Tour;

typedef struct TourPosition_t TourPosition;

Tour *createEmptyTour(void);

Tour *createTourFromFile(char *filename);

void freeTour(Tour *tour, int n);

void addTownAtTourEnd(Tour *tour, Town *town);

void addTownAfterTourPosition(Tour *tour, TourPosition *pos, Town *town);

TourPosition *getTourStartPosition(Tour *tour);

TourPosition *getNextTourPosition(Tour *tour, TourPosition *pos);

Town *getTownAtPosition(Tour *tour, TourPosition *pos);

int getTourSize(Tour *tour);

int getTourLength(Tour *tour);

#endif
