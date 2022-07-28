//Amaan Khan BT20CSE065 R3  DSPD-II Assignment 2

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "contacts.h"

void choose (int c);

int main()
{
    int c;
    printf("Enter a number for corresponding choice:\n1.Insert/Create contact\n2.Edit contact\n3.Delete a contact\n4.Search contacts\n5.Sort contacts\n6.Display contacts\n7.Range Search\n8.Sort based on first name and mobile number\n0.Exit\n");
    scanf("%d", &c);
    choose(c);
    return 0;
}

void choose (int c)
{
    contact* root1;
    root1 = scan_pers_pb();
    root1 = scan_prof_pb(root1);
    int t;
    char field[20];
    contact* root = root1;      //change phonebook here
    
    while (c != 0)
    {
        if (c == 1)
        {
            root = insert_contact(root);
        }
        if (c == 2)
        {
            inOrder(root, 2);
            printf("Enter name of contact to be edited: ");
            scanf("%s", field);
            root = edit_contact(field, root);
        }
        if (c == 3)
        {
            display(root, 0);
            display(root, 1);
            printf("Enter name of contact to be deleted: ");
            scanf("%s", field);
            root = delete_contact(root, field);
            printf("Contact of %s deleted\n", field);
        }
        if (c == 4)
        {
            printf("Search contact through:\n1.Name\n2.Number\n3.Address\n");
            scanf("%d", &t);
            char arr[20];
            if (t == 1)
            {
                printf("Enter first name: ");
                scanf("%s", arr);
                printf("Search results: \n");
                search_name(root, arr);
            }
            else if (t == 2)
            {
                printf("Enter mobile number: ");
                scanf("%s", arr);
                printf("Search results: \n");
                search_number(root, arr);
            }
            else
            {
                printf("Enter address: ");
                scanf("%s", arr);
                printf("Search results: \n");
                search_address(root, arr);
            }
        }
        if (c == 5)
        {
            printf("Sort in\n1.Ascending order\n2.Descending order\n3.Personal first\n4.Professional first\n");
            scanf("%d", &t);
            if (t == 1)
            {
                inOrder(root, 2);
                printf("Contacts are sorted in ascending order\n");
            }
            else if (t == 2)
            {
                reverse_order(root, 2);
                printf("Contacts are sorted in descending order\n");
            }
            else if (t == 3)
            {
                display(root, 0);
                display(root, 1);
                printf("Contacts are sorted personals first\n");
            }
            else if (t == 4)
            {
                display(root, 1);
                display(root, 0);
                printf("Contacts are sorted professional first\n");
            }
        }
        if (c == 6)
        {
            printf("1.Display personal list\n2.Display professional list\n3.Complete List\n");
            scanf("%d", &t);
            display(root, t-1);
        }
        if (c == 7)
        {
            char f_num[15], t_num[15];
            printf("Enter range: \n");
            printf("Starting Number: ");
            scanf("%s", f_num);
            printf("Ending Number: ");
            scanf("%s", t_num);
            printf("Contacts found in given range: \n");
            range_search(root, f_num, t_num);
        }
        if (c == 8)
        {
            inOrder(root, 2);
            printf("Contacts are sorted based on first name and mobile number\n");
        }
        printf("\nChose next option: ");
        scanf("%d", &c);
    }
    delete_tree(root1);
}
