#include <stdio.h>
// Structure Declaration
struct Record{
    char name[20];
    int roll;
    char address[100];
};
// Utility Function Declarations
void insertRecord();
void deleteRecord();
void searchRecord();
void displayRecord();

int main()
{
    int choice;
    do{
        printf("Press 1: To insert A Record\n");
        printf("Press 2: To Delete a Record\n");
        printf("Press 3: To Search the Record\n");
        printf("Press 4: To Display a Record\n");
        printf("Press 5: To Exit\n");
        scanf("%d", &choice);
        
        
    // SWTICH CONDITIONS
        switch(choice){
            case 1: insertRecord();
                    break;
            case 2: deleteRecord();
                    break;
            case 3: searchRecord();
                    break;
            case 4: displayRecord();
                    break;
            case 5: printf("\n\n Thank You");
                    break;
            default: printf("\n\n Wrong Input! \nEnter a Valid Input!");
        }
    } while(choice != 5);
    
    return 0;
}

void insertRecord(){
    struct Record student;
    FILE *ptr;
    ptr = fopen("Prince.dat", "ab");
    while(getchar() != '\n');
    printf("\nEnter Your Information :\n");
    printf("Enter Your Name :\n");
    fgets(student.name, 20, stdin);
    
    printf("Enter Your Roll Number:\n");
    scanf("%d", &student.roll);
    
    while(getchar() != '\n');
    printf("Enter Your Address:\n");
    fgets(student.address, 100, stdin);
    
    fwrite((char*)&student,sizeof(student),1,ptr);
    fclose(ptr);
}

void deleteRecord(){
    
};

void searchRecord(){
    
};

void displayRecord(){
    
};

