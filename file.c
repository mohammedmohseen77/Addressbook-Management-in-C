#include <stdio.h>
#include "file.h"
#include "ui.h"

void saveContactsToFile(AddressBook *addressBook)
{
    // Open file in write mode
    FILE *fp = fopen("contacts.txt", "w");

    // Check if file opened successfully
    if (fp == NULL)
    {
        printf(RED "Error opening file...!\n" RESET);
        return;
    }

    // Write contact count
    fprintf(fp, "#%d\n", addressBook->contactCount);

    // Write each contact details
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    // Close file
    fclose(fp);

    printf(GREEN "Contacts saved successfully...!\n" RESET);
}


void loadContactsFromFile(AddressBook *addressBook) 
{
    // Open file in read mode
    FILE *fp = fopen("contacts.txt", "r");

    // Check if file exists
    if (fp == NULL)
    {
        printf(RED "No file found! Starting fresh.\n" RESET);
        return;
    }

    // Read contact count (first line)
    fscanf(fp, "#%d\n", &addressBook->contactCount);

    // Read each contact
    for (int i = 0; i < addressBook->contactCount && i < MAX_CONTACTS; i++)
    {
        fscanf(fp, "%49[^,],%19[^,],%49[^\n]\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
    

    // Close file
    fclose(fp);

    printf(CYAN "Contacts loaded successfully...!\n" RESET);
}
