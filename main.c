//------------ Address Book Management System using  C-----------------------//

// Auther  Adwaith jayan

// The Address Book Management System is a menu - driven C application that allows users to create,
// search, edit, delete, and display contacts.Each contact contains a name, phone number, and email address.
// The project uses structures, arrays, and functions to organize contact information,
// along with input validation and duplicate checking to maintain data accuracy.File handling is implemented to save and load contact details,
// allowing data to persist between program executions.
//

#include <stdio.h>
#include "contact.h"
#include "utils.h"

int main()
{
    int choice = 0;
    AddressBook addressBook;
    initialize(&addressBook);

    do
    {
        printf("\n");
        printBox("Address Book Menu");
        printf("[1] Create contact\n");
        printf("[2] Search contact\n");
        printf("[3] Edit contact\n");
        printf("[4] Delete contact\n");
        printf("[5] List all contacts\n");
        printf("[6] Save and Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printBox("Invalid choice. Please try again.");

            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;

            if (ch == EOF)
                break;

            continue;
        }

        switch (choice)
        {
        case 1:
            createContact(&addressBook);
            break;
        case 2:
            searchContact(&addressBook);
            break;
        case 3:
            editContact(&addressBook);
            break;
        case 4:
            deleteContact(&addressBook);
            break;
        case 5:
            listContacts(&addressBook);
            break;
        case 6:
            printBox("Saving and Exiting...");
            saveContactsToFile(&addressBook);
            break;
        default:
            printBox("Invalid choice. Please try again.");
        }
    } while (choice != 6);

    return 0;
}
