#include <stdio.h>

#include <string.h>

#include <stdlib.h>



#define MAX_STUDENTS 10



struct Student {

    char name[20];

    int roll;

    char telephone[11];

    char address[20];

};



struct SReg {

    int count; /* represents valid student entries,

                initially it should be set to 0 */

    struct Student studentArray[MAX_STUDENTS];

};



int add(struct SReg *sr, struct Student s) {

    if (sr->count >= MAX_STUDENTS) {

        return -1;

    }

    for (int i = 0; i < sr->count; i++) {

        if (sr->studentArray[i].roll == s.roll)

            return 0;

    }

    sr->studentArray[sr->count++] = s;

    return 1;

}



struct Student get(struct SReg sr, int r) {

    struct Student empty = {"", 0, "", ""};

    for (int i = 0; i < sr.count; i++) {

        if (sr.studentArray[i].roll == r)

            return sr.studentArray[i];

    }

    return empty;

}



int delete(struct SReg *sr, int r) {

    for (int i = 0; i < sr->count; i++) {

        if (sr->studentArray[i].roll == r) {

            for (int j = i; j < sr->count - 1; j++) {

                sr->studentArray[j] = sr->studentArray[j + 1];

            }

            sr->count--;

            return 1;

        }

    }

    return 0;

}



int modify(struct SReg *sr, struct Student s) {

    for (int i = 0; i < sr->count; i++) {

        if (sr->studentArray[i].roll == s.roll) {

            sr->studentArray[i] = s;

            return 1;

        }

    }

    return 0;

}



void sortStudents(struct SReg *sr) {

    for (int i = 0; i < sr->count - 1; i++) {

        for (int j = i + 1; j < sr->count; j++) {

            if (strcmp(sr->studentArray[i].name, sr->studentArray[j].name) > 0) {

                struct Student temp = sr->studentArray[i];

                sr->studentArray[i] = sr->studentArray[j];

                sr->studentArray[j] = temp;

            }

        }

    }

}



int getCount(struct SReg sr) {

    return sr.count;

}



void export(struct SReg sr, const char *fname) {

    FILE *fp = fopen(fname, "w");

    if (!fp) {

        printf("Failed to open file for writing.\n");

        return;

    }

    for (int i = 0; i < sr.count; i++) {

        fprintf(fp, "%s|%d|%s|%s\n", sr.studentArray[i].name, sr.studentArray[i].roll,

                sr.studentArray[i].telephone, sr.studentArray[i].address);

    }

    fclose(fp);

}



void load(struct SReg *sr, const char *fname) {

    FILE *fp = fopen(fname, "r");

    if (!fp) {

        printf("Failed to open file for reading.\n");

        return;

    }

    sr->count = 0;

    struct Student s;

    int items_read;

    while ((items_read = fscanf(fp, "%19[^|]|%d|%10[^|]|%19[^\n]\n", 

                                s.name, &s.roll, s.telephone, s.address)) == 4) {

        if (sr->count < MAX_STUDENTS) {

            sr->studentArray[sr->count++] = s;

        }

    }

    fclose(fp);

}



void printStudent(struct Student s) {

    printf("Name: %s | Roll: %d | Phone: %s | Address: %s\n",

           s.name, s.roll, s.telephone, s.address);

}



int main() {

    struct SReg reg = {0};



    struct Student s1 = {"Shaw, Mrigaj", 123456, "9837299274", "Kolkata"};

    struct Student s2 = {"Agarwal, Riddhi", 234567, "8367273913", "Pune"};

    struct Student s3 = {"Gupta, Sanchita", 345678, "8392936283", "Jaipur"};



    add(&reg, s1);

    add(&reg, s2);

    add(&reg, s3);



    printf("\n--- All Students ---\n");

    for (int i = 0; i < reg.count; i++) {

        printStudent(reg.studentArray[i]);

    }



    printf("\n--- Get Roll 234567 ---\n");

    printStudent(get(reg, 234567));

    

    printf("\n--- Delete Roll 123456 ---\n");

    delete(&reg, 123456);

    

    printf("\n--- All Students ---\n");

    for (int i = 0; i < reg.count; i++) {

        printStudent(reg.studentArray[i]);

    }

    

    printf("\n--- Modify Roll 345678 ---\n");

    struct Student sMod = {"Singh, Ubika", 345678, "9878964257", "Bangalore"};

    modify(&reg, sMod);

    

    printf("\n--- All Students ---\n");

    for (int i = 0; i < reg.count; i++) {

        printStudent(reg.studentArray[i]);

    }



    printf("\n--- Sorted Students ---\n");

    sortStudents(&reg);

    

    printf("\n--- All Students ---\n");

    for (int i = 0; i < reg.count; i++) {

        printStudent(reg.studentArray[i]);

    }

    

    printf("\n--- Exporting to file ---\n");

    export(reg, "students.txt");



    printf("\n--- Loading from file ---\n");

    struct SReg newReg = {0};

    load(&newReg, "students.txt");

    for (int i = 0; i < newReg.count; i++) {

        printStudent(newReg.studentArray[i]);

    }

    

    printf("\n--- Total Students: %d ---\n", getCount(newReg));

    

    return 0;

}
