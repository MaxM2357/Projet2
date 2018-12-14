#include <stdio.h>
#include "easyppm.h"
#include "tour.h"
#include "tsp.h"


void ppmTour(Tour *tour, const char *ppmName, int size);

int main(){
    const int size = 2000;
    Tour *defaultTour = createTourFromFile("xy-belgium-towns.csv");
    Tour *H1Tour = heuristic1(defaultTour);
//    Tour *H2Tour = heuristic2(defaulttour);
    
    ppmTour(defaultTour, "tour-default.ppm", size);
    ppmTour(H1Tour, "tour-heuristic1.ppm", size);
//    ppmTour(H2Tour, "tour-heuristic2.ppm", size);
    
    double len = getTourLength(defaultTour);
    int taille = getTourSize(defaultTour);
    printf("Longueur tour par defaut: %lf\n", len);
    printf("Taille tour par defaut: %d\n", taille);
    len = getTourLength(H1Tour);
    taille = getTourSize(H1Tour);
    printf("Longueur tour avec heuristic 1: %lf\n",len);
    printf("Taille tour avec heuristic 1: %d\n",taille);
    //    len = getTourLength(H2Tour);
    //    printf("Longueur tour avec heuristic 2: %lf\n",len);
    
    return 0;
}

void ppmTour(Tour *tour, const char *ppmName, int size) {

  ppmcolor black = easyppm_rgb(0,0,0);
  ppmcolor white = easyppm_rgb(255,255,255);
       
  double prevX, prevY;
  double nextX, nextY;

  TourPosition *current = getTourStartPosition(tour);
  Town *currentTown = getTownAtPosition(tour, current);
  double minX = getTownX(currentTown);
  double maxX = minX;
  double minY = getTownY(currentTown);
  double maxY = minY;

  while (current != NULL) {
    double currentX = getTownX(getTownAtPosition(tour, current));
    double currentY = getTownY(getTownAtPosition(tour, current));
    
    if (currentX < minX)
      minX = currentX;
    else if (currentX > maxX)
      maxX = currentX;

    if (currentY < minY)
      minY = currentY;
    else if (currentY > maxY)
      maxY = currentY;
    
    current = getNextTourPosition(tour, current);
  }
  
  double xRange = maxX - minX;
  double yRange = maxY - minY;
  
  int sizex, sizey;
  if (xRange > yRange) {
    sizex = size;
    sizey = size*yRange/xRange;
  } else {
    sizex = size*xRange/yRange;
    sizey = size;
  }
  
  PPM ppm = easyppm_create(sizex+10, sizey+10, IMAGETYPE_PPM);
  easyppm_clear(&ppm, white);
  
  printf("minx = %f, maxx = %f, miny = %f, maxy = %f\n",minX,maxX,minY,maxY);
  current = getTourStartPosition(tour);
  while (current) {
    prevX = (getTownX(getTownAtPosition(tour, current)) - minX)*sizex/xRange+5;
    prevY = (getTownY(getTownAtPosition(tour, current)) - minY)*sizey/yRange+5;
	     
    TourPosition *next = getNextTourPosition(tour, current);
    if (next) {
      nextX = (getTownX(getTownAtPosition(tour, next)) - minX)*sizex/xRange+5;
      nextY = (getTownY(getTownAtPosition(tour, next)) - minY)*sizey/yRange+5;
      easyppm_draw_line(&ppm, (int) prevX, (int) prevY, (int) nextX, (int) nextY, black);
    }
        
    current = next;
  }
    
  double startX, startY;
  startX = (getTownX(getTownAtPosition(tour, getTourStartPosition(tour))) - minX) * sizex/xRange+5;;
  startY = (getTownY(getTownAtPosition(tour, getTourStartPosition(tour))) - minY) * sizey/yRange+5;
  easyppm_draw_line(&ppm, (int) nextX, (int) nextY, (int) startX, (int) startY, black);
  
  easyppm_write(&ppm, ppmName);
  easyppm_destroy(&ppm);

}
