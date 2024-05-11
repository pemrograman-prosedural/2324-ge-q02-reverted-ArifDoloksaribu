// 12S23026 - Arif M. Doloksaribu
// 12S23051 - Theresia Silaban


#include <stdio.h>
#include "./libs/dorm.h"
#include "./libs/student.h"
#include <stdlib.h>
#include <string.h>

int main(int _argc, char **_argv)
{
    struct dorm_t *dorm = malloc(100 * sizeof(struct dorm_t));
    struct student_t *student = malloc(100 * sizeof(struct student_t));
    int i = 0;

    char masukan[100], *argument, *token;
    int h = 0;

    while (1) {
        fgets(masukan, 100, stdin);
        masukan[strcspn(masukan, "\n")] = 0;
        if (strcmp(masukan, "---") == 0) {
            break;
        } else if (strcmp(masukan, "dorm-print-all") == 0) {
            print_dorms(dorm, h);
            continue;
        }
        else if(strcmp(masukan, "dorm-print-all-detail")==0){
            dorm_print_all_detail(dorm, h);
        }
        else if (strcmp(masukan, "student-print-all") == 0) {
            print_stu(student, i);
            continue;
        }
        else if(strcmp(masukan, "student-print-all-detail")==0){
            student_print_all_detail(student, i);
            continue;
        }
        argument = strtok(masukan, "#");
        if (strcmp(argument, "dorm-add") == 0) {
            token = strtok(NULL, "#");
            strcpy(dorm[h].name, token);
            token = strtok(NULL, "#");
            dorm[h].capacity = atoi(token);
            token = strtok(NULL, "#");
            if (strcmp(token, "male") == 0) {
                dorm[h].gender = GENDER_MALE;
            } else {
                dorm[h].gender = GENDER_FEMALE;
            }
            
            dorm[h] = create_dorm(dorm[h].name, dorm[h].capacity, dorm[h].gender);

            h++;
        }
        else if (strcmp(argument, "student-add") == 0){
            token = strtok(NULL, "#");
            strcpy(student[i].id, token);
            token = strtok(NULL, "#");
            strcpy(student[i].name, token);
            token = strtok(NULL, "#");
            strcpy(student[i].year, token);
            token = strtok(NULL, "#");
            if (strcmp(token, "male") == 0) {
                 student[i].gender = GENDER_MALE;
            } else {
                student[i].gender = GENDER_FEMALE;
            }
             student[i] = create_student(student[i].id, student[i].name, student[i].year, student[i].gender);

            i++;
        }   
        else if(strcmp(argument,"assign-student")==0){
            int x, y; 
            int z; 
            token = strtok(NULL, "#");
            char student_id[20];
            strcpy(student_id, token);

            for(x = 0; x < i; x++){
                if(strcmp(student[x].id, student_id) == 0){
                    y = x;
                    break;
                }
            }

            if(x == i){
                continue;
            }

            token = strtok(NULL, "#");
            char dorm_name[20];
            strcpy(dorm_name, token);

            for(x = 0; x < h; x++){
                if(strcmp(dorm[x].name, dorm_name) == 0){
                    z = x;
                    break;
                }
            }

            if(x == h){
                continue;
            }

            assign_student(&student[y], y, &dorm[z], z);
        }
                
        else if(strcmp(argument,"move-student")==0){
            int x, y, w;
            token = strtok(NULL, "#");
            char student_id[20];
            strcpy(student_id, token);

            for(x = 0; x < i; x++){
                if(strcmp(student[x].id, student_id) == 0){
                    y = x;
                    break;
                }
            }

            if(x == i){
                continue;
            }

            token = strtok(NULL, "#");
            char dorm_name[20];
            strcpy(dorm_name, token);

            for(x = 0; x < h; x++){
                if(strcmp(dorm[x].name, dorm_name) == 0){
                    w = x;
                    break;
                }
            }

            if(w == h){ 
                continue;
            }
            
            if(student[y].dorm == NULL){
                assign_student(&student[y], y, &dorm[w], w); 
            }
            else{
                if(strcmp(student[y].dorm->name, dorm[w].name) != 0){
                    move_student(&student[y], y, &dorm[w], w); 
                }
            }
        }

        else if(strcmp(argument,"dorm-empty")==0){
            char dorm_name[20];
            int l=-1;
            token = strtok(NULL, "#");
            strcpy(dorm_name, token);
            for(int r = 0; r<h; r++){
                if(strcmp(dorm[r].name, dorm_name) == 0){
                    l = r;
                    break;
                }
            }
            if(l != -1){ 
                for(int y=0; y<i; y++){
                    if(student[y].dorm != NULL && strcmp(student[y].dorm->name, dorm_name) == 0){
                        dorm_empty(&student[y], i, &dorm[l], l); 
                    }
                }
            }
        }

    }
    return 0;
}