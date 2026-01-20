#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct panel {
    char uid[10];
    char pwd[10];
};

struct Menu {
    char pname[20];
    int price;
    char category[20];
    int quantity;
};

struct record {
    char name[20];
    long long phone;
    char address[30];
};

/* Utility function to clear input buffer */
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* ADMIN REGISTER */
void registerAdmin() {
    struct panel person;
    FILE *ptr = fopen("restaurant.txt", "ab");

    if (!ptr) {
        printf("File error!\n");
        return;
    }

    printf("Enter the uid: ");
    fgets(person.uid, sizeof(person.uid), stdin);
    person.uid[strcspn(person.uid, "\n")] = 0;

    printf("Enter the password: ");
    fgets(person.pwd, sizeof(person.pwd), stdin);
    person.pwd[strcspn(person.pwd, "\n")] = 0;

    fwrite(&person, sizeof(person), 1, ptr);
    fclose(ptr);

    printf("\nHey %s, now you are the admin!\n", person.uid);
}

/* CHECK IF CUSTOMER EXISTS */
int check(long long pno) {
    struct record customer;
    FILE *ptr = fopen("rest.txt", "rb");

    if (!ptr) return 0;

    while (fread(&customer, sizeof(customer), 1, ptr)) {
        if (customer.phone == pno) {
            fclose(ptr);
            return 1;
        }
    }
    fclose(ptr);
    return 0;
}

/* REGISTER NEW CUSTOMER */
void createNewCustomer() {
    struct record customer;
    FILE *ptr = fopen("rest.txt", "ab");

    if (!ptr) {
        printf("File error!\n");
        return;
    }

    printf("Enter your name: ");
    fgets(customer.name, sizeof(customer.name), stdin);
    customer.name[strcspn(customer.name, "\n")] = 0;

    printf("Enter phone number: ");
    scanf("%lld", &customer.phone);
    clearBuffer();

    if (check(customer.phone)) {
        printf("\nCustomer already exists!\n");
        fclose(ptr);
        return;
    }

    printf("Enter address: ");
    fgets(customer.address, sizeof(customer.address), stdin);
    customer.address[strcspn(customer.address, "\n")] = 0;

    fwrite(&customer, sizeof(customer), 1, ptr);
    fclose(ptr);

    printf("\nRegistration successful. Welcome %s!\n", customer.name);
}

/* OLD CUSTOMER */
void oldCustomer() {
    long long pno;
    printf("Enter phone number: ");
    scanf("%lld", &pno);
    clearBuffer();

    if (!check(pno)) {
        printf("\nNot registered. Please register first.\n");
        createNewCustomer();
    } else {
        printf("\nWelcome back!\n");
    }
}

/* ADMIN VERIFICATION */
int verifiedAdmin() {
    struct panel admin, input;
    FILE *ptr = fopen("restaurant.txt", "rb");

    if (!ptr) {
        printf("No admin registered!\n");
        return 0;
    }

    fread(&admin, sizeof(admin), 1, ptr);
    fclose(ptr);

    for (int i = 0; i < 3; i++) {
        printf("Enter user id: ");
        fgets(input.uid, sizeof(input.uid), stdin);
        input.uid[strcspn(input.uid, "\n")] = 0;

        printf("Enter password: ");
        fgets(input.pwd, sizeof(input.pwd), stdin);
        input.pwd[strcspn(input.pwd, "\n")] = 0;

        if (!strcmp(admin.uid, input.uid) &&
            !strcmp(admin.pwd, input.pwd)) {
            printf("Verified successfully!\n");
            return 1;
        }
        printf("Wrong credentials!\n");
    }

    printf("Too many attempts. Try later.\n");
    sleep(3);
    return 0;
}

/* REGISTER PRODUCTS */
void registerProduct() {
    struct Menu product;
    FILE *ptr = fopen("product.txt", "ab");

    if (!ptr) {
        printf("File error!\n");
        return;
    }

    int more = 1;
    while (more) {
        printf("Product name: ");
        fgets(product.pname, sizeof(product.pname), stdin);
        product.pname[strcspn(product.pname, "\n")] = 0;

        printf("Price: ");
        scanf("%d", &product.price);

        printf("Quantity: ");
        scanf("%d", &product.quantity);
        clearBuffer();

        printf("Category: ");
        fgets(product.category, sizeof(product.category), stdin);
        product.category[strcspn(product.category, "\n")] = 0;

        fwrite(&product, sizeof(product), 1, ptr);
        printf("Product registered!\n");

        printf("Add more? (1/0): ");
        scanf("%d", &more);
        clearBuffer();
    }
    fclose(ptr);
}

/* DISPLAY PRODUCTS */
void displayProducts() {
    struct Menu product;
    FILE *ptr = fopen("product.txt", "rb");

    if (!ptr) {
        printf("No products available.\n");
        return;
    }

    printf("\nName            Price   Category        Qty   Total\n");
    printf("-----------------------------------------------------\n");

    while (fread(&product, sizeof(product), 1, ptr)) {
        printf("%-15s %-7d %-15s %-5d %-7d\n",
               product.pname, product.price,
               product.category, product.quantity,
               product.price * product.quantity);
    }
    fclose(ptr);
}

/* MAIN */
int main() {
    int type, choice, cont = 1;

    while (cont) {
        printf("\n1. Admin\n2. Customer\nChoice: ");
        scanf("%d", &type);
        clearBuffer();

        if (type == 1) {
            if (verifiedAdmin()) {
                printf("1. Register Product\n2. Display Products\n");
                scanf("%d", &choice);
                clearBuffer();

                if (choice == 1) registerProduct();
                else if (choice == 2) displayProducts();
            }
        } else if (type == 2) {
            printf("1. New Customer\n2. Old Customer\n");
            scanf("%d", &choice);
            clearBuffer();

            if (choice == 1) createNewCustomer();
            else if (choice == 2) {
                oldCustomer();
                displayProducts();
            }
        }

        printf("Continue? (1/0): ");
        scanf("%d", &cont);
        clearBuffer();
    }

    printf("\nGoodbye!\n");
    return 0;
}
