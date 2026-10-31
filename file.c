#include <stdio.h>
#include "file.h"
#include "utils.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp = fopen("addressBook.csv", "w");
    if (fp == NULL)
    {
        printBox("Error opening file!");
        return;
    }

    fprintf(fp, "#%d\n", addressBook->contactCount);
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    fclose(fp);
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen("addressBook.csv", "r");
    if (fp == NULL)
    {
        printBox("Error opening file!");
        return;
    }
    fscanf(fp, "#%d\n", &(addressBook->contactCount));

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fp, "%[^,],%[^,],%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    fclose(fp);
}
