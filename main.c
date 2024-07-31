#include "students.h"

int main()
{   
    int choice, yesORNo;
    do
    { 

        printf("Enter choice: \n1.Add Student\n2.Edit Student Info\n3.All Students\n4.Delete Student\n");
        scanf("%d", &choice);

        getchar();


       switch (choice)
       {
            case 1:
                addStudent();
            break;
            case 2:
                updateStudent();
                break;
            case 3:
                allStudents();
            break;
            case 4:
                deleteStudents();
                break;
       
            default:
            break;
       }

        printf("Do you want to continue (1) ?\n");
        scanf("%d", &yesORNo);
        
    } while (yesORNo);
    
    

    return 0;
}
