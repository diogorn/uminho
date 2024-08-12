
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <list_drivers.h>
#include <glib.h>

struct driver{
    char id[16];
    char name[32];
    Date birth_date;
    Gender gender;
    CarClass car_class;
    char license_plate[16];
    char city[16];
    Date account_creation;
    AccountStatus account_status;

 } ;

Driver driver_parsing( char* driverStr){
    Driver drv = malloc(sizeof(struct driver));
    char *tok,*end;

    end = strdup(driverStr);

    tok = strsep(&end, ";");
    strcpy(drv -> id, tok);
    if(strlen(drv->id) == 0){
        free(drv);
        return NULL;
    }

    tok = strsep(&end, ";");
    strcpy(drv -> name, tok);
    if(strlen(drv->name) == 0){
        free(drv);
        return NULL;
    }

    tok = strsep(&end, ";");
    drv -> birth_date = parsingDate(tok);
    if(!dateisValid(drv -> birth_date)){
        free(drv);
        return NULL;
    }

    tok= strsep(&end, ";");
    if(tok[0] == 'M'){
        drv -> gender = M;
    }else if(tok[0] == 'F'){
        drv -> gender = F;
    }else{
        free(drv);
        return NULL;
    }

    tok = strsep(&end, ";");
    to_lower_case(tok);
    if(!strcmp(tok, "basic")){
        drv -> car_class = BASIC;
    }else if(!strcmp(tok ,"green")){
        drv -> car_class = GREEN;
    }else if(!strcmp(tok, "premium") ){
        drv -> car_class = PREMIUM;
    }else{
        free(drv);
        return NULL;
    }

    tok = strsep(&end, ";");
    strcpy(drv ->license_plate, tok);
    if(strlen(drv->license_plate) == 0){
        free(drv);
        return NULL;
    }


   
    tok = strsep(&end, ";");
    strcpy(drv -> city, tok);
    if(strlen(drv->city) == 0){
        free(drv);
        return NULL;
    }

    tok = strsep(&end, ";");
    drv -> account_creation = parsingDate(tok);
    if(!dateisValid(drv -> account_creation)){
        free(drv);
        return NULL;
    }

    tok = strsep(&end, "\n");
    to_lower_case(tok);
    if(!strcmp(tok,"inactive")){
        drv -> account_status = INACTIVE;
    }else if(!strcmp(tok,"active")){
        drv -> account_status = ACTIVE;
    }else{
        free(drv);
        return NULL;
    }


    return drv;

}
void printDriver(Driver drv){

    if(drv == NULL){
        printf("NULL driver\n");
    }else{
        printf("id = %s, name = %s, birth_day = %d/%d/%d, gender = %c, car_class = %s, license_plate = %s, city = %s, accou_creation = %d/%d/%d, account_status = %s \n",
            drv -> id,
            drv -> name,
            drv -> birth_date. day,
            drv -> birth_date.month,
            drv -> birth_date.year,
            genderToString(drv -> gender),
            classToString(drv -> car_class),
            drv -> license_plate,
            drv -> city,
            drv -> account_creation.day,
            drv -> account_creation.month,
            drv -> account_creation.year,
            statusToString(drv -> account_status));
            


    }


}

void driverFree(Driver drv){
        free(drv);
}

Driver driverClone(Driver original){
    Driver copy = malloc(sizeof(struct driver));

    memcpy(copy, original, sizeof(struct driver));

    return copy;
}

char* driverId(Driver drv){
    return strdup(drv -> id);
}

char* driverGender(Driver drv){
    switch (drv->gender)
    {
    case M:
        return strdup("M");
        break;
    case F:
        return strdup("F");
        break;
    default:
    return strdup("I");
        break;
    }
}

CarClass driverClass(Driver drv){
    return(drv -> car_class);
}

Date driverBirth(Driver drv){
    return(drv -> birth_date);
}

char* driverCity(Driver drv){
    return strdup(drv -> city);
}

char* driverName(Driver drv){
    return strdup(drv -> name);
}

AccountStatus driverStatus(Driver drv){
    AccountStatus status= drv->account_status;
    return status;
}


struct list_drivers{
    GHashTable *drivers;

};

ListDrivers new_list_driver(){
    ListDrivers drivers = malloc(sizeof(struct list_drivers));
    drivers -> drivers = g_hash_table_new(g_str_hash, g_str_equal);

    return drivers;
}

void driverAdd(Driver drv,ListDrivers list){
    g_hash_table_insert(list -> drivers, driverId(drv), driverClone(drv));
}

Driver getDriver(ListDrivers list, char* id){
    return g_hash_table_lookup(list -> drivers, id);
}

CarClass getClass(ListDrivers list, char*id){
    Driver r =(g_hash_table_lookup(list -> drivers, id) );
    return driverClass(r);
}



