#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_FILE "students.dat"
#define TEMP_FILE "temp.dat"

struct record {
    char name[50];
    int roll;
    char address[200];
};

/* Read a line from stdin into buf (maxlen), removing the trailing newline if present */
static void read_line(char *buf, size_t maxlen)
{
    if (fgets(buf, (int)maxlen, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }
    size_t len = strlen(buf);
    if (len > 0 && buf[len-1] == '\n')
        buf[len-1] = '\0';
}

void addStudent(void)
{
    struct record stud;
    FILE *fp = NULL;

    printf("\nEnter the name: ");
    read_line(stud.name, sizeof(stud.name));

    printf("Enter the roll: ");
    if (scanf("%d", &stud.roll) != 1) {
        printf("Invalid roll number.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n'); /* clear rest of line */

    printf("Enter the address: ");
    read_line(stud.address, sizeof(stud.address));

    fp = fopen(DATA_FILE, "ab");
    if (!fp) {
        perror("Unable to open data file for appending");
        return;
    }

    if (fwrite(&stud, sizeof(stud), 1, fp) != 1) {
        perror("Write error");
    } else {
        printf("Record added successfully.\n");
    }
    fclose(fp);
}

void deleteStudent(void)
{
    struct record stud;
    FILE *fp = NULL, *tmp = NULL;
    int r;
    int found = 0;

    printf("\nEnter the roll number to delete: ");
    if (scanf("%d", &r) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    fp = fopen(DATA_FILE, "rb");
    if (!fp) {
        perror("Unable to open data file");
        return;
    }
    tmp = fopen(TEMP_FILE, "wb");
    if (!tmp) {
        perror("Unable to open temporary file");
        fclose(fp);
        return;
    }

    while (fread(&stud, sizeof(stud), 1, fp) == 1) {
        if (stud.roll == r) {
            found = 1;
            continue; /* skip writing this record */
        }
        fwrite(&stud, sizeof(stud), 1, tmp);
    }

    fclose(fp);
    fclose(tmp);

    if (found) {
        if (remove(DATA_FILE) != 0) {
            perror("Unable to remove original file");
            /* attempt cleanup */
        }
        if (rename(TEMP_FILE, DATA_FILE) != 0) {
            perror("Unable to rename temp file");
        } else {
            printf("Record deleted successfully.\n");
        }
    } else {
        /* no change: remove tmp and keep original */
        remove(TEMP_FILE);
        printf("Record not found.\n");
    }
}

void searchStudent(void)
{
    struct record stud;
    FILE *fp = NULL;
    int r;
    int found = 0;

    printf("\nEnter the roll number to search: ");
    if (scanf("%d", &r) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    fp = fopen(DATA_FILE, "rb");
    if (!fp) {
        perror("Unable to open data file");
        return;
    }

    while (fread(&stud, sizeof(stud), 1, fp) == 1) {
        if (stud.roll == r) {
            found = 1;
            printf("\nName: %s\n", stud.name);
            printf("Roll: %d\n", stud.roll);
            printf("Address: %s\n", stud.address);
            break;
        }
    }

    if (!found) {
        printf("Record not found.\n");
    }
    fclose(fp);
}

void displayStudent(void)
{
    struct record stud;
    FILE *fp = NULL;

    fp = fopen(DATA_FILE, "rb");
    if (!fp) {
        perror("Unable to open data file");
        return;
    }

    printf("\nAll student records:\n");
    while (fread(&stud, sizeof(stud), 1, fp) == 1) {
        printf("-------------------------------\n");
        printf("Name   : %s\n", stud.name);
        printf("Roll   : %d\n", stud.roll);
        printf("Address: %s\n", stud.address);
    }
    printf("-------------------------------\n");

    fclose(fp);
}

int main(void)
{
    int choice;
    do {
        printf("\n\tStudents Record System\n");
        printf("1. Insert a record\n");
        printf("2. Delete a record\n");
        printf("3. Search a record\n");
        printf("4. Display all records\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1: addStudent(); break;
            case 2: deleteStudent(); break;
            case 3: searchStudent(); break;
            case 4: displayStudent(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Wrong choice, try again.\n");
        }
    } while (choice != 5);

    return 0;
}
