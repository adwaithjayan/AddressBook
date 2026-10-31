# Address Book Management System
![Build](https://github.com/YOUR-USERNAME/AddressBook/actions/workflows/build.yml/badge.svg)

A command-line **Address Book Management System built with C**. It allows users to create, search, edit, delete, and display contacts through a simple menu-driven interface. Contact information is stored in a CSV file so it can be loaded again when the program starts.

## Features

- Create contacts with a name, phone number, and email address.
- Search for contacts by name, phone number, or email address.
- Edit existing contact details.
- Delete contacts.
- Display all saved contacts in a formatted table.
- Validate user input and check for duplicate phone numbers and email addresses.
- Load contacts from and save contacts to `addressBook.csv`.

## Input validation

- Names must begin with an alphabetic character.
- Phone numbers must contain exactly 10 digits and start with a digit from `6` to `9`.
- Email addresses are converted to lowercase, must begin with an alphabetic character, and must end in `.com`.
- Phone numbers and email addresses must be unique.

## Screenshots

### Main menu

![Address Book main menu](screenshots/main-menu.png)

### Contact list

![Address Book contact list](screenshots/contact-list.png)


## Project structure

```text
AddressBook/
├── main.c              # Application entry point and main menu
├── contact.c           # Create, search, edit, delete, and list contacts
├── contact.h           # Contact structures and declarations
├── utils.c             # Input validation and helper functions
├── utils.h             # Utility function declarations
├── file.c              # CSV file loading and saving
├── file.h              # File-handling declarations
├── addressBook.csv     # Contact data
└── screenshots/        # Project interface screenshots
```

## Requirements

- GCC compiler (or another C compiler)
- Terminal or command prompt

## Build and run

Clone the repository:

```bash
git clone https://github.com/YOUR-USERNAME/AddressBook.git
cd AddressBook
```

Compile the source files:

```bash
gcc main.c contact.c utils.c file.c -o addressbook
```

Run the program:

**Linux / macOS**

```bash
./addressbook
```

**Windows**

```bash
addressbook.exe
```

> Run the program from the project directory so it can access `addressBook.csv`. Select **Save and Exit** from the menu to save the contact data.

## Data storage

Contacts are stored in `addressBook.csv`. The application loads the saved contacts when it starts and writes the contact data back to the file when you choose **Save and Exit**.

## Concepts used

- Structures and arrays
- Functions and modular programming
- String handling
- Input validation
- Searching, editing, and deleting records
- File handling using standard C file I/O

## Author

**Adwaith**
