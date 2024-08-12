#ifndef SAMESTATS_H
#define SAMESTATS_H

typedef enum carClass{
    BASIC = 0,
    GREEN = 1,
    PREMIUM = 2
} CarClass;

typedef enum accountStatus {
    ACTIVE = 0, 
    INACTIVE = 1
} AccountStatus;

typedef enum gender{
    M = 0,
    F = 1
} Gender;

typedef enum payMethod {
    CASH = 0, 
    CREDIT_CARD = 1,
    DEBIT_CARD = 2,
} PayMethod;

typedef struct date{
    int day;
    int month;
    int year;
} Date;

char* statusToString(AccountStatus status);

Date parsingDate(char* dateStr);
Date parsingDateInput(char* dateStr);

char* pmToString(PayMethod method);

char genderToString(Gender g);

char* classToString(CarClass c);

int Datecmp(Date d1, Date d2);

int dateisValid(Date d);

int is_digits(char* c);
int is_decimal(char *str);
void to_lower_case(char *str);
#endif