#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.txt"

typedef struct {
    char name[50];
    int roll;
    char course[50];
    float marks;
} Student;

void add_student() {
    FILE *file = fopen(FILE_NAME, "a");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    
    Student s;
    printf("Enter Name: ");
    scanf(" %s", s.name);
    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);
    printf("Enter Course: ");
    scanf(" %s", s.course);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);
    
    fprintf(file, "%s %d %s %.2f\n", s.name, s.roll, s.course, s.marks);
    fclose(file);
    printf("Student added successfully!\n");
}

void view_students() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No student records found.\n");
        return;
    }
    
    printf("\n%-20s %-10s %-20s %-10s\n", "Name", "Roll No", "Course", "Marks");
    printf("----------------------------------------------------------\n");
    
    Student s;
    while (fscanf(file, "%49s %d %49s %f", s.name, &s.roll, s.course, &s.marks) != EOF) {
        printf("%-20s %-10d %-20s %-10.2f\n", s.name, s.roll, s.course, s.marks);
    }
    fclose(file);
}

void search_student() {
    int roll;
    printf("Enter Roll Number to Search: ");
    scanf("%d", &roll);
    
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No student records found.\n");
        return;
    }
    
    Student s;
    int found = 0;
    while (fscanf(file, "%49s %d %49s %f", s.name, &s.roll, s.course, &s.marks) != EOF) {
        if (s.roll == roll) {
            printf("\nStudent Found:\n");
            printf("Name: %s\nRoll No: %d\nCourse: %s\nMarks: %.2f\n", s.name, s.roll, s.course, s.marks);
            found = 1;
            break;
        }
    }
    fclose(file);
    if (!found) printf("Student not found.\n");
}

void delete_student() {
    int roll;
    printf("Enter Roll Number to Delete: ");
    scanf("%d", &roll);
    
    FILE *file = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!file || !temp) {
        printf("Error opening file!\n");
        return;
    }
    
    Student s;
    int found = 0;
    while (fscanf(file, "%49s %d %49s %f", s.name, &s.roll, s.course, &s.marks) != EOF) {
        if (s.roll == roll) {
            found = 1;
            continue;
        }
        fprintf(temp, "%s %d %s %.2f\n", s.name, s.roll, s.course, s.marks);
    }
    fclose(file);
    fclose(temp);
    
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
    
    if (found)
        printf("Student deleted successfully!\n");
    else
        printf("Student not found.\n");
}

int main() {
    int choice;
    do {
        printf("\n==== Student Management System ===="
               "\n1. Add Student"
               "\n2. View Students"
               "\n3. Search Student"
               "\n4. Delete Student"
               "\n5. Exit"
               "\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: add_student(); break;
            case 2: view_students(); break;
            case 3: search_student(); break;
            case 4: delete_student(); break;
            case 5: printf("Exiting program.\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);
    
    return 0;
}
