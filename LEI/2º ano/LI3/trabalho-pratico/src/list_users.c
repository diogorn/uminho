#include "list_users.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>

struct user {
    char username[64];
    char name[64];
    Gender gender;
    Date birth_date;
    Date account_creation;
    PayMethod pay_method;
    AccountStatus account_status;
};

struct list_users{
    GHashTable *users;
};


User user_parsing(char* userStr){
    User user = malloc(sizeof(struct user));
    char *tok,*end;

    end = strdup(userStr);

    tok = strsep(&end, ";");
    strcpy(user -> username, tok);
    if(strlen(user->username) == 0){
        free(user);
        return NULL;
    }

    tok = strsep(&end, ";");
    strcpy(user -> name, tok);
    if(strlen(user->name) == 0){
        free(user);
        return NULL;
    }

    tok= strsep(&end, ";");
    if(tok[0] == 'M'){
        user -> gender = M;
    }else{
        if(tok[0] == 'F'){
            user -> gender = F;
    }
        else{
            free(user);
            return NULL;
        }
    }

    tok = strsep(&end, ";");
    user -> birth_date = parsingDate(tok);
    if(!dateisValid(user -> birth_date)){
        free(user);
        return NULL;
    }

    tok= strsep(&end, ";");
    user -> account_creation = parsingDate(tok);
    if(!dateisValid(user -> account_creation)){
        free(user);
        return NULL;
    }

    tok= strsep(&end, ";");
    to_lower_case(tok);
    if(!strcmp(tok, "cash")){
        user ->pay_method = CASH;

    }else if(!strcmp(tok, "credit_card")){
        user ->pay_method = CREDIT_CARD;

    }else if(!strcmp(tok, "debit_card")){
        user ->pay_method = DEBIT_CARD;
    }else{
        free(user);
        return NULL;
    }

    tok = strsep(&end, "\n");
    to_lower_case(tok);
    if(!strcmp(tok,"active")){
        user -> account_status = ACTIVE;
    }else if(!strcmp(tok,"inactive")){
        user -> account_status = INACTIVE;
    }else{
        free(user);
        return NULL;
    }  
    return user;
    
}
void printUser(User sr){
    if(sr == NULL){
        printf("NULL user\n");
    }else{
        printf("username = %s, name = %s, gender=%c, birth_date = %d/%d/%d, account_date = %d/%d/%d, paymethod = %s, account_status = %s\n", 
            sr -> username, 
            sr -> name,  
            sr -> birth_date.day, 
            sr -> birth_date.month, 
            sr -> birth_date.year, 
            sr -> account_creation.day,
            sr -> account_creation.month, 
            sr -> account_creation.year,
            genderToString(sr -> gender),
            pmToString(sr -> pay_method),
            statusToString(sr -> account_status));

    }

}
 void userFree(User usr){
    free(usr);
 }

 User userClone(User original){
    User copy = malloc(sizeof(struct user));

    memcpy(copy,original, sizeof(struct user));

    return copy;
 }

 char* userId(User sr){
    return strdup(sr->username);
 }

 char* userName(User sr){
    return strdup(sr->name);
 }
 char* userGender(User sr){
    switch (sr->gender)
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

Date userBirth(User sr){
    return sr ->birth_date;
}
AccountStatus userStatus(User sr){
    return sr -> account_status;
}

ListUsers new_list_users(){
    ListUsers users = malloc(sizeof(struct list_users));
    users->users = g_hash_table_new(g_str_hash, g_str_equal);
    return users;
}

void userAdd(User user, ListUsers list){
    
    g_hash_table_insert(list->users, userId(user), userClone(user));
}

User getUser(ListUsers list, char* id){
    return g_hash_table_lookup(list->users,id);
}