#ifndef UTILS_H
#define UTILS_H

int validName(char name[]);

int validPhone(char phone[]);

int validEmail(char email[]);

int uniqEmail(AddressBook *addressBook, char email[]);

int uniqPhone(AddressBook *addressBook, char phone[]);

void searchByName(AddressBook *addressBook);

void searchByPhone(AddressBook *addressBook);

void searchByEmail(AddressBook *addressBook);

void editName(AddressBook *addressBook, int choice);

void editPhone(AddressBook *addressBook, int choice);

void editEmail(AddressBook *addressBook, int choice);

void edit(AddressBook *addressBook, int sl);

void delete (AddressBook *addressBook, int byname);

void printBox(char message[]);

int getSerialNumber(int maxSerial);

#endif
