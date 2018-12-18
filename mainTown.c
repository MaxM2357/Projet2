#include <stdio.h>
#include "town.h"

int main(){
    Town *t,*t2;
    
    t=createTown("bonjvjffjfjbj§dgr A",100,100);
    t2=createTown("bij",0,1000);
    
    printf("%lf\n", getTownX(t));
    printf("%lf\n", getTownY(t));
    printf("%s\n", getTownName(t));
    printf("%lf\n", distanceBetweenTowns(t,t2));

    freeTown(t);


    return 0;
    
}
