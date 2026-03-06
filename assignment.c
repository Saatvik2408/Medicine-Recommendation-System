#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEDICINES 200
#define MAX_NAME_LEN 50
#define MAX_CATEGORY_LEN 30
#define MAX_SYMPTOMS_LEN 100

typedef struct {
    int medID;
    char name[MAX_NAME_LEN];
    char category[MAX_CATEGORY_LEN];
    char symptoms[MAX_SYMPTOMS_LEN];
    int stock;
} Medicine;

Medicine medicines[MAX_MEDICINES];
int medicineCount = 0;

// Function prototypes
void loadMedicinesFromFile(const char *filename);
void saveMedicinesToFile(const char *filename);
void addOrUpdateMedicine();
void searchMedicine();
void printMedicinesByCategory(const char *filename);
void sortMedicinesByName();
void displayMenu();

int main() {
    int choice;
    const char *filename = "medicines.txt";

    loadMedicinesFromFile(filename);

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addOrUpdateMedicine();
                saveMedicinesToFile(filename);
                break;
            case 2:
                searchMedicine();
                break;
            case 3:
                printMedicinesByCategory("category_output.txt");
                break;
            case 4:
                sortMedicinesByName();
                break;
            case 5:
                saveMedicinesToFile(filename);
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void loadMedicinesFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("File not found. Starting with an empty database.\n");
        return;
    }

    medicineCount = 0;
    while (fscanf(file, "%d,%49[^,],%29[^,],%99[^,],%d\n", &medicines[medicineCount].medID,
                  medicines[medicineCount].name, medicines[medicineCount].category,
                  medicines[medicineCount].symptoms, &medicines[medicineCount].stock) == 5) {
        medicineCount++;
    }

    fclose(file);
}

void saveMedicinesToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error saving to file.\n");
        return;
    }

    for (int i = 0; i < medicineCount; i++) {
        fprintf(file, "%d,%s,%s,%s,%d\n", medicines[i].medID, medicines[i].name,
                medicines[i].category, medicines[i].symptoms, medicines[i].stock);
    }

    fclose(file);
}

void addOrUpdateMedicine() {
    int id, found = 0;
    printf("Enter Medicine ID: ");
    scanf("%d", &id);

    for (int i = 0; i < medicineCount; i++) {
        if (medicines[i].medID == id) {
            printf("Medicine found. Updating details...\n");
            printf("Enter Name: ");
            scanf(" %[^\n]", medicines[i].name);
            printf("Enter Category: ");
            scanf(" %[^\n]", medicines[i].category);
            printf("Enter Symptoms: ");
            scanf(" %[^\n]", medicines[i].symptoms);
            printf("Enter Stock: ");
            scanf("%d", &medicines[i].stock);
            found = 1;
            break;
        }
    }

    if (!found) {
        if (medicineCount >= MAX_MEDICINES) {
            printf("Medicine database is full.\n");
            return;
        }

        medicines[medicineCount].medID = id;
        printf("Enter Name: ");
        scanf(" %[^\n]", medicines[medicineCount].name);
        printf("Enter Category: ");
        scanf(" %[^\n]", medicines[medicineCount].category);
        printf("Enter Symptoms: ");
        scanf(" %[^\n]", medicines[medicineCount].symptoms);
        printf("Enter Stock: ");
        scanf("%d", &medicines[medicineCount].stock);
        medicineCount++;
    }
}

void searchMedicine() {
    int choice, id;
    char name[MAX_NAME_LEN];
    printf("Search by:\n1. Name\n2. ID\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter Medicine Name: ");
        scanf(" %[^\n]", name);
        for (int i = 0; i < medicineCount; i++) {
            if (strcmp(medicines[i].name, name) == 0) {
                printf("Medicine Found: ID=%d, Name=%s, Category=%s, Symptoms=%s, Stock=%d\n",
                       medicines[i].medID, medicines[i].name, medicines[i].category,
                       medicines[i].symptoms, medicines[i].stock);
                return;
            }
        }
    } else if (choice == 2) {
        printf("Enter Medicine ID: ");
        scanf("%d", &id);
        for (int i = 0; i < medicineCount; i++) {
            if (medicines[i].medID == id) {
                printf("Medicine Found: ID=%d, Name=%s, Category=%s, Symptoms=%s, Stock=%d\n",
                       medicines[i].medID, medicines[i].name, medicines[i].category,
                       medicines[i].symptoms, medicines[i].stock);
                return;
            }
        }
    }

    printf("Medicine not found.\n");
}

void printMedicinesByCategory(const char *filename) {
    char category[MAX_CATEGORY_LEN];
    printf("Enter Category: ");
    scanf(" %[^\n]", category);

    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < medicineCount; i++) {
        if (strcmp(medicines[i].category, category) == 0) {
            fprintf(file, "ID=%d, Name=%s, Category=%s, Symptoms=%s, Stock=%d\n",
                    medicines[i].medID, medicines[i].name, medicines[i].category,
                    medicines[i].symptoms, medicines[i].stock);
        }
    }

    fclose(file);
    printf("Medicines of category '%s' have been written to %s.\n", category, filename);
}

void sortMedicinesByName() {
    for (int i = 0; i < medicineCount - 1; i++) {
        for (int j = i + 1; j < medicineCount; j++) {
            if (strcmp(medicines[i].name, medicines[j].name) > 0) {
                Medicine temp = medicines[i];
                medicines[i] = medicines[j];
                medicines[j] = temp;
            }
        }
    }

    printf("Medicines sorted alphabetically by name.\n");
}

void displayMenu() {
    printf("\nMedicine Recommendation System\n");
    printf("1. Add/Update Medicine\n");
    printf("2. Search Medicine\n");
    printf("3. Print Medicines by Category\n");
    printf("4. Sort Medicines by Name\n");
    printf("5. Exit\n");
}