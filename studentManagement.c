#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>
#include <stdbool.h>


struct studentInfo
{
    char id[10];
    char name[20];
    char email[30];
    char phone[10];
    int numberOfCourses;
};
struct studentInfo students[100];

struct courseInfo
{
    char studentId[10];
    char code[10];
    char name[20];
};
struct courseInfo courses[500];

int i,j;
int TotalStudents=0;
int TotalCourses=0;
char studentId[10];

FILE *allStudents;
FILE *allCourses;
FILE *existingAllStudents;
FILE *tempAllStudents;
FILE *existingAllCourses;
FILE *tempAllCourses;

bool isRunning=true;

void menu();
void userGuidelines();
void aboutUs();
void goBackOrExit();
void exitProject();
void dataSeed();

void addNewStudent();
void showAllStudents();

int searchStudent(char studentId[10]);
void editStudent(int studentFoundIndex);
int alreadyExists(char givenInfo[300], char infoType, char studentId[300]);
void errorAndRestart(char *error[100]);

void delStudent(int studentIndex);
void delAllStudents();
void delCourseByIndex(int courseIndex);
void delStudentByIndex(int courseIndex);


int main()
{
    dataSeed();
    while (isRunning)
    {
        menu();
        int option;
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            system("cls");
            printf("\n\t\t ****ADD A NEW STUDENT: ****\n\n");
            addNewStudent();
            goBackOrExit();
            break;
        case 2:
            system("cls");
            printf("\n\t\t\t **** ALL STUDENTS: ****\n\n");
            showAllStudents();
            goBackOrExit();
            break;
        case 3:
            system("cls");
            printf("\n\t\t **** SEARCH STUDENT: ****\n\n");
            printf("Enter Student ID: ");
            scanf("%s", &studentId);
            int isFound = searchStudent(studentId);
            if (isFound<0)
            {
                printf("No Student Found\n\n");
            }
            printf("\n");
            goBackOrExit();
            break;
        case 4:
            system("cls");
            printf("\n\t\t **** EDIT A STUDENT: ****\n\n");
            printf("Enter Student ID: ");
            scanf("%s", &studentId);
            int studentFoundIndex = searchStudent(studentId);
            if (studentFoundIndex>=0)
            {
                editStudent(studentFoundIndex);
            }
            else{
                printf("No Student Found\n\n");
            }
            goBackOrExit();
            break;
        case 5:
            system("cls");
            printf("\n\t\t **** DELETE A STUDENT: ****\n\n");
            printf("Enter Student ID: ");
            scanf("%s", &studentId);
            int delStudentFoundIndex = searchStudent(studentId);
            if (delStudentFoundIndex>=0)
            {
                char sure = 'N';
                getchar();
                printf("\n\n");
                printf("Are you sure you want to delete this student? (Y/N): ");
                scanf("%c", &sure);
                if (sure=='Y' || sure=='y')
                {
                    delStudent(delStudentFoundIndex);
                }
                else{
                    printf("Your data is safe.\n\n");
                    goBackOrExit();
                }
            }
            else{
                printf("No Student Found\n\n");
                goBackOrExit();
            }
            break;
        case 6:
        {
            char sure='N';
            getchar();
            system("cls");
            printf("\n\t\t **** DELETE ALL STUDENTS: ****\n\n");
            printf("Are you sure you want to delete all the students? (Y/N): ");
            scanf("%c", &sure);
            if (sure=='Y' || sure=='y')
            {
                delAllStudents();
            }
            else
            {
                printf("Your data is safe.\n\n");
                goBackOrExit();
            }
            break;
        }
        case 7:
            system("cls");
            break;
        case 8:
            system("cls");
            userGuidelines();
            goBackOrExit();
            break;
        case 9:
            system("cls");
            aboutUs();
            goBackOrExit();
            break;
        case 10:
            isRunning=false;
            exitProject();
            break;
        default:
            exitProject();
            break;
        }
    }
    

    return 0;
}


void menu(){
    printf("\n\n\t****** STUDENT MANAGEMENT SYSTEM ******\n\n");
    printf("\t\t       MAIN MENU:\n");
    printf("\t       =========================\n");
    printf("\t         1. Add a new student\n");
    printf("\t         2. Show all students\n");
    printf("\t         3. Search a student\n");
    printf("\t         4. Update a student\n");
    printf("\t         5. Delete a student\n");
    printf("\t         6. Delete all students\n");
    printf("\t         7. Clear the window\n");
    printf("\t         8. User Guidelines\n");
    printf("\t         9. About Us\n");
    printf("\t        10. Exit the program\n");
    printf("\t       =========================\n");
    printf("\nEnter your choice: ");
}


int alreadyExists(char givenInfo[300], char infoType, char studentId[300]){
    int emailExists=0;
    int phoneExists=0;
    int idExists=0;
    int index;

    for ( index = 0; index < TotalStudents; index++)
    {
        if (strcmp(givenInfo, students[index].id) == 0)
        {
            idExists++;
        }
        if (strcmp(givenInfo, students[index].email)==0 && strcmp(studentId, students[index].id) != 0)
        {
            emailExists++;
        }
        if (strcmp(givenInfo, students[index].phone)==0 && strcmp(studentId, students[index].id) != 0)
        {
            phoneExists++;
        }
    }
    
    if (infoType=='i')
    {
        return idExists;
    }
    else if (infoType=='e')
    {
        return emailExists;
    }
    else if (infoType=='p')
    {
        return phoneExists;
    }
    else{
        return 0;
    }
}

void addNewStudent(){
    char studentId[300];
    char name[300];
    char phone[300];
    char email[300];
    int numberOfCourses;
    char courseCode[300];
    char courseName[300];
    int isValidID=0;
    while (!isValidID)
    {
        printf("Enter the ID: ");
        scanf("%s", &studentId);
        if (alreadyExists(studentId, 'i', studentId)>0)
        {
            printf("Error: This ID already exists.\n\n");
            isValidID=0;
        }
        else if (strlen(studentId)>10)
        {
            printf("Error: ID can't be more than 10 characters.\n\n");
            isValidID=0;
        }
        else if (strlen(studentId)<=0)
        {
            printf("Error: ID can't be empty.\n\n");
            isValidID=0;
        }
        else
        {
            isValidID=1;
        }
    }

    int isValidName=0;
    while (!isValidName)
    {
        printf("Enter the Name: ");
        scanf("%s", &name);
        if (strlen(name)>20)
        {
            printf("Error: Name can't be more than 20 characters.\n\n");
            isValidName=0;
        }
        else if (strlen(name)<=0)
        {
            printf("Error: Name can't be empty.\n\n");
            isValidName=0;
        }
        else
        {
            isValidName=1;
        }
    }

    int isValidEmail=0;
    while (!isValidEmail)
    {
        printf("Enter the Email: ");
        scanf("%s", &email);
        if (alreadyExists(email, 'e', studentId)>0)
        {
            printf("Error: This Email already exists.\n\n");
            isValidEmail=0;
        }
        else if (strlen(email)>30)
        {
            printf("Error: Email can't be more than 30 characters.\n\n");
            isValidEmail=0;
        }
        else if (strlen(email)<=0)
        {
            printf("Error: Email can't be empty.\n\n");
            isValidEmail=0;
        }
        else
        {
            isValidEmail=1;
        }
    }

    int isValidPhone=0;
    while (!isValidPhone)
    {
        printf("Enter the Phone Number: ");
        scanf("%s", &phone);
        if (alreadyExists(phone, 'p', studentId)>0)
        {
            printf("Error: This Phone Number already exists.\n\n");
            isValidPhone=0;
        }
        else if (strlen(phone)>10)
        {
            printf("Error: Phone Number can't be more than 10 characters.\n\n");
            isValidPhone=0;
        }
        else if (strlen(phone)<=0)
        {
            printf("Error: Phone Number can't be empty.\n\n");
            isValidPhone=0;
        }
        else
        {
            isValidPhone=1;
        }
    }

    int isValidNoOfCourse=0;
    while (!isValidNoOfCourse)
    {
        printf("Enter the No. of Courses: ");
        scanf("%d", &numberOfCourses);
        if (numberOfCourses <=0 || numberOfCourses > 4)
        {
            printf("Error: No. of Courses can't be more than 4 & less than 1.\n\n");
            isValidNoOfCourse=0;
        }
        else
        {
            isValidNoOfCourse=1;
        }
    }

    strcpy(students[TotalStudents].id, studentId);
    strcpy(students[TotalStudents].name, name);
    strcpy(students[TotalStudents].phone, phone);
    strcpy(students[TotalStudents].email, email);
    students[TotalStudents].numberOfCourses = numberOfCourses;
    TotalStudents++;

    for (int i = 0; i < numberOfCourses; i++)
    {
        printf("Enter Course %d Code: ", i+1);
        scanf("%s", &courseCode);
        printf("Enter Course %d Name: ", i+1);
        scanf("%s", &courseName);

        strcpy(courses[TotalCourses].studentId, studentId);
        strcpy(courses[TotalCourses].code, courseCode);
        strcpy(courses[TotalCourses].name, courseName);
    }
    
    printf("\nSTUDENT ADDED SUCCESSFULLY.\n\n");
}


void showAllStudents(){
    printf("|==========|====================|==============================|====================|=================|\n");
    printf("|   ID     |       Name         |              Email           |        Phone       |  No. of Courses |\n");
    printf("|==========|====================|==============================|====================|=================|\n");

    for (i = 0; i < TotalStudents; i++)
    {
        printf("|");
        printf("%s", students[i].id);
        for ( j = 0; j < (10-strlen(students[i].id)); j++)
        {
            printf(" ");
        }

        printf("|");
        printf("%s", students[i].name);
        for ( j = 0; j < (20-strlen(students[i].name)); j++)
        {
            printf(" ");
        }

        printf("|");
        printf("%s", students[i].email);
        for ( j = 0; j < (30-strlen(students[i].email)); j++)
        {
            printf(" ");
        }

        printf("|");
        printf("%s", students[i].phone);
        for ( j = 0; j < (20-strlen(students[i].phone)); j++)
        {
            printf(" ");
        }

        printf("|");
        printf("%d", students[i].numberOfCourses);
        for ( j = 0; j < 16; j++)
        {
            printf(" ");
        }

        printf("|\n");
        printf("|----------|--------------------|------------------------------|--------------------|-----------------|\n");
    }
    printf("\n");
}


int searchStudent(char studentId[10]){
    system("cls");
    int studentFoundIndex = -1;
    int i;
    for ( i = 0; i < TotalStudents; i++)
    {
        if (strcmp(studentId, students[i].id)==0)
        {
            studentFoundIndex = i;
            printf("\nOne student found for ID: %s\n\n", studentId);
            printf("Student Information:\n");
            printf("---------------------\n");
            printf("ID:    %s\n", students[i].id);
            printf("Name:  %s\n", students[i].name);
            printf("Email: %s\n", students[i].email);
            printf("Phone: %s\n", students[i].phone);
            printf("\nTotal no. of courses: %d\n", students[i].numberOfCourses);
        }
    }
    int courseCount=0;
    int j;
    for ( j = 0; j < TotalCourses; j++)
    {
        if (strcmp(studentId, courses[j].studentId)==0)
        {
            courseCount++;
            printf("---------------------\n");
            printf("Course %d Code: %s\n", courseCount, courses[j].code);
            printf("Course %d Name: %s\n", courseCount, courses[j].name);
        }
    }
    return studentFoundIndex;
}


void editStudent(int studentFoundIndex){
    printf("\n\t\t**** UPDATE THE STUDENT ****\n\n");

    char newName[300];
    char newPhone[300];
    char newEmail[300];
    int newNumberOfCourses;
    char studentId[300];

    strcpy(studentId, students[studentFoundIndex].id);

    int oldTotalNumberOfCourse = students[studentFoundIndex].numberOfCourses;

    int isValidName=0;
    while (!isValidName)
    {
        printf("Enter the new name(0 for skip): ");
        scanf("%s", &newName);
        if (strlen(newName)>20)
        {
            printf("Error: Name can't be more than 20 characters.\n\n");
            isValidName=0;
        }
        else if (strlen(newName)<=0)
        {
            printf("Error: Name can't be empty.\n\n");
            isValidName=0;
        }
        else
        {
            isValidName=1;
        }
    }

    int isValidEmail=0;
    while (!isValidEmail)
    {
        printf("Enter the new Email(0 for skip): ");
        scanf("%s", &newEmail);
        if (strlen(newEmail)>30)
        {
            printf("Error: Email can't be more than 30 characters.\n\n");
            isValidEmail=0;
        }
        else if (strlen(newEmail)<=0)
        {
            printf("Error: Email can't be empty.\n\n");
            isValidEmail=0;
        }
        else if (alreadyExists(newEmail, 'e', studentId)>0)
        {
            printf("Error: This Email already exists.\n\n");
            isValidEmail=0;
        }
        else
        {
            isValidEmail=1;
        }
    }

    int isValidPhone=0;
    while (!isValidPhone)
    {
        printf("Enter the new Phone(0 for skip): ");
        scanf("%s", &newPhone);
        if (strlen(newPhone)>20)
        {
            printf("Error: Phone number can't be more than 20 characters.\n\n");
            isValidPhone=0;
        }
        else if (strlen(newPhone)<=0)
        {
            printf("Error: Phone number can't be empty.\n\n");
            isValidPhone=0;
        }
        else if (alreadyExists(newPhone, 'p', studentId)>0)
        {
            printf("Error: This Phone number already exists.\n\n");
            isValidPhone=0;
        }
        else
        {
            isValidPhone=1;
        }
    }

    int isValidNoOfCourse=0;
    while (!isValidNoOfCourse)
    {
        printf("Enter no. of New courses(0 for skip): ");
        scanf("%d", &newNumberOfCourses);
        
        if (newNumberOfCourses > 4 || newNumberOfCourses < 0)
        {
            printf("Error: A student can have maximum 4 & minimum 0 no. of courses.\n\n");
            isValidNoOfCourse=0;
        }
        else
        {
            isValidNoOfCourse=1;
        }
    }
    
    if (strcmp(newName, "0") != 0)
    {
        strcpy(students[studentFoundIndex].name, newName);
    }

    if (strcmp(newEmail, "0") != 0)
    {
        strcpy(students[studentFoundIndex].email, newEmail);
    }

    if (strcmp(newPhone, "0") != 0)
    {
        strcpy(students[studentFoundIndex].phone, newPhone);
    }
    if (newNumberOfCourses != 0)
    {
        int OldTotalCourse = students[studentFoundIndex].numberOfCourses;
        students[studentFoundIndex].numberOfCourses =  newNumberOfCourses;

        int  firstCourseIndex;
        int delcourseIndex;
        for ( delcourseIndex = 0; delcourseIndex < TotalCourses; delcourseIndex++)
        {
            if (strcmp(studentId, courses[delcourseIndex].studentId)==0)
            {
                firstCourseIndex=delcourseIndex;
                break;
            }
        }

        for ( delcourseIndex = 1; delcourseIndex <= TotalCourses; delcourseIndex++)
        {
            delCourseByIndex(firstCourseIndex);
        }
        
        char courseCode[300];
        char courseName[300];
        for ( i = 1; i < newNumberOfCourses; i++)
        {
            printf("Enter new course %d code: ", i);
            scanf("%s", &courseCode);
            printf("Enter new name %d code: ", i);
            scanf("%s", &courseName);

            strcpy(courses[TotalCourses].studentId, studentId);
            strcpy(courses[TotalCourses].code, courseCode);
            strcpy(courses[TotalCourses].name, courseName);
            TotalCourses++;
        }
    }

    printf("Student updated successfully.\n\n");
}

void delStudent(int studentIndex){
    int d;
    int FirstCourseIndex;
    struct studentInfo thisStudents;
    thisStudents = students[studentIndex];
    for ( d = 0; d < TotalCourses; d++)
    {
        if (strcmp(thisStudents.id, courses[d].studentId)==0)
        {
            FirstCourseIndex=d;
            break;
        }
    }
    for ( d = 0; d <= thisStudents.numberOfCourses; d++)
    {
        delCourseByIndex(FirstCourseIndex);
    }
    delStudentByIndex(studentIndex);
    printf("Student deleted Successfully.\n\n");
    goBackOrExit();
}

void delAllStudents(){
    TotalStudents=0;
    TotalCourses=0;
    printf("All students deleted successfully.\n\n");
    goBackOrExit();
}

void delCourseByIndex(int courseIndex){
    int c;
    for ( c = 0; c < TotalCourses-1; c++)
    {
        if(c>=courseIndex){
            courses[c] = courses[c+1];
        }
    }
    TotalCourses--;
}

void delStudentByIndex(int courseIndex){
    int s;
    for ( s = 0; s < TotalStudents-1; s++)
    {
        if (s>=courseIndex)
        {
            students[s] = students[s+1];
        }
    }
    TotalStudents--;
}


void errorAndRestart(char *error[100]){
    printf("%s\n", error);
    int i=0;
    printf("Restarting the program: ");
    for ( i = 0; i < 10; i++)
    {
        printf(".");
        Sleep(500);
    }
    system("cls");
    main();
}


void userGuidelines(){
    printf("\n\t\t****HOW IT WORKS?****\n\n");
    printf("--> You will only able to store the Studengt's ID, Name, Email, Phone, Number of courses.\n");           
    printf("--> A Student can have maximum 4 courses & minimum 1 course.\n");
    printf("--> Student ID can be maximum 10 characters long & unique for every student.\n");                     
    printf("--> Student Name can be maximum 20 characters long.\n");
    printf("--> Student Email can be maximum 30 characters long & unique for every student.\n");
    printf("--> Student Phone number can be maximum 10 characters long & unique for every student.\n");
    printf("--> Course code can be maximum 10 characters long.\n");
    printf("--> Course namw can be maximum 20 characters long.\n");
    printf("->> Visit www.studentManagement.com for more info. <<-\n\n ");
}


void aboutUs(){
    printf("\n\t\t**** ABOUT US ****\n");
    printf("Some important notes that we should remember:-");
    printf("--> This is a simple student management system project.\n");
    printf("--> You can modify the source code.\n");
    printf("--> You can use this project only for personal purpose not for business.\n\n");
    printf("->> Visit www.studentManagement.com for more info. <<-\n\n ");
}


void exitProject(){
    system("cls");
    int i;
    char thanku[100]="======================THANK YOU======================\n";
    for (int i = 0; i < strlen(thanku); i++)
    {
        printf("%c", thanku[i]);
        Sleep(40);
    }
    exit(0);
}


void goBackOrExit(){
    getchar();
    char option;
    printf("Go back(b)? or Exit(0)?: ");
    scanf("%c", &option);
    if (option == '0')
    {
        exitProject();
    }
    else{
        system("cls");
    }
}


void dataSeed(){
    strcpy(students[0].id, "S-1");
    strcpy(students[0].name, "Student-1");
    strcpy(students[0].phone, "1234567890");
    strcpy(students[0].email, "student-1@gmail.com");
    students[0].numberOfCourses=1;
    strcpy(courses[0].studentId, "S-1");
    strcpy(courses[0].code, "CSE-1");
    strcpy(courses[0].name, "Course-1");

    strcpy(students[1].id, "S-2");
    strcpy(students[1].name, "Student-2");
    strcpy(students[1].phone, "2234567890");
    strcpy(students[1].email, "student-2@gmail.com");
    students[1].numberOfCourses=2;
    strcpy(courses[1].studentId, "S-2");
    strcpy(courses[1].code, "CSE-1");
    strcpy(courses[1].name, "Course-1");
    strcpy(courses[2].studentId, "S-2");
    strcpy(courses[2].code, "CSE-2");
    strcpy(courses[2].name, "Course-2");

    strcpy(students[2].id, "S-3");
    strcpy(students[2].name, "Student-3");
    strcpy(students[2].phone, "1234567890");
    strcpy(students[2].email, "student-3@gmail.com");
    students[2].numberOfCourses=3;
    strcpy(courses[3].studentId, "S-3");
    strcpy(courses[3].code, "CSE-1");
    strcpy(courses[3].name, "Course-1");
    strcpy(courses[4].studentId, "S-3");
    strcpy(courses[4].code, "CSE-2");
    strcpy(courses[4].name, "Course-2");
    strcpy(courses[5].studentId, "S-3");
    strcpy(courses[5].code, "CSE-3");
    strcpy(courses[5].name, "Course-3");

    TotalStudents=3;
    TotalCourses=6;

}