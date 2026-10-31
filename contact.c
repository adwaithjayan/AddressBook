#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "contact.h"
#include "utils.h"
#include "file.h"

// Displays all contacts in a formatted table.
void listContacts(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printBox("No contacts available.");
        return;
    }

    printf("\n");
    printf("+------+----------------------+------------+--------------------------------+\n");
    printf("| %-4s | %-20s | %-10s | %-30s |\n", "No.", "Name", "Phone", "Email");
    printf("+------+----------------------+------------+--------------------------------+\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("| %-4d | %-20.20s | %-10.10s | %-30.30s |\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);

        printf("+------+----------------------+------------+--------------------------------+\n");
    }
}

// Initializes the address book and loads saved contacts from the file.
void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;

    loadContactsFromFile(addressBook);
}

// Saves the current contacts to a file before terminating the program.
void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

// Validates user input and adds a new contact if all fields are valid and unique.
void createContact(AddressBook *addressBook)
{
    if (addressBook->contactCount >= 100)
    {
        printf("\n+----------------------------------+\n");
        printf("|       Address Book Is Full       |\n");
        printf("+----------------------------------+\n");
        return;
    }
    char name[50];
    char email[50];
    char phone[20];
    int attempt = 3;

    while (attempt > 0)
    {
        printf("Enter Name: ");
        scanf(" %49[^\n]", name);

        if (validName(name))
        {
            break;
        }

        attempt--;

        if (attempt == 0)
            printBox("Maximum attempts reached.");
    }
    if (attempt == 0)
        return;

    attempt = 3;

    while (attempt > 0)
    {
        printf("Enter Phone number: ");
        scanf("%19s", phone);
        if (validPhone(phone) && uniqPhone(addressBook, phone))
        {
            break;
        }
        attempt--;
        if (attempt == 0)
            printBox("Maximum attempts reached.");
    }
    if (attempt == 0)
        return;

    attempt = 3;
    while (attempt > 0)
    {
        printf("Enter Email address: ");
        scanf("%49s", email);
        if (validEmail(email) && uniqEmail(addressBook, email))
        {
            break;
        }
        attempt--;
        if (attempt == 0)
            printBox("Maximum attempts reached.");
    }
    if (attempt == 0)
        return;

    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);
    addressBook->contactCount++;

    printf("\n+----------------------------------+\n");
    printf("|    Contact Created Successfully  |\n");
    printf("+----------------------------------+\n");
}

// Displays the search menu and calls the selected search function.
void searchContact(AddressBook *addressBook)
{
    int choice = 0;

    do
    {
        printBox("Search Menu");
        printf("[1] Search by name\n");
        printf("[2] Search by phone\n");
        printf("[3] Search by email\n");
        printf("[4] Exit\n");
        printf("Enter the choice: ");
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
            searchByName(addressBook);
            break;

        case 2:
            searchByPhone(addressBook);
            break;

        case 3:
            searchByEmail(addressBook);
            break;

        case 4:
            printf("Exiting Search Menu\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 4);
}

// Allows the user to search for a contact and edit its details.
void editContact(AddressBook *addressBook)
{
    int choice = 0, sl;

    do
    {
        printBox("Search For Edit");
        printf("[1] Search by name\n");
        printf("[2] Search by phone\n");
        printf("[3] Search by email\n");
        printf("[4] Exit\n");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid choice. Please try again.\n");

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
            searchByName(addressBook);
            edit(addressBook, 1);
            break;

        case 2:
            searchByPhone(addressBook);
            edit(addressBook, 0);
            break;

        case 3:
            searchByEmail(addressBook);
            edit(addressBook, 0);
            break;

        case 4:
            printf("Exiting Search Menu\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 4);
}

// Allows the user to search for a contact and delete it.
void deleteContact(AddressBook *addressBook)
{
    int choice = 0, sl;

    do
    {
        printBox("Search For Delete");
        printf("[1] Search by name\n");
        printf("[2] Search by phone\n");
        printf("[3] Search by email\n");
        printf("[4] Exit\n");
        printf("Enter the choice: ");

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
            searchByName(addressBook);
            delete(addressBook, 1);

            break;

        case 2:
            searchByPhone(addressBook);
            delete(addressBook, 0);

            break;

        case 3:
            searchByEmail(addressBook);
            delete(addressBook, 0);

            break;

        case 4:
            printf("Exiting Search Menu\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 4);
}
