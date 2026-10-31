#include <stdio.h>
#include <string.h>
#include "contact.h"
#include "utils.h"

static int tests_run = 0;
static int tests_failed = 0;

#define CHECK(description, condition)                               \
    do                                                              \
    {                                                               \
        tests_run++;                                                \
        if (condition)                                              \
        {                                                           \
            printf("[PASS] %s\n", description);                     \
        }                                                           \
        else                                                        \
        {                                                           \
            printf("[FAIL] %s (line %d)\n", description, __LINE__); \
            tests_failed++;                                         \
        }                                                           \
    } while (0)

static void test_valid_name(void)
{
    char valid[] = "Adwaith";
    char invalid[] = "1Adwaith";
    char empty[] = "";

    CHECK("Name beginning with an alphabet is valid", validName(valid));
    CHECK("Name beginning with a digit is invalid", !validName(invalid));
    CHECK("Empty name is invalid", !validName(empty));
}

static void test_valid_phone(void)
{
    char valid[] = "9876543210";
    char invalid_length[] = "98765";
    char invalid_start[] = "5123456789";
    char invalid_chars[] = "98765abc10";

    CHECK("10-digit phone beginning with 6-9 is valid", validPhone(valid));
    CHECK("Phone with incorrect length is invalid", !validPhone(invalid_length));
    CHECK("Phone beginning below 6 is invalid", !validPhone(invalid_start));
    CHECK("Phone containing letters is invalid", !validPhone(invalid_chars));
}

static void test_valid_email(void)
{
    char valid[] = "Adwaith@example.com";
    char invalid_start[] = "1adwaith@example.com";
    char invalid_at[] = "adwaith@@example.com";
    char invalid_domain[] = "adwaith@example1.com";
    char invalid_suffix[] = "adwaith@example.org";
    char invalid_empty_domain[] = "adwaith@.com";

    CHECK("Valid .com email is accepted", validEmail(valid));
    CHECK("Email is converted to lowercase", strcmp(valid, "adwaith@example.com") == 0);
    CHECK("Email beginning with a digit is rejected", !validEmail(invalid_start));
    CHECK("Email with multiple @ symbols is rejected", !validEmail(invalid_at));
    CHECK("Email with digits in domain is rejected", !validEmail(invalid_domain));
    CHECK("Email not ending in .com is rejected", !validEmail(invalid_suffix));
    CHECK("Email with an empty domain is rejected", !validEmail(invalid_empty_domain));
}

static void test_unique_contact_fields(void)
{
    AddressBook book = {0};

    strcpy(book.contacts[0].name, "Adwaith");
    strcpy(book.contacts[0].phone, "9876543210");
    strcpy(book.contacts[0].email, "adwaith@example.com");
    book.contactCount = 1;

    char duplicate_phone[] = "9876543210";
    char new_phone[] = "9123456780";
    char duplicate_email[] = "adwaith@example.com";
    char new_email[] = "new@example.com";

    CHECK("Duplicate phone number is rejected", !uniqPhone(&book, duplicate_phone));
    CHECK("New phone number is accepted", uniqPhone(&book, new_phone));
    CHECK("Duplicate email is rejected", !uniqEmail(&book, duplicate_email));
    CHECK("New email is accepted", uniqEmail(&book, new_email));
}

int main(void)
{
    printf("AddressBook unit tests\n");
    printf("======================\n\n");

    test_valid_name();
    test_valid_phone();
    test_valid_email();
    test_unique_contact_fields();

    printf("\n======================\n");
    printf("Tests run: %d\n", tests_run);
    printf("Passed:    %d\n", tests_run - tests_failed);
    printf("Failed:    %d\n", tests_failed);

    return tests_failed == 0 ? 0 : 1;
}
