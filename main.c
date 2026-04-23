#include <stdio.h>
#include "contact.h"
#include "ui.h"


int main()
{
    int choice;
    AddressBook addressBook;
    printf("\n");
    initialize(&addressBook);

    do
    {
        printf(YELLOW "\n--- Address Book Menu ---\n" RESET);
        printf("1. Create Contact\n");
        printf("2. Search Contact\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. List Contact\n");
        printf("6. Exit\n");

        printf(BLUE "Enter a choice : " RESET);
        scanf("%d", &choice);

        switch(choice)
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
                saveContactsToFile(&addressBook);
                printf(YELLOW "Save and Exiting Contacts...!\n" RESET);
                break;
            default:
                printf(RED "Invalid choice!\n" RESET);
        }

    } while(choice != 6);

    return 0;
}