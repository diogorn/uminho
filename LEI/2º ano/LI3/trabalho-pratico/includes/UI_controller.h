#include <string.h>
#include <stdlib.h>

#include <list_drivers.h>
#include <list_users.h>
#include <list_rides.h>
#include <stats.h>
#include <UI.h>
#include <UI_queries.h>
#include <results.h>


Stats loadFiles1(char *argv);
int UI_controller(Stats s, bool fileIsLoaded);
int UI_files_controller(bool fileIsLoaded);