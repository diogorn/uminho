#ifndef STATS_H
#define STATS_H


#include <list_users.h>
#include <list_drivers.h>
#include <list_rides.h>
#include <stdio.h>

typedef struct stats *Stats;
typedef struct results *Results; 

Stats statsInit(ListUsers listU, ListDrivers listD, ListRides listR);

Results stats_result_new();

void stats_results_add_row(Results res);

void stats_results_add_cell(Results res, char* cell);

void stats_results_add_cell_double(Results res, double value);

char* stats_results_get_cell(Results res, int rowIdx, int colIdx);

void stats_results_add_cell_int(Results res, int value);

void print_table(Results res, FILE* file);

void print_row(Results res, FILE* file, int row);

GSList* parseLine(const char *input);

Results Q1(Stats s, char* id);

Results Q2( Stats s, int n_drivers);

Results Q3( Stats s, int n_users);

Results Q4(Stats s, char* city);

Results Q5(Stats s, Date d1, Date d2);

Results Q6( Stats s, char* city, Date d1, Date d2);

#endif