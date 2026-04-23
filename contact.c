#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include <unistd.h>
#include "ui.h"
#include "validate.h"

/* FUNCTION TO LIST CONTACT */
void listContacts(AddressBook *addressBook) 
{
    // Condition to check empty contacts
    if (addressBook->contactCount == 0)
    {
        printf(RED "No contacts found!\n" RESET);
        return;
    }

    // Display total number of contacts
    printf(YELLOW "\n#%d Contacts Found\n" RESET, addressBook->contactCount);

    // Table Header
    printf(BLUE "\n|| LIST OF CONTACTS ||\n" RESET);
    printf("-----------------------------------------------------------------------\n");
    printf("| %-3s | %-20s | %-15s | %-20s |\n", "No", "Name", "Phone", "Email"); //This keeps properly aligned in table format
    printf("-----------------------------------------------------------------------\n");

    // Display contacts
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("| %-3d | %-20s | %-15s | %-20s |\n",
               i + 1, 
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email); 
    }

    printf("-----------------------------------------------------------------------\n");
}

/* FUNCTION TO LOAD CONTACT */
void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);  //Load contacts from file during initialization (After files) 
}

/* FUNCTION TO SAVE CONTACT */
void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

/* FUNCTION TO CREATE CONTACT */
void createContact(AddressBook *addressBook)
{
    // if the contact list is full.
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf(RED "Address Book is Full!\n" RESET);
        return;
    }

    Contact newContact;
    int valid, attempts;

    /* NAME VALIDATION */
    attempts = 0;
    while (attempts < 3)
    {
        valid = 1;
        printf("Enter Name: ");
        scanf(" %[^\n]", newContact.name); // it Reads a full line including spaces 

        /* Call validation function */
        if (!validateName(newContact.name))
        {
            attempts++;
            continue;
        }

       /* Check duplicate name */
        if (valid == 1)
        {
            for (int j = 0; j < addressBook->contactCount; j++)
            {
                if (strcmp(addressBook->contacts[j].name, newContact.name) == 0) // unique name
                {
                    valid = 0;
                    printf(RED "Name Already Exists!\n" RESET);
                    break;
                }
            }
        }

        if (valid)
            break;

        printf(RED "Invalid Name! Only alphabets allowed.\n" RESET);
        attempts++;
    }
    // if the attempts reached the max.
    if (attempts == 3)
    {
        printf("Maximum attempts reached for Name.\n");
        return;
    }

    /* PHONE VALIDATION */
    attempts = 0;
    while (attempts < 3)
    {
        valid = 1;
        printf("Enter Phone Number: ");
        scanf("%s", newContact.phone);

        /* Call validation function */
        if (!validatePhone(newContact.phone))
        {
            attempts++;
            continue;
        }

        /* Check duplicate phone number */
        for (int j = 0; j < addressBook->contactCount; j++)
        {
            if (strcmp(addressBook->contacts[j].phone, newContact.phone) == 0) // unique number
            {
                valid = 0;
                printf(RED "Phone Number Already Exists!\n" RESET);
                break;
            }
        }

        if (valid)
            break;

        printf(RED "Invalid Phone! Must be 10 unique digits.\n" RESET);
        attempts++;
    }
    // if the attempts reached the max.
    if (attempts == 3)
    {
        printf("Maximum attempts reached for Phone Number.\n");
        return;
    }

    /* EMAIL VALIDATION */
    attempts = 0;
    while (attempts < 3)
    {
        valid = 1;

        printf("Enter Email: ");
        scanf("%s", newContact.email);

        /* Call validation function */
        if (!validateEmail(newContact.email))
        {
            attempts++;
            continue;
        }

        /* Check duplicate email */
        for (int j = 0; j < addressBook->contactCount; j++)
        {
            if (strcmp(addressBook->contacts[j].email, newContact.email) == 0) // unique email
            {
                valid = 0;
                printf(RED "Email Already Exists!\n" RESET);
                break;
            }
        }

        if (valid == 1)
        {
            break;
        }

        printf(RED "Invalid Email! Use lowercase, one '@', one '.com', unique email only.\n" RESET);
        attempts++;
    }
     // if the attempts reached the max.
    if (attempts == 3)
    {
        printf("Maximum attempts reached for Email.\n");
        return;
    }

    /* TO STORE THE CONTACT */
    addressBook->contacts[addressBook->contactCount] = newContact;
    addressBook->contactCount++; // Increment contact count

    /*For Loading Animation*/
    for (int i = 0; i <= 100; i++)
    {
        printf(MAGENTA "Loading............%d%%\r" RESET, i); // '\r' (carriage return, overwriting the same line) 
        usleep(15000);
        fflush(stdout);
    }

    printf("\n");
    printf(GREEN "Contact Added Successfully!\n" RESET);

    printf(CYAN "Total number of Contacts count = %d\n" RESET,addressBook->contactCount); // it prints the how many contact created.
}
    
/* FUNCTION TO SEARCH CONTACT */
void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int choice;
    char input[50];
    
    do
    {   
        printf(YELLOW "SEARCH MENU:\n" RESET);
        
        printf("1.Search by Name\n");
        printf("2.Search by Phone Number\n");
        printf("3.Search by Mail ID\n");
        printf("4.Exit\n");      
        printf("\n");

        printf(BLUE "Enter your choice: " RESET);        
        scanf("%d",&choice);

        getchar();
        switch(choice)
        {
            case 1:
                searchbyname(addressBook);
                break;
            case 2:
                searchbyphone(addressBook);
                break;
            case 3:
                searchbymail(addressBook);
                break;
            case 4:
                printf(GREEN "Exiting Search Menu..!\n" RESET); 
                break;
            default:
                printf(RED "Error....!\n" RESET);
                break;
        }
    } while(choice  != 4);
}

/*Search by name*/
void searchbyname(AddressBook *addressBook)
{
    char name[50];
    int found = 0;

    printf(BLUE "Enter the name: " RESET);
    scanf(" %[^\n]", name);
    printf("\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        // it wll go the adressbook and access the contact and comapre, comapre stored conatct with user input  
        if (strcmp(addressBook->contacts[i].name, name) == 0)
        {
            printf(YELLOW "\nContact Found:\n" RESET);
            printf("Name  : %s\n", addressBook->contacts[i].name);
            printf("Phone : %s\n", addressBook->contacts[i].phone);
            printf("Email : %s\n", addressBook->contacts[i].email);
            printf("\n");
            found = 1;
            break;
        }
    }
    if (!found)
        printf(RED "Contact not found!\n" RESET);
}

/*Search by phone*/
void searchbyphone(AddressBook *addressBook)
{
    char phone[20];
    int found = 0;

    printf(BLUE "Enter phone number: " RESET);
    scanf("%s", phone);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        // it wll go the adressbook and access the contact and comapre, comapre stored conatct with user input 
        if (strcmp(addressBook->contacts[i].phone, phone) == 0) 
        {
            printf(YELLOW "\nContact Found:\n" RESET);
            printf("Name  : %s\n", addressBook->contacts[i].name);
            printf("Phone : %s\n", addressBook->contacts[i].phone);
            printf("Email : %s\n", addressBook->contacts[i].email);
            printf("\n");
            found = 1;
            break;
        }
    }   
    if (!found)
        printf(RED "Contact not found!\n" RESET);
}

/*Search by email*/
void searchbymail(AddressBook *addressBook)
{
    char email[50];
    int found = 0;

    printf(BLUE "Enter a email: " RESET);
    scanf("%s", email);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        // it wll go the adressbook and access the contact and comapre, comapre stored conatct with user input  
        if (strcmp(addressBook->contacts[i].email, email) == 0)
        {
            printf(YELLOW "\nContact Found:\n" RESET);
            printf("Name  : %s\n", addressBook->contacts[i].name);
            printf("Phone : %s\n", addressBook->contacts[i].phone);
            printf("Email : %s\n", addressBook->contacts[i].email);
            printf("\n");
            found = 1;
            break;
        }
    }
    if (!found)
        printf(RED "Contact not found!\n" RESET);
}

/* FUNCTION TO EDIT CONTACT */
void editContact(AddressBook *addressBook)
{
    int choice, found = 0;
    char input[50];

    printf(YELLOW "\nEDIT MENU:\n" RESET);
    printf("1. Edit by Name\n");
    printf("2. Edit by Phone\n");
    printf("3. Edit by Email\n");
    printf("4. Exit\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

    /* SHOW CONTACTS HERE */
    listContacts(addressBook);

    
    if (choice == 1)
    {
        printf("Enter name to edit: ");
        scanf(" %[^\n]", input);
    }
    else if (choice == 2)
    {
        printf("Enter phone to edit: ");
        scanf("%s", input);
    }
    else if (choice == 3)
    {
        printf("Enter email to edit: ");
        scanf("%s", input);
    }
    else if (choice == 4)
    {
        printf("Exiting Edit Menu...\n"); // Exit condition 
        return;
    }
    else
    {
        printf("Invalid choice!\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        // it will comapre with user input.
        if ((choice == 1 && strcmp(addressBook->contacts[i].name, input) == 0) ||
            (choice == 2 && strcmp(addressBook->contacts[i].phone, input) == 0) ||
            (choice == 3 && strcmp(addressBook->contacts[i].email, input) == 0))
        {
            found = 1;
            printf(YELLOW "\nContact Found!\n" RESET);

            /*Edit Name*/
            if (choice == 1)
            {
                char newName[50];
                int valid = 1;

                printf(CYAN "Enter new name: " RESET);
                scanf(" %[^\n]", newName);

                for (int j = 0; newName[j] != '\0'; j++)
                {
                    if (!isalpha(newName[j]) && newName[j] != ' ')
                    {
                        valid = 0;
                        break;
                    }
                }

                if (valid)
                {
                    strcpy(addressBook->contacts[i].name, newName); // replace new name.
                    printf(YELLOW "Name updated successfully!\n" RESET);
                }
                else
                {
                    printf(RED "Invalid name! Only alphabets allowed.\n" RESET);
                }
            }

            /*Edit Phone*/
            else if (choice == 2)
            {
                char newPhone[20];
                int valid = 1;

                printf("Enter new phone: ");
                scanf("%s", newPhone);

                if (strlen(newPhone) != 10)
                    valid = 0;

                for (int j = 0; newPhone[j] != '\0'; j++)
                {
                    if (!isdigit(newPhone[j]))
                    {
                        valid = 0;
                        break;
                    }
                }

                if (valid)
                {
                    strcpy(addressBook->contacts[i].phone, newPhone); // replace new phone
                    printf(YELLOW "Phone updated successfully!\n" RESET);
                }
                else
                {
                    printf(RED "Invalid phone! Must be 10 digits.\n" RESET);
                }
            }

            /*Edit email*/
            else if (choice == 3)
            {
                char newEmail[50];
                int valid = 1, at = 0;

                printf("Enter new email: ");
                scanf("%s", newEmail);

                for (int j = 0; newEmail[j] != '\0'; j++)
                {
                    if (isupper(newEmail[j]))
                        valid = 0;

                    if (newEmail[j] == '@')
                        at++;
                }

                if (strstr(newEmail, ".com") == NULL || at != 1)
                    valid = 0;

                if (valid)
                {
                    strcpy(addressBook->contacts[i].email, newEmail); // replace new email.
                    printf(YELLOW "Email updated successfully!\n" RESET);
                }
                else
                {
                    printf(RED "Invalid email!\n" RESET);
                }
            }

            break;
        }
    }
    if (!found)
    {
        printf(RED "Contact not found!\n" RESET);
    }
}

/* FUNCTION TO DELETE CONTACT */
void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    listContacts(addressBook); // This prints all saved contacts so the user can choose which contact to delete.
    if(addressBook->contactCount == 0) // no contacts to delete
    {
        printf(RED "No contacts available to delete...!\n" RED);
        return;
    }

    int choice, found = 0;
    char input[50];

    printf(YELLOW "\nDELETE MENU:\n" RESET);
    printf("1. Delete by Name\n");
    printf("2. Delete by Phone\n");
    printf("3. Delete by Email\n");
    printf("4. Exit\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();   // clear buffer

    /* Exit option */
    if (choice == 4)
    {
        printf("Exiting Delete Menu...\n");
        return;
    }

    /*Search and Delete*/
    printf("Enter value to delete: ");
    scanf(" %[^\n]", input);

    for (int i = 0; i < addressBook->contactCount; i++)
        {
            if ((choice == 1 && strcmp(addressBook->contacts[i].name, input) == 0) ||
                (choice == 2 && strcmp(addressBook->contacts[i].phone, input) == 0) ||
                (choice == 3 && strcmp(addressBook->contacts[i].email, input) == 0))
            {
                found = 1;
                
                char confirm;
                printf(YELLOW "Are you sure you want to delete this contact? (y/n): " RESET);
                scanf(" %c", &confirm);

                if (confirm == 'y' || confirm == 'Y')
                {
                    // shift contacts left
                    for (int j = i; j < addressBook->contactCount - 1; j++)
                    {
                        addressBook->contacts[j] = addressBook->contacts[j + 1];
                    }

                    addressBook->contactCount--;

                    printf(GREEN "Contact deleted successfully!\n" RESET);
                }
                else
                {
                    printf(GREEN "Deletion cancelled.\n" RESET);
                }

                break;
            }
        }

        if (!found)
        {
            printf(RED "Contact not found!\n" RESET);
        }
    }