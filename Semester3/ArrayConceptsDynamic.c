#include<stdio.h>

#include<stdlib.h>

#include<string.h>



#define MAX_STUDENTS 10



typedef struct Student {

    char* name;

    int roll;

    char telephone[11];

    char *address;

} Student;



typedef struct SReg {

    int maxStuds;

    int count;

    Student **arrStudPtr;

} SReg;



Student* createStudentRecord(){

    Student *s = (Student *)malloc(sizeof(Student));

    if(!s){

        return NULL;

    }

    char buffer[100];



    printf("Enter name: ");

    scanf(" %[^\n]",buffer);

    s->name = (char *)malloc(strlen(buffer) + 1);

    if(!s->name){

        return NULL;

    }

    strcpy (s->name, buffer);



    printf("Enter roll: ");

    scanf("%d", &s->roll);



    printf("Enter telephone: ");

    scanf("%10s", &s->telephone);



    printf("Enter address: ");

    scanf(" %[^\n]",buffer);

    s->address = (char *)malloc(strlen(buffer) + 1);

    if(!s->address){

        return NULL;

    }

    strcpy (s->address, buffer);



    return s;

}



Student* createStudentRecordFromFile(const char *line){

    Student *s = (Student *)malloc(sizeof(Student));

    if(!s){

        return NULL;

    }

    char name[100], address[100];

    int r;

    char phone[11];

    if(sscanf(line, "%99[^|]|%d|%10[^|]|%99[^\n]", name, &r, phone, address) != 4 ){

        free(s);

        return NULL;

    }



    s->name = strdup(name);

    s->roll = r;

    strcpy(s->telephone,phone);

    s->address = strdup(address);



    return s;

}



void freeStudentRecord(Student *s){

    if(!s){

        return;

    }

    free(s->name);

    free(s->address);

    free(s);

}



int add(SReg *sr ,Student *s) {

    if (sr->count >= sr->maxStuds) {

        return -1;

    }

    for (int i = 0; i < sr->count; i++) {

        if (sr->arrStudPtr[i]->roll == s->roll)

            return 0;

    }

    sr->arrStudPtr[sr->count++] = s;

    return 1;

}



Student* get(SReg sr, int r) {

    for (int i = 0; i < sr.count; i++) {

        if (sr.arrStudPtr[i]->roll == r)

            return sr.arrStudPtr[i];

    }

    return NULL; 

}



int delete(SReg *sr, int r) {

    for (int i = 0; i < sr->count; i++) {

        if (sr->arrStudPtr[i]->roll == r) {

            freeStudentRecord(sr->arrStudPtr[i]);

            for (int j = i; j < sr->count - 1; j++) {

                sr->arrStudPtr[j] = sr->arrStudPtr[j + 1];

            }

            sr->count--;

            return 1;

        }

    }

    return 0;

}



int modify(SReg *sr, Student *s) {

    for (int i = 0; i < sr->count; i++) {

        if (sr->arrStudPtr[i]->roll == s->roll) {

            freeStudentRecord(sr->arrStudPtr[i]);

            sr->arrStudPtr[i] = s;

            return 1;

        }

    }

    return 0;

}



void sortStudents(SReg *sr) {

    for (int i = 0; i < sr->count - 1; i++) {

        for (int j = i + 1; j < sr->count; j++) {

            if (strcmp(sr->arrStudPtr[i]->name, sr->arrStudPtr[j]->name) > 0) {

                Student *temp = sr->arrStudPtr[i];

                sr->arrStudPtr[i] = sr->arrStudPtr[j];

                sr->arrStudPtr[j] = temp;

            }

        }

    }

}





int getCount(SReg sr) {

    return sr.count;

}



void export(SReg sr, const char *fname) {

    FILE *fp = fopen(fname, "w");

    if (!fp) {

        printf("Failed to open file for writing.\n");

        return;

    }

    for (int i = 0; i < sr.count; i++) {

        fprintf(fp, "%s|%d|%s|%s\n", sr.arrStudPtr[i]->name, sr.arrStudPtr[i]->roll,

                sr.arrStudPtr[i]->telephone, sr.arrStudPtr[i]->address);

    }

    fclose(fp);

}



void load(SReg *sr, const char *fname) {

    FILE *fp = fopen(fname, "r");

    if (!fp) {

        printf("Failed to open file for reading.\n");

        return;

    }

    sr->count = 0;

    char line[300];

    while (fgets(line, sizeof(line), fp)) {

        if(sr->count >= sr->maxStuds){

            break;

        }

        Student *s = createStudentRecordFromFile(line);

        if(s){

            sr->arrStudPtr[sr->count++] = s;

        }

    }

    fclose(fp);

}



void printStudent(Student *s) {

    if(!s){

        return;

    }

    printf("Name: %s | Roll: %d | Phone: %s | Address: %s\n",

           s->name, s->roll, s->telephone, s->address);

}



void freeRegister(SReg *sr){

    for(int i=0; i<sr->count;i++){

        freeStudentRecord(sr->arrStudPtr[i]);

    }

    free(sr->arrStudPtr);

}



int main(){

    int max = MAX_STUDENTS;



    SReg reg;

    reg.maxStuds = max;

    reg.count = 0;

    reg.arrStudPtr = (Student **)malloc(sizeof(Student *) * max);



    int toAdd;

    printf("Enter the number of students to be added(<10): ");

    scanf("%d",&toAdd);

    printf("\n--- Adding students ---\n");

    for(int i = 0;i<toAdd;i++){

        Student *s = createStudentRecord();

        if(add(&reg, s)==1){

            printf("Added.\n");

        }

        else{

            printf("Failed to add.\n");

        }

    }



    printf("\n--- All Students ---\n");

    for (int i = 0; i < reg.count; i++) {

        printStudent(reg.arrStudPtr[i]);

    }



    int roll_num;

    printf("\nEnter roll to get that student's information:");

    scanf("%d",&roll_num);

    // printf("\n--- Get Roll ---\n");

    printStudent(get(reg, roll_num));



    printf("\nEnter roll to delete that student's information:");

    scanf("%d",&roll_num);

    // printf("\n--- Delete Roll ---\n");

    delete(&reg, roll_num);



    printf("\n--- All Students ---\n");

    for (int i = 0; i < reg.count; i++) {

        printStudent(reg.arrStudPtr[i]);

    }



    printf("\n--- Modify Roll ---\n");

    Student *sMod = createStudentRecord();

    modify(&reg, sMod);



    printf("\n--- All Students ---\n");

    for (int i = 0; i < reg.count; i++) {

        printStudent(reg.arrStudPtr[i]);

    }



    printf("\n--- Sorted Students ---\n");

    sortStudents(&reg);



    printf("\n--- All Students ---\n");

    for (int i = 0; i < reg.count; i++) {

        printStudent(reg.arrStudPtr[i]);

    }



    printf("\n--- Exporting to file ---\n");

    export(reg, "students_dynamic.txt");



    printf("\n--- Loading from file ---\n");

    SReg newReg;

    newReg.maxStuds = max;

    newReg.count = 0;

    newReg.arrStudPtr = (Student **)malloc(sizeof(Student *) * max);

    load(&newReg, "students_dynamic.txt");

    for (int i = 0; i < newReg.count; i++) {

        printStudent(newReg.arrStudPtr[i]);

    }

    

    printf("\n--- Total Students: %d ---\n", getCount(newReg));



    freeRegister(&reg);

    freeRegister(&newReg);



    return 0;

}


