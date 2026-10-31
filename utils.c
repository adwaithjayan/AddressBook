// Most of user defined funtions are in this file.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "contact.h"
#include "utils.h"

// Stores the original indexes of contacts found during a search.
int foundNames[100], found = 0, k = 0;

// Validates whether the contact name starts with an alphabet.
int validName(char name[])
{
    if (isalpha(name[0]) == 0)
    {
        printBox("The first letter must be alphabet");
        return 0;
    }
    return 1;
}

// Validates the phone number length, starting digit, and digit-only content.
int validPhone(char phone[])
{
    if (strlen(phone) != 10)
    {
        printBox("Phone number must have 10 digits");
        return 0;
    }
    else if (!(phone[0] >= '6' && phone[0] <= '9'))
    {
        printBox("Start digit must be within range of 6 and 9");
        return 0;
    }
    else if (strspn(phone, "0123456789") != strlen(phone))
    {
        printBox("Phone number only contain digits");
        return 0;
    }

    return 1;
}

// Converts the email to lowercase and validates its format.
int validEmail(char email[])
{
    int i = 0;
    int at = 0;
    int atPos = -1;
    int lastDot = -1;

    while (email[i] != '\0')
    {
        email[i] = tolower(email[i]);
        i++;
    }

    i = 0;

    if (!isalpha(email[0]))
    {
        printBox("Email must start with alphabet");
        return 0;
    }

    while (email[i] != '\0')
    {
        if (email[i] == '@')
        {
            if (at == 1)
            {
                printBox("Email must contain exactly one @ symbol");
                return 0;
            }

            at = 1;
            atPos = i;
        }
        else if (email[i] == '.' && at == 1)
        {
            lastDot = i;
        }

        i++;
    }

    if (at == 0)
    {
        printBox("Email must contain @ symbol");
        return 0;
    }

    int len = strlen(email);

    if (len < 5 || strcmp(&email[len - 4], ".com") != 0)
    {
        printBox("Email must end with .com");
        return 0;
    }

    if (lastDot <= atPos + 1)
    {
        printBox("Domain name must contain characters before the dot");
        return 0;
    }

    for (i = atPos + 1; i < len - 4; i++)
    {
        if (email[i] == '.')
        {
            if (i == atPos + 1 || email[i - 1] == '.')
            {
                printBox("Invalid dot placement in domain");
                return 0;
            }
        }
        else if (!isalpha(email[i]))
        {
            printBox("Domain must contain only alphabets and dots");
            return 0;
        }
    }

    if (email[len - 5] == '.')
    {
        printBox("Invalid domain name");
        return 0;
    }

    return 1;
}

// Checks whether the phone number already exists in the address book.
int uniqPhone(AddressBook *addressBook, char phone[])
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            printBox("The number already exist in the AddressBook");
            return 0;
        }
    }

    return 1;
}

// Checks whether the email already exists in the address book.
int uniqEmail(AddressBook *addressBook, char email[])
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0)
        {
            printBox("The email already exist in the AddressBook");
            return 0;
        }
    }

    return 1;
}

// Searches for exact name matches and stores their original array indexes.
void searchByName(AddressBook *addressBook)
{
    char name[50];

    int attempt = 3;

    while (attempt > 0)
    {
        printf("Enter Name: ");
        scanf(" %49[^\n]", name);

        if (validName(name))
        {
            // Resets the search result status before starting a new search.
            found = 0;
            k = 0;

            for (int i = 0; i < addressBook->contactCount; i++)
            {
                // Checks whether the stored name exactly matches the entered name.
                if (strcmp(addressBook->contacts[i].name, name) == 0)
                {
                    if (!found)
                    {
                        printf("\n");
                        printf("+------+----------------------+------------+--------------------------------+\n");
                        printf("| %-4s | %-20s | %-10s | %-30s |\n", "No.", "Name", "Phone", "Email");
                        printf("+------+----------------------+------------+--------------------------------+\n");
                    }
                    printf("| %-4d | %-20.20s | %-10.10s | %-30.30s |\n", k + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);

                    printf("+------+----------------------+------------+--------------------------------+\n");
                    found = 1;
                    // Stores the original array index of the matching contact.
                    foundNames[k++] = i;
                }
            }

            // Displays a message when no matching contact is found.
            if (!found)
            {

                printf("\n+----------------------------------+\n");
                printf("|          Name not Found          |\n");
                printf("+----------------------------------+\n");
            }
            break;
        }

        attempt--;

        if (attempt == 0)
            printBox("Maximum attempts reached.");
    }
    if (attempt == 0)
        return;
}

// Searches for a contact using an exact phone number.
void searchByPhone(AddressBook *addressBook)
{
    char phone[20];

    int attempt = 3;

    while (attempt > 0)
    {
        printf("Enter Number: ");
        scanf(" %29[^\n]", phone);

        if (validPhone(phone))
        {
            found = 0;

            for (int i = 0; i < addressBook->contactCount; i++)
            {
                // Checks whether the stored number exactly matches the entered number.
                if (strcmp(addressBook->contacts[i].phone, phone) == 0)
                {
                    if (!found)
                    {

                        printf("\n");
                        printf("+------+----------------------+------------+--------------------------------+\n");
                        printf("| %-4s | %-20s | %-10s | %-30s |\n", "No.", "Name", "Phone", "Email");
                        printf("+------+----------------------+------------+--------------------------------+\n");
                    }
                    printf("| %-4d | %-20.20s | %-10.10s | %-30.30s |\n", 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);

                    printf("+------+----------------------+------------+--------------------------------+\n");
                    found = 1;
                    foundNames[0] = i;
                    break;
                }
            }
            if (!found)
            {

                printf("\n+----------------------------------+\n");
                printf("|       Phone number not Found     |\n");
                printf("+----------------------------------+\n");
            }
            break;
        }

        attempt--;

        if (attempt == 0)
            printBox("Maximum attempts reached.");
    }
    if (attempt == 0)
        return;
}

// Searches for a contact using an exact email address.
void searchByEmail(AddressBook *addressBook)
{
    char email[50];

    int attempt = 3;

    while (attempt > 0)
    {
        printf("Enter Email: ");
        scanf(" %49[^\n]", email);

        if (validEmail(email))
        {
            // Resets the search result status before starting a new search.
            found = 0;

            for (int i = 0; i < addressBook->contactCount; i++)
            {
                // Checks whether the stored email exactly matches the entered email.
                if (strcmp(addressBook->contacts[i].email, email) == 0)
                {

                    if (!found)
                    {
                        printf("\n");
                        printf("+------+----------------------+------------+--------------------------------+\n");
                        printf("| %-4s | %-20s | %-10s | %-30s |\n", "No.", "Name", "Phone", "Email");
                        printf("+------+----------------------+------------+--------------------------------+\n");
                    }

                    printf("| %-4d | %-20.20s | %-10.10s | %-30.30s |\n", 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);

                    printf("+------+----------------------+------------+--------------------------------+\n");
                    found = 1;
                    foundNames[0] = i;
                    break;
                }
            }
            if (!found)
            {

                printf("\n+----------------------------------+\n");
                printf("|          Email not Found         |\n");
                printf("+----------------------------------+\n");
            }
            break;
        }

        attempt--;

        if (attempt == 0)
            printBox("Maximum attempts reached.");
    }
    if (attempt == 0)
        return;
}

// Validates and updates the selected contact's name.
void editName(AddressBook *addressBook, int choice)
{

    int attempt = 3;
    char name[50];

    while (attempt > 0)
    {
        printf("Enter Name: ");
        scanf(" %49[^\n]", name);

        if (validName(name))
        {
            strcpy(addressBook->contacts[choice].name, name);

            printf("\n+----------------------------------+\n");
            printf("|    Contact Edited Successfully  |\n");
            printf("+----------------------------------+\n");
            break;
        }

        attempt--;

        if (attempt == 0)
            printBox("Maximum attempts reached.");
    }
    if (attempt == 0)
        return;
}

// Validates and updates the selected contact's phone number.
void editPhone(AddressBook *addressBook, int choice)
{

    int attempt = 3;
    char phone[20];

    while (attempt > 0)
    {
        printf("Enter Phone number: ");
        scanf(" %19[^\n]", phone);

        if (!uniqPhone(addressBook, phone))
        {

            printf("\n+----------------------------------+\n");
            printf("|        Number already Exist      |\n");
            printf("+----------------------------------+\n");
            return;
        }

        if (validPhone(phone))
        {
            strcpy(addressBook->contacts[choice].phone, phone);

            printf("\n+----------------------------------+\n");
            printf("|    Contact Edited Successfully  |\n");
            printf("+----------------------------------+\n");
            break;
        }

        attempt--;

        if (attempt == 0)
            printBox("Maximum attempts reached.");
    }
    if (attempt == 0)
        return;
}

// Validates and updates the selected contact's email address.
void editEmail(AddressBook *addressBook, int choice)
{

    int attempt = 3;
    char email[50];

    while (attempt > 0)
    {
        printf("Enter Email: ");
        scanf(" %49[^\n]", email);

        if (!uniqEmail(addressBook, email))
        {

            printf("\n+----------------------------------+\n");
            printf("|        Email already Exist      |\n");
            printf("+----------------------------------+\n");
            return;
        }

        if (validEmail(email))
        {
            strcpy(addressBook->contacts[choice].email, email);

            printf("\n+----------------------------------+\n");
            printf("|    Contact Edited Successfully  |\n");
            printf("+----------------------------------+\n");
            break;
        }

        attempt--;

        if (attempt == 0)
            printBox("Maximum attempts reached.");
    }
    if (attempt == 0)
        return;
}

// Displays edit options and calls the function for the selected field.
void edit(AddressBook *addressBook, int byname)
{
    int c, sl = 1;

    // Prevents editing when the previous search returned no results.
    if (!found)
        return;
    if (byname == 1)
    {
        sl = getSerialNumber(k);

        if (sl == -1)
        {
            return;
        }
    }

    do
    {
        printBox("Edit Options");
        printf("[1] Edit Name\n");
        printf("[2] Edit Phone Number\n");
        printf("[3] Edit Email\n");
        printf("[4] Exit\n");

        printf("Enter the choice: ");

        if (scanf("%d", &c) != 1)
        {
            int ch;

            while ((ch = getchar()) != '\n' && ch != EOF)
                ;

            if (ch == EOF)
                return;

            printBox("Invalid choice. Please try again.");
            continue;
        }

        // Executes the editing operation selected by the user.
        switch (c)
        {
        case 1:
            editName(addressBook, foundNames[sl - 1]);
            break;

        case 2:
            editPhone(addressBook, foundNames[sl - 1]);
            break;

        case 3:
            editEmail(addressBook, foundNames[sl - 1]);
            break;

        case 4:
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (c != 4);
}

// Deletes the selected contact and shifts the remaining contacts.
void delete(AddressBook *addressBook, int byname)
{
    int sl = 1;
    char ch;

    // Prevents deletion when no contact was found.
    if (!found)
        return;
    if (byname == 1)
    {
        sl = getSerialNumber(k);

        if (sl == -1)
        {
            return;
        }
    }

    printBox("conform deletion Yes(y)/No(n)");
    scanf(" %c", &ch);

    if (ch == 'y')
    {

        // Shifts subsequent contacts left to fill the deleted contact's position.
        for (int i = foundNames[sl - 1]; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }
        // Decreases the contact count after successful deletion.
        addressBook->contactCount--;

        printf("\n+----------------------------------+\n");
        printf("|    Contact Deleted Successfully  |\n");
        printf("+----------------------------------+\n");
    }
    else
    {

        printBox("Canceled deletation.");
        return;
    }
}

// Prints a message inside a dynamically sized text box.
void printBox(char message[])
{
    // Calculates the message length to determine the box width.
    int len = strlen(message);
    int width = len + 10;
    int padding = (width - len) / 2;

    printf("+");
    // Prints the horizontal border of the message box.
    for (int i = 0; i < width; i++)
        printf("-");
    printf("+\n");

    printf("|");
    for (int i = 0; i < padding; i++)
        printf(" ");

    // Prints the message inside the box.
    printf("%s", message);

    for (int i = 0; i < width - padding - len; i++)
        printf(" ");

    printf("|\n");

    printf("+");
    for (int i = 0; i < width; i++)
        printf("-");
    printf("+\n");
}

// funtion for validation serial number;
int getSerialNumber(int maxSerial)
{
    int sl;
    int atm = 3;

    do
    {
        printf("Enter the SL number: ");

        if (scanf("%d", &sl) != 1)
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
            if (ch == EOF)
                return -1;
            ;
            printBox("Invalid Serial.");
            atm--;
            continue;
        }

        if (sl < 1 || sl > maxSerial)
        {
            printBox("Invalid Serial.");
            atm--;
        }
        else
        {
            return sl;
        }

    } while (atm > 0);

    return -1;
}