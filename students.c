#include "students.h"

Student *head = NULL;

void addStudent()
{
    Student *s1 = (Student*)malloc(sizeof(Student));

    if (s1 == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    s1->name = malloc(100 *sizeof(char));
    s1->branchName = malloc(100 *sizeof(char));

    if (s1->name == NULL || s1->branchName == NULL)
    {
        printf("Memory allocation for strings failed\n");
        free(s1);
        return;
    }

    printf("Enter roll: ");
    scanf("%d", &s1->roll);
    getchar();

    printf("Enter name: ");
    fgets(s1->name, 100, stdin);
    s1->name[strcspn(s1->name, "\n")] = '\0';

    printf("Enter branch name: ");
    fgets(s1->branchName, 100, stdin);
    s1->branchName[strcspn(s1->branchName, "\n")] = '\0';

    printf("Enter batch: ");
    scanf("%d", &s1->batch);

    s1->next = head;
    head = s1;

    // save data to a file

    FILE *file = fopen("students.csv", "a");
    if (file == NULL)
    {
        printf("Could not open file for writing");
        return;
    }

    fprintf(file, "%d,%s,%s,%d\n", s1->roll, s1->name, s1->branchName, s1->batch);
    fclose(file);
}

void allStudents()
{
    FILE *file = fopen("students.csv", "r");

    if(file == NULL)
    {
        printf("Could not open file for reading");
        return;
    }

    int roll, batch;
    char name[100], branchName[100];
    char line[256];

    printf("=========================================================================\n");
    printf("| %-10s | %-20s | %-20s | %-10s |\n", "Roll", "Name", "Branch", "Batch");
    printf("=========================================================================\n");

    // Print data
    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%d,%99[^,],%99[^,],%d", &roll, name, branchName, &batch);
        printf("| %-10d | %-20s | %-20s | %-10d |\n", roll, name, branchName, batch);
    }

    // Print footer
    printf("=========================================================================\n");
    fclose(file);
}

void updateStudent()
{
    int roll, found = 0;
    printf("Enter roll number of student to update: ");
    scanf("%d", &roll);
    getchar();

    FILE *file = fopen("students.csv", "r+");
    if (file == NULL)
    {
        printf("Could not open file for reading and writing");
        return;
    }

    FILE *tempFile = fopen("temp.csv", "w");
    if (tempFile == NULL)
    {
        printf("Could not open temporary file for writing");
        fclose(file);
        return;
    }


    int tempRoll, tempBatch;
    char tempName[100], tempBranchName[100];
    char line[256];

    while (fgets(line, sizeof(line),file))
    {
        sscanf(line, "%d, %99[^,],%99[^,],%d",&tempRoll, tempName, tempBranchName, &tempBatch);

        if(tempRoll == roll)
        {
            found = 1;
            printf("\n\n[Found] Roll No: %d\n", tempRoll);
            printf("Name: %s\n", tempName);
            printf("Branch Name: %s\n", tempBranchName);
            printf("batch: %d\n", tempBatch);

            printf("\nEnter new name: ");
            fgets(tempName, 100, stdin);
            tempName[strcspn(tempName, "\n")] = '\0';

            printf("Enter new branch name: ");
            fgets(tempBranchName, 100, stdin);
            tempBranchName[strcspn(tempBranchName, "\n")] = '\0';

            printf("Enter new batch: ");
            scanf("%d", &tempBatch);
            getchar();

            fprintf(tempFile, "%d,%s,%s,%d\n", tempRoll, tempName, tempBranchName, tempBatch);
        }
        else
        {
            fprintf(tempFile, "%d,%s,%s,%d\n", tempRoll, tempName, tempBranchName, tempBatch);

        }
    }
    

    if(!found)
    {
        printf("Student with roll number %d not found\n", roll);
    }  
    else
    {
        printf("Student update is successful\n");
    }

    fclose(file);
    fclose(tempFile);

    remove("students.csv");
    rename("temp.csv","students.csv");
}

void deleteStudents()
{
    int roll, found = 0;
    printf("Enter roll number of student to delete: ");
    scanf("%d", &roll);
    getchar();

    FILE *file = fopen("students.csv", "r");
    if(file == NULL)
    {
        printf("Could not open file for reading\n");
        return;
    }

    FILE *tempFile = fopen("temp.csv", "w");
    if(tempFile == NULL)
    {
        printf("Could not open temporary file for writing\n");
        fclose(file);
        return;
    }

    int tempRoll, tempBatch;
    char tempName[100], tempBranchName[100];
    char line[256];

    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%d,%99[^,],%99[^,],%d", &tempRoll,tempName,tempBranchName,&tempBatch);

        if (tempRoll == roll)
        {
            found = 1;
            printf("\n[Found and Deleted] Roll No: %d\n", tempRoll);
            printf("Name: %s\n", tempName);
            printf("Branch Name: %s\n", tempBranchName);
            printf("Batch: %d\n", tempBatch);
        }
        else
        {
            fprintf(tempFile, "%d,%s,%s,%d\n", tempRoll, tempName, tempBranchName, tempBatch);
        }
    }
    
    if (!found)
    {
        printf("Student with roll number %d not found\n", roll);
    }
    else
    {
        printf("Student deletion is successful\n");
    }

    fclose(file);
    fclose(tempFile);

    remove("students.csv");
    rename("temp.csv", "students.csv");
}