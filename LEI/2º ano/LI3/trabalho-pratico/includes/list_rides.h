#ifndef LIST_RIDES_H
#define LIST_RIDES_H

#include <list_drivers.h>
#include <list_users.h>
#include <list_rides.h>
#include <sameStats.h>
#include <glib.h>


typedef struct ride* Ride;


Ride ride_parsing(char *rideStr);

void printRide(Ride rd);

void rideFree(Ride rd);

Ride rideClone(Ride original);

char* rideId(Ride rd);

char* rideDriver(Ride rd);

char* rideUser(Ride rd);

int rideDistance(Ride rd);

double rideTip(Ride rd);

double rideScoreUser(Ride rd);

double rideScoreDriver(Ride rd);

char* rideCity(Ride rd);

Date rideDate(Ride rd);

typedef struct list_rides* ListRides;

ListRides new_list_rides();

void rideAdd(Ride rd, ListRides listR, ListDrivers listD, ListUsers listU);

Ride getRide(ListRides list, char* id);

int ud_stats_age(Date birth);

void userStatsAdd(ListRides listR, ListDrivers listD, ListUsers listU, Ride rd);

void driverStatsAdd(ListRides listR, ListDrivers listD, ListUsers listU, Ride rd);

void ud_stats_add(ListRides listR, ListDrivers listD, ListUsers listU, Ride rd);

void driverStatsAdd(ListRides listR, ListDrivers listD, ListUsers listU,Ride rd);

void cityStatsAdd(ListRides listR, ListDrivers listD, ListUsers listU, Ride rd);

int getNviagensUsr(ListRides listR, char* id);

int getNviagensDrv(ListRides listR, char* id);

int userStatsAge(ListRides listR, char* id);

int driverStatsAge(ListRides listR, char* id);


int userStatsDistance(ListRides listR, char* id);

double userStatsAMedia(ListRides listR,char *id);

double driverStatsAMedia(ListRides listR,char *id);

double userStatsTotal(ListRides listR, char *id);

double driverStatsTotal(ListRides listR, char *id);

int validCity (ListRides listR, char* city);

int cityDistance(ListRides listR, char* city);

int cityNViagens(ListRides listR, char *city);

double cityTotal(ListRides listR, char* city);

void hash_table_to_array(gpointer key, gpointer value, gpointer array);

int compare_drivers(gconstpointer a, gconstpointer b);

GArray* get_top_drivers(ListRides listR);

int compare_users(gconstpointer a, gconstpointer b);

GArray* get_top_users(ListRides listR);

double getCostByDate(ListRides listR,ListDrivers listD,ListUsers listU, Date begin, Date end);

double getRideCost(Ride rd, ListDrivers listD);

double getRidesTotal(ListRides listR, ListDrivers ListD);

int getRidesN(ListRides listR);

double getDistByDateByCity(ListRides listR,ListDrivers listD,ListUsers listU, char *city, Date begin, Date end);

double getRidesTotalDistance(ListRides listR);

#endif