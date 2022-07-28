#include "contacts.h"

contact* new_contact ()
{
    contact* nn;
    nn = (contact *)malloc(sizeof(contact));
    nn->left = NULL;
    nn->right = NULL;
    nn->height = 1;
    return nn;
}

int height(contact *N)
{
    int h = 0;
    if (N != NULL)
    {
        h = N->height;
    }
    return h;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

void copy_data (contact* c1, contact* c2)
{
    contact* l = c1->left, *r = c1->right;
    c1 = c2;
    c1->left = l;
    c1->right = r;
}

contact* rightRotate(contact* y)
{
    contact *x = y->left;
    contact *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

contact* leftRotate(contact* x)
{
    contact *y = x->right;
    contact *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

int getBalance(contact *N)
{
    int rv = 0;
    if (N != NULL)
    {
        rv = height(N->left) - height(N->right);
    }
    return rv;
}

contact* insert(contact* node, contact* q)
{
    
    if (node == NULL)
    {
        return q;
    }
 
    if (strcmp(q->f_name, node->f_name) < 0)
    {
        node->left = insert(node->left, q);
    }
    else if (strcmp(q->f_name, node->f_name) > 0)
    {
        node->right = insert(node->right, q);
    }
    else
    {
        if (strcmp(q->mo_number, node->mo_number) < 0)
        {
            node->left = insert(node->left, q);
        }
        else if (strcmp(q->mo_number, node->mo_number) > 0)
        {
            node->right = insert(node->right, q);
        }
        else
        {
            return node;
        }
    }
 
    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);
 
    if (node->left != NULL)
    {
        if (balance > 1 && strcmp(q->f_name, node->left->f_name) < 0)        // Left Left Case
        {
            return rightRotate(node);
        }
     
        if (balance < -1 && strcmp(q->f_name, node->left->f_name) > 0)      // Right Right Case
        {
            return leftRotate(node);
        }
     
        if (balance > 1 && strcmp(q->f_name, node->left->f_name) > 0)        // Left Right Case
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
     
        if (balance < -1 && strcmp(q->f_name, node->left->f_name) < 0)      // Right Left Case
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        if (strcmp(q->f_name, node->left->f_name) == 0)
        {
            if (balance > 1 && strcmp(q->mo_number, node->left->mo_number) < 0)        // Left Left Case
            {
                return rightRotate(node);
            }
         
            if (balance < -1 && strcmp(q->mo_number, node->left->mo_number) > 0)      // Right Right Case
            {
                return leftRotate(node);
            }
         
            if (balance > 1 && strcmp(q->mo_number, node->left->mo_number) > 0)        // Left Right Case
            {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
         
            if (balance < -1 && strcmp(q->mo_number, node->left->mo_number) < 0)      // Right Left Case
            {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }
    }
    return node;
}

void preOrder(contact *root)
{
    if(root != NULL)
    {
        display_contact(root);
        preOrder(root->left);
        preOrder(root->right);
    }
}

contact* scan_pers_pb (void)               //scans input from file
{
    FILE *fp;
    fp = fopen("pers_pb.txt", "r");

    if(fp == 0)
    {
        perror("fopen");
        exit(1);
    }
    
    char str[100];
    int flag1 = 0;
    contact *root = NULL;
    
    while (flag1 == 0)
    {
        fgets(str, 100, fp);
        if (root != NULL)
        {
            if (feof(fp) != 0)
            {
                flag1++;
            }
        }
        if (flag1 == 0)
        {
            contact *q;
            q = new_contact();
            sscanf(str, "%s %s %s %s %s %d", q->f_name, q->l_name, q->mo_number, q->email, q->type, &q->no_of_calls);
            q->c_type = PERSONAL;
            if (q->no_of_calls > 0)
            {
                for (int i = 0; i < q->no_of_calls; i++)
                {
                    fgets(str, 100, fp);
                    char dates[15], time[15];
                    sscanf(str, "%s %s", dates, time);
                    strcpy(q->call_date[i].day, dates);
                    strcpy(q->call_date[i].duration, time);
                }
            }
            root = insert(root, q);
        }
    }
    fclose(fp);
    return root;
}

contact* scan_prof_pb (contact* root)               //scans input from file
{
    FILE *fp;
    fp = fopen("prof_pb.txt", "r");
    if(fp == 0)
    {
        perror("fopen");
        exit(1);
    }

    char str[100];
    int flag1 = 0;
    
    while (flag1 == 0)
    {
        fgets(str, 100, fp);
        if (root != NULL)
        {
            if (feof(fp) != 0)
            {
                flag1++;
            }
        }
        if (flag1 == 0)
        {
            contact *q;
            q = new_contact();
            sscanf(str, "%s %s %s %s %d %s %s %s %d", q->f_name, q->l_name, q->mo_number, q->email, &q->office_no, q->office, q->address, q->type, &q->no_of_calls);
            q->c_type = PROFESSIONAL;
            if (q->no_of_calls > 0)
            {
                for (int i = 0; i < q->no_of_calls; i++)
                {
                    fgets(str, 100, fp);
                    char dates[15], time[15];
                    sscanf(str, "%s %s", dates, time);
                    strcpy(q->call_date[i].day, dates);
                    strcpy(q->call_date[i].duration, time);
                }
            }
            root = insert(root, q);
        }
    }
    fclose(fp);
    return root;
}

contact* insert_contact (contact* root)
{
    contact* q = root;
    while (q->right != NULL)
    {
        q = q->right;
    }
    q = new_contact();
    int t;
    printf("Enter the following fields:\nFirst Name: ");
    scanf("%s", q->f_name);
    printf("Last name: ");
    scanf("%s", q->l_name);
    printf("Mobile Number: ");
    scanf("%s", q->mo_number);
    printf("Email: ");
    scanf("%s", q->email);
    printf("Contact type(Enter 0 for Personal, 1 for Professional): ");
    scanf("%d", &t);
    if (t == 0)
    {
        q->c_type = PERSONAL;
    }
    else
    {
        q->c_type = PROFESSIONAL;
        printf("Office Number: ");
        scanf("%d", &q->office_no);
        printf("Office: ");
        scanf("%s", q->office);
        printf("Address: ");
        scanf("%s", q->address);
    }
    printf("Type(description): ");
    scanf("%s", q->type);
    printf("Number of calls made to this contact: ");
    scanf("%d", &q->no_of_calls);
    for (t = 0; t < q->no_of_calls; t++)
    {
        printf("Date(dd/mm/yyyy): ");
        scanf("%s", q->call_date[t].day);
        printf("Duration(hh:mm:ss): ");
        scanf("%s", q->call_date[t].duration);
    }
    root = insert(root, q);
    printf("New contact added\n");
    display_contact(q);
    return root;
}

void display_contact (contact* q)
{
    if (q != NULL)
    {
        if (q->c_type == PERSONAL)
        {
            printf("%s\t%s\t%s\t%s\t%s\t%d\n", q->f_name, q->l_name, q->mo_number, q->email, q->type, q->no_of_calls);
        }
        else
        {
            printf("%s\t%s\t%s\t%s\t%d\t%s\t%s\t%s\t%d\n", q->f_name, q->l_name, q->mo_number, q->email, q->office_no, q->office, q->address, q->type, q->no_of_calls);
        }
        for (int i = 0; i < q->no_of_calls; i++)
        {
            printf("%s\t%s\n", q->call_date[i].day, q->call_date[i].duration);
        }
    }
    else
    {
        printf("Null contact\n");
    }
}

void inOrder(contact *root, contact_type c)
{
    if(root != NULL)
    {
        inOrder(root->left, c);
        if (root->c_type == c || c == 2)
        {
            display_contact(root);
        }
        inOrder(root->right, c);
    }
}

void display (contact* root, contact_type ct)
{
    if (ct == PERSONAL)
    {
        printf("Name\t\tMobile\tEmail\tType\tNo of calls\n");
        inOrder(root, ct);
    }
    else if (ct == PROFESSIONAL)
    {
        printf("Name\t\tMobile\tEmail\tOfficeNo\tOffice\tAddress\tType\tNo of calls\n");
        inOrder(root, ct);
    }
    else
    {
        inOrder(root, ct);
    }
}

contact* minValueNode(contact* node)
{
    contact* current = node;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

contact* delete_contact(contact* root, char name[20])
{
    if (root == NULL)
    {
        printf("Contact with name %s not found\n", name);
        return root;
    }
    
    if (strcmp(name, root->f_name) < 0)
    {
        root->left = delete_contact(root->left, name);
    }
    else if (strcmp(name, root->f_name) > 0)
    {
        root->right = delete_contact(root->right, name);
    }
    else
    {
        if (root->left == NULL || root->right == NULL)
        {
            contact* temp = root->left ? root->left : root->right;
 
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
            {
                *root = *temp;
            }
            free(temp);
        }
        else
        {
            contact* temp = minValueNode(root->right);
            copy_data(root, temp);
            root->right = delete_contact(root->right, name);
        }
    }
 
    if (root == NULL)
    {
        return root;
    }
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)     // Left Left Case
    {
        return rightRotate(root);
    }

    if (balance > 1 && getBalance(root->left) < 0)      // Left Right Case
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
 
    if (balance < -1 && getBalance(root->right) <= 0)       // Right Right Case
    {
        return leftRotate(root);
    }

    if (balance < -1 && getBalance(root->right) > 0)        // Right Left Case
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

contact* edit_contact(char name[20], contact *root)
{
    contact* q;
    q = root;
    int flag = 0;
    
    while (flag == 0 && q != NULL)
    {
        if (strcmp(name, q->f_name) != 0)
        {
            if (strcmp(q->f_name, name) > 0)
            {
                q = q->left;
            }
            else
            {
                q = q->right;
            }
        }
        else
        {
            flag++;
        }
    }
    
    if (q == NULL)
    {
        printf("Contact with name %s not found\n", name);
    }
    else
    {
        printf("Enter corresponding number of field to be edited:\n1.First name\n2.Last name\n3.Mobile Number\n4.Email\n5.Type\n6.Number of calls/Date/Duration\n7.Contact type\n");
        if (q->c_type == PROFESSIONAL)
        {
            printf("8.Office Number\n9.Office/Institute\n10.Address\n");
        }
        int opt;
        scanf("%d", &opt);
        if (opt == 1)
        {
            contact* new;
            new = new_contact();
            *new = *q;
            root = delete_contact(root, q->f_name);
            printf("Enter new first name: ");
            scanf("%s", new->f_name);
            root = insert(root, new);
            printf("Contact is modified\n");
            display_contact(new);
            return root;
        }
        if (opt == 2)
        {
            printf("Enter new last name: ");
            scanf("%s", q->l_name);
        }
        if (opt == 3)
        {
            printf("Enter new mobile number: ");
            scanf("%s", q->mo_number);
        }
        if (opt == 4)
        {
            printf("Enter new email: ");
            scanf("%s", q->email);
        }
        if (opt == 5)
        {
            printf("Enter new type: ");
            scanf("%s", q->type);
        }
        if (opt == 6)
        {
            printf("Enter number of calls: ");
            scanf("%d", &q->no_of_calls);
            for (int i = 0; i < q->no_of_calls; i++)
            {
                printf("Enter date(dd/mm/yy): ");
                {
                    scanf("%s", q->call_date[i].day);
                }
                printf("Enter duration(hh:mm:ss): ");
                {
                    scanf("%s", q->call_date[i].duration);
                }
            }
        }
        if (opt == 7)
        {
            printf("Enter contact type (0 for personal, 1 for professional): ");
            scanf("%d", &q->c_type);
        }
        if (q->c_type == 1)
        {
            if (opt == 8)
            {
                printf("Enter new office number: ");
                scanf("%d", &q->office_no);
            }
            if (opt == 9)
            {
                printf("Enter new office/institute name: ");
                scanf("%s", q->office);
            }
            if (opt == 10)
            {
                printf("Enter new address: ");
                scanf("%s", q->address);
            }
        }
        if (opt != 1)
        {
            printf("Contact is modified\n");
            display_contact(q);
        }
    }
    return root;
}

void search_name (contact* root, char name[20])
{
    if (root != NULL)
    {
        search_name(root->left, name);
        if (strcmp(root->f_name, name) == 0)
        {
            display_contact(root);
        }
        search_name(root->right, name);
    }
}

void search_number (contact* root, char num[15])
{
    if (root != NULL)
    {
        search_number(root->left, num);
        if (strcmp(root->mo_number, num) == 0)
        {
            display_contact(root);
        }
        search_number(root->right, num);
    }
}

void search_address (contact* root, char add[20])
{
    if (root != NULL)
    {
        search_address(root->left, add);
        if (strcmp(root->address, add) == 0)
        {
            display_contact(root);
        }
        search_address(root->right, add);
    }
}

void reverse_order (contact* root, contact_type c)
{
    if (root != NULL)
    {
        reverse_order(root->right, c);
        display_contact(root);
        reverse_order(root->left, c);
    }
}

void range_search (contact* root, char num1[15], char num2[15])
{
    if (root != NULL)
    {
        range_search(root->left, num1, num2);
        if (strcmp(root->mo_number, num1) >= 0 && strcmp(root->mo_number, num2) <= 0)
        {
            display_contact(root);
        }
        range_search(root->right, num1, num2);
    }
}

void delete_tree (contact* root)
{
    if (root != NULL)
    {
        delete_tree(root->left);
        delete_tree(root->right);
        free(root);
        root = NULL;
    }
}
