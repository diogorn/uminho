// TO DO

typedef struct person{
    char name[200];
    int age;
} Person;

int insert_person(char* name, int age);
int list_persons(int N);
int person_change_age(char* name, int age);