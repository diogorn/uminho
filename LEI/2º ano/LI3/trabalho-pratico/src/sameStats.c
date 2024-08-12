#include <sameStats.h>
#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int is_digits(char *str) {
    int i;
    for (i = 0; str[i]; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

int is_decimal(char *str) {
    int i;
    for (i = 0; str[i]; i++) {
        if (!isdigit(str[i])){
            if(str[i] != '.'){
                return 0;
            }
        }
    }
    return 1;
}

void to_lower_case(char *str) {
    int i;
    for (i = 0; i < strlen(str); i++) {
        str[i] = tolower(str[i]);
    }
}
Date parsingDate(char* dateStr){
    Date date;
    int s;
    char *tok, *end;

    end = strdup(dateStr);

    if(strlen(end) != 10){
        date.day = 0;
        date.month = 0;
        date.year = 0;
        return date;
    }
    tok = strsep(&end, "/");
    sscanf(tok,"%d",&s);
    date.day = s;
    

    tok = strsep(&end, "/");
    sscanf(tok,"%d",&s);
    date.month = s;

    tok = strsep(&end, "/");
    sscanf(tok,"%d",&s);
    date.year= s;

    return date;
}

Date parsingDateInput(char* dateStr){
    Date date;
    int s;
    char *tok, *end;

    end = strdup(dateStr);

    tok = strsep(&end, "/");
    sscanf(tok,"%d",&s);
    date.day = s;
    

    tok = strsep(&end, "/");
    sscanf(tok,"%d",&s);
    date.month = s;

    tok = strsep(&end, "/");
    sscanf(tok,"%d",&s);
    date.year= s;

    return date;
}

char* statusToString(AccountStatus status){
    switch(status){
        case ACTIVE:
            return "active";

        case INACTIVE:
            return "inactive";
    }
    return "invalid";
}

char* pmToString(PayMethod method){
    switch(method){
        case CASH:
            return "cash";
        case CREDIT_CARD:
            return"credit_card";
        case DEBIT_CARD:
            return "debit_card";
    }
    return "invalid";
}

char genderToString(Gender g){
    switch(g){
        case M :
            return 'M';
        case F :
            return 'F';
    }
    return 'I';

}

char* classToString(CarClass class){
    switch (class){
    case BASIC:
        return "basic";
        break;
    case GREEN:
        return "green";
        break;
    case PREMIUM:
        return "premium";
        break;
    }
}


int Datecmp(Date d1, Date d2){
    if(d1.year > d2.year){
        return 1;
    }else if(d1.year < d2.year){
        return -1;
    }else{
        if(d1.month > d2.month){
            return 1;
        }else if(d1.month < d2.month){
            return -1;
        }else{
            if(d1.day > d2.day){
                return 1;
            }else if (d1.day < d2.day){
                return -1;
            } else {
                return 0;
            }
        }
    }
}

int dateisValid(Date date){//datas nn/nn/nnnn dias entre 1 e 31, meses entre 1 e 12, anos entre 1900 e 2100
    if(date.day < 1 || date.day > 31){
        return 0;
    }
    if(date.month < 1 || date.month > 12){
        return 0;
    }
    if(date.year < 1900 || date.year > 2100){
        return 0;
    }
    return 1;
}
