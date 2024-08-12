#include <list_rides.h>
#include <stdlib.h>
#include <stdio.h>
#define MONTH (10)
#define DAY (9)
#define YEAR (2022)

struct ride{
    char id[64];
    Date date;
    char driver[64];
    char user[64];
    char city[16];
    int distance;
    int score_user;
    int score_driver;
    double tip;
    char comment[128];

};


typedef struct ud_stats{
    char id[64];
    int idade;
    int nr_viagens;
    int distancia;
    double score;
    double total_envolvido;
    double tips;
    Date latest_ride;
};

typedef struct city_stats{
    Date date;
    int nr_viagens;
    int distance;
    double total;
};


struct list_rides{
    GHashTable *rides;
    GHashTable *user_stats;
    GHashTable *driver_stats;
    GHashTable *city_stats;

    
};

Ride ride_parsing(char *rideStr){
    Ride rd = malloc(sizeof(struct ride));
    char *tok,*end;
    int s;
    double d;

    end = strdup(rideStr);

    tok = strsep(&end, ";");
    strcpy(rd -> id, tok);
    if(strlen(rd->id) == 0){
        free(rd);
        return NULL;
    }

    tok = strsep(&end, ";");
    rd -> date = parsingDate(tok);
    
    if(!dateisValid(rd->date)){
        free(rd);
        return NULL;
    }

    tok = strsep(&end, ";");
    strcpy(rd -> driver,tok);
    if(strlen(rd->driver) == 0){
        free(rd);
        return NULL;
    }

    tok = strsep(&end, ";");
    strcpy(rd -> user, tok);
    if(strlen(rd->user) == 0){
        free(rd);
        return NULL;
    }

    tok= strsep(&end, ";");
    strcpy(rd -> city, tok);
    if(strlen(rd->city) == 0){
        free(rd);
        return NULL;
    }

    tok = strsep(&end, ";");
    if(strlen (tok) == 0){
        free(rd);
        return NULL;
    }
    if(is_digits(tok) == 0){
        free(rd);
        return NULL;
    }
    sscanf(tok,"%d",&s);
    rd -> distance = s;
    if(s>100) printf("%s\n", rd->id);
    
    if(rd->distance <= 0){
        free(rd);
        return NULL;
    }
    
    

    tok = strsep(&end, ";");
    if(is_digits(tok) == 0){
        free(rd);
        return NULL;
    }
    if(strlen (tok) == 0){
        free(rd);
        return NULL;
    }
    sscanf(tok,"%d",&s);
    rd -> score_user = s;
    if(rd->score_user <= 0 || rd->score_user > 5){
        free(rd);
        return NULL;
    }
    tok= strsep(&end, ";");

    if(is_digits(tok) == 0){
        free(rd);
        return NULL;
    }

    if(strlen (tok) == 0){
        free(rd);
        return NULL;
    }
    sscanf(tok,"%d",&s);
    rd -> score_driver = s;
    if(rd->score_driver <= 0 || rd->score_driver > 5){
        free(rd);
        return NULL;
    }   
    tok = strsep(&end, ";");
    if(is_digits(tok) == 1){
        free(rd);
        return NULL;
    }
    if(is_decimal(tok) == 0){
       
        free(rd);
        return NULL;
    }
    sscanf(tok,"%lf",&d);
    rd -> tip = d;
    if(rd->tip < 0.0){
        free(rd);
        return NULL;
    }

    tok = strsep(&end, "\n");
    if(tok) {
        strcpy(rd -> comment, tok);
    } else {
        rd -> comment[0] = '\0';
    }

    return rd;

}

void printRide(Ride rd){

    printf("id = %s, date = %d/%d/%d,user= %s ,driver = %s, city = %s,  distance = %d, score_user = %d, score_driver = %d, tip = %f, comment = %s \n",
        rd -> id,
        rd -> date.day,
        rd ->date.month,
        rd ->date.year,
        rd -> user,
        rd -> driver,
        rd -> city,
        rd ->distance,
        rd -> score_user,
        rd -> score_driver,
        rd -> tip,
        rd -> comment);
}

void rideFree(Ride rd){
    free(rd);
}

Ride rideClone(Ride original){
    Ride copy = malloc(sizeof(struct ride));

    memcpy(copy, original, sizeof(struct ride));

    return copy;
}


char* rideId(Ride rd){
    return strdup(rd -> id);
}

char* rideDriver(Ride rd){
    return strdup(rd -> driver);
}

char* rideUser(Ride rd){
    return strdup(rd -> user);
}

int rideDistance(Ride rd){
    return(rd -> distance);
}
double rideTip(Ride rd){
    return(rd->tip);
}

double rideScoreUser(Ride rd){
    return(rd -> score_user);
}

double rideScoreDriver(Ride rd){
    return(rd -> score_driver);
}

char* rideCity(Ride rd){
    return(strdup(rd -> city));
}

Date rideDate(Ride rd){
    return rd-> date;
}

ListRides new_list_rides(){
    ListRides rides = malloc(sizeof(struct list_rides));

    rides->rides = g_hash_table_new(g_str_hash, g_str_equal);
    rides ->user_stats = g_hash_table_new(g_str_hash, g_str_equal);
    rides -> driver_stats = g_hash_table_new(g_str_hash, g_str_equal);
    rides -> city_stats = g_hash_table_new(g_str_hash, g_str_equal);


    return rides;
}

void rideAdd (Ride rd, ListRides listR, ListDrivers listD, ListUsers listU){
    g_hash_table_insert(listR -> rides, rideId(rd), rideClone(rd));
    userStatsAdd(listR, listD, listU, rd);
    driverStatsAdd(listR, listD, listU, rd);
    cityStatsAdd(listR, listD, listU, rd);


}

int ud_stats_age(Date birth){
    int idade = (YEAR - birth.year);

    if(birth.month > MONTH ){
        idade--;
    }else if(birth.month == MONTH){
        if( birth.day  > DAY){
            idade--;
        }
    }
    return idade;

}


Ride getRide(ListRides list, char* id){
    return g_hash_table_lookup(list -> rides, id);
}

void driverStatsAdd(ListRides listR,ListDrivers listD,ListUsers listU,Ride rd){
    if(g_hash_table_contains(listR -> driver_stats , rideDriver(rd))){
        struct ud_stats *st = (struct ud_stats*)g_hash_table_lookup(listR -> driver_stats, rideDriver(rd));
        st -> nr_viagens++;
        st -> distancia += rideDistance(rd);
        st -> score += rideScoreDriver(rd);
        st -> tips += rideTip(rd);
        if(Datecmp(rideDate(rd), st -> latest_ride) == 1){
            st -> latest_ride = rideDate(rd);
        }
        
        CarClass c3= getClass(listD, rideDriver(rd));
        
        switch (c3)
        {
        case BASIC:
            st -> total_envolvido += 3.25 + rideDistance(rd)*0.62;
            break;
        
        case GREEN:
            st -> total_envolvido += 4 + rideDistance(rd)*0.79;
            break;
        case PREMIUM:
            st -> total_envolvido += 5.2 + rideDistance(rd)*0.94;
        }
        g_hash_table_insert(listR -> driver_stats, rideDriver(rd), st);

    }else{
        struct ud_stats *st =  malloc(sizeof(struct ud_stats));
        strcpy(st -> id, rideDriver(rd));
        st -> idade = ud_stats_age(driverBirth(getDriver(listD,(rideDriver(rd)))));
        st -> nr_viagens = 1;
        st -> distancia = rideDistance(rd);
        st -> score = rideScoreDriver(rd);
        st -> tips = rideTip(rd);
        st -> latest_ride = rideDate(rd);
        CarClass c4 = getClass(listD, rideDriver(rd));
        switch (c4)
        {
        case BASIC:
            st -> total_envolvido = 3.25 + rideDistance(rd)*0.62;
            break;
        
        case GREEN:
            st -> total_envolvido = 4 + rideDistance(rd)*0.79;
            break;
        case PREMIUM:
            st -> total_envolvido = 5.2 + rideDistance(rd)*0.94;
        }

        g_hash_table_insert(listR ->driver_stats, rideDriver(rd), st);
    }

}


void userStatsAdd(ListRides listR, ListDrivers listD, ListUsers listU, Ride rd){
    if(g_hash_table_contains(listR -> user_stats, rideUser(rd))){
        struct ud_stats *st = (struct ud_stats*)g_hash_table_lookup(listR -> user_stats, rideUser(rd));
        st -> nr_viagens++;
        st -> distancia += rideDistance(rd);
        st -> tips += rideTip(rd);
        st -> score += rideScoreUser(rd);
        
        if(Datecmp(rideDate(rd), st -> latest_ride) == 1){
            st -> latest_ride = rideDate(rd);
        }
        CarClass c2= getClass(listD, rideDriver(rd));
        switch (c2)
        {
        case BASIC:
            st -> total_envolvido += 3.25 + rideDistance(rd)*0.62;
            break;
        
        case GREEN:
            st -> total_envolvido += 4 + rideDistance(rd)*0.79;
            break;
        case PREMIUM:
            st -> total_envolvido += 5.2 + rideDistance(rd)*0.94;
        }
        g_hash_table_insert(listR ->user_stats, rideUser(rd), st);

    }else{
        struct ud_stats *st =  malloc(sizeof(struct ud_stats));
        st -> idade = ud_stats_age(userBirth(getUser(listU,(rideUser(rd)))));
        strcpy(st -> id, rideUser(rd));
        st -> nr_viagens = 1;
        st -> distancia = rideDistance(rd);
        st -> score = rideScoreUser(rd);
        st -> tips = rideTip(rd);
        st -> latest_ride = rideDate(rd);
        CarClass c1 = getClass(listD, rideDriver(rd));
        
        switch (c1)
        {
        case BASIC:
            st -> total_envolvido = 3.25 + rideDistance(rd)*0.62;
            break;
        
        case GREEN:
            st -> total_envolvido = 4 + rideDistance(rd)*0.79;
            break;
        case PREMIUM:
            st -> total_envolvido = 5.2 + rideDistance(rd)*0.94;
        }

        g_hash_table_insert(listR ->user_stats, rideUser(rd), st);
    }
}

void cityStatsAdd(ListRides listR, ListDrivers listD, ListUsers listU, Ride rd){
    char * city = rideCity(rd);

    if(g_hash_table_contains(listR -> city_stats, city)){
        struct city_stats *st = (struct city_stats*)g_hash_table_lookup(listR -> city_stats, city);

        st -> nr_viagens++;
        st -> distance += rideDistance(rd);

        CarClass c1 = getClass(listD, rideDriver(rd));
        switch (c1)
        {
        case BASIC:
            st -> total += 3.25 + rideDistance(rd)*0.62;
            break;
        
        case GREEN:
            st -> total += 4 + rideDistance(rd)*0.79;
            break;
        case PREMIUM:
            st -> total += 5.2 + rideDistance(rd)*0.94;
        }
        g_hash_table_insert(listR -> city_stats, city, st);
        
    }else{
        struct city_stats *st = malloc(sizeof(struct city_stats));
            st -> nr_viagens = 1;
            st -> distance = rideDistance(rd);
            CarClass c1 = getClass(listD, rideDriver(rd));
        switch (c1){
        case BASIC:
            st -> total = 3.25 + rideDistance(rd)*0.62;
            break;
        
        case GREEN:
            st -> total = 4 + rideDistance(rd)*0.79;
            break;
        case PREMIUM:
            st -> total = 5.2 + rideDistance(rd)*0.94;

        }
        g_hash_table_insert(listR -> city_stats, city, st);
        
    }


}

int getNviagensUsr(ListRides listR, char* id){
    struct ud_stats *st = g_hash_table_lookup(listR -> user_stats, id);

    return st -> nr_viagens;
}

int getNviagensDrv(ListRides listR, char* id){
    struct ud_stats *st = g_hash_table_lookup(listR -> driver_stats, id);

    return st -> nr_viagens;
}

int userStatsAge(ListRides listR, char* id){
    struct ud_stats *st = g_hash_table_lookup(listR -> user_stats, id);

    
    return st -> idade;
}

int driverStatsAge(ListRides listR, char* id){
    struct ud_stats *st = g_hash_table_lookup(listR -> driver_stats, id);

    return st -> idade;
}


int userStatsDistance(ListRides listR, char* id){
    struct ud_stats *st = g_hash_table_lookup(listR -> user_stats, id);

    return st -> distancia;
}

double userStatsAMedia(ListRides listR,char *id){
    struct ud_stats *st = g_hash_table_lookup(listR -> user_stats, id);
    return((st -> score)/(st -> nr_viagens));
}

double driverStatsAMedia(ListRides listR,char *id){
    struct ud_stats *st = g_hash_table_lookup(listR -> driver_stats, id);
    return((st -> score)/(st -> nr_viagens));
}

double userStatsTotal(ListRides listR, char *id){
    struct ud_stats *st = g_hash_table_lookup(listR -> user_stats, id);

    return(st -> total_envolvido + st->tips);
}

double driverStatsTotal(ListRides listR, char *id){
    struct ud_stats *st = g_hash_table_lookup(listR -> driver_stats, id);

    return(st -> total_envolvido + st->tips);
}
int validCity (ListRides listR, char* city){
    if(g_hash_table_lookup(listR -> city_stats, city)){
        return 1;
    }
    return 0;
}

int cityDistance(ListRides listR, char* city){
    struct city_stats *st = g_hash_table_lookup(listR -> city_stats, city);
    return(st -> distance);
}

int cityNViagens(ListRides listR, char *city){
   struct city_stats *st = g_hash_table_lookup(listR -> city_stats, city);
   return(st -> nr_viagens);
}

double cityTotal(ListRides listR, char* city){
    struct city_stats *st = g_hash_table_lookup(listR -> city_stats, city);

    return(st -> total);
}


void hash_table_to_array(gpointer key, gpointer value, gpointer array){
    g_array_append_val(array, *(struct ud_stats*)value);
}





int compare_drivers(gconstpointer a, gconstpointer b){
    const struct ud_stats* st_a = a;
    const struct ud_stats* st_b = b; 

    double score_a = (st_a -> score/st_a -> nr_viagens);

    double score_b = (st_b -> score/ st_b -> nr_viagens);

    if( score_a > score_b){
        return -1;
    } else if(score_a < score_b){
        return 1;
    } else {
        if(Datecmp(st_a -> latest_ride, st_b -> latest_ride) == 1){
            return -1;
        }else if(Datecmp(st_a -> latest_ride, st_b -> latest_ride) == -1){
            return 1;
        }else{
            return strcmp(st_a -> id, st_b -> id);

        }

    }

}



GArray* get_top_drivers(ListRides listR){
    GArray *n_drivers = g_array_new(FALSE, FALSE, sizeof(struct ud_stats));
    g_hash_table_foreach(listR -> driver_stats, hash_table_to_array , n_drivers );
    g_array_sort(n_drivers, compare_drivers);

    GArray *drivers_ids = g_array_new(FALSE, FALSE, sizeof(char *));
    for(int i = 0; i< n_drivers -> len; i++){
        struct ud_stats st = g_array_index(n_drivers, struct ud_stats, i);
        char *str = strdup(st.id);
        g_array_append_val(drivers_ids, str);
    }
    g_array_free(n_drivers, TRUE);
    return drivers_ids;
}

int compare_users(gconstpointer a, gconstpointer b){
    const struct ud_stats* st_a = a;
    const struct ud_stats* st_b = b; 

    int distancia_a = (st_a -> distancia);


    int distancia_b = (st_b -> distancia);

    if( distancia_a > distancia_b){
        return -1;
    } else if(distancia_a < distancia_b){
        return 1;
    } else {
        if(Datecmp(st_a -> latest_ride, st_b -> latest_ride) == 1){
            return -1;
        }else if(Datecmp(st_a -> latest_ride, st_b -> latest_ride) == -1){
            return 1;
        }else{
            return strcmp(st_a -> id, st_b -> id);

        }

    }

}


GArray* get_top_users(ListRides listR){
    GArray *n_users = g_array_new(FALSE, FALSE, sizeof(struct ud_stats));
    g_hash_table_foreach(listR -> user_stats, hash_table_to_array , n_users );
    g_array_sort(n_users, compare_users);

    GArray *user_ids = g_array_new(FALSE, FALSE, sizeof(char *));
    for(int i = 0; i< n_users -> len; i++){
        struct ud_stats st = g_array_index(n_users, struct ud_stats, i);
        char *str = strdup(st.id);
        g_array_append_val(user_ids, str);
    }
    g_array_free(n_users, TRUE);
    return user_ids;
}

double getCostByDate(ListRides listR,ListDrivers listD,ListUsers listU, Date begin, Date end){
    double cost=0.0;
    int n=0;
    GArray *n_rides = g_array_new(FALSE, FALSE, sizeof(struct ride));

    g_hash_table_foreach(listR -> rides, hash_table_to_array , n_rides );
    
    for(int i = 0; i < n_rides -> len; i++){
        struct ride rd= g_array_index(n_rides, struct ride, i);
        Ride r = &rd;
        if(Datecmp(rd.date, begin) >= 0 && Datecmp(rd.date, end) <= 0){
            cost += getRideCost(r, listD);
            n+=1;
        }
    }
    if (n==0) return 0.0;
    g_array_free(n_rides, TRUE);
    return cost/n;
}

double getDistByDateByCity(ListRides listR,ListDrivers listD,ListUsers listU, char *city, Date begin, Date end){
    GArray *n_rides = g_array_new(FALSE, FALSE, sizeof(struct ride));
    double dist=0.0;
    int n=0;
    g_hash_table_foreach(listR -> rides, hash_table_to_array , n_rides );
    
    for(int i = 0; i < n_rides -> len; i++){
        struct ride rd= g_array_index(n_rides, struct ride, i);
        if(Datecmp(rd.date, begin) >= 0 && Datecmp(rd.date, end) <= 0 && strcmp(rd.city, city) == 0){
            dist += rd.distance;
            n+=1;
        }
    }
    if (n==0) return 0.0;
    g_array_free(n_rides, TRUE);
    return dist/n;
}
double getRideCost(Ride rd, ListDrivers listD){
    CarClass c1 = getClass(listD, rideDriver(rd));
    double total = 0.0;
    switch (c1)
    {
    case BASIC:
        total = 3.25 + rideDistance(rd)*0.62;
        break;
     
    case GREEN:
        total = 4 + rideDistance(rd)*0.79;
        break;
    case PREMIUM:
        total= 5.2 + rideDistance(rd)*0.94;
    }
    return total;
}
double getRidesTotal(ListRides listR, ListDrivers ListD){
    double total = 0.0;
    GArray *nr_rides = g_array_new(FALSE, FALSE, sizeof(struct ride));
    g_hash_table_foreach(listR -> rides, hash_table_to_array , nr_rides );

    for(int i = 0; i < nr_rides -> len; i++){
        struct ride rd= g_array_index(nr_rides, struct ride, i);
        Ride r = &rd;
        total += getRideCost(r,ListD);
    }
    return total;
}

double getRidesTotalDistance(ListRides listR){
    double total = 0.0;
    GArray *nr_rides = g_array_new(FALSE, FALSE, sizeof(struct ride));
    g_hash_table_foreach(listR -> rides, hash_table_to_array , nr_rides );

    for(int i = 0; i < nr_rides -> len; i++){
        struct ride rd= g_array_index(nr_rides, struct ride, i);
        total += rd.distance;
    }
    return total;
}

int getRidesN(ListRides listR){
    GArray *nr_rides = g_array_new(FALSE, FALSE, sizeof(struct ride));
    g_hash_table_foreach(listR -> rides, hash_table_to_array , nr_rides );
    return nr_rides -> len;
}


/*  idade da conta, nao do utilizador



GArray* getRidesForQ8(ListRides listR,ListDrivers listD,ListUsers listU, char g, int age){
    GArray *nr_rides = g_array_new(FALSE, FALSE, sizeof(struct ride));
    g_hash_table_foreach(listR -> rides, hash_table_to_array , nr_rides );
    GArray *rides_ids = g_array_new(FALSE, FALSE, sizeof(char *));
    g_array_sort(nr_rides, compare_rides);
    for(int i = 0; i < nr_rides -> len; i++){
        struct ride rd= g_array_index(nr_rides, struct ride, i);
        Ride r=&rd;
        char drv = rideDriver(r);
        char usr = rideUser(r);
        Driver d= getDriver(listD, drv);
        User u= getUser(listU, usr);
        if(strcmp(driverGender(d),userGender(u))==0 && strcmp(driverGender(d),g)==0 && driverStatsAge(listR,drv)>=age && userStatsAge(listR,usr)>=age){
            g_array_append_val(rides_ids, rd.id);
        }

    }
    //falta ordenar
    g_array_free(nr_rides, TRUE);
    return rides_ids;

}
*/
