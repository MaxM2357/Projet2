//
//  main.c
//  
//
//  Created by Victor Dachet on 01/12/2018.
//

#include <stdio.h>
#include "town.h"

int main(){
    Town *t,*t2;
    
    t=createTown("bonj",1,1);
    t2=createTown("bij",0,0);
    
    printf("%lf\n", getTownX(t));
    printf("%lf\n", getTownY(t));
    printf("%s\n", getTownName(t));
    printf("%lf\n", distanceBetweenTowns(t,t2));

    freeTown(t);


    return 0;
    
}
