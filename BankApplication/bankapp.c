#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

// FILE_MANAGEMENT
FILE *sPtr, *curPtr, *domPtr, *childrenPtr;

// Define The Struct - Global
struct bankApp {
    char fullname[30];
    int age;
    char job[30];
    char address[30];
    char city[30];
    char placeOfBirth[30];
    char country[30];
    char mobileNumber[30];
};

// Define Struct For The Children Account Form
struct childrenAcc {
    char guardian_parent_name[30];
    char gender[30];
    char address[30];
    int age;
    char country[30];
    char mobileNumber[30];
};

// Function to Calculate Age
int calculateAge(int birthYear) {
    time_t currentTime;
    struct tm *localTime;
    time(&currentTime);
    localTime = localtime(&currentTime);
    int currentYear = localTime->tm_year + 1900;
    int actualAge = currentYear - birthYear;
    return actualAge;
}

struct bankApp *bA;
struct childrenAcc *cA;

void bankForm(FILE *file) {
    // Allocate memory for bA
    bA = (struct bankApp *)malloc(sizeof(struct bankApp));

    // Clear input buffer
    while (getchar() != '\n');

    printf("Full Names : ");
    fgets(bA->fullname, sizeof(bA->fullname), stdin);

    printf("Date Of Birth (YY) : ");
    scanf("%d", &bA->age);
    int actualAge = calculateAge(bA->age);

    // Clear input buffer
    while (getchar() != '\n');

    printf("Occupation : ");
    fgets(bA->job, sizeof(bA->job), stdin);
    printf("Mailing Address : ");
    fgets(bA->address, sizeof(bA->address), stdin);
    printf("City : ");
    fgets(bA->city, sizeof(bA->city), stdin);
    printf("Place Of Birth : ");
    fgets(bA->placeOfBirth, sizeof(bA->placeOfBirth), stdin);
    printf("Nationality : ");
    fgets(bA->country, sizeof(bA->country), stdin);
    printf("Mobile Number : ");
    fgets(bA->mobileNumber, sizeof(bA->mobileNumber), stdin);

    // Write user input to the file
    fprintf(file, "Full Names: %s", bA->fullname);
    fprintf(file, "Date Of Birth (YY): %d\n", bA->age);
    fprintf(file, "Age: %d\n", actualAge); // Adding actual age
    fprintf(file, "Occupation: %s", bA->job);
    fprintf(file, "Mailing Address: %s", bA->address);
    fprintf(file, "City: %s", bA->city);
    fprintf(file, "Place Of Birth: %s", bA->placeOfBirth);
    fprintf(file, "Nationality: %s", bA->country);
    fprintf(file, "Mobile Number: %s", bA->mobileNumber);

    //Time Stamp
    time_t timeStamp;
    time(&timeStamp);
    struct tm *realTime = localtime(&timeStamp);

    fprintf(file, "\n\nTime Stamp\nForm Completed Today: %04d-%02d-%02d %02d:%02d:%02d",
    realTime->tm_year + 1900, realTime->tm_mon + 1, realTime->tm_mday,
    realTime->tm_hour, realTime->tm_min, realTime->tm_sec);


    free(bA);
}

void childrenBankForm(FILE *file) {
    cA = (struct childrenAcc *)malloc(sizeof(struct childrenAcc));

    printf("Guardian/Parent Names: ");
    fgets(cA->guardian_parent_name, sizeof(cA->guardian_parent_name), stdin);

    printf("Date Of Birth (YY): ");
    scanf("%d", &cA->age);

    while (getchar() != '\n');

    printf("Mailing Address: ");
    fgets(cA->address, sizeof(cA->address), stdin);
    printf("Country: ");
    fgets(cA->country, sizeof(cA->country), stdin);
    printf("(Guardian/Parent) Mobile Number: ");
    fgets(cA->mobileNumber, sizeof(cA->mobileNumber), stdin);

    // Write user input to the file
    fprintf(file, "Guardian/Parent Names: %s", cA->guardian_parent_name);
    fprintf(file, "Date Of Birth (YY): %d\n", cA->age);
    fprintf(file, "Mailing Address: %s", cA->address);
    fprintf(file, "Country: %s", cA->country);
    fprintf(file, "(Guardian/Parent) Mobile Number: %s", cA->mobileNumber);

    free(cA);
}

void bankingServices() {
    printf("Enter 1 Savings Account\nEnter 2 Current Account\nEnter 3 Domiciliary Account\nEnter 4 Children Account\nEnter 5 To Go Back To Main Menu\n\nEnter Option : ");
    int menuOption;
    scanf("%d", &menuOption);
    getchar();
    switch (menuOption) {
        case 1:
            printf("Savings Account Opening Form\n");
            bankForm(sPtr);
            break;
        case 2:
            printf("Current Account Opening Form\n");
            bankForm(curPtr);
            break;
        case 3:
            printf("Domiciliary Account Opening Form\n");
            bankForm(domPtr);
            break;
        case 4:
            printf("Children Account Opening Form\n");
            childrenBankForm(childrenPtr); // Call the childrenBankForm for children account
            break;
        case 5:
            return;
        default:
            break;
    }
}

void serviceCentre() {
    printf("Enter 1 Account Officer\nEnter 2 Insurance Brokers\nEnter 3 Pension Managers\nEnter 4 Loan Officers\nEnter 5 To Go Back To Main Menu\n\nEnter Option : ");
    int menuOption;
    scanf("%d", &menuOption);
    getchar();
    switch (menuOption) {
    case 5:
        return;
        break;
    default:
        break;
    }
}

int main() {
    printf("\t\t\t\t\tBank Of The SouthWestLands\n\n");

    sPtr = fopen("savingsAcc.txt", "w+");
    curPtr = fopen("currentAcc.txt", "w+");
    domPtr = fopen("DomiciliaryAcc.txt", "w+");
    childrenPtr = fopen("childrenAcc.txt", "w+");

    if (sPtr == NULL || curPtr == NULL || domPtr == NULL || childrenPtr == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    while (1) {
        printf("\n\t\t\tEnter 1 For Banking Services\n\t\t\tEnter 2 For Service Centre\n\t\t\tEnter 3 To Exit Program\n\t\t\tEnter Option : ");
        int option;
        scanf("%d", &option);
        getchar();
        switch (option) {
            case 1:
                printf("Banking Service\n\n\n");
                bankingServices();
                break;
            case 2:
                printf("Service Centre\n\n\n");
                serviceCentre();
                break;
            case 3:
                printf("Exiting Program\n");
                Sleep(3000);
                printf("Bye!!!.... We'd Love To See You Again!!\n");
                exit(0);
                break;
            default:
                break;
        }
    }

    fclose(sPtr);
    fclose(curPtr);
    fclose(domPtr);
    fclose(childrenPtr);
}