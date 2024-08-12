#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <list_drivers.h>
#include <list_users.h>
#include <list_rides.h>
#include <stats.h>
#include <UI.h>
#include <UI_queries.h>
#include <results.h>
#include "UI_controller.h"


int main(int argc, char **argv){

    if(argv[1] == NULL){ 
       UI_controller(NULL,FALSE);
    } else {
      Stats s= loadFiles1(argv[1]);
      queries_file(s,argc,argv[2]);
    }
    return 0;
    
}
