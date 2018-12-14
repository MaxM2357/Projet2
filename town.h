#ifndef TOWN_H_
#define TOWN_H_


//definition du type opaque
typedef struct Town_t Town;

//cree une ville de nom "name", et de coordonnées (x,y)
Town *createTown(char *name, double x, double y);

//renvoie la coordonnée x de la ville
double getTownX(Town *town);

//renvoie la coordonnée y de la ville
double getTownY(Town *town);

//renvoie le nom de town
const char *getTownName(Town *town);

//renvoie la distance eucliedienne entre 2 villes
double distanceBetweenTowns(Town *town1, Town *town2);

//libere la memoire de town
void freeTown(Town *town);

#endif
