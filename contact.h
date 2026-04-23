#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

// structure to store single contact.
typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

// structure of addressbook.
typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

// Functions of prototype 
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);

void searchbyname(AddressBook *addressBook);
void searchbyphone(AddressBook *addressBook);
void searchbymail(AddressBook *addressBook);

#endif