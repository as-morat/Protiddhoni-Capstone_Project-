#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include<windows.h>
#include <time.h>
#define MAX_MEDICINES 100
int medicineCount = 0;
char searchDate[15];

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
}appt;
struct User {
    char fname[50];
    char email[100];
    char user_name[50];
    char password[50];
}User,currentUser;
struct Emergency {
    char address[50];
    char sos[20];
    char fname[50];
}emergency;
struct medicine {
    char name[50];
    char dosage[20];
    char frequency[20];
    char mealTime[50];
    char startDate[15];
    int duration;
    int daysLeft;
    int taken;
}medicines[MAX_MEDICINES];
struct NoteData{
    char note[1000];
    char date[15];
} data,notesOnDate[100],temp;

void clear(){
     printf("\n------------------------------\n");
    printf(YELLOW"| Press Enter to continue..."RESET);
    getchar();
    system("cls");
}

void showTitle(char title[]) {
    int len = strlen(title);
    int padding = (26 - len) / 2;
    int i;
    printf(GREEN"\n\t\t\t\t\t -------------------------- \n");
    printf("\t\t\t\t\t|"RESET);
    for (i = 0; i < padding; i++) printf(" ");
    printf(CYAN"%s"RESET, title);
    for (i = 0; i < (26 - len - padding); i++) printf(" ");
    printf(GREEN"|\n");
    printf("\t\t\t\t\t -------------------------- \n\n"RESET);
}
void introTitle() {
    showTitle("PROTIDDHONI_2.0");
    printf(MAGENTA "|\t\t\t 1. Log In\n|\t\t\t 2. Sign Up\n|\t\t\t 3. Exit\n" RESET);
}
void appointmentTitle() {
    showTitle("Appointment Menu");
    printf(MAGENTA"|\t\t\t 1. Add Appointment\n|\t\t\t 2. View Appointment\n|\t\t\t 3. Mark as Completed\n|\t\t\t 4. Cancel Appointment\n|\t\t\t 5. Back\n\n"RESET);
}
void noteTitle() {
    showTitle("Note Menu");
    printf(MAGENTA"|\t\t\t 1. Add Note\n|\t\t\t 2. View Notes\n|\t\t\t 3. Delete Note by Date\n|\t\t\t 4. Back\n\n"RESET);
}
void emergencyTitle() {
    showTitle("Emergency Menu");
    printf(GREEN"| Welcome Sir! Let me know how I can assist you? \n\n"RESET);
    printf(MAGENTA"|\t\t\t 1. Add Emergency Information\n|\t\t\t 2. View Emergency Information\n|\t\t\t 3. Back\n\n"RESET);
}
void userTitle() {
    showTitle("Main Menu");
    printf(GREEN"| Welcome, Sir...\n\n"RESET);
    printf(MAGENTA"|\t\t\t 1. Appointment\n|\t\t\t 2. Note\n|\t\t\t 3. Medicine\n|\t\t\t 4. Emergency\n|\t\t\t 5. Log out\n\n"RESET);
}
void MedicineTitle() {
    showTitle("Medicine Menu");
    printf(MAGENTA"|\t\t\t 1. Add Medicine\n|\t\t\t 2. Show Medicine Chart\n|\t\t\t 3. Mark Medicine as Taken\n|\t\t\t 4. Exit\n\n"RESET);
}

int isValidEmail(char email[]) {
    char *at = strchr(email, '@');
    char *dot = strrchr(email, '.');
    if (at && dot && at < dot) {
        if (at != email && *(dot + 1) != '\0' && !strchr(email, ' ')) {
            return 1;
        }
    }
    return 0;
}
int isEmailExists(char email[]) {
    FILE *fptr = fopen("login.txt", "r");
    char existingUsername[50], existingPassword[50], existingFname[50], existingEmail[50];

    while (fscanf(fptr, "%s %s %s %s", existingUsername, existingPassword, existingFname, existingEmail) == 4) {
        if (strcmp(existingEmail, email) == 0) {
            fclose(fptr);
            return 1;
        }
    }
    fclose(fptr);
    return 0;
}
void generateVerificationCode(char code[]) {
    srand(time(0));
    for (int i = 0; i < 4; i++) {
        code[i] = '0' + rand() % 10;
    }
    code[4] = '\0';
}
void getPassword(char *password, int maxLength) {
    int i = 0;
    int showPassword = 0;  // 0 for hidden, 1 for visible
    char ch;
    while (1) {
        ch = getch();   // Enter key (finish input)
        if (ch == '\r') {
            password[i] = '\0';  // Null-terminate the password
            break;
        }
        else if (ch == '\b') { // Backspace key (delete character)
            if (i > 0) {
                i--;
                printf("\b \b");  // Move cursor back and overwrite with space
            }
        }
        else if (ch == 'v' || ch == 'V') {        // Toggle password visibility with 'v' key
            showPassword = !showPassword;  // Toggle visibility
        }
        else if (i < maxLength - 1) {  // Valid character input
            password[i++] = ch;

            if (showPassword) {
                printf("%c", ch);  // Show password character if visibility is enabled
            } else {
                printf(RED"*"RESET);  // Hide password character with asterisk
            }
        }
    }
    printf("\n");
}
void showRegister() {
    showTitle("Sign Up");
    struct User newUser;
    FILE *fptr = fopen("login.txt", "a");
    char newUserPassword[50], confirmPassword[50], verificationCode[5], userCode[5];

    printf(BLUE"| Enter your full name: "RESET);
    fgets(newUser.fname, sizeof(newUser.fname), stdin);
    newUser.fname[strlen(newUser.fname) - 1] = '\0';

    while (1) {
        printf(BLUE"| Enter your email address: "RESET);
        fgets(newUser.email, sizeof(newUser.email), stdin);
        newUser.email[strlen(newUser.email) - 1] = '\0';

        if (!isValidEmail(newUser.email)) {
            printf(RED"\n| Invalid email format. Please try again.\n"RESET);
            continue;
        }
        if (isEmailExists(newUser.email)) {
            printf(RED"\n| Email already registered. Please use another email.\n"RESET);
            continue;
        }
        break;
    }

    generateVerificationCode(verificationCode);
    printf("..........................................................\n\n"MAGENTA"| Verification code sending...\n"RESET);
    printf(BLUE"| Verification code sent: "RESET);
    Sleep(2000);
    printf(GREEN"%s\n"RESET, verificationCode);
    clear();
    showTitle("Sign Up");

    printf(BLUE "| Enter the verification code: " RESET);
    fgets(userCode, sizeof(userCode), stdin);
    getchar();
    if (
        userCode[strlen(userCode) - 1] == '\n') {
        userCode[strlen(userCode) - 1] = '\0';
    }
    if (
        strcmp(verificationCode, userCode) != 0) {
                printf(RED "\n| Verification failed. Please try again.\n" RESET);
                fclose(fptr);
                clear();
                return;
    }
    printf(GREEN "\n| Verification successful! Proceeding to the next step..." RESET);
    clear();
    showTitle("Sign Up");
    int i = 0, maxLength = 8;
    while (newUser.email[i] != '@' && newUser.email[i] != '\0' && i < maxLength) {
        newUser.user_name[i] = newUser.email[i];
        i++;
    }
    newUser.user_name[i] = '\0';
    printf(MAGENTA "| User name creating....\n" RESET);
    printf(BLUE "| Your user name: " RESET );
    Sleep(2000);
    printf(GREEN "%s\n" RESET, newUser.user_name);
    clear();
    showTitle("Sign Up");

    printf(GREEN"| To visible password press [V] or [v]....\n\n"RESET);
    while (1) {
        printf(BLUE"| Enter password (at least 5 characters): "RESET);
        getPassword(newUserPassword, sizeof(newUserPassword));
        if (strlen(newUserPassword) < 5) {
            printf(RED"\n| Password must be at least 5 characters long. Please try again.\n"RESET);
            continue;
        }
        break;
    }

    while (1) {
        printf(BLUE"| Confirm password: "RESET);
        getPassword(confirmPassword, sizeof(confirmPassword));
        if (strcmp(newUserPassword, confirmPassword) != 0) {
            printf(RED"\n| Passwords do not match. Please try again.\n"RESET);
        } else {
            strcpy(newUser.password, newUserPassword);
            break;
            }
        }
            fprintf(fptr, "%s %s %s %s\n", newUser.user_name, newUser.password, newUser.fname, newUser.email);
            fclose(fptr);
            printf(GREEN"\n| Sign up successful !!"RESET);
            clear();
}
void showLogin() {
    showTitle("Log In");
    struct User inputUser, storedUser;
    FILE *fptr = fopen("login.txt", "r");

    printf(BLUE"| Enter user name: "RESET);
    fgets(inputUser.user_name, sizeof(inputUser.user_name), stdin);
    inputUser.user_name[strlen(inputUser.user_name)-1] = '\0';

    printf(GREEN"\n| To visible password press [V] or [v]....\n"RESET);
    printf(BLUE"\n| Enter password: "RESET);
    getPassword(inputUser.password, sizeof(inputUser.password));

    while (fscanf(fptr, "%s %s %s %s", storedUser.user_name, storedUser.password, storedUser.fname, storedUser.email) == 4) {
    if (strcmp(storedUser.user_name, inputUser.user_name) == 0 &&
        strcmp(storedUser.password, inputUser.password) == 0) {
        printf(GREEN"\n| Login successful! Welcome, Sir...\n"RESET);
        fclose(fptr);
        clear();
        return userMenu();
        }
    }
    fclose(fptr);
    printf(RED"\n| Invalid!!!\n| Please enter the correct username and password or sign up first."RESET);
    clear();
}

int confirmation(char msg[], char msg1[]) {
    char choice;
    printf(BLUE"\n| Confirm details? (y/n): "RESET);
    scanf(" %c", &choice);
    getchar();
    if (choice != 'y' && choice != 'Y') {
        printf(RED"\n| %s not saved.\n"RESET, msg);
        return 0;
    } else {
        printf(GREEN"\n| %s successfully!!"RESET, msg1);
    }
    return 1;
}
void addAppointment() {
    showTitle("Appointment Form");

    printf(YELLOW"           ___________________Patient Information___________________\n\n"RESET);
    printf(BLUE"| Full Name: "RESET);
    fgets(appt.hname, sizeof(appt.hname), stdin);
    appt.hname[strlen(appt.hname)-1] = '\0';

    printf(BLUE"| Age: "RESET);
    fgets(appt.age, sizeof(appt.age), stdin);
    appt.age[strlen(appt.age)-1] = '\0';

    printf(BLUE"| Gender: "RESET);
    printf(MAGENTA"\n\t\t\t| 1. Male\n\t\t\t| 2. Female \n"RESET);
    int gender_choice;
    printf(BLUE"\n| Enter your choice (1 or 2): "RESET);
    scanf("%d", &gender_choice);
    getchar();
    strcpy(appt.gender, (gender_choice == 1) ? "Male" : "Female");

    printf(BLUE "| Phone Number: " RESET);
    fgets(appt.phone, sizeof(appt.phone), stdin);
    appt.phone[strlen(appt.phone) - 1] = '\0';

    if (isValidPhoneNumber(appt.phone)) {
    char formattedPhone[15];
    snprintf(formattedPhone, sizeof(formattedPhone), GREEN "+88%s" RESET, appt.phone); // Green formatting for success
    strcpy(emergency.sos, formattedPhone);
    } else {
    printf(RED "\n| Invalid phone number. It must be 11 digits long.\n" RESET);
    clear();
    return;
    }

    printf(YELLOW"\n          ___________________Appointment Details___________________\n\n"RESET);
    printf(BLUE"| Doctor Name(Neurologist): "RESET);
    fgets(appt.dname, sizeof(appt.dname), stdin);
    appt.dname[strlen(appt.dname)-1] = '\0';

    printf(BLUE"| Preferred Date (date - month - year): "RESET);
    fgets(appt.date, sizeof(appt.date), stdin);
    appt.date[strlen(appt.date)-1] = '\0';

    printf(BLUE"| Preferred Time (hour : minutes  am/pm): "RESET);
    fgets(appt.time, sizeof(appt.time), stdin);
    appt.time[strlen(appt.time)-1] = '\0';

    printf(BLUE"| Reason for Checkup: "RESET);
    fgets(appt.reason, sizeof(appt.reason), stdin);
    appt.reason[strlen(appt.reason)-1] = '\0';

    printf(YELLOW"\n          ___________________Payment Method___________________\n\n"RESET);
    printf(BLUE"| Payment Method: "RESET);
    printf(MAGENTA"\n|\t\t\t 1. Cash\n|\t\t\t 2. Card\n|\t\t\t 3. Online Banking\n|\t\t\t 4. Insurance\n "RESET);
    printf(BLUE"\n| Enter your choice: "RESET);
    int payChooice;
    scanf("%d",&payChooice);
    getchar();
    strcpy(appt.payment, (payChooice == 1) ? "Cash" : (payChooice == 2) ? "Card" : (payChooice == 3) ? "Online Banking" : "Insurance");

    appt.isCompleted = 0;
    if (!confirmation("Appointment details", "Appointment registration")) {
        clear();
        return;
    }
    FILE *file = fopen("appointment.txt", "a");
    fprintf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n", appt.hname, appt.age, appt.gender, appt.phone, appt.dname, appt.date, appt.time, appt.reason, appt.payment, appt.isCompleted);
    fclose(file);clear();

}
void updateAppointmentStatus(char statusMessage[], int statusValue) {
    FILE *file = fopen("appointment.txt", "r");
    showTitle("Appointment Updating");
    char searchName[100];
    printf(BLUE"| Enter the patient's full name to %s: "RESET, statusMessage);
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strlen(searchName)-1] = '\0';

    struct appointment appointments[100];
    int appointmentCount = readAppointmentsFromFile(file, appointments, searchName);
    fclose(file);

    if (appointmentCount == 0) {
        printf(RED"\n| No appointments found for %s."RESET, searchName);
        clear();
        return;
    }
    displayAppointmentsList(appointments, appointmentCount);
    int choice;
    printf(BLUE"| Select the appointment number to %s: "RESET, statusMessage);
    scanf("%d", &choice);
    getchar();

    if (choice < 1 || choice > appointmentCount) {
        printf(RED"\n| Invalid choice. Operation canceled.\n"RESET);
        clear();
        return;
    }

    int selectedAppointment = choice - 1;
    if (appointments[selectedAppointment].isCompleted == statusValue) {
        printf(RED"\n| The appointment is already %s.\n"RESET,(statusValue == 1) ? "marked as completed" : "canceled");
        clear();
        return;
    }
    if (statusValue == 1 && appointments[selectedAppointment].isCompleted == -1) {
        printf(RED"\n| The appointment is already canceled and cannot be marked as completed.\n"RESET);
        clear();
        return;
    }
    if (statusValue == -1 && appointments[selectedAppointment].isCompleted == 1) {
        printf(RED"\n| The appointment is already marked as completed and cannot be canceled.\n"RESET);
        clear();
        return;
    }

    appointments[selectedAppointment].isCompleted = statusValue;
    printf("-----------------------------------------------\n"GREEN"\n| Appointment with Doctor %s on %s at %s has been %s."RESET,
           appointments[selectedAppointment].dname, appointments[selectedAppointment].date,
           appointments[selectedAppointment].time, statusMessage);

    file = fopen("appointment.txt", "w");
    for (int i = 0; i < appointmentCount; i++) {
        fprintf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n",
                appointments[i].hname, appointments[i].age, appointments[i].gender, appointments[i].phone, appointments[i].dname,
                appointments[i].date, appointments[i].time, appointments[i].reason, appointments[i].payment, appointments[i].isCompleted);
    }
    fclose(file);

    printf(GREEN"\n| File updated successfully!!"RESET);
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
    printf(BLUE "\n| Found " RED "%d" BLUE " appointment(s):\n" RESET, appointmentCount);

    for (int i = 0; i < appointmentCount; i++) {
        printf(BLUE "\n| Appointment ["GREEN"%d"BLUE"]:\n\n", i + 1);
        printf("| Date   : " YELLOW "%s\n", appointments[i].date);
        printf(BLUE "| Time   : " YELLOW "%s\n", appointments[i].time);
        printf(BLUE "| Doctor : " YELLOW "%s\n", appointments[i].dname);
        printf(BLUE "| Reason : " YELLOW "%s\n", appointments[i].reason);
        printf(CYAN "------------------------------------------------------------------------------------------\n" RESET);
    }
}
void displayAppointment() {
    FILE *file = fopen("appointment.txt", "r");
    showTitle("Display Appointment");
    char patientName[100];
    printf(BLUE"| Enter the patient's full name to view appointments: "RESET);
    fgets(patientName, sizeof(patientName), stdin);
    patientName[strlen(patientName)-1] = '\0';

    struct appointment appointments[100];
    int appointmentCount = readAppointmentsFromFile(file, appointments, patientName);
    fclose(file);
    if (appointmentCount == 0) {
        printf(RED"\n| No appointments found for patient: "GREEN"%s\n"RESET, patientName);
        clear();
        return;
    }
    displayAppointmentsList(appointments, appointmentCount);
    int choice;
    printf(BLUE"\n| Enter the number of the appointment to view details: "RESET, appointmentCount);
    scanf("%d", &choice);
    getchar();
    system("cls");showTitle("Display Appointment");
    if (choice < 1 || choice > appointmentCount) {
        printf(RED"\n| Invalid choice.\n"RESET);
        clear();
        return;
    }

    struct appointment selected = appointments[choice - 1];
    printf(YELLOW"\n           ___________________Patient Information___________________\n\n");
    printf(BLUE"| Full Name: "GREEN"%s\n", selected.hname);
    printf(BLUE"| Age: "GREEN"%s\n", selected.age);
    printf(BLUE"| Gender: "GREEN"%s\n", selected.gender);
    printf(BLUE"| Phone Number: "GREEN"%s\n", selected.phone);

    printf(YELLOW"\n          ___________________Appointment Details___________________\n\n");
    printf(BLUE"| Doctor Name: "GREEN"%s\n", selected.dname);
    printf(BLUE"| Date: "GREEN"%s\n", selected.date);
    printf(BLUE"| Time: "GREEN"%s\n", selected.time);
    printf(BLUE"| Reason: "GREEN"%s\n", selected.reason);

    printf(YELLOW"\n          ___________________Payment Method___________________\n\n");
    printf(BLUE"| Payment Method: "GREEN"%s\n", selected.payment);

    if (selected.isCompleted == 1) {
        printf(BLUE"| Status: "GREEN"Completed"RESET);
    } else if (selected.isCompleted == -1) {
        printf(BLUE"| Status: "RED"Canceled"RESET);
    } else {
        printf(BLUE"| Status: "MAGENTA"Pending"RESET);
    }
    clear();
}

void addNote() {
    FILE *file = fopen("note.txt", "a");
    showTitle("Add Note");

    printf(BLUE"| Enter the date (format: dd-mm-yyyy): "RESET);
    fgets(data.date, sizeof(data.date), stdin);
    data.date[strcspn(data.date, "\n")] = 0;

    printf(CYAN"\n\n|\t\t\t\t<<<<<<<<< Write your note >>>>>>>>>\n\n\n| "RESET);
    fgets(data.note, sizeof(data.note), stdin);
    data.note[strcspn(data.note, "\n")] = 0;

    fprintf(file, "%s -> %s\n", data.date, data.note);
    fclose(file);
    printf(GREEN"\n| Note saved successfully!\n"RESET);
    clear();
}
void viewNotes() {
    FILE *file = fopen("note.txt", "r");
    showTitle("View Note");
    printf(BLUE"\t\t\t\t<<<<<<<<< Your Notes >>>>>>>>>\n\n\n"RESET);
    int found = 0;
    while (fscanf(file, "%14s -> %999[^\n]\n", temp.date, temp.note) != EOF) {
        found = 1;
        printf(MAGENTA"| %-12s"RED" ->\t "YELLOW"%s\n"RESET, temp.date, temp.note);
    }
    if (!found) {
        printf(RED"\n| No notes found.\n"RESET);
    }
    fclose(file);
    clear();
}
void deleteNote() {
    FILE *file = fopen("note.txt", "r");
    showTitle("Delete A Note");
    int found = 0;

    printf(BLUE"\n| Enter the date of the note to delete (format: dd-mm-yyyy): "RESET);
    fgets(searchDate, sizeof(searchDate), stdin);
    searchDate[strcspn(searchDate, "\n")] = 0;

    FILE *tempFile = fopen("temp.txt", "w");
    int totalNotesOnDate = 0, noteIndex = 0;
    while (fscanf(file, "%14s -> %999[^\n]\n", temp.date, temp.note) != EOF) {
        if (strcmp(temp.date, searchDate) == 0) {
            found = 1;
            notesOnDate[totalNotesOnDate] = temp;
            totalNotesOnDate++;
        }
    }
    if (!found) {
        fclose(file);
        fclose(tempFile);
        remove("temp.txt");
        printf(RED"\n| No notes found for the given date.\n"RESET);
        clear();
        return;
    }
    printf(CYAN"\n| Total "RED"%d "CYAN"Notes available on "MAGENTA"%s .....\n\n"RESET, totalNotesOnDate, searchDate);
    for (int i = 0; i < totalNotesOnDate; i++) {
        printf(CYAN"| %d. "MAGENTA"%-12s "RED"->\t"YELLOW"%s\n"RESET, i + 1, notesOnDate[i].date, notesOnDate[i].note);
    }
    int deleteIndex;
    printf(BLUE"\n| Enter the note number to delete: "RESET);
    scanf("%d", &deleteIndex);
    getchar();
    if (deleteIndex < 1 || deleteIndex > totalNotesOnDate) {
        fclose(file);
        fclose(tempFile);
        remove("temp.txt");
        printf(RED"\n| Invalid note number. Deletion canceled.\n"RESET);
        clear();
        return;
    }
    rewind(file);
    noteIndex = 0;
    while (fscanf(file, "%14s -> %999[^\n]\n", temp.date, temp.note) != EOF) {
        if (strcmp(temp.date, searchDate) == 0) {
            noteIndex++;
            if (noteIndex == deleteIndex) {
                continue;
            }
        }
        fprintf(tempFile, "%s -> %s\n", temp.date, temp.note);
    }
    fclose(file);
    fclose(tempFile);
    remove("note.txt");
    rename("temp.txt", "note.txt");
    printf(GREEN"\n| Note deleted successfully!\n"RESET);
    clear();
}

int isValidPhoneNumber(char *phone) {
    int len = strlen(phone);
    if (len != 11) return 0;
    for (int i = 0; i < len; i++) {
        if (!isdigit(phone[i])) return 0;
    }
    return 1;
}
void addInfo() {
    showTitle("Add Emergency Info.");
    printf(BLUE"| Full Name: "RESET);
    fgets(emergency.fname, sizeof(emergency.fname), stdin);
    emergency.fname[strcspn(emergency.fname, "\n")] = '\0';

    printf(BLUE"| Home Address: "RESET);
    fgets(emergency.address, sizeof(emergency.address), stdin);
    emergency.address[strcspn(emergency.address, "\n")] = '\0';

    printf(BLUE"| Phone Number (11 digits): "RESET);
    fgets(emergency.sos, sizeof(emergency.sos), stdin);
    emergency.sos[strcspn(emergency.sos, "\n")] = '\0';

    if (isValidPhoneNumber(emergency.sos)) {
        char formattedPhone[15];
        snprintf(formattedPhone, sizeof(formattedPhone), "+88%s", emergency.sos);
        strcpy(emergency.sos, formattedPhone);
    } else {
        printf(RED"\nInvalid phone number. It must be 11 digits long.\n"RESET);clear();
        return;
    }
    if (!confirmation("Emergency details", "Emergency details added")) {
        clear();
        return;
    }
    FILE *file = fopen("emergency.txt", "w");
    fprintf(file, "%s\n%s\n%s\n", emergency.fname, emergency.address, emergency.sos);
    fclose(file);
    clear();
}
void displayEmergency() {
    FILE *file = fopen("emergency.txt", "r");
    showTitle("Emergency Information");
    if (fgets(emergency.fname, sizeof(emergency.fname), file) && fgets(emergency.address, sizeof(emergency.address), file) && fgets(emergency.sos, sizeof(emergency.sos), file)) {

        emergency.fname[strcspn(emergency.fname, "\n")] = '\0';
        emergency.address[strcspn(emergency.address, "\n")] = '\0';
        emergency.sos[strcspn(emergency.sos, "\n")] = '\0';

        printf(GREEN"\t\t<<<<<<<<< Patient Information >>>>>>>>>\n\n"RESET);
        printf(BLUE"| Full Name   : " RESET YELLOW "%s\n"RESET, emergency.fname);
        printf(BLUE  "| Home Address: " RESET YELLOW "%s\n"RESET, emergency.address);
        printf(BLUE"| Phone Number: " RESET YELLOW "%s\n"RESET, emergency.sos);

    } else {
        printf(RED"\n| No emergency information available right now.\n"RESET);
    }
    fclose(file);
    clear();
}

void saveToFile() {
    FILE *file = fopen("medicine.txt", "w");
    fprintf(file, "%d\n", medicineCount);
    for (int i = 0; i < medicineCount; i++) {
        fprintf(file, "%s,%s,%s,%s,%s,%d,%d,%d\n",medicines[i].name, medicines[i].dosage, medicines[i].frequency,medicines[i].mealTime, medicines[i].startDate, medicines[i].duration,medicines[i].daysLeft, medicines[i].taken);
    }
    fclose(file);
}
void addMedicine() {
    showTitle("Add Medicine");
    if (medicineCount >= MAX_MEDICINES) {
        printf(RED"\n| Medicine chart is full.\n"RESET);clear();
        return;
    }

    printf(BLUE"| Enter Medicine Name: "RESET);
    fgets(medicines[medicineCount].name, sizeof(medicines[medicineCount].name), stdin);
    medicines[medicineCount].name[strcspn(medicines[medicineCount].name, "\n")] = '\0';

    printf(BLUE"| Enter Dosage (e.g., 500mg, 1 Tablet): "RESET);
    fgets(medicines[medicineCount].dosage, sizeof(medicines[medicineCount].dosage), stdin);
    medicines[medicineCount].dosage[strcspn(medicines[medicineCount].dosage, "\n")] = '\0';

    printf(BLUE"| Enter Frequency (e.g., Morning, Night): "RESET);
    fgets(medicines[medicineCount].frequency, sizeof(medicines[medicineCount].frequency), stdin);
    medicines[medicineCount].frequency[strcspn(medicines[medicineCount].frequency, "\n")] = '\0';

    printf(BLUE"| Should the medicine be taken-\n\n"RESET MAGENTA"\t\t\t| 1. Before Meals\n\t\t\t| 2. After Meals\n\n"RESET);
    int Mchoice;
    printf(BLUE"\n| Enter your choice (1 or 2): "RESET);
    scanf("%d", &Mchoice);getchar();
    strcpy(medicines[medicineCount].mealTime, (Mchoice == 1) ? "Before Meals" : "After Meals");

    printf(BLUE"| Enter Start Date (DD-MM-YYYY): "RESET);
    fgets(medicines[medicineCount].startDate, sizeof(medicines[medicineCount].startDate), stdin);
    medicines[medicineCount].startDate[strcspn(medicines[medicineCount].startDate, "\n")] = '\0';

    char durationStr[10];
    printf(BLUE"| Enter Duration (in days): "RESET);
    fgets(durationStr, sizeof(durationStr), stdin);
    if (sscanf(durationStr, "%d", &medicines[medicineCount].duration) != 1 || medicines[medicineCount].duration <= 0) {
        printf(RED"\n| Invalid duration! Please enter a positive number.\n"RESET);clear();
        return;
    }
    medicines[medicineCount].daysLeft = medicines[medicineCount].duration;
    medicines[medicineCount].taken = 0;
    medicineCount++;
    printf(GREEN"\n| Medicine added successfully!"RESET);
    saveToFile(); clear();
}
void showChart() {
    showTitle("Medicine Chart");

    FILE *file = fopen("medicine.txt", "r");
    int count;
    if (fscanf(file, "%d\n", &count) != 1) {
        printf(RED"\n| Error: Invalid file format.\n"RESET);
        fclose(file);clear();
        return;
    }

    printf(BLUE"------------------------------------------------------------------------------------------------------------------------\n"RESET);
    printf("| "RED"%-20s"BLUE" | "RED"%-10s"BLUE" | "RED"%-15s"BLUE" | "RED"%-15s"BLUE" | "RED"%-10s"BLUE" | "RED"%-8s"BLUE" | "RED"%-6s"BLUE" | "RED"%-10s"BLUE" |\n"RESET,
           "Name", "Dosage", "Frequency", "Meal Time", "Start Date", "Days Left", "Taken", "Status");
    printf(BLUE"------------------------------------------------------------------------------------------------------------------------\n"RESET);

    for (int i = 0; i < count; i++) {
        struct medicine med;
        if (fscanf(file, " %[^,],%[^,],%[^,],%[^,],%[^,],%d,%d,%d\n",
                   med.name, med.dosage, med.frequency, med.mealTime,
                   med.startDate, &med.duration, &med.daysLeft, &med.taken) == 8) {
            char status[10];
            strcpy(status, med.daysLeft > 0 ? "Ongoing" : "Complete");

            printf("| "GREEN"%-20s"RESET" | "BLUE"%-10s"RESET" | "MAGENTA"%-15s"RESET" | "CYAN"%-15s"RESET" | "YELLOW"%-10s"RESET" | "RED"%-8d"RESET" | "BLUE"%-6d"RESET" | "GREEN"%-10s"RESET" |\n",
                   med.name, med.dosage, med.frequency, med.mealTime,
                   med.startDate, med.daysLeft, med.taken, status);
        } else {
            printf(RED"\n| Error reading medicine information.\n"RESET);
            break;
        }
    }

    printf(BLUE"------------------------------------------------------------------------------------------------------------------------\n"RESET);
    printf(CYAN"************************************************************************************************************************\n"RESET);
    fclose(file);
    clear();
}
void markAsTaken() {
    showTitle("Mark As Taken");

    FILE *file = fopen("medicine.txt", "r");

    int medicineCountFromFile = 0;
    if (fscanf(file, "%d\n", &medicineCountFromFile) != 1) {
        printf(RED"| Error: Invalid file format.\n"RESET);
        fclose(file);
        return;
    }

    medicineCount = medicineCountFromFile;

    for (int i = 0; i < medicineCount; i++) {
        if (fscanf(file, " %[^,],%[^,],%[^,],%[^,],%[^,],%d,%d,%d\n",
                   medicines[i].name, medicines[i].dosage, medicines[i].frequency,
                   medicines[i].mealTime, medicines[i].startDate, &medicines[i].duration,
                   &medicines[i].daysLeft, &medicines[i].taken) != 8) {
            printf(RED"| Error: Unable to read medicine data.\n"RESET);
            fclose(file);clear();
            return;
        }
    }
    fclose(file);

    char name[50];
    printf(BLUE"| Enter the name of the medicine to mark as taken: "RESET);
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < medicineCount; i++) {
        if (strcmp(medicines[i].name, name) == 0) {
            found = 1;
            if (medicines[i].daysLeft > 0) {
                medicines[i].taken++;
                medicines[i].daysLeft--;
                saveToFile();
                printf(GREEN"\n| Marked '%s' as taken.\tDays left: %d\n"RESET, medicines[i].name, medicines[i].daysLeft);
                if (medicines[i].daysLeft == 0) {
                    printf(GREEN"\n| '%s' dosage is now complete!"RESET, medicines[i].name);
                }
            } else {
                printf(RED"\n| '%s' has no remaining doses. Dosage is already complete.\n"RESET, medicines[i].name);
            }
            break;
        }
    }
    if (!found) {
        printf(RED"\n| Medicine not found.\n"RESET);
    }
    clear();
}

void Medicinemenu() {
    int choice;
    do {
        MedicineTitle();
        printf(BLUE"|Give me a command: "RESET);
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
                printf(GREEN"\n| Back to the main menu....\n| Stay healthy!"RESET);
                clear();
                break;
            default:
                MedicineTitle();
                printf(RED"\n| Invalid choice! Please try again."RESET);
                clear();
        }
    } while (choice != 4);
}
void userMenu() {
    int choice;
    while (1) {
        userTitle();
        printf(BLUE"| Give Me a command: "RESET);
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
                printf(GREEN"\n| Log Out from the program. Goodbye!"RESET);
                clear();
                return main();
                break;
            default:
                userTitle();
                printf(RED"\n| Invalid choice. Try again."RESET);
                clear();
                break;
} } }
void emergencyMenu() {
    while (1) {
        emergencyTitle();
        printf(BLUE"| Give me a command: "RESET);
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
                printf(GREEN"| Back to the main menu, Thanks..."RESET);
                clear();
                return;
            default:
                emergencyTitle();
                printf(RED"\n| Invalid option. Try again."RESET);
                clear();
        }
    }
}
void appointmentMenu() {
    int choice;
    do {
        appointmentTitle();
        printf(BLUE"| Give me a command: "RESET);
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
                printf(GREEN"\n| Returning to Main Menu..."RESET);
                clear();
                break;
            default:
                appointmentTitle();
                printf(RED"\n| Invalid choice. Try again."RESET);
                clear();
                break;
        }
    } while (choice != 5);
}
void noteMenu() {
     int choice;
    do {
        noteTitle();
        printf(BLUE"| Give me a command: "RESET);
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
                deleteNote();
                break;
            case 4:
                noteTitle();
                printf(GREEN"\n| Returning to Main Menu..."RESET);
                clear();
                break;
            default:
                noteTitle();
                printf(RED"\n| Invalid choice. Try again."RESET);
                clear();
                break;
        }
    } while (choice != 4);
}

int main() {
    while (1) {
        introTitle();
        printf(BLUE "\n| Give me a command: " RESET);
        int choice;
        scanf("%d", &choice);
        getchar();
        system("cls");
        switch (choice) {
            case 2:
                showRegister();
                break;
            case 1:
                showLogin();
                break;
            case 3:
                introTitle();
                printf(GREEN"\n| Exiting program...\n\n"RESET);
                clear();
                exit(0);
                break;
            default:
                introTitle();
                printf(RED"\n| Invalid option. Please try again."RESET);
                clear();
                break;
        }
    }

    return 0;
}
