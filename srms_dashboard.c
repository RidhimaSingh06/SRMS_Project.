#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define STUDENT_FILE "students.txt"
#define ATTENDANCE_FILE "attendance.txt"
#define PASSWORD_FILE "password.txt"

typedef struct {
    int roll;
    char name[50];
    int marks;
    char grade[5];
} Student;

void formatLine() { printf("-----------------------------------------------------------\n"); }
void setColor(int color) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); }

// Password Handling
void initPassword() {
    FILE *fp=fopen(PASSWORD_FILE,"r");
    if(!fp){ fp=fopen(PASSWORD_FILE,"w"); fprintf(fp,"admin123"); fclose(fp); return;}
    fclose(fp);
}

void inputPassword(char *pass) {
    int i=0; char ch;
    while(1){
        ch=getch();
        if(ch==13){ pass[i]='\0'; printf("\n"); break; }
        else if(ch==8){ if(i>0){ i--; printf("\b \b"); } }
        else { pass[i++]=ch; printf("*"); }
    }
}

int checkPassword(char *pass){
    char stored[50]; FILE *fp=fopen(PASSWORD_FILE,"r"); fscanf(fp,"%s",stored); fclose(fp);
    return strcmp(pass,stored)==0;
}

void changePassword() {
    char newPass[50];
    printf("Enter new password: "); inputPassword(newPass);
    FILE *fp=fopen(PASSWORD_FILE,"w"); fprintf(fp,"%s",newPass); fclose(fp);
    setColor(10); printf("Password updated successfully!\n"); setColor(7);
}

// Student Functions
float calculateCGPA(int marks){ return marks/10.0; }
float calculatePercentage(int marks){ return marks; }

void displayHeader() {
    setColor(14); printf("\n===========================================\n");
    printf("       STUDENT RESULT MANAGEMENT SYSTEM   \n");
    printf("===========================================\n\n"); setColor(7);
}

void displayStudents() {
    FILE *fp=fopen(STUDENT_FILE,"r");
    if(!fp){ setColor(12); printf("No records found!\n"); setColor(7); return; }
    Student s; formatLine();
    printf("| %-7s | %-20s | %-5s | %-5s | %-6s | %-6s |\n","RollNo","Name","Marks","Grade","CGPA","Result");
    formatLine();
    while(fscanf(fp,"%d,%[^,],%d,%s\n",&s.roll,s.name,&s.marks,s.grade)!=EOF){
        float cgpa=calculateCGPA(s.marks);
        printf("| %-7d | %-20s | %-5d | %-5s | %-6.2f | ",s.roll,s.name,s.marks,s.grade,cgpa);
        if(s.marks>=40) { setColor(10); printf("PASS |\n"); setColor(7);}
        else { setColor(12); printf("FAIL |\n"); setColor(7);}
    }
    formatLine(); fclose(fp);
}

void addStudent() {
    FILE *fp=fopen(STUDENT_FILE,"a"); if(!fp){ setColor(12); printf("Cannot open student file!\n"); setColor(7); return; }
    Student s;
    printf("Enter Roll No: "); scanf("%d",&s.roll);
    printf("Enter Name   : "); scanf(" %[^\n]",s.name);
    printf("Enter Marks  : "); scanf("%d",&s.marks);
    if(s.marks>=90) strcpy(s.grade,"A+");
    else if(s.marks>=80) strcpy(s.grade,"A");
    else if(s.marks>=70) strcpy(s.grade,"B");
    else if(s.marks>=60) strcpy(s.grade,"C");
    else strcpy(s.grade,"F");
    fprintf(fp,"%d,%s,%d,%s\n",s.roll,s.name,s.marks,s.grade); fclose(fp);
    setColor(10); printf("Student added successfully!\n"); setColor(7);
}

void deleteStudent() {
    FILE *fp=fopen(STUDENT_FILE,"r"); FILE *temp=fopen("temp.txt","w");
    if(!fp || !temp){ setColor(12); printf("File error!\n"); setColor(7); return;}
    int roll; printf("Enter Roll No to delete: "); scanf("%d",&roll);
    Student s; int found=0;
    while(fscanf(fp,"%d,%[^,],%d,%s\n",&s.roll,s.name,&s.marks,s.grade)!=EOF){
        if(s.roll==roll){ found=1; continue;}
        fprintf(temp,"%d,%s,%d,%s\n",s.roll,s.name,s.marks,s.grade);
    }
    fclose(fp); fclose(temp); remove(STUDENT_FILE); rename("temp.txt",STUDENT_FILE);
    if(found){ setColor(10); printf("Student deleted successfully!\n"); setColor(7);}
    else{ setColor(12); printf("Student not found!\n"); setColor(7);}
}

void markAttendance() {
    FILE *fp=fopen(ATTENDANCE_FILE,"a"); if(!fp){ setColor(12); printf("Cannot open attendance!\n"); setColor(7); return;}
    int roll; char status[2]; printf("Enter Roll No: "); scanf("%d",&roll);
    printf("Enter Status (P/A): "); scanf("%s",status);
    fprintf(fp,"%d,%s\n",roll,status); fclose(fp);
    setColor(10); printf("Attendance marked!\n"); setColor(7);
}

void viewAttendance() {
    FILE *fp=fopen(ATTENDANCE_FILE,"r"); if(!fp){ setColor(12); printf("No attendance records!\n"); setColor(7); return;}
    int roll,total=0,present=0,readRoll; char status[2];
    printf("Enter Roll No to view attendance: "); scanf("%d",&roll);
    while(fscanf(fp,"%d,%s\n",&readRoll,status)!=EOF){
        if(readRoll==roll){ total++; if(status[0]=='P'||status[0]=='p') present++; }
    }
    fclose(fp);
    if(total==0){ setColor(12); printf("No records found.\n"); setColor(7);}
    else{ setColor(11); printf("Attendance Percentage: %.2f%%\n",(present*100.0)/total); setColor(7);}
}

// Main Dashboard
int main() {
    char username[20],password[50]; int attempts=3;
    initPassword(); displayHeader();

    while(attempts>0){
        printf("Login (%d attempts left)\nUsername: ",attempts); scanf("%s",username);
        printf("Password: "); inputPassword(password);
        if(strcmp(username,"admin")==0 && checkPassword(password)){ setColor(10); printf("Login Successful!\n\n"); setColor(7); break;}
        else{ setColor(12); printf("Invalid credentials!\n\n"); setColor(7); attempts--;}
        if(attempts==0){ setColor(12); printf("Too many attempts. Exiting.\n"); setColor(7); return 0;}
    }

    int exitFlag=0;
    while(!exitFlag){
        setColor(14); printf("\n===== ADMIN MENU =====\n"); setColor(7);
        printf("1. Add Student\n2. Display Students\n3. Delete Student\n4. Attendance\n5. Change Password\n6. Logout\nEnter choice: ");
        int ch; scanf("%d",&ch);
        switch(ch){
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: deleteStudent(); break;
            case 4: {
                int ac; printf("1. Mark Attendance 2. View Attendance\nEnter choice: "); scanf("%d",&ac);
                if(ac==1) markAttendance(); else viewAttendance(); break;
            }
            case 5: changePassword(); break;
            case 6: {
                char confirm; printf("Are you sure you want to exit? (Y/N): "); scanf(" %c",&confirm);
                if(confirm=='Y'||confirm=='y') exitFlag=1; break;
            }
            default: setColor(12); printf("Invalid choice!\n"); setColor(7);
        }
    }

    setColor(14); printf("\nThank you for using SRMS. Goodbye!\n"); setColor(7);
    return 0;
}

