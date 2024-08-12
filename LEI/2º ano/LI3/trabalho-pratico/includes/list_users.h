#ifndef LIST_USERS_H
#define LIST_USERS_H

#include <sameStats.h>


typedef struct list_users* ListUsers;

typedef struct user* User;


User user_parsing(char* userStr);

void printUser(User sr);

void userFree(User usr);

User userClone(User original);

char* userName(User sr);

char* userId(User sr);

char* userGender(User sr);

Date userBirth(User sr);

ListUsers new_list_users();

void userAdd(User user, ListUsers list);

AccountStatus userStatus(User sr);

User getUser(ListUsers list, char* id);

void free_list_users();

#endif