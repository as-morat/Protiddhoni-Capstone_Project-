#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_MEDICINES 100
struct appointment {
    char hname[100];
    char searchName[100];
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
    char dosage[20];
    char frequency[20];
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
    printf("| Press Enter to continue...");
    getchar();
    system("cls");
}
void showTitle() {
    printf("\n\t\t\t -------------------------- \n");
    printf("\t\t\t|       PROTIDDHONI        |\n");
    printf("\t\t\t -------------------------- \n\n");
    printf("| 1. Log in\n| 2. Sign up\n| 3. Exit\n");
    printf("| Choose an option: ");

}
void appointmentTitle(){printf("\n\t\t\t ------------------  Appointment Menu  ------------------\n\n");
        printf("| 1. Add Appointment\n| 2. View Appointment\n| 3. Mark as Completed\n| 4. Cancel Appointment\n| 5. Back\n");}
void noteTitle(){printf("\n\t\t\t ------------------  Note Menu  ------------------\n\n");
        printf("| 1. Add Note\n| 2. View Notes\n| 3. Back\n");}
void emergencyTitle(){printf("\n\t\t\t ------------------  Emergency Menu  ------------------\n\n");
        printf("| Welcome! Let me know how I can assist you...\n");
        printf("| 1. Add Emergency Information\n| 2. View Emergency Information\n| 3. Back\n");}
void userTitle(){printf("\n\t\t\t ------------------  Main Menu  ------------------\n\n");
        printf("| Welcome, Sir...\n");
        printf("| 1. Appointment\n| 2. Note\n| 3. Medicine\n| 4. Emergency\n| 5. Log out\n");}
void MedicineTitle(){printf("\n\t\t\t ------------------  Medicine Menu  ------------------\n\n");
        printf("| 1. Add Medicine\n| 2. Show Medicine Chart\n | 3. Mark Medicine as Taken\n| 4. Exit\n");}
void showRegister() {
    printf("\n\t\t\t--- Sign Up Screen ---\n\n");
    struct User newUser;
    FILE *fptr = fopen("login.txt", "a");

    printf("| Enter your full name: ");
    fgets(newUser.fname, sizeof(newUser.fname), stdin);
    newUser.fname[strlen(newUser.fname) - 1] = '\0';

    while (1) {
        printf("| Enter your email address: ");
        fgets(newUser.email, sizeof(newUser.email), stdin);
        newUser.email[strlen(newUser.email) - 1] = '\0';
        if (isValidEmail(newUser.email)) {
            break;
        } else {
            printf("\033[1;31m| Invalid email format. Please try again.\n\033[0m");

        }
    }
    int i = 0;
    int maxLength = 8;
    while (newUser.email[i] != '@' && newUser.email[i] != '\0' && i < maxLength) {
        newUser.user_name[i] = newUser.email[i];
        i++;
    }
    newUser.user_name[i] = '\0';
    printf("| Your user name: %s\n", newUser.user_name);

    printf("| Enter password: ");
    fgets(newUser.password, sizeof(newUser.password), stdin);
    newUser.password[strlen(newUser.password) - 1] = '\0';

    fprintf(fptr, "%s %s %s %s\n", newUser.user_name, newUser.password, newUser.fname, newUser.email);
    fclose(fptr);
    printf("| Sign up successful !!");
    clear();
}
int isValidEmail(const char *email) {
    const char *at = strchr(email, '@');
    const char *dot = strrchr(email, '.');
    if (at && dot && at < dot) {
        if (at != email && *(dot + 1) != '\0' && !strchr(email, ' ')) {
            return 1;
        }
    }
    return 0;
}

int showLogin() {
    printf("\n\t\t\t--- Login Screen ---\n\n");
    struct User inputUser, storedUser;
    FILE *fptr = fopen("login.txt", "r");

    printf("| Enter user name: ");
    fgets(inputUser.user_name, sizeof(inputUser.user_name), stdin);
    inputUser.user_name[strlen(inputUser.user_name) - 1] = '\0';

    printf("| Enter password: ");
    fgets(inputUser.password, sizeof(inputUser.password), stdin);
    inputUser.password[strlen(inputUser.password) - 1] = '\0';

    while (fscanf(fptr, "%s %s %*s %*s", storedUser.user_name, storedUser.password) == 2) {
        if (strcmp(inputUser.user_name, storedUser.user_name) == 0 &&
            strcmp(inputUser.password, storedUser.password) == 0) {
            fclose(fptr);
            printf("| Log in successful !!");
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
    printf("| Full Name: ");
    fgets(appt.hname, sizeof(appt.hname), stdin);
    appt.hname[strcspn(appt.hname, "\n")] = '\0';

    printf("| Age: ");
    fgets(appt.age, sizeof(appt.age), stdin);
    appt.age[strcspn(appt.age, "\n")] = '\0';

    printf("| Gender: ");
    printf("\n| 1. Male\n| 2. Female ");
    int gender_choice;
    printf("\n| Enter your choice (1 or 2): ");
    scanf("%d", &gender_choice);
    getchar();
    strcpy(appt.gender, (gender_choice == 1) ? "Male" : "Female");

    printf("| Phone Number: ");
    fgets(appt.phone, sizeof(appt.phone), stdin);
    appt.phone[strcspn(appt.phone, "\n")] = '\0';

    printf("\n\t\t          ___________________Appointment Details___________________\n\n");
    printf("| Doctor Name(Neurologist): ");
    fgets(appt.dname, sizeof(appt.dname), stdin);
    appt.dname[strcspn(appt.dname, "\n")] = '\0';

    printf("| Preferred Date (date - month - year): ");
    fgets(appt.date, sizeof(appt.date), stdin);
    appt.date[strcspn(appt.date, "\n")] = '\0';

    printf("| Preferred Time (hour : minutes  am/pm): ");
    fgets(appt.time, sizeof(appt.time), stdin);
    appt.time[strcspn(appt.time, "\n")] = '\0';

    printf("| Reason for Checkup: ");
    fgets(appt.reason, sizeof(appt.reason), stdin);
    appt.reason[strcspn(appt.reason, "\n")] = '\0';

    printf("\n\t\t          ___________________Payment Method___________________\n\n");
    printf("| Payment Method (e.g., Cash, Card, Insurance): ");
    fgets(appt.payment, sizeof(appt.payment), stdin);
    appt.payment[strcspn(appt.payment, "\n")] = '\0';

    appt.isCompleted = 0;

    FILE *file = fopen("appointment.txt", "a");
    fprintf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n", appt.hname, appt.age, appt.gender, appt.phone, appt.dname, appt.date, appt.time, appt.reason, appt.payment, appt.isCompleted);
    fclose(file);

    printf("\n| Confirm appointment details? (y/n): ");
    char choice;
    scanf(" %c", &choice);
    getchar();
    if (choice != 'y' && choice != 'Y') {
        printf("\033[1;31m| Appointment not saved.\033[0m");
        clear();
        return;
    } else {
        printf("\n| Appointment registration successfully!!");
        clear();
    }
}
void updateAppointmentStatus(char statusMessage[], int statusValue) {
    FILE *file = fopen("appointment.txt", "r");
    printf("\n\t\t\t ------------------  Status Updating Screen  ------------------\n\n");
    char searchName[100];
    printf("\n| Enter the patient's full name to %s: ", statusMessage);
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    struct appointment appointments[100];
    int appointmentCount = readAppointmentsFromFile(file, appointments, searchName);
    fclose(file);

    if (appointmentCount == 0) {
        printf("\033[1;31m| No appointments found for %s.\033[0m", searchName);
        clear();
        return;
    }
    displayAppointmentsList(appointments, appointmentCount);
    int choice;
    printf("\n| Select the appointment number to %s: ", statusMessage);
    scanf("%d", &choice);
    getchar();

    if (choice < 1 || choice > appointmentCount) {
        printf("\033[1;31m| Invalid choice. Operation canceled.\033[0m");
        clear();
        return;
    }
    int selectedAppointment = choice - 1;
    appointments[selectedAppointment].isCompleted = statusValue;
    printf("-----------------------------------------------\n\n|Appointment with Doctor %s on %s at %s has been %s.\n",
           appointments[selectedAppointment].dname, appointments[selectedAppointment].date,
           appointments[selectedAppointment].time, statusMessage);
    file = fopen("appointment.txt", "w");
    for (int i = 0; i < appointmentCount; i++) {
        fprintf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n",
                appointments[i].hname, appointments[i].age, appointments[i].gender, appointments[i].phone, appointments[i].dname,
                appointments[i].date, appointments[i].time, appointments[i].reason, appointments[i].payment, appointments[i].isCompleted);
    }
    fclose(file);
    printf("| File updated successfully!!");
    clear();
}
void markAppointment() {
    updateAppointmentStatus("mark as completed", 1);
}
void cancelAppointment() {
    updateAppointmentStatus("cancel the appointment", -1);
}
int readAppointmentsFromFile(FILE *file, struct appointment appointments[], char searchName[100]) {
    int appointmentCount = 0;
    while (fscanf(file, "%99[^\n]\n%4[^\n]\n%9[^\n]\n%14[^\n]\n%99[^\n]\n%14[^\n]\n%9[^\n]\n%99[^\n]\n%19[^\n]\n%d\n",
                  appointments[appointmentCount].hname, appointments[appointmentCount].age, appointments[appointmentCount].gender,
                  appointments[appointmentCount].phone, appointments[appointmentCount].dname, appointments[appointmentCount].date,
                  appointments[appointmentCount].time, appointments[appointmentCount].reason, appointments[appointmentCount].payment,
                  &appointments[appointmentCount].isCompleted) != EOF) {
        if (strcmp(appointments[appointmentCount].hname, searchName) == 0) {
            appointmentCount++;
        }
    }
    return appointmentCount;
}
void displayAppointmentsList(struct appointment appointments[], int appointmentCount) {
    printf("\n| Found %d appointment(s):\n", appointmentCount);
    for (int i = 0; i < appointmentCount; i++) {
        printf("\n| Appointment %d:\n", i + 1);
        printf("| Date: %s, Time: %s, Doctor: %s, Reason: %s\n", appointments[i].date, appointments[i].time, appointments[i].dname, appointments[i].reason);
        printf("------------------------------------------------------------------------------------------\n");
    }
}
void displayAppointment() {
    FILE *file = fopen("appointment.txt", "r");
    printf("\n\t\t\t ------------------  Appointment Viewing Screen  ------------------\n\n");
    char patientName[100];
    printf("| Enter the patient's full name to view appointments: ");
    fgets(patientName, sizeof(patientName), stdin);
    patientName[strcspn(patientName, "\n")] = '\0';

    struct appointment appointments[100];
    int appointmentCount = readAppointmentsFromFile(file, appointments, patientName);
    fclose(file);
    if (appointmentCount == 0) {
        printf("\033[1;31m| No appointments found for patient: %s\033[0m", patientName);
        clear();
        return;
    }
    displayAppointmentsList(appointments, appointmentCount);
    int choice;
    printf("\n| Enter the number of the appointment to view details: ", appointmentCount);
    scanf("%d", &choice);
    getchar();
    system("cls");
    if (choice < 1 || choice > appointmentCount) {
        printf("\033[1;31m| Invalid choice.\033[0m");
        clear();
        return;
    }

    struct appointment selected = appointments[choice - 1];
    printf("\n\t\t           ___________________Patient Information___________________\n\n");
    printf("| Full Name: %s\n", selected.hname);
    printf("| Age: %s\n", selected.age);
    printf("| Gender: %s\n", selected.gender);
    printf("| Phone Number: %s\n", selected.phone);

    printf("\n\t\t          ___________________Appointment Details___________________\n\n");
    printf("| Doctor Name: %s\n", selected.dname);
    printf("| Date: %s\n", selected.date);
    printf("| Time: %s\n", selected.time);
    printf("| Reason: %s\n", selected.reason);

    printf("\n\t\t          ___________________Payment Method___________________\n\n");
    printf("| Payment Method: %s\n", selected.payment);

    if (selected.isCompleted == 1) {
        printf("| Status: Completed");
    } else if (selected.isCompleted == -1) {
        printf("| Status: Canceled");
    } else {
        printf("| Status: Pending");
    }
    clear();
}
void addNote() {
    FILE *file = fopen("note.txt", "a");
    printf("\n\t\t\t ------------------  Note Adding Screen  ------------------\n\n");

    char note[1000];
    printf("| Write your note: \n|");
    fgets(note, sizeof(note), stdin);

    fprintf(file, "%s\n", note);
    fclose(file);

    printf("| Note saved successfully!!");
    clear();
}
void viewNotes() {
    FILE *file = fopen("note.txt", "r");
     printf("\n\t\t\t ------------------  Note Viewer Screen  ------------------\n\n");
    char note[1000];
    printf("| Your Notes:\n");
    while (fgets(note, sizeof(note), file)) {
        printf("| %s", note);
    }
    fclose(file);
    clear();
}
void addInfo() {
    printf("\n\t\t\t ------------------  Emergency Information Add Screen  ------------------\n\n");
    printf("| Full Name: ");
    fgets(emergency.fname, sizeof(emergency.fname), stdin);
    emergency.fname[strcspn(emergency.fname, "\n")] = '\0';

    printf("| Home Address: ");
    fgets(emergency.address, sizeof(emergency.address), stdin);
    emergency.address[strcspn(emergency.address, "\n")] = '\0';


    printf("| Phone Number: ");
    fgets(emergency.sos, sizeof(emergency.sos), stdin);
    emergency.sos[strcspn(emergency.sos, "\n")] = '\0';


    FILE *file = fopen("emergancy.txt", "a");
    fprintf(file, "%s %s %s\n",emergency.fname,emergency.address, emergency.sos );
    fclose(file);

    printf("\n| Confirm details? (y/n): ");
    char choice;
    scanf(" %c", &choice);
    getchar();
    if (choice != 'y' && choice != 'Y') {
    printf("\033[1;31m| Information not saved.\033[0m");
    clear();
    return;
    }else{
    printf("\n| Information added successfully!!");
    clear();
    }
}
void displayEmergency() {
    FILE *file = fopen("emergancy.txt", "r");
    printf("\n\t\t\t ------------------  Emergency Information Screen  ------------------\n\n");

    while (fscanf(file, "%s %s %s", emergency.fname, emergency.address, emergency.sos) != EOF) {
        printf("\t\t           ___________________Patient Information___________________\n\n");
        printf("| Full Name: %s\n", emergency.fname);
        printf("| Home Address: %s\n", emergency.address);
        printf("| Phone Number: %s\n", emergency.sos);
    }
    fclose(file);
    clear();
}
void saveToFile() {
    FILE *file = fopen("medicine.txt", "w");
    fprintf(file, "%d\n", medicineCount);
    for (int i = 0; i < medicineCount; i++) {
        fprintf(file, "%s,%s,%s,%s,%d,%d,%d\n",medicines[i].name,medicines[i].dosage,medicines[i].frequency,medicines[i].startDate,medicines[i].duration,medicines[i].daysLeft,medicines[i].taken);
    }
    fclose(file);
}

void addMedicine() {
    printf("\n\t\t\t ------------------  Add Medicine  ------------------\n\n");
    if (medicineCount >= MAX_MEDICINES) {
        printf("\033[1;31m| Medicine chart is full!\033[0m\n");clear();
        return;
    }

    printf("| Enter Medicine Name: ");
    scanf(" %[^\n]", medicines[medicineCount].name);

    printf("| Enter Dosage (e.g., 1 tablet): ");
    scanf(" %[^\n]", medicines[medicineCount].dosage);

    printf("| Enter Frequency (e.g., Morning, Night): ");
    scanf(" %[^\n]", medicines[medicineCount].frequency);

    printf("| Enter Start Date (DD-MM-YYYY): ");
    scanf(" %[^\n]", medicines[medicineCount].startDate);

    printf("| Enter Duration (in days): ");
    if (scanf("%d", &medicines[medicineCount].duration) != 1 || medicines[medicineCount].duration <= 0) {
        printf("\033[1;31m| Invalid duration! Please enter a positive number.\033[0m\n");
        return;clear();
    }
    medicines[medicineCount].daysLeft = medicines[medicineCount].duration;
    medicines[medicineCount].taken = 0;
    medicineCount++;
    saveToFile();
    printf("| Medicine added successfully!\n");clear();
}

void showChart() {
    printf("\n\t\t\t ------------------  Medicine Chart  ------------------\n\n");
    FILE *file = fopen("medicine.txt", "r");
    int count;
    if (fscanf(file, "%d\n", &count) != 1) {
        printf("\033[1;31m-----------------------|------------|-----------------|------------|-----------|------------|\n| Error: Invalid.\033[0m");
        fclose(file);clear();
        return;
    }

    printf("\n| %-20s | %-10s | %-15s | %-10s | %-8s | %-10s |\n",
           "Name", "Dosage", "Frequency", "Start Date", "Days Left", "Taken?");
    printf("---------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        struct medicine med;
        if (fscanf(file, " %[^,],%[^,],%[^,],%[^,],%d,%d,%d\n",med.name,med.dosage,med.frequency,med.startDate,&med.duration,&med.daysLeft,&med.taken) == 7) {
            printf("| %-20s | %-10s | %-15s | %-10s | %-8d | %-10s |\n", med.name,med.dosage,med.frequency,med.startDate,med.daysLeft,med.taken ? "Yes" : "No");
        } else {
            printf("\033[1;31m-----------------------|------------|-----------------|------------|-----------|------------|\n| Sorry!! There is no medicine info in file.\033[0m");
            fclose(file);clear();
            return;
        }
    }
    printf("---------------------------------------------------------------------------------------------\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
    fclose(file);clear();
}

void markAsTaken() {
    printf("\n\t\t\t ------------------  Mark Medicine as Taken  ------------------\n\n");

    char name[50];
    printf("| Enter the name of the medicine to mark as taken: ");
    scanf(" %[^\n]", name);getchar();

    for (int i = 0; i < medicineCount; i++) {
        if (strcmp(medicines[i].name, name) == 0) {
            if (medicines[i].daysLeft > 0 && !medicines[i].taken) {
                medicines[i].taken = 1;
                medicines[i].daysLeft--;
                saveToFile();
                printf("| Marked '%s' as taken. Days left: %d\n", medicines[i].name, medicines[i].daysLeft);
            } else if (medicines[i].daysLeft == 0) {
                printf("| '%s' has no remaining doses.\n", medicines[i].name);
            } else {
                printf("| '%s' is already marked as taken today.\n", medicines[i].name);
            }clear();
            return;
        }
    }
    printf("\033[1;31m| Medicine not found!\033[0m\n");clear();
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
                printf("| Exiting program. Stay healthy!");
                clear();
                break;
            default:
                MedicineTitle();
                printf("\033[1;31m| Invalid choice! Please try again.\033[0m");
                clear();
        }
    } while (choice != 4);
}
void userMenu() {
    int choice;
    while (1) {
        userTitle();
        printf("| Enter your choice: ");
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
                printf("| Log Out from the program. Goodbye!");
                clear();
                return main();
                break;

            default:
                userTitle();
                printf("\033[1;31m| Invalid choice. Try again.\033[0m");
                clear();
                break;
} } }
void emergencyMenu() {
    while (1) {
        emergencyTitle();
        printf("| Choose an option: ");
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
                printf("\033[1;31m| Invalid option. Try again.\033[0m");
                clear();
        }
    }
}
void appointmentMenu() {
    int choice;
    do {
        appointmentTitle();
        printf("| Enter your choice: ");
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
                printf("| Returning to Main Menu...");
                clear();
                break;
            default:
                appointmentTitle();
                printf("\033[1;31m| Invalid choice. Try again.\033[0m");
                clear();
                break;
        }
    } while (choice != 5);
}
void noteMenu() {
    int choice;
    do {
        noteTitle();
        printf("| Enter your choice: ");
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
                printf("| Returning to Main Menu...");
                clear();
                break;
            default:
                noteTitle();
                printf("\033[1;31m| Invalid choice. Try again.\033[0m");
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
                    printf("\033[1;31m| Invalid!!!\n| Please enter the correct username and password or sign up first.\033[0m\n");
                    clear();
                }
                break;

            case 3:
                showTitle();
                printf("\n\033[1;31m| Exiting program...\033[0m\n");
                exit(0);
                break;

            default:
                showTitle();
                printf("\033[1;31m| Invalid option. Please try again.\033[0m");
                clear();
                break;
        }
    }

    return 0;
}
