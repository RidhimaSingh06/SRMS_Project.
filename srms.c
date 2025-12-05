#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> // For getch()
#include <windows.h> // For colored text

#define STUDENT_FILE "students.txt"
#define ATTENDANCE_FILE "attendance.txt"
#define PASSWORD_FILE "password.txt"

typedef struct {
    int roll;
    char name[50];
    int marks;
    char grade[5];
} Student;

// Utility Functions
void formatLine() { printf("-----------------------------------------------------------\n"); }
void setColor(int color) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); }

// Password Handling
void initPassword() {
    FILE *fp = fopen(PASSWORD_FILE, "r");
    if (!fp) {
        fp = fopen(PASSWORD_FILE, "w");
        fprintf(fp, "admin123"); // default password
    }
    fclose(fp);
}

void inputPassword(char *pass) {
    int i = 0;
    char ch;
    while(1) {
        ch = getch();
        if(ch==13){ pass[i]='\0'; printf("\n"); break; } // Enter
        else if(ch==8){ // Backspace
            if(i>0){ i--; printf("\b \b"); }
        } else { pass[i++] = ch; printf("*"); }
    }
}

int checkPassword(char *pass) {
    char stored[50]; FILE *fp=fopen(PASSWORD_FILE,"r"); fscanf(fp,"%s",stored); fclose(fp);
    return strcmp(pass, stored)==0;
}

void changePassword() {
    char newPass[50];
    printf("Enter new password: ");
    inputPassword(newPass);
    FILE *fp=fopen(PASSWORD_FILE,"w"); fprintf(fp,"%s",newPass); fclose(fp);
    setColor(10); printf("Password updated successfully!\n"); setColor(7);
}

// Student Functions
void addStudent() {
    FILE *fp=fopen(STUDENT_FILE,"a");
    if(!fp){ setColor(12); printf("Cannot open student file!\n"); setColor(7); return; }
    Student s;
    printf("Enter Roll No: "); scanf("%d",&s.roll);
    printf("Enter Name   : "); scanf(" %[^\n]",s.name);
    printf("Enter Marks  : "); scanf("%d",&s.marks);
    if(s.marks>=90) strcpy(s.grade,"A+");
    else if(s.marks>=80) strcpy(s.grade,"A");
    else if(s.marks>=70) strcpy(s.grade,"B");
    else if(s.marks>=60) strcpy(s.grade,"C");
    else strcpy(s.grade,"F");
    fprintf(fp,"%d,%s,%d,%s\n",s.roll,s.name,s.marks,s.grade);
    fclose(fp);
    setColor(10); printf("Student added successfully!\n"); setColor(7);
}

void deleteStudent() {
    FILE *fp=fopen(STUDENT_FILE,"r");
    FILE *temp=fopen("temp.txt","w");
    if(!fp || !temp){ setColor(12); printf("File error!\n"); setColor(7); return; }
    int roll; printf("Enter Roll No to delete: "); scanf("%d",&roll);
    Student s; int found=0;
    while(fscanf(fp,"%d,%[^,],%d,%s\n",&s.roll,s.name,&s.marks,s.grade)!=EOF){
        if(s.roll==roll){ found=1; continue; }
        fprintf(temp,"%d,%s,%d,%s\n",s.roll,s.name,s.marks,s.grade);
    }
    fclose(fp); fclose(temp);
    remove(STUDENT_FILE); rename("temp.txt",STUDENT_FILE);
    if(found){ setColor(10); printf("Student deleted successfully!\n"); setColor(7);}
    else { setColor(12); printf("Student not found!\n"); setColor(7);}
}

float calculateCGPA(int marks){ return marks/10.0; }
float calculatePercentage(int marks){ return marks; }

void displayStudents() {
    FILE *fp=fopen(STUDENT_FILE,"r");
    if(!fp){ setColor(12); printf("No records found!\n"); setColor(7); return; }
    Student s; formatLine();
    printf("| %-7s | %-20s | %-5s | %-5s | %-6s | %-6s |\n","RollNo","Name","Marks","Grade","CGPA","Result");
    formatLine();
    while(fscanf(fp,"%d,%[^,],%d,%s\n",&s.roll,s.name,&s.marks,s.grade)!=EOF){
        float cgpa=calculateCGPA(s.marks);
        printf("| %-7d | %-20s | %-5d | %-5s | %-6.2f | ",s.roll,s.name,s.marks,s.grade,cgpa);
        if(s.marks>=40) printf("PASS |\n"); else printf("FAIL |\n");
    }
    formatLine(); fclose(fp);
}

void searchStudent() {
    int choice; printf("Search By: 1. Roll  2. Name\nEnter choice: "); scanf("%d",&choice);
    FILE *fp=fopen(STUDENT_FILE,"r"); if(!fp){ setColor(12); printf("No records found!\n"); setColor(7); return; }
    Student s; int found=0;
    if(choice==1){
        int roll; printf("Enter Roll No: "); scanf("%d",&roll);
        while(fscanf(fp,"%d,%[^,],%d,%s\n",&s.roll,s.name,&s.marks,s.grade)!=EOF){
            if(s.roll==roll){ found=1; break; }
        }
    } else if(choice==2){
        char name[50]; printf("Enter Name: "); scanf(" %[^\n]",name);
        while(fscanf(fp,"%d,%[^,],%d,%s\n",&s.roll,s.name,&s.marks,s.grade)!=EOF){
            if(strcmp(s.name,name)==0){ found=1; break; }
        }
    }
    if(found){
        formatLine();
        printf("| %-7s | %-20s | %-5s | %-5s | %-6s | %-6s |\n","RollNo","Name","Marks","Grade","CGPA","Result");
        formatLine();
        float cgpa=calculateCGPA(s.marks);
        printf("| %-7d | %-20s | %-5d | %-5s | %-6.2f | ",s.roll,s.name,s.marks,s.grade,cgpa);
        if(s.marks>=40) printf("PASS |\n"); else printf("FAIL |\n");
        formatLine();
    } else { setColor(12); printf("Student not found!\n"); setColor(7);}
    fclose(fp);
}

// Sorting
void sortStudents() {
    FILE *fp=fopen(STUDENT_FILE,"r"); if(!fp){ setColor(12); printf("No records!\n"); setColor(7); return;}
    Student students[100]; int count=0;
    while(fscanf(fp,"%d,%[^,],%d,%s\n",&students[count].roll,students[count].name,&students[count].marks,students[count].grade)!=EOF) count++;
    fclose(fp);
    int choice; printf("Sort By: 1.Name A-Z 2.Marks High-Low 3.Roll Low-High\nEnter choice: "); scanf("%d",&choice);
    for(int i=0;i<count-1;i++){
        for(int j=0;j<count-i-1;j++){
            int swap=0;
            if(choice==1 && strcmp(students[j].name,students[j+1].name)>0) swap=1;
            else if(choice==2 && students[j].marks<students[j+1].marks) swap=1;
            else if(choice==3 && students[j].roll>students[j+1].roll) swap=1;
            if(swap){ Student temp=students[j]; students[j]=students[j+1]; students[j+1]=temp;}
        }
    }
    formatLine();
    printf("| %-7s | %-20s | %-5s | %-5s | %-6s | %-6s |\n","RollNo","Name","Marks","Grade","CGPA","Result");
    formatLine();
    for(int i=0;i<count;i++){
        float cgpa=calculateCGPA(students[i].marks);
        printf("| %-7d | %-20s | %-5d | %-5s | %-6.2f | ",students[i].roll,students[i].name,students[i].marks,students[i].grade,cgpa);
        if(students[i].marks>=40) printf("PASS |\n"); else printf("FAIL |\n");
    }
    formatLine();
}

// Attendance
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
        if(readRoll==roll){ total++; if(status[0]=='P'||status[0]=='p') present++;}
    }
    fclose(fp);
    if(total==0){ setColor(12); printf("No records found.\n"); setColor(7);}
    else{ setColor(11); printf("Attendance Percentage: %.2f%%\n",(present*100.0)/total); setColor(7);}
}

// Main
int main() {
    char username[20],password[50]; int attempts=3;
    initPassword();
    setColor(14); printf("\n===== STUDENT RESULT MANAGEMENT SYSTEM =====\n\n"); setColor(7);

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
        printf("1. Add Student\n2. Display Students\n3. Search Student\n4. Sort Students\n5. Attendance\n6. Change Password\n7. Delete Student\n8. Logout\nEnter choice: ");
        int ch; scanf("%d",&ch);
        switch(ch){
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: sortStudents(); break;
            case 5: {
                int ac; printf("1. Mark Attendance 2. View Attendance\nEnter choice: "); scanf("%d",&ac);
                if(ac==1) markAttendance(); else viewAttendance(); break;
            }
            case 6: changePassword(); break;
            case 7: deleteStudent(); break;
            case 8: {
                char confirm; printf("Are you sure you want to exit? (Y/N): "); scanf(" %c",&confirm);
                if(confirm=='Y'||confirm=='y') exitFlag=1; break;
            }
            default: setColor(12); printf("Invalid choice!\n"); setColor(7);
        }
    }
    return 0;
}

