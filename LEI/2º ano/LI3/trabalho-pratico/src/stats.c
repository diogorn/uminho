#include <stdio.h>
#include <stats.h>
#include <string.h>
#include <glib.h>



struct stats{
    ListUsers list_users;
    ListDrivers list_drivers;
    ListRides list_rides;
};

typedef struct row{
    GArray *cells; // char*
};

typedef struct results{
    GArray *row; // struct row
};

Stats statsInit(ListUsers listU, ListDrivers listD, ListRides listR){
    Stats s = malloc(sizeof(struct stats));
    s->list_users = listU;
    s->list_drivers = listD;
    s->list_rides = listR; 
    
    return s;
}


Results stats_result_new(){
    Results res = malloc(sizeof(struct results));
    res->row = g_array_new(FALSE, FALSE, sizeof(struct row));
    return res;
}

void stats_results_add_row(Results res){
    struct row new_row;
    new_row.cells = g_array_new(FALSE, FALSE, sizeof(char*));
    g_array_append_val(res -> row, new_row);
}

void stats_results_add_cell(Results res, char* cell){
    struct row last = g_array_index(res -> row, struct row, res -> row -> len - 1);
    g_array_append_val(last.cells, cell);
}

void stats_results_add_cell_double(Results res, double value){
 char str[64];
 sprintf(str, "%.3f", value);
 stats_results_add_cell(res, strdup(str));
}

void stats_results_add_cell_int(Results res, int value){
    char str[12];
    sprintf(str, "%d", value);
    stats_results_add_cell(res, strdup(str));
}

char* stats_results_get_cell(Results res, int rowIdx, int colIdx){
    struct row r = g_array_index(res -> row, struct row, rowIdx);
    char *cell = g_array_index(r.cells, char*, colIdx );
    return strdup(cell);
}

Results Q1(Stats s, char* id){
    Results resp = stats_result_new();

    if((getUser(s->list_users, id)) != NULL){
        User u = getUser(s->list_users, id);
        AccountStatus status = userStatus(u);
        if (status==ACTIVE){
            stats_results_add_row(resp);
            
            stats_results_add_cell(resp,userName(u));
            stats_results_add_cell(resp, userGender(u));
            stats_results_add_cell_int(resp, userStatsAge(s -> list_rides, id));
            stats_results_add_cell_double(resp, userStatsAMedia(s -> list_rides, id));
            stats_results_add_cell_int(resp, getNviagensUsr(s -> list_rides, id));
            stats_results_add_cell_double(resp, userStatsTotal(s -> list_rides, id));
        }
    }
    else if(getDriver(s->list_drivers, id)){
        Driver dr = getDriver(s->list_drivers, id);
        AccountStatus status = driverStatus(dr);
        if (status==ACTIVE){
            stats_results_add_row(resp);
            
            stats_results_add_cell(resp,driverName(dr));
            stats_results_add_cell(resp,driverGender(dr));
            stats_results_add_cell_int(resp, driverStatsAge(s -> list_rides, id));
            stats_results_add_cell_double(resp,driverStatsAMedia(s -> list_rides, id));
            stats_results_add_cell_int(resp, getNviagensDrv(s -> list_rides, id));
            stats_results_add_cell_double(resp,driverStatsTotal(s -> list_rides, id));
        }
    }
    return resp;

}

Results Q2( Stats s, int n_drivers){
   GArray *drivers_ids = get_top_drivers(s -> list_rides);

    Results res = stats_result_new();
    int n=0;

    for(int i = 0; n < n_drivers;i++){
        //stats_results_add_row(res);
        char * drv_id = g_array_index(drivers_ids, char*, i);
        Driver drv = getDriver(s -> list_drivers, g_array_index(drivers_ids, char*, i));
        //printDriver(drv);
        AccountStatus status = driverStatus(drv);
        if (status==ACTIVE){
            stats_results_add_row(res);
            stats_results_add_cell(res, driverId(drv));
            stats_results_add_cell(res, driverName(drv));
            stats_results_add_cell_double(res, driverStatsAMedia(s -> list_rides, drv_id));
            n++;
        }
    }

    return res;
    
}

Results Q3( Stats s, int n_users){
   GArray *users_ids = get_top_users(s -> list_rides);

    Results res = stats_result_new();
    int n=0;

    for(int i = 0; n < n_users;i++){
        //stats_results_add_row(res);
        char * usr_id = g_array_index(users_ids, char*, i);
        User usr = getUser(s -> list_users, g_array_index(users_ids, char*, i));
        //printDriver(drv);
        AccountStatus status = userStatus(usr);
        if (status==ACTIVE){
            stats_results_add_row(res);
            stats_results_add_cell(res, userId(usr));
            stats_results_add_cell(res, userName(usr));
            stats_results_add_cell_int(res, userStatsDistance(s -> list_rides, usr_id));
            n++;
        }
    }

    return res;
}
Results Q4( Stats s, char* city){
    Results res = stats_result_new();
    if(validCity(s -> list_rides,city)){
        stats_results_add_row(res);
        double result = cityTotal(s -> list_rides, city)/ cityNViagens(s -> list_rides, city);
        stats_results_add_cell_double(res, result);
    }
    return res;

}

Results Q5( Stats s, Date d1, Date d2){
    
    Results res = stats_result_new();
    double result = getCostByDate(s -> list_rides,s -> list_drivers,s -> list_users, d1, d2);
    if (result != 0.0){
        stats_results_add_row(res);
        stats_results_add_cell_double(res, result);
    }
    return res;

}

Results Q6( Stats s, char* city, Date d1, Date d2){
    
    Results res = stats_result_new();
    
    double result = getDistByDateByCity(s -> list_rides,s -> list_drivers,s -> list_users,city, d1, d2);
    if (result != 0.0){
        stats_results_add_row(res);
        stats_results_add_cell_double(res, result);
    }
    return res;

}


void print_table(Results res, FILE *file){
    int n_rows = res ->row ->len;

    for(int i = 0; i < n_rows; i++){
        print_row(res, file, i);
    }
}

void print_row(Results res, FILE *file, int row){
    struct row r = g_array_index(res -> row, struct row, row);

    for(int i = 0; i < r.cells -> len ; i++){
        if(i == r.cells -> len - 1){
            fprintf(file, "%s", g_array_index(r.cells, char*, i));
        }else{
            fprintf(file, "%s;", g_array_index(r.cells, char*, i));
        }
    }
    fprintf(file, "\n");
}

