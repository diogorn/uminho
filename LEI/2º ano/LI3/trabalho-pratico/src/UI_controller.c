#include "UI_controller.h"
#include <unistd.h>
#include <stdlib.h>
#include "sameStats.h"

#define SIZE 100

#define RANKINGSIZE puts(RESET_COR"\nEscolha o tamanho do ranking\n");
#define INTERVALO puts(RESET_COR"\nInsira o intervalo de datas que pretende consultar\n");
#define invalidINP puts(RED_BOLD"Input inválido"RESET_COR);
Stats loadFiles1(char *argv){
    char *arg = strdup(argv);
    arg[strcspn(arg,"\r\n")] = 0;
    char pathDrivers[100],pathUsers[100],pathRides[100];
    sprintf(pathDrivers,"%s/drivers.csv",arg);
    sprintf(pathUsers,"%s/users.csv",arg);
    sprintf(pathRides,"%s/rides.csv",arg);

    pathDrivers[strcspn(pathDrivers,"\r\n")] = 0;
    pathUsers[strcspn(pathUsers,"\r\n")] = 0;
    pathRides[strcspn(pathRides,"\r\n")] = 0;

    FILE* fp = NULL;
    fp = fopen(pathUsers, "r");//sera um path
    ListUsers list_users = new_list_users();
    if (!fp) {
        perror("Error");
    }
    char* line = NULL;
    ssize_t read;
    size_t len;

    getline(&line, &len, fp);
    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("%s",line);
        User usr = user_parsing(line);
        if (usr != NULL) {
            userAdd(usr, list_users);
            userFree(usr); 
        }
          
    }
    free(line);
    fclose(fp);
    
    FILE* fp2 = NULL;
    fp2 = fopen(pathDrivers, "r");//sera um path
    ListDrivers list_drivers = new_list_driver();

    if (!fp2) {
        perror("Error");
    }
    char* line2 = NULL;
    ssize_t read2;
    size_t len2;

    getline(&line2, &len2, fp2);
    while ((read2 = getline(&line2, &len2, fp2)) != -1) {
        Driver drvr = driver_parsing(line2);
        if (drvr != NULL) {
            driverAdd(drvr, list_drivers);
            driverFree(drvr);   
        } 
    }
    free(line2);
    fclose(fp2);

    FILE* fp3 = NULL;
    fp3 = fopen(pathRides, "r");
    ListRides list_rides = new_list_rides();

    if (!fp3) {
        perror("Error");
    }
    char* line3 = NULL;
    ssize_t read3;
    size_t len3;

    getline(&line3, &len3, fp3);

    while ((read3 = getline(&line3, &len3, fp3)) != -1) {
        Ride rd = ride_parsing(line3);
        if(rd != NULL){
           // printf("here");
            rideAdd(rd, list_rides, list_drivers, list_users);
            rideFree(rd); 
            
        }
    }
    free(line3);
    fclose(fp3);

    Stats s = statsInit(list_users, list_drivers, list_rides);
    return s;
}  


int UI_controller(Stats s, bool fileIsLoaded){
    char line[SIZE];
    Results res;
    menuPrincipal(fileIsLoaded);
    

while (1){
    while(fgets(line, SIZE, stdin) == NULL); 
    int n;
    if(sscanf(line, "%d", &n) != 1) continue;
    if (fileIsLoaded){
        switch (n){
        case 0:
            UI_files_controller(fileIsLoaded);
            return 0;
            break;
        case 1:
            querie1_UI();
            while(strcmp(line,"0") != 0){
                 fgets(line, sizeof(line), stdin);
                 line[strcspn(line,"\n\r")] = 0;
                 res = Q1(s, line);
                 print_table(res, stdout);
            }
            UI_controller(s,fileIsLoaded);
            return 0;
            break;
        case 2:
            querie2_UI();
            while(n != 0){
            if (scanf("%d",&n)!=0){
                res = Q2(s, n);
                print_table(res, stdout);
                RANKINGSIZE
            } else {
                invalidINP
                break;
            }
            }
             UI_controller(s,fileIsLoaded);
             return 0;
            break;

        case 3:
            querie3_UI();
            while(n != 0){
                if (scanf("%d",&n) != 0){
                    res = Q3(s, n);
                    print_table(res, stdout);
                    RANKINGSIZE
                } else {
                 invalidINP
                 break;
                }
            }
            UI_controller(s,fileIsLoaded);
            return 0;
            break;
        case 4:
            querie4_UI();
            while(strcmp(line,"0") != 0){
                 fgets(line, sizeof(line), stdin);
                 line[strcspn(line,"\n\r")] = 0;
                 res = Q4(s, line);
                 print_table(res, stdout);
            }
            UI_controller(s,fileIsLoaded);
            return 0;
            break;

        case 5:
           querie5_UI();
             while(strcmp(line, "0") != 0){
                fgets(line, sizeof(line), stdin);
                line[strcspn(line,"\n")] = 0;
                Date date1, date2;
                sscanf(line, "%d/%d/%d %d/%d/%d", &date1.day, &date1.month, &date1.year, &date2.day, &date2.month, &date2.year);
                res = Q5(s, date1, date2);
                print_table(res, stdout);
            }
            UI_controller(s,fileIsLoaded);
            return 0;
            break;

        case 6:
            querie6_UI();
            while(strcmp(line, "0") != 0){
                fgets(line, sizeof(line), stdin);
                line[strcspn(line,"\n")] = 0;
                char city[100];
                Date date1, date2;
                sscanf(line, "%s %d/%d/%d %d/%d/%d", city, &date1.day, &date1.month, &date1.year, &date2.day, &date2.month, &date2.year);
                res = Q6(s, city, date1, date2);
                print_table(res, stdout);

            }
            UI_controller(s,fileIsLoaded);
            return 0;
            break;
 
        case 7:
            querie7_UI();
            while(strcmp(line, "0") != 0){
                fgets(line, sizeof(line), stdin);
                line[strcspn(line,"\n")] = 0;
                char city[30];
             /* sscanf(line, "%d %s", &n, city);
                res = Q7(s, n, city);
                print_table(res, stdout);
                */
            }
            UI_controller(s,fileIsLoaded);
            return 0;
            break;
        case 8:
            querie8_UI();
             while(strcmp(line, "0") != 0){
                fgets(line, sizeof(line), stdin);
                line[strcspn(line,"\n")] = 0;
                /*
                char gender[10];
                sscanf(line, "%s %d", gender, &n);
                res = Q8(s, gender, n);
                print_table(res, stdout);
                */
            }
            UI_controller(s,fileIsLoaded);
            return 0;
            break;
        case 9:
            querie9_UI();
             while(strcmp(line, "0") != 0){
                fgets(line, sizeof(line), stdin);
                line[strcspn(line,"\n")] = 0;
                /*
                Date date1, date2;
                sscanf(line, "%d/%d/%d %d/%d/%d", &date1.day, &date1.month, &date1.year, &date2.day, &date2.month, &date2.year);
                res = Q9(s, date1, date2);
                print_table(res, stdout);
                memset(line, 0, sizeof(line));
                */
            }
            UI_controller(s,fileIsLoaded);
            return 0;
            break;
            
        case 10:
            closedProgramUI();
            return 0;
            break;
        default:
            UI_controller(s, fileIsLoaded);
            return 0;
            break;
        }
    } else if (!fileIsLoaded && n <= 9 ){
        UI_files_controller(FALSE);
        return 0;
        //free(s);
    } else {
          switch (n) {
            case 0:
                UI_files_controller(fileIsLoaded);
                return 0;
                break;
            case 10:
                closedProgramUI();
                return 0;
                break;
            default:
                UI_controller(s, fileIsLoaded);
                return 0;
                 break;
        }
    } 
}
    return 0;
}

int UI_files_controller(bool fileIsLoaded){
    UIloadFiles();
    Stats s=NULL;
    char str[SIZE];
    int selected;
    FILE *fp = NULL;
    //if (fileIsLoaded){
        //free(s);
     //   fileIsLoaded = FALSE;
    //}
    // scanf("%d",&selected);
while (1){
    while(fgets(str, SIZE, stdin) == NULL); 
    if(sscanf(str, "%d", &selected) != 1) continue;
    switch (selected){
    case 0:
        UI_controller(s,fileIsLoaded);
        // free(s);
        return 0;
        break;
    case 1:
       UIPreLoadedFiles();
        int opcao;
        scanf("%d",&opcao);
        switch(opcao){
           case 0:
                UI_files_controller(fileIsLoaded);
               // free(s);
                return 0;
                break;
           case 1:
                loadingMenu();
                s = loadFiles1("data/data-regular-errors");
                fileIsLoaded = TRUE;
                break;
           case 2:
                loadingMenu();
                s = loadFiles1("data/data-regular-errors-invalid");
                fileIsLoaded = TRUE;
                break;
           case 3:
                loadingMenu();
                s = loadFiles1("data/data-large");
                fileIsLoaded = TRUE;
                break;
           case 4:
                loadingMenu();
                s = loadFiles1("data/data-large-errors-invalid");
                fileIsLoaded = TRUE;
                break;
            default:
                UI_files_controller(fileIsLoaded);
               // free(s);
                return 0;
             break;
        }
        UI_files_controller(fileIsLoaded);
       // free(s);
        return 0;
    break;
    case 2:
    UIFilePath();
    while (scanf("%s",str) != 0) {
        str[strcspn(str,"\n\r")] = 0;
        if (strcmp(str, "0") == 0) {
            UI_files_controller(fileIsLoaded);
            return 0;
        }
        fp = fopen(str, "r");
        if (fp == NULL) {
            invalidINP
            continue;
        } else {
            loadingMenu();
            s = loadFiles1(str);
            fileIsLoaded = TRUE;
            UI_controller(s,fileIsLoaded);
        }
        fclose(fp);
        return 0;
    }
    break;
    case 3:
    // Trabalhar na opção gerir ficheiros carregados
    break;
    default:
        UI_controller(s,fileIsLoaded);
        return 0;
        break;
    }

   // UI_controller(s,fileIsLoaded);
}
    return 0;
}