#ifndef contacts_h
#define contacts_h

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define CALLS 10

typedef enum {FAILURE, SUCCESS} status_code;
typedef enum {PERSONAL, PROFESSIONAL} contact_type;

typedef struct
{
    char day[15];
    char duration[15];
} date;

typedef struct contact_tag
{
    char f_name[20];
    char l_name[20];
    char mo_number[15];
    char email[40];
    int office_no;      //
    char office[20];    //      Extras for professional contacts
    char address[20];   //
    char type[20];
    int time;
    int no_of_calls;
    date call_date[CALLS];
    contact_type c_type;
    struct contact_tag *left;
    struct contact_tag *right;
    int height;
} contact;

contact* new_contact (void);
int height(contact *N);
int max(int a, int b);
contact *rightRotate(contact *y);
contact *leftRotate(contact *x);
int getBalance(contact *N);
contact* insert(contact* node, contact* q);
void preOrder(contact *root);
void display_contact (contact* q);
contact* scan_pers_pb (void);
contact* scan_prof_pb (contact* root);
contact* insert_contact (contact* root);
void inOrder(contact *root, contact_type c);
void display (contact* root, contact_type ct);
contact* delete_contact(contact* root, char name[20]);
contact* edit_contact(char name[20], contact *root);
void search_name (contact* root, char name[20]);
void search_number (contact* root, char num[15]);
void search_address (contact* root, char add[20]);
void reverse_order (contact* root, contact_type c);
void range_search (contact* root, char num1[15], char num2[15]);
void delete_tree (contact* root);

#endif /* contacts_h */
