#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_MEDICINES 100
struct appointment {
    char hname[100];
    char dname[100];
    char date[15];
    char time[10];
    char age[5];
    char gender[10];
    char phone[15];
    char reason[100];
    char payment[20];
    int isCompleted;
};
struct User {
    char fname[50];
    char email[50];
    char user_name[50];
    char password[50];
};
struct Emergency {
    char address[50];
    char sos[20];
    char fname[50];
};
struct medicine {
    char name[50];
    char dosage[30];
    char frequency[30];
    char startDate[15];
    int duration;
    int daysLeft;
    int taken;
};
struct appointment appt;
struct User currentUser;
struct Emergency emergency;
struct medicine medicines[MAX_MEDICINES];
int medicineCount = 0;
void clear(){
     printf("\n------------------------------\n");
    printf("|Press Enter to continue...");
    getchar();
    system("cls");
}
void showTitle() {
    printf("\n\t\t\t -------------------------- \n");
    printf("\t\t\t|       PROTIDDHONI        |\n");
    printf("\t\t\t -------------------------- \n\n");
    printf("|1. Log in\n|2. Sign up\n|3. Exit\n");
    printf("|Choose an option: ");
}
void appointmentTitle(){printf("\n\t\t\t ------------------  Appointment Menu  ------------------\n\n");
        printf("|1. Add Appointment\n|2. View Appointment\n|3. Mark as Completed\n|4. Cancel Appointment\n|5. Back\n");}
void noteTitle(){printf("\n\t\t\t ------------------  Note Menu  ------------------\n\n");
        printf("|1. Add Note\n|2. View Notes\n|3. Back\n");}
void emergencyTitle(){printf("\n\t\t\t ------------------  Emergency Menu  ------------------\n\n");
        printf("|Welcome! Let me know how I can assist you...\n");
        printf("|1. Add Emergency Information\n|2. View Emergency Information\n|3. Back\n");}
void userTitle(){printf("\n\t\t\t ------------------  Main Menu  ------------------\n\n");
        printf("| Welcome, Sir...\n");
        printf("|1. Appointment\n|2. Note\n|3. Medicine\n|4. Emergency\n|5. Log out\n");}
void MedicineTitle(){printf("\n\t\t\t ------------------  Medicine Menu  ------------------\n\n");
        printf("|1. Add Medicine\n|2. Show Medicine Chart\n|3. Mark Medicine as Taken\n|4. Exit\n");}
void showRegister() {
    printf("\n\t\t\t--- Sign Up Screen ---\n\n");
    struct User newUser;
    FILE *fptr = fopen("login.txt", "a");

    printf("|Enter your full name: ");
    fgets(newUser.fname, sizeof(newUser.fname), stdin);
    newUser.fname[strlen(newUser.fname) - 1] = '\0';

    printf("|Enter your email address: ");
    fgets(newUser.email, sizeof(newUser.email), stdin);
    newUser.email[strlen(newUser.email) - 1] = '\0';

    printf("|Enter user name: ");
    fgets(newUser.user_name, sizeof(newUser.user_name), stdin);
    newUser.user_name[strlen(newUser.user_name) - 1] = '\0';

    printf("|Enter password: ");
    fgets(newUser.password, sizeof(newUser.password), stdin);
    newUser.password[strlen(newUser.password) - 1] = '\0';

    fprintf(fptr, "%s %s %s %s\n", newUser.user_name, newUser.password, newUser.fname, newUser.email);
    fclose(fptr);

    printf("|Sign up successful !!");
    clear();
}
int showLogin() {
    printf("\n\t\t\t--- Login Screen ---\n\n");
    struct User inputUser, storedUser;
    FILE *fptr = fopen("login.txt", "r");

    printf("|Enter user name: ");
    fgets(inputUser.user_name, sizeof(inputUser.user_name), stdin);
    inputUser.user_name[strlen(inputUser.user_name) - 1] = '\0';

    printf("|Enter password: ");
    fgets(inputUser.password, sizeof(inputUser.password), stdin);
    inputUser.password[strlen(inputUser.password) - 1] = '\0';

    while (fscanf(fptr, "%s %s %*s %*s", storedUser.user_name, storedUser.password) == 2) {
        if (strcmp(inputUser.user_name, storedUser.user_name) == 0 &&
            strcmp(inputUser.password, storedUser.password) == 0) {
            fclose(fptr);
            printf("|Log in successful !!");
            clear();
            return 1;
        }
    }
    fclose(fptr);
    return 0;
}
void addAppointment() {
    printf("\n\t\t\t ------------------  Doctor's Regular Checkup Appointment Form  ------------------\n\n");

    printf("\t\t           ___________________Patient Information___________________\n\n");
    printf("|Full Name: ");
    fgets(appt.hname, sizeof(appt.hname), stdin);
    appt.hname[strcspn(appt.hname, "\n")] = '\0';

    printf("|Age: ");
    fgets(appt.age, sizeof(appt.age), stdin);
    appt.age[strcspn(appt.age, "\n")] = '\0';

    printf("|Gender: ");
    fgets(appt.gender, sizeof(appt.gender), stdin);
    appt.gender[strcspn(appt.gender, "\n")] = '\0';

    printf("|Phone Number: ");
    fgets(appt.phone, sizeof(appt.phone), stdin);
    appt.phone[strcspn(appt.phone, "\n")] = '\0';

    printf("\n\t\t          ___________________Appointment Details___________________\n\n");
    printf("|Doctor Name(Neurologist): ");
    fgets(appt.dname, sizeof(appt.dname), stdin);
    appt.dname[strcspn(appt.dname, "\n")] = '\0';

    printf("|Preferred Date (date - month - year): ");
    fgets(appt.date, sizeof(appt.date), stdin);
    appt.date[strcspn(appt.date, "\n")] = '\0';

    printf("|Preferred Time (hour : minutes  am/pm): ");
    fgets(appt.time, sizeof(appt.time), stdin);
    appt.time[strcspn(appt.time, "\n")] = '\0';

    printf("|Reason for Checkup: ");
    fgets(appt.reason, sizeof(appt.reason), stdin);
    appt.reason[strcspn(appt.reason, "\n")] = '\0';

    printf("\n\t\t          ___________________Payment Method___________________\n\n");
    printf("|Payment Method (e.g., Cash, Card, Insurance): ");
    fgets(appt.payment, sizeof(appt.payment), stdin);
    appt.payment[strcspn(appt.payment, "\n")] = '\0';

    appt.isCompleted = 0;

    FILE *file = fopen("appointment.txt", "w");
    fprintf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n", appt.hname, appt.age, appt.gender, appt.phone, appt.dname, appt.date, appt.time, appt.reason, appt.payment, appt.isCompleted);
    fclose(file);

    printf("\nConfirm appointment details? (y/n): ");
    char choice;
    scanf(" %c", &choice);
    getchar();
    if (choice != 'y' && choice != 'Y') {
        printf("|Appointment not saved.");
        clear();
        return;
    } else {
        printf("\nAppointment registration successfully!!");
        clear();
    }
}
void markAppointment() {
    FILE *file = fopen("appointment.txt", "r+");
    printf("\n|Enter the patient's full name to mark as completed: ");
    char searchName[100];
    getchar();
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    FILE *tempFile = fopen("temp.txt", "w");
    int found = 0;
    while (fscanf(file, "%99[^\n]\n%4[^\n]\n%9[^\n]\n%14[^\n]\n%99[^\n]\n%14[^\n]\n%9[^\n]\n%99[^\n]\n%19[^\n]\n%d\n",
                  appt.hname, appt.age, appt.gender, appt.phone, appt.dname, appt.date, appt.time, appt.reason, appt.payment, &appt.isCompleted) != EOF) {
        if (strcmp(appt.hname, searchName) == 0) {
            found = 1;
            appt.isCompleted = 1;
            printf("|Appointment for %s marked as completed.\n", appt.hname);
        }
        fprintf(tempFile, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n",
                appt.hname, appt.age, appt.gender, appt.phone, appt.dname, appt.date, appt.time, appt.reason, appt.payment, appt.isCompleted);
    }
    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("appointment.txt");
        rename("temp.txt", "appointment.txt");
    } else {
        printf("|No appointment found for the name %s.", searchName);
        remove("temp.txt");
    }
    clear();
}
void cancelAppointment() {
    FILE *file = fopen("appointment.txt", "r+");

    printf("\n|Enter the patient's full name to cancel the appointment: ");
    char searchName[100];
    getchar();
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    FILE *tempFile = fopen("temp.txt", "w");
    int found = 0;
    while (fscanf(file, "%99[^\n]\n%4[^\n]\n%9[^\n]\n%14[^\n]\n%99[^\n]\n%14[^\n]\n%9[^\n]\n%99[^\n]\n%19[^\n]\n%d\n",
                  appt.hname, appt.age, appt.gender, appt.phone, appt.dname, appt.date, appt.time, appt.reason, appt.payment, &appt.isCompleted) != EOF) {
        if (strcmp(appt.hname, searchName) == 0) {
            found = 1;
            appt.isCompleted = -1;
            printf("|Appointment for %s canceled.\n", appt.hname);
        }
        fprintf(tempFile, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n",
                appt.hname, appt.age, appt.gender, appt.phone, appt.dname, appt.date, appt.time, appt.reason, appt.payment, appt.isCompleted);
    }
    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("appointment.txt");
        rename("temp.txt", "appointment.txt");
    } else {
        printf("|No appointment found for the name %s.", searchName);
        remove("temp.txt");
    }
    clear();
}
void displayAppointment() {
    FILE *file = fopen("appointment.txt", "r");
    printf("\n\t\t\t ------------------  Appointments Forum  ------------------\n\n");

    while (fscanf(file, "%99[^\n]\n%4[^\n]\n%9[^\n]\n%14[^\n]\n%99[^\n]\n%14[^\n]\n%9[^\n]\n%99[^\n]\n%19[^\n]\n%d\n",
                  appt.hname, appt.age, appt.gender, appt.phone, appt.dname, appt.date, appt.time, appt.reason, appt.payment, &appt.isCompleted) != EOF) {
        printf("\t\t           ___________________Patient Information___________________\n\n");
        printf("|Full Name: %s\n", appt.hname);
        printf("|Age: %s\n", appt.age);
        printf("|Gender: %s\n", appt.gender);
        printf("|Phone Number: %s\n", appt.phone);

        printf("\n\t\t          ___________________Appointment Details___________________\n\n");
        printf("|Doctor Name: %s\n", appt.dname);
        printf("|Date: %s\n", appt.date);
        printf("|Time: %s\n", appt.time);
        printf("|Reason: %s\n", appt.reason);

        printf("\n\t\t          ___________________Payment Method___________________\n\n");
        printf("|Payment Method: %s\n", appt.payment);

        if (appt.isCompleted == 1) {
            printf("|Status: Completed");
        } else if (appt.isCompleted == -1) {
            printf("|Status: Canceled");
        } else {
            printf("|Status: Pending");
        }
    }
    fclose(file);
    clear();
}
void addNote() {
    FILE *file = fopen("note.txt", "a");
    printf("\n\t\t\t ------------------  Note Adding Screen  ------------------\n\n");

    char note[1000];
    printf("|Write your note: \n");
    fgets(note, sizeof(note), stdin);

    fprintf(file, "%s\n", note);
    fclose(file);

    printf("|Note saved successfully!!");
    clear();
}
void viewNotes() {
    FILE *file = fopen("note.txt", "r");
     printf("\n\t\t\t ------------------  Note Viewer Screen  ------------------\n\n");
    char note[1000];
    printf("|Your Notes:\n");
    while (fgets(note, sizeof(note), file)) {
        printf("%s", note);
    }
    fclose(file);
    clear();
}
void addInfo() {
    printf("\n\t\t\t ------------------  Emergency Information Add Screen  ------------------\n\n");
    printf("|Full Name: ");
    fgets(emergency.fname, sizeof(emergency.fname), stdin);
    emergency.fname[strcspn(emergency.fname, "\n")] = '\0';

    printf("|Home Address: ");
    fgets(emergency.address, sizeof(emergency.address), stdin);
    emergency.address[strcspn(emergency.address, "\n")] = '\0';


    printf("|Phone Number: ");
    fgets(emergency.sos, sizeof(emergency.sos), stdin);
    emergency.sos[strcspn(emergency.sos, "\n")] = '\0';


    FILE *file = fopen("emergancy.txt", "a");
    fprintf(file, "%s %s %s\n",emergency.fname,emergency.address, emergency.sos );
    fclose(file);

    printf("\nConfirm details? (y/n): ");
    char choice;
    scanf(" %c", &choice);
    getchar();
    if (choice != 'y' && choice != 'Y') {
    printf("|Information not saved.");
    clear();
    return;
    }else{
    printf("\nInformation added successfully!!");
    clear();
    }
}
void displayEmergency() {
    FILE *file = fopen("emergancy.txt", "r");
    printf("\n\t\t\t ------------------  Emergency Information Screen  ------------------\n\n");

    while (fscanf(file, "%s %s %s", emergency.fname, emergency.address, emergency.sos) != EOF) {
        printf("\t\t           ___________________Patient Information___________________\n\n");
        printf("|Full Name: %s\n", emergency.fname);
        printf("|Home Address: %s\n", emergency.address);
        printf("|Phone Number: %s\n", emergency.sos);
    }
    fclose(file);
    clear();
}
void saveToFile() {
    FILE *file = fopen("medicine.txt", "w");
    fprintf(file, "%d\n", medicineCount);
    for (int i = 0; i < medicineCount; i++) {
        fprintf(file, "%s,%s,%s,%s,%d,%d,%d\n",medicines[i].name,medicines[i].dosage,medicines[i].frequency,medicines[i].startDate, medicines[i].duration, medicines[i].daysLeft,medicines[i].taken);
    }
    fclose(file);
    printf("Data saved successfully to file!!");
    clear();
}
void addMedicine() {
    printf("\n\t\t\t ------------------  Medicine Adding  ------------------\n\n");
    if (medicineCount >= MAX_MEDICINES) {
        printf("|Medicine chart is full!\n");
        return;
    }
    printf("|Enter Medicine Name: ");
    scanf(" %[^\n]", medicines[medicineCount].name);
    printf("|Enter Dosage (e.g., 1 tablet): ");
    scanf(" %[^\n]", medicines[medicineCount].dosage);
    printf("|Enter Frequency (e.g., Morning, Night): ");
    scanf(" %[^\n]", medicines[medicineCount].frequency);
    printf("|Enter Start Date (DD-MM-YYYY): ");
    scanf(" %[^\n]", medicines[medicineCount].startDate);
    printf("|Enter Duration (in days): ");
    scanf("%d", &medicines[medicineCount].duration);

    medicines[medicineCount].daysLeft = medicines[medicineCount].duration;
    medicines[medicineCount].taken = 0;

    medicineCount++;
    saveToFile();
    printf("|Medicine added successfully!!!");
    clear();
}
void showChart() {
    printf("\n\t\t\t ------------------  Medicine Chart  ------------------\n\n");

    FILE *file = fopen("medicine", "r");
    int count;
    fscanf(file, "%d\n", &count);

    printf("\n--- Medicine Chart ---\n");
    printf("| %-20s | %-10s | %-15s | %-10s | %-8s | %-10s |\n",
           "Name", "Dosage", "Frequency", "Start Date", "Days Left", "Taken?");
    printf("---------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        struct medicine med;
        fscanf(file, " %[^,],%[^,],%[^,],%[^,],%d,%d,%d\n",
               med.name,
               med.dosage,
               med.frequency,
               med.startDate,
               &med.duration,
               &med.daysLeft,
               &med.taken);

        printf("| %-20s | %-10s | %-15s | %-10s | %-8d | %-10s |\n",
               med.name,
               med.dosage,
               med.frequency,
               med.startDate,
               med.daysLeft,
               med.taken ? "Yes" : "No");
    }
    printf("---------------------------------------------------------------------------------\n");

    fclose(file);
    clear();
}
void markAsTaken() {
        printf("\n\t\t\t ------------------  Medicine Mark Screen  ------------------\n\n");

    char name[50];
    printf("|Enter the name of the medicine to mark as taken: ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < medicineCount; i++) {
        if (strcmp(medicines[i].name, name) == 0) {
            if (medicines[i].daysLeft > 0 && !medicines[i].taken) {
                medicines[i].taken = 1;
                medicines[i].daysLeft--;
                saveToFile();
                printf("|Marked '%s' as taken. Days left: %d\n", medicines[i].name, medicines[i].daysLeft);
            } else if (medicines[i].daysLeft == 0) {
                printf("|'%s' has no remaining doses.\n", medicines[i].name);
            } else {
                printf("|'%s' is already marked as taken today.\n", medicines[i].name);
            }
            clear();
            return;
        }
    }
    printf("|Medicine not found!!");
            clear();
}
void Medicinemenu() {
    int choice;
    do {
        MedicineTitle();
        printf("|Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        system("cls");
        switch (choice) {
            case 1:
                addMedicine();
                break;
            case 2:
                showChart();
                break;
            case 3:
                markAsTaken();
                break;
            case 4:
                MedicineTitle();
                printf("|Exiting program. Stay healthy!");
                clear();
                break;
            default:
                MedicineTitle();
                printf("|Invalid choice! Please try again.");
                clear();
        }
    } while (choice != 4);
}
void userMenu() {
    int choice;
    while (1) {
        userTitle();
        printf("|Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        system("cls");

        switch (choice) {
            case 1:
                appointmentMenu();
                break;

            case 2:
                noteMenu();
                break;

            case 3:
                Medicinemenu();
                break;

            case 4:
                emergencyMenu();
                break;

            case 5:
                userTitle();
                printf("|Log Out from the program. Goodbye!");
                clear();
                return main();
                break;

            default:
                userTitle();
                printf("|Invalid choice. Try again.");
                clear();
                break;
} } }
void emergencyMenu() {
    while (1) {
        emergencyTitle();
        printf("|Choose an option: ");
        int choice;
        scanf("%d", &choice);
        getchar();
        system("cls");
        switch (choice) {
            case 1:
                addInfo();
                break;
            case 2:
                displayEmergency();
                break;
            case 3:
                emergencyTitle();
                clear();
                return;
            default:
                emergencyTitle();
                printf("|Invalid option. Try again.");
                clear();
        }
    }
}
void appointmentMenu() {
    int choice;
    do {
        appointmentTitle();
        printf("|Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        system("cls");

        switch (choice) {
            case 1:
                addAppointment();
                break;
            case 2:
                displayAppointment();
                break;
            case 3:
                markAppointment();
                break;
            case 4:
                cancelAppointment();
                break;
            case 5:
                appointmentTitle();
                printf("|Returning to Main Menu...");
                clear();
                break;
            default:
                appointmentTitle();
                printf("|Invalid choice. Try again.");
                clear();
                break;
        }
    } while (choice != 5);
}
void noteMenu() {
    int choice;
    do {
        noteTitle();
        printf("|Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        system("cls");
        switch (choice) {
            case 1:
                addNote();
                break;
            case 2:
                viewNotes();
                break;
            case 3:
                noteTitle();
                printf("|Returning to Main Menu...");
                clear();
                break;
            default:
                noteTitle();
                printf("|Invalid choice. Try again.");
                clear();
                break;
        }
    } while (choice != 3);
}
int main() {
    int log_in = 0;
    int isLoggedIn = 0;

    while (!isLoggedIn) {
        showTitle();
        int choice;
        scanf("%d", &choice);
        getchar();
        system("cls");
        switch (choice) {
            case 2:
                system("cls");
                showRegister();
                break;

            case 1:
                system("cls");
                log_in = showLogin();
                if (log_in == 1) {
                    isLoggedIn = 1;
                    userMenu();
                } else {
                    printf("|Invalid!!!\n|Please enter the correct username and password or sign up first.\n");
                    clear();
                }
                break;

            case 3:
                showTitle();
                printf("\nExiting program...\n");
                exit(0);
                break;

            default:
                showTitle();
                printf("|Invalid option. Please try again.");
                clear();
                break;
        }
    }

    return 0;
}
