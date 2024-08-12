#ifndef LIST_DRIVERS_H
#define LIST_DRIVERS_H

#include <sameStats.h>

typedef struct driver* Driver;
typedef struct list_drivers* ListDrivers;


Driver driver_parsing( char* driverStr);

void printDriver(Driver drv);

void driverFree(Driver drv);

Driver driverClone(Driver original);

char* driverId(Driver drv);

char* driverGender(Driver drv);

CarClass driverClass (Driver drv);

Date driverBirth(Driver drv);

int driverAge(Driver drv);

char* driverCity(Driver drv);

char* driverName(Driver drv);

ListDrivers new_list_driver();

void driverAdd(Driver driver, ListDrivers list);

Driver getDriver(ListDrivers cat , char* id);

CarClass getClass(ListDrivers cat, char*id);

AccountStatus driverStatus(Driver drv);

#endif