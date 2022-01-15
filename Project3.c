#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 100

FILE* fp;

struct vehicle
{
    int serial_no;
    char vehicle_type[10];
    char maker[20];
    int year_of_manufacture;
    char engine_no[10];
    char registration_no[10];
    unsigned int vehicle_price;
    int owners_ID;
};

struct owner
{
    int owner_ID;
    char owner_name[20];
    char father_name[20];
    char address[100];
    int date_of_purchase;
    int month_of_purchase;
    int year_of_purchase;
    double purchase_amount;
    struct vehicle vehicles[5];
    int totalcars;
};

struct vehicle cars[SIZE];
struct owner owners_ID[SIZE];


int scan_owners(int rc);
int scan_cars(int vc, int rc);
int add_owner(int n);
int add_vehicle(int n, int rc);
int delete_owner(int rc, int id);
int delete_car(int vc, int rc);
int list_cars(int rc);
int delete_1990(int vc, int rc);
int max_vehicles(int rc);
int two_wheelers(int rc);
int costliest(int rc);
int brands(int rc);
int three_wheelers(int vc);


int main()
{
    int rc = 0, option = 0, vc = 0, i, del;      //rc = recordcount, vc = vehiclecount
    
    rc = scan_owners(0);
    vc = scan_cars(0, rc);
        
    printf("List of tasks:\n1. Add a new owner\n2. Add a new car to an owner\n3. Delete a car by ID\n4. List all the cars of a particular owner in ascending order of the year of manufacture\n5. Delete all cars that have a manufacturing year before 1990\n6. List owners with maximum and second maximum number of vehicles\n7. List the owners who purchased more than 1, 2-wheeler vehicles in the same year\n8. Determine the price of the costliest vehicle owned by an owner\n9. List the owners who own more than one vehicle of a brand\n10. List the owners who purchased 3-wheeler in a particular year\n11. View complete owner records\n12. View complete vehicle records\n13. Exit\n");
    
    while (option != 13)
    {
        printf("\nEnter a number to execute the corresponding task from the task list: ");
        scanf("%d", &option);
        
        if (option == 1)
        {
            rc = add_owner(rc);
        }
        
        if (option == 2)
        {
            vc = add_vehicle(vc, rc);
        }
        
        if (option == 3)
        {
            del = delete_car(vc, rc);
            if (del == 1)
            {
                vc--;
            }
            else if (del == 2)
            {
                vc--;
                rc--;
            }
        }
        
        if (option == 4)
        {
            list_cars(rc);
        }
        
        if (option == 5)
        {
            vc = delete_1990(vc, rc);
            rc = scan_owners(0);
        }
        
        if (option == 6)
        {
            max_vehicles(rc);
        }
        
        if (option == 7)
        {
            two_wheelers(rc);
        }
        
        if (option == 8)
        {
            costliest(rc);
        }
        
        if (option == 9)
        {
            brands(rc);
        }
        
        if (option == 10)
        {
            three_wheelers(vc);
        }
        
        if (option == 11)
        {
            for (i = 0; i < rc; i++)
            {
                printf("\n%d\t%s\t%s\t%s\t%d\t%d\t%d\t%.2lf", owners_ID[i].owner_ID, owners_ID[i].owner_name, owners_ID[i].father_name, owners_ID[i].address, owners_ID[i].date_of_purchase, owners_ID[i].month_of_purchase, owners_ID[i].year_of_purchase, owners_ID[i].purchase_amount);
            }
            printf("\n");
        }
        
        if (option == 12)
        {
            for (i = 0; i < vc; i++)
            {
                printf("%d\t%s\t%s\t%d\t%s\t%s\t%u\t%d\n", cars[i].serial_no, cars[i].vehicle_type, cars[i].maker, cars[i].year_of_manufacture, cars[i].engine_no, cars[i].registration_no, cars[i].vehicle_price, cars[i].owners_ID);
            }
        }
    }
    return 0;
}


int scan_owners(int rc)
{
    char str[100];
    int flag1 = 0;
    
    fp = fopen("own.txt", "r");
    if(fp == 0)
    {
        perror("fopen");
        exit(1);
    }
    
    while (flag1 == 0)
    {
        fgets(str, 100, fp);
        if (atoi(&str[0]) == owners_ID[rc-1].owner_ID)
        {
            flag1++;
        }
        if (flag1 == 0)
        {
            sscanf(str, "%d %s %s %s %d %d %d %lf", &owners_ID[rc].owner_ID, owners_ID[rc].owner_name, owners_ID[rc].father_name, owners_ID[rc].address, &owners_ID[rc].date_of_purchase, &owners_ID[rc].month_of_purchase, &owners_ID[rc].year_of_purchase, &owners_ID[rc].purchase_amount);
            owners_ID[rc].totalcars = 0;
            rc++;
        }
    }//There are a total of 'rc' owner IDs
    
    fclose(fp);
    return rc;
}


int scan_cars(int vc, int rc)
{
    char str[100];
    int flag1 = 0, i;
    
    fp = fopen("cars.txt", "r");
    if(fp == 0)
    {
        perror("fopen");
        exit(1);
    }
    
    while (flag1 == 0)
    {
        fgets(str, 100, fp);
        if (atoi(&str[0]) == cars[vc-1].serial_no && vc>0)
        {
            flag1++;
        }
        if (flag1 == 0)
        {
            sscanf(str, "%d %s %s %d %s %s %u %d", &cars[vc].serial_no, cars[vc].vehicle_type, cars[vc].maker, &cars[vc].year_of_manufacture, cars[vc].engine_no, cars[vc].registration_no, &cars[vc].vehicle_price, &cars[vc].owners_ID);
            i = 0;
            while (i < rc)
            {
                if (owners_ID[i].owner_ID == cars[vc].owners_ID)
                {
                    owners_ID[i].vehicles[owners_ID[i].totalcars] = cars[vc];
                    owners_ID[i].totalcars++;
                }
                i++;
            }
            vc++;
        }
    }//There are a total 'vc' cars
    
    fclose(fp);
    return vc;
}


int add_owner(int n)
{
    int flag = 0, j = 0, id;
    printf("Enter Owner's ID: ");
    scanf("%d", &id);
    
    while (j < n && flag == 0)
    {
        if (id == owners_ID[j].owner_ID)
        {
            flag++;
        }
        j++;
    }
    
    if (flag != 0)
    {
        printf("\nThe entered owner's ID already exists.\n");
    }
    else
    {
        owners_ID[n].owner_ID = id;
        printf("Enter owner's name: ");
        scanf("%s", owners_ID[n].owner_name);
        printf("Enter father's name: ");
        scanf("%s", owners_ID[n].father_name);
        printf("Enter Address: ");
        scanf("%s", owners_ID[n].address);
        printf("Enter date of purchase: ");
        scanf("%d", &owners_ID[n].date_of_purchase);
        printf("Enter month of purchase: ");
        scanf("%d", &owners_ID[n].month_of_purchase);
        printf("Enter year of purchase: ");
        scanf("%d", &owners_ID[n].year_of_purchase);
        printf("Enter purchase amount: ");
        scanf("%lf", &owners_ID[n].purchase_amount);
        
        fp = fopen("own.txt", "a");
        fprintf(fp, "\n%d\t%s\t%s\t%s\t%d\t%d\t%d\t%.2lf", owners_ID[n].owner_ID, owners_ID[n].owner_name, owners_ID[n].father_name, owners_ID[n].address, owners_ID[n].date_of_purchase, owners_ID[n].month_of_purchase, owners_ID[n].year_of_purchase, owners_ID[n].purchase_amount);
        owners_ID[n].totalcars = 0;
        fclose(fp);
        
        printf("New owner has been added.\n");
        n++;
    }
    return n;
}


int add_vehicle(int n, int rc)
{
    int id, i, flag = 0;
    printf("Enter Owners ID: ");
    scanf("%d", &id);
    
    for (i = 0; i < rc && flag == 0; i++)
    {
        if (owners_ID[i].owner_ID == id)
        {
            flag++;
        }
    }
    i--;
    
    if (flag == 0)
    {
        printf("Owner not found.\n");
    }
    else if (owners_ID[i].totalcars >= 5)
    {
        printf("New purchase denied as owner already has five vehicles.\n");
    }
    else
    {
        cars[n].serial_no = n;
        printf("Enter vehicle type: ");
        scanf("%s", cars[n].vehicle_type);
        printf("Enter vehicle maker: ");
        scanf("%s", cars[n].maker);
        printf("Enter year of manufacture: ");
        scanf("%d", &cars[n].year_of_manufacture);
        printf("Enter engine number: ");
        scanf("%s", cars[n].engine_no);
        printf("Enter registration number: ");
        scanf("%s", cars[n].registration_no);
        printf("Enter vehicle price: ");
        scanf("%u", &cars[n].vehicle_price);
        cars[n].owners_ID = id;
        
        owners_ID[i].vehicles[owners_ID[i].totalcars] = cars[n];
        owners_ID[i].totalcars++;
        
        fp = fopen("cars.txt", "a");
        fprintf(fp, "\n%d\t%s\t%s\t%d\t%s\t%s\t%u\t%d", cars[n].serial_no, cars[n].vehicle_type, cars[n].maker, cars[n].year_of_manufacture, cars[n].engine_no, cars[n].registration_no, cars[n].vehicle_price, cars[n].owners_ID);
        fclose(fp);
        
        printf("New vehicle has been added to the owner.\n");
        n++;
    }
    return n;
}


int delete_owner(int rc, int id)
{
    int j, flag = 0, k;
    for (j = 0; j < rc && flag == 0; j++)
    {
        if (owners_ID[j].owner_ID == id)
        {
            flag++;
        }
    }
    j--;
    
    for(k = j; k < rc - 1; k++)
    {
        owners_ID[k] = owners_ID[k+1];
    }
    rc--;
    
    fp = fopen("own.txt", "w");
    for (j = 0; j < rc; j++)
    {
        fprintf(fp, "%d\t%s\t%s\t%s\t%d\t%d\t%d\t%.2lf\n", owners_ID[j].owner_ID, owners_ID[j].owner_name, owners_ID[j].father_name, owners_ID[j].address, owners_ID[j].date_of_purchase, owners_ID[j].month_of_purchase, owners_ID[j].year_of_purchase, owners_ID[j].purchase_amount);
    }
    fclose(fp);
    
    printf("Owner ID: %d deleted successfully.\n", id);
    return 0;
}


int delete_car(int vc, int rc)
{
    int id, flag = 0, i, j = 0, k, retval = 0;
    char regno[10];
    
    printf("Enter owner's ID: ");
    scanf("%d", &id);
    for (i = 0; i < rc && flag == 0; i++)
    {
        if (owners_ID[i].owner_ID == id)
        {
            flag++;
        }
    }
    i--;
    
    if (flag == 0)
    {
        printf("Owner not found.\n");
    }
    else
    {
        while (j < owners_ID[i].totalcars)
        {
            printf("\n%s\t%s\t%d\t%s\t%s\t%d", owners_ID[i].vehicles[j].vehicle_type, owners_ID[i].vehicles[j].maker, owners_ID[i].vehicles[j].year_of_manufacture, owners_ID[i].vehicles[j].engine_no, owners_ID[i].vehicles[j].registration_no, owners_ID[i].vehicles[j].owners_ID);
            j++;
        }
        
        printf("\nWarning: If the owner doesn't have another car, the owner's entry will be deleted too.\nEnter registration number of vehicle to be deleted: ");
        scanf("%s", regno);
        
        flag = 0;
        for (j = 0; j < owners_ID[i].totalcars && flag == 0; j++)
        {
            if (strcmp(regno, owners_ID[i].vehicles[j].registration_no) == 0)
            {
                flag++;
            }
        }
        j--;
        
        if (flag == 0)
        {
            printf("Invalid registration number.\n");
        }
        else
        {
            for (k = j; k < owners_ID[i].totalcars - 1; k++)
            {
                owners_ID[i].vehicles[k] = owners_ID[i].vehicles[k+1];
            }
            owners_ID[i].totalcars--;
            retval++;
            if (owners_ID[i].totalcars == 0)
            {
                delete_owner(rc, id);
                retval++;
                rc--;
            }
            
            fp = fopen("cars.txt", "w");
            flag = 0;
            for(j = 0; j < vc && flag == 0; j++)
            {
                if (strcmp(regno, cars[j].registration_no) == 0)
                {
                    flag++;
                }
            }
            j--;
            
            for (k = j; k < vc - 1; k++)
            {
                cars[k] = cars[k+1];
                cars[k].serial_no = cars[k].serial_no - 1;
            }
            vc--;
            
            for (j = 0; j < vc; j++)
            {
                fprintf(fp, "%d\t%s\t%s\t%d\t%s\t%s\t%u\t%d\n", cars[j].serial_no, cars[j].vehicle_type, cars[j].maker, cars[j].year_of_manufacture, cars[j].engine_no, cars[j].registration_no, cars[j].vehicle_price, cars[j].owners_ID);
            }
            printf("Car deleted successfully.\n");
            fclose(fp);
        }
    }
    return retval;
}


int list_cars(int rc)
{
    int id, i, flag = 0;
    printf("Enter Owners ID: ");
    scanf("%d", &id);
    
    for (i = 0; i < rc && flag == 0; i++)
    {
        if (owners_ID[i].owner_ID == id)
        {
            flag++;
        }
    }
    i--;
    
    if (flag == 0)
    {
        printf("Owner not found.\n");
    }
    else
    {
        int j, k, n = owners_ID[i].totalcars;
        struct vehicle temp;
        for (j = 0; j < n - 1; j++)
        {
            for (k = 0; k < (n - 1 - j); k++)
            {
                if (owners_ID[i].vehicles[k].year_of_manufacture > owners_ID[i].vehicles[k+1].year_of_manufacture)
                {
                    temp = owners_ID[i].vehicles[k];
                    owners_ID[i].vehicles[k] = owners_ID[i].vehicles[k+1];
                    owners_ID[i].vehicles[k+1] = temp;
                }
            }
        }
        for (j = 0; j < n; j++)
        {
            printf("\n%s\t%s\t%d\t%s\t%s\t%d", owners_ID[i].vehicles[j].vehicle_type, owners_ID[i].vehicles[j].maker, owners_ID[i].vehicles[j].year_of_manufacture, owners_ID[i].vehicles[j].engine_no, owners_ID[i].vehicles[j].registration_no, owners_ID[i].vehicles[j].owners_ID);
        }
    }
    return 0;
}


int delete_1990(int vc, int rc)
{
    int i, k = 0, j, y, flag = 0;
    
    for (i = 0; i < vc; i++)
    {
        if (k > 0)
        {
            cars[i] = cars[i+k];
            cars[i].serial_no = i + 1;
        }
        if (cars[i].year_of_manufacture < 1990)
        {
            for (j = 0; j < rc; j++)
            {
                if (owners_ID[j].owner_ID == cars[i].owners_ID)
                {
                    for (y = 0; y < owners_ID[j].totalcars; y++)
                    {
                        if (owners_ID[j].vehicles[y].year_of_manufacture < 1990 && flag == 0)
                        {
                            flag++;
                            owners_ID[j].totalcars--;
                        }
                        if (flag == 1 && owners_ID[j].totalcars > 0)
                        {
                            owners_ID[j].vehicles[y] = owners_ID[j].vehicles[y+1];
                        }
                    }
                    if (owners_ID[j].totalcars == 0)
                    {
                        delete_owner(rc, owners_ID[j].owner_ID);
                    }
                }
            }
            k++;
            vc--;
            i--;
        }
    }
    
    if (k > 0)
    {
        fp = fopen("cars.txt", "w");
        for (i = 0; i < vc; i++)
        {
            fprintf(fp, "%d\t%s\t%s\t%d\t%s\t%s\t%u\t%d\n", cars[i].serial_no, cars[i].vehicle_type, cars[i].maker, cars[i].year_of_manufacture, cars[i].engine_no, cars[i].registration_no, cars[i].vehicle_price,     cars[i].owners_ID);
        }
        fclose(fp);
    
        printf("Cars manufactured before 1990 are deleted successfully.\n");
    }
    else
    {
        printf("No records found of cars manufactured before 1990.\n");
    }
    return vc;
}


int max_vehicles (int rc)
{
    int max = 0, max2 = 0, i, j;
    
    for (i = 0; i < rc; i++)
    {
        if (owners_ID[i].totalcars > max)
        {
            max2 = max;
            max = owners_ID[i].totalcars ;
        }
        if (owners_ID[i].totalcars > max2 && owners_ID[i].totalcars < max)
        {
            max2 = owners_ID[i].totalcars ;
        }
    }
    
    printf("\nOwners with maximum number of vehicles i.e. %d:\n\n", max);
    for (i = 0; i < rc; i++)
    {
        if (owners_ID[i].totalcars == max)
        {
            printf("%d\t%s\t%s\t%s\t%d\t%d\t%d\t%.2lf\n", owners_ID[i].owner_ID, owners_ID[i].owner_name, owners_ID[i].father_name, owners_ID[i].address, owners_ID[i].date_of_purchase, owners_ID[i].month_of_purchase, owners_ID[i].year_of_purchase, owners_ID[i].purchase_amount);
            for (j = 0; j < owners_ID[i].totalcars; j++)
            {
                printf("%s\t%s\t%d\t%s\t%s\t%d\n", owners_ID[i].vehicles[j].vehicle_type, owners_ID[i].vehicles[j].maker, owners_ID[i].vehicles[j].year_of_manufacture, owners_ID[i].vehicles[j].engine_no, owners_ID[i].vehicles[j].registration_no, owners_ID[i].vehicles[j].owners_ID);
            }
            printf("\n");
        }
    }
    
    printf("\nOwners with second maximum number of vehicles i.e. %d:\n\n", max2);
    for (i = 0; i < rc; i++)
    {
        if (owners_ID[i].totalcars == max2)
        {
            printf("%d\t%s\t%s\t%s\t%d\t%d\t%d\t%.2lf\n", owners_ID[i].owner_ID, owners_ID[i].owner_name, owners_ID[i].father_name, owners_ID[i].address, owners_ID[i].date_of_purchase, owners_ID[i].month_of_purchase, owners_ID[i].year_of_purchase, owners_ID[i].purchase_amount);
            for (j = 0; j < owners_ID[i].totalcars; j++)
            {
                printf("%s\t%s\t%d\t%s\t%s\t%d\n", owners_ID[i].vehicles[j].vehicle_type, owners_ID[i].vehicles[j].maker, owners_ID[i].vehicles[j].year_of_manufacture, owners_ID[i].vehicles[j].engine_no, owners_ID[i].vehicles[j].registration_no, owners_ID[i].vehicles[j].owners_ID);
            }
            printf("\n");
        }
    }
    return 0;
}


int two_wheelers(int rc)
{
    int i, j, k, flag = 0;
    for (i = 0; i < rc; i++)
    {
        for (j = 0; j < owners_ID[i].totalcars; j++)
        if (strcmp(owners_ID[i].vehicles[j].vehicle_type, "2wheel") == 0)
        {
            for (k = j + 1; k < owners_ID[i].totalcars; k++)
            {
                if (strcmp(owners_ID[i].vehicles[k].vehicle_type, "2wheel") == 0 && owners_ID[i].vehicles[k].year_of_manufacture == owners_ID[i].vehicles[j].year_of_manufacture)
                {
                    printf("%s\t%s\t%d\t%s\t%s\t%d\n", owners_ID[i].vehicles[k].vehicle_type, owners_ID[i].vehicles[k].maker, owners_ID[i].vehicles[k].year_of_manufacture, owners_ID[i].vehicles[k].engine_no, owners_ID[i].vehicles[k].registration_no, owners_ID[i].vehicles[k].owners_ID);
                    flag++;
                }
            }
            if (flag > 0)
            {
                printf("%s\t%s\t%d\t%s\t%s\t%d\n", owners_ID[i].vehicles[j].vehicle_type, owners_ID[i].vehicles[j].maker, owners_ID[i].vehicles[j].year_of_manufacture, owners_ID[i].vehicles[j].engine_no, owners_ID[i].vehicles[j].registration_no, owners_ID[i].vehicles[j].owners_ID);
            }
            flag = 0;
        }
    }
    return 0;
}


int costliest(int rc)
{
    int id, i, max = 0, maxindex = 0, flag = 0, j;
    printf("Enter owner's ID: ");
    scanf("%d", &id);
    
    for (i = 0; i < rc && flag == 0; i++)
    {
        if (owners_ID[i].owner_ID == id)
        {
            flag++;
        }
    }
    i--;
    
    for (j = 0; j < owners_ID[i].totalcars; j++)
    {
        if (owners_ID[i].vehicles[j].vehicle_price > max)
        {
            max = owners_ID[i].vehicles[j].vehicle_price;
            maxindex = j;
        }
    }
    
    printf("Costliest vehicle owned by the owner:\n%s\t%s\t%d\t%s\t%s\t%d\n", owners_ID[i].vehicles[maxindex].vehicle_type, owners_ID[i].vehicles[maxindex].maker, owners_ID[i].vehicles[maxindex].year_of_manufacture, owners_ID[i].vehicles[maxindex].engine_no, owners_ID[i].vehicles[maxindex].registration_no, owners_ID[i].vehicles[maxindex].owners_ID);
    return 0;
}


int brands(int rc)
{
    char brand[20];
    printf("Enter brand name: ");
    scanf("%s", brand);

    int i, j, count = 0, flag = 0;
    for (i = 0; i < rc; i++)
    {
        for (j = 0; j < owners_ID[i].totalcars && count < 2; j++)
        {
            if(strcmp(owners_ID[i].vehicles[j].maker, brand) == 0)
            {
                count++;
            }
        }
        if (count >= 2)
        {
            flag++;
            printf("\n%d\t%s\t%s\t%s\t%d\t%d\t%d\t%.2lf\n", owners_ID[i].owner_ID, owners_ID[i].owner_name, owners_ID[i].father_name, owners_ID[i].address, owners_ID[i].date_of_purchase, owners_ID[i].month_of_purchase, owners_ID[i].year_of_purchase, owners_ID[i].purchase_amount);
            for (j = 0; j < owners_ID[i].totalcars; j++)
            {
                if(strcmp(owners_ID[i].vehicles[j].maker, brand) == 0)
                {
                    printf("%s\t%s\t%d\t%s\t%s\t%d\n", owners_ID[i].vehicles[j].vehicle_type, owners_ID[i].vehicles[j].maker, owners_ID[i].vehicles[j].year_of_manufacture, owners_ID[i].vehicles[j].engine_no, owners_ID[i].vehicles[j].registration_no, owners_ID[i].vehicles[j].owners_ID);
                }
            }
        }
        count = 0;
    }
    
    if (flag == 0)
    {
        printf("There are no owners who own more than one vehicles of the chosen brand.\n");
    }
    return 0;
}


int three_wheelers(int vc)
{
    int year, i, flag = 0;
    printf("Enter a year: ");
    scanf("%d", &year);
    
    for (i = 0; i < vc; i++)
    {
        if (strcmp(cars[i].vehicle_type, "3wheel") == 0 && cars[i].year_of_manufacture == year)
        {
            printf("%d\t%s\t%s\t%d\t%s\t%s\t%u\t%d\n", cars[i].serial_no, cars[i].vehicle_type, cars[i].maker, cars[i].year_of_manufacture, cars[i].engine_no, cars[i].registration_no, cars[i].vehicle_price,     cars[i].owners_ID);
            flag++;
        }
    }
    if (flag == 0)
    {
        printf("There are no 3 wheelers bought by any owner in the given year.\n");
    }
    
    return 0;
}
