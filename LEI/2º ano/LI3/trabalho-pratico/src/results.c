#include <stats.h>
#include <glib.h>
#include <stdio.h>
#include <stdio.h>
#include <results.h>

GSList* parseLine(const char *input){
    char *end, *tok;
    GSList* cmd=NULL;

    end = strdup(input);

    while(end!=NULL){
        tok = strsep(&end, " ");
        cmd = g_slist_append(cmd,tok);
    }
    return cmd;
}


int queries_file(Stats s,int argc, char *file_path){

    Results res = stats_result_new();
    
    FILE* fp = NULL;
    if (argc < 2) {
        fp = stdin;
    }
    else {
        fp = fopen(file_path, "r");
        if (!fp) {
            perror("Error");
            return 2;
        }
    }
    char* line = NULL;;
    ssize_t read;
    size_t len;
    char* str;
    int i=1;
    char filename[64];
    while ((read = getline(&line, &len, fp)) != -1) {
        str=&line[2];
        sprintf(filename,"Resultados/command%d_output.txt",i);
        FILE* f = fopen(filename,"w");
        i++;
        int a;
        char* tok;
        Date d1;
        Date d2;
        char* city;
        switch(line[0]){
            case '1':
            
            str[strcspn(str,"\n\r")] = 0;
            res = Q1(s, str);
            print_table(res, f);
            break;

            case '2':
            sscanf(str,"%d",&a);
            res = Q2(s, a);
            print_table(res, f);
            break;

            case '3':
            sscanf(str,"%d",&a);
            res = Q3(s, a);
            print_table(res, f);
            break;

            case '4':
            str[strcspn(str,"\n\r")] = 0;
            res = Q4(s, str);
            print_table(res, f);
            break;

            case '5':
            tok = strsep(&str, " ");
            d1=parsingDateInput(tok);

            tok = strsep(&str," ");
            d2=parsingDateInput(tok);
            res = Q5(s, d1,d2);

            
            print_table(res, f);
            
            break;

            case '6':

            tok = strsep(&str, " ");
            city=strdup(tok);

            tok = strsep(&str, " ");
            d1=parsingDateInput(tok);

            tok = strsep(&str," ");
            d2=parsingDateInput(tok);
            res = Q6(s, city,d1,d2);
            print_table(res, f);
            break;

            case '7':
            break;

            case '8':
            break;

            case '9':
            break;
        }
        fclose(f);
        
    }
    return 0;
}
