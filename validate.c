#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "ui.h"


/* FUNCTION DEFINATION TO VALIDATE NAME */
int validateName(char name[])
{
    int len = strlen(name);

    /* Checks Minimum 4 characters */
    if (len < 4)
    {
        printf(RED "Error: Name must contain at least 4 characters\n" RESET);
        return 0;
    }

    /* Checks Only alphabets and spaces */
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!isalpha(name[i]) && name[i] != ' ')
        {
            printf(RED "Error: Name should contain only alphabets\n" RESET);
            return 0;
        }
    }

    return 1; // valid
}

/* FUNCTION DEFINATION TO VALIDATE PHONE */
int validatePhone(char phone[])
{
    /* Checks it must be 10 digits only */
    if (strlen(phone) != 10)
    {
        printf(RED "Error: Phone number must be exactly 10 digits\n" RESET);
        return 0;
    }

    /*Checks for Only digits */
    for (int i = 0; phone[i] != '\0'; i++)
    {
        if (!isdigit(phone[i]))
        {
            printf(RED "Error: Only digits allowed in phone number\n" RESET);
            return 0;
        }
    }

    return 1; // valid
}

/* FUNCTION DEFINATION TO VALIDATE EMAIL */
int validateEmail(char email[])
{
    int atCount = 0;
    int atIndex = -1;
    int dotIndex = -1;

    /*Checks Count '@' and check characters */
    for (int i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '@')
        {
            atCount++;
            atIndex = i; // store position of '@'
        }

        /* Checks allow only letters, digits, @ and . */
        if (!isalnum(email[i]) && email[i] != '@' && email[i] != '.')
        {
            printf("Invalid: Only letters, digits, @ and . allowed\n");
            return 0;
        }
    }

    /* Check exactly one '@' */
    if (atCount != 1)
    {
        printf("Invalid: Must contain exactly one '@'\n");
        return 0;
    }

    /* It Find '.' after '@' */
    for (int i = atIndex + 1; email[i] != '\0'; i++)
    {
        if (email[i] == '.')
        {
            dotIndex = i;
            break;
        }
    }

    if (dotIndex == -1)
    {
        printf("Invalid: '.' must come after '@'\n");
        return 0;
    }

    /* Check something exists between '@' and '.' */
    if (dotIndex == atIndex + 1)
    {
        printf("Invalid: No characters between '@' and '.'\n");
        return 0;
    }

    /* Checks After '.' only alphabets allowed */
    for (int i = dotIndex + 1; email[i] != '\0'; i++)
    {
        if (!isalpha(email[i]))
        {
            printf("Invalid: Only letters allowed after '.'\n");
            return 0;
        }
    }

    return 1; // valid email
}