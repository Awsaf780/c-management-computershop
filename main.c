#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct computer
{
    char model[100];
    char CPU[100];
    int ram;
    float price;
    int storage;

} a[100];

int num=0; //number of valid data stored in array globally defined

//user defined functions

void edit_info(int i);
void output();
void modify();
void append();
void password();
void del(int d);
void search();

//functions under search()

void search_name();
void search_priceRange();

void main()
{
    password();

    FILE *data;
    data = fopen("Database.dat", "r");
    num = fread(a, sizeof(struct computer), 100, data);

    fclose(data);

    int c;

    while(1)
    {
        system("cls");
        system("color 04");
        printf("#1. Enter Records\n");
        printf("#2. Show Records\n");
        printf("#3. Search Records\n");
        printf("#4. Modify or Delete\n");
        printf("#5. Exit\n");
        printf("\n\nEnter your choice: ");
        scanf("%d", &c);


        switch(c)
        {
        case 1:
            append();
            break;
        case 4:
            modify();
            break;
        case 2:
            output();
            break;
        case 5:
            system("cls");
            exit(1);
        case 3:
            search();
            break;
        }

    }

}


void password()
{
    int i, ch;
    char password[10];

    system("cls");

    printf("Enter passcode: ");

    for(i=0; i<4; i++) //stars will be displayed in program
    {
        ch = getch();
        password[i] = ch;
        ch = '*' ;
        printf("%c",ch);
    }

    password[i] = '\0';

    if(strcmp(password, "1234")==0)
    {
        return;
    }

    else
    {
        main(); //keep prompting for authentic PIN
    }
}



void output()
{
    FILE *data;
    data = fopen("Database.dat", "r");
    num = fread(a, sizeof(struct computer), 100, data);

    system("cls");

    printf("COMPUTERS AVAILABLE IN STOCK: ");

    int i;
    for(i=0; i<num; i++)
    {
        printf("\n\n\n");
        printf("ENTRY #%d\n", i+1);
        printf("__________________________\n");
        printf("Model Name     :  %s\n", a[i].model);
        printf("Processor Type :  %s\n", a[i].CPU);
        printf("Size of RAM    :  %d GB\n", a[i].ram);
        printf("Size of SSD    :  %d GB\n", a[i].storage);
        printf("Price in $     :  $%.2f\n", a[i].price);
    }

    fclose(data);
    getch();
}



void modify()
{
    int i;
    char n;
    char search_name[20];
    int registr;
    int edit=0;
    char proceed;

    FILE *data;
    data = fopen("Database.dat", "r");

    system("cls");
    fflush(stdin);

    printf("Search For A Computer in Stock\n");

    printf("Enter Model Name: ");
    gets(search_name);

    for(i=0; i<100; i++)
    {
        if(strcmp(search_name, a[i].model)==0)
        {
            printf("\n\n\n");
            printf("\Search result index #%d\n", i+1);
            printf("__________________________\n");
            printf("Model Name     :  %s\n", a[i].model);
            printf("Processor Type :  %s\n", a[i].CPU);
            printf("Size of RAM    :  %d GB\n", a[i].ram);
            printf("Size of SSD    :  %d GB\n", a[i].storage);
            printf("Price in $     :  $%.2f\n", a[i].price);
            edit++;
        }
        else
        {
            continue;
        }
    }
    if(edit!=0)
    {
        printf("\n\nPress M to modify or D to delete (D/M)");
        proceed = getch();
        if(proceed == 'M' || proceed =='m')
        {

            printf("\n\nEnter index number to modify: ");
            scanf("%d", &registr);
            registr = registr-1;

            edit_info(registr);
        }
        else if(proceed == 'd' || proceed== 'D')
        {
            system("color 40");
            printf("\n\nEnter index number to Delete: ");
            scanf("%d", &registr);
            registr = registr-1;

            del(registr);
        }
    }
    else
    {

        printf("\n\nNo Results found!");
        getch();
    }

}


void edit_info(int i)
{
    FILE *data;
    data = fopen("Database.dat", "w");

    system("cls");

    printf("Enter Model name: ");
    fflush(stdin);
    gets(a[i].model);

    printf("Enter CPU type: ");
    fflush(stdin);
    gets(a[i].CPU);


    printf("Enter RAM Size: ");
    fflush(stdin);
    scanf("%d", &a[i].ram);


    printf("Enter Storage size: ");
    fflush(stdin);
    scanf("%d", &a[i].storage);


    printf("Enter Price: ");
    fflush(stdin);
    scanf("%f", &a[i].price);

    fwrite(a, sizeof(struct computer), num, data);
    fclose(data);
    output();
}



void append()
{
    FILE *data;
    data = fopen("Database.dat", "a");
    num = fread(a, sizeof(struct computer), 100, data);

    int i;
    char c;

    for(i=0; ; i++)
    {
        system("cls");

        printf("Enter Model name: ");
        fflush(stdin);
        gets(a[i].model);

        if(strcmp(a[i].model, "")==0)
            break;

        printf("Enter CPU type: ");
        fflush(stdin);
        gets(a[i].CPU);


        printf("Enter RAM Size: ");
        fflush(stdin);
        scanf("%d", &a[i].ram);


        printf("Enter Storage size: ");
        fflush(stdin);
        scanf("%d", &a[i].storage);


        printf("Enter Price: ");
        fflush(stdin);
        scanf("%f", &a[i].price);

        fflush(stdin);

    }
    num = i; //Updates the valid number of storage

    fwrite(a, sizeof(struct computer), num, data);
    fclose(data);
}



void search()
{
    system("cls");
    int choice;

    printf("Categories to search: \n\n");
    printf("#1. Search by name\n");
    printf("#2. Search by range of price: \n");
    printf("#3. Return to main menu: \n");


    printf("\nEnter your choice: ");

    scanf("%d", &choice);

    switch(choice)
    {
    case 1:
        search_name();
        break;
    case 2:
        search_priceRange();
        break;

    default:
        break;
    }
}

void search_name()
{
    system("cls");
    int i, count=0;
    char again;
    char name[20];

    printf("Search For A Computer in Stock\n");
    fflush(stdin);

    printf("Enter Model Name: ");
    gets(name);

    for(i=0; i<100; i++)
    {
        if(strcmp(name, a[i].model)==0)
        {
            printf("\n\n\n");
            printf("\Search result index #%d\n", i+1);
            printf("__________________________\n");
            printf("Model Name     :  %s\n", a[i].model);
            printf("Processor Type :  %s\n", a[i].CPU);
            printf("Size of RAM    :  %d GB\n", a[i].ram);
            printf("Size of SSD    :  %d GB\n", a[i].storage);
            printf("Price in $     :  $%.2f\n", a[i].price);
            count++;
        }
        else
        {
            continue;
        }
    }
    if(count == 0)
    {
        printf("\n\nNo results found");
    }
    else
    {
        printf("\n\nWe found %d results", count);
        printf("\nDo you want to search again? (y/n)");
        again = getch();
        if(again == 'y')
            search();
        else
            return;
    }
    getch();
}

void search_priceRange()
{
    system("cls");

    printf("Search For A Computer in Stock\n");
    int min, max, i, j;
    int count = 0;
    char again;
    printf("Enter Minimum price: ");
    scanf("%d", &min);
    printf("Enter Maximum Price: ");
    scanf("%d", &max);


    for(i=0; i<100; i++)
    {
        for(j=min; j<=max; j++)
        {
            if(j == a[i].price)
            {


                printf("\n\n\n");
                printf("\Search result index #%d\n", i+1);
                printf("__________________________\n");
                printf("Model Name     :  %s\n", a[i].model);
                printf("Processor Type :  %s\n", a[i].CPU);
                printf("Size of RAM    :  %d GB\n", a[i].ram);
                printf("Size of SSD    :  %d GB\n", a[i].storage);
                printf("Price in $     :  $%.2f\n", a[i].price);
                count++;

            }
            else
            {
                continue;
            }
        }

    }
    if(count == 0)
    {
        printf("\n\nNo results found");
    }
    else
    {
        printf("\n\nWe found %d results", count);
        printf("\nDo you want to search again? (y/n)");
        again = getch();
        if(again == 'y')
            search();
        else
            return;
    }
}

void del(int d)
{
    int i;

    FILE *data;
    data = fopen("Database.dat", "w");

    for(i=d; i<=num; i++)
    {
        a[i] = a[i + 1];
    }
    num--;
    fwrite(a, sizeof(struct computer), num, data);
    fclose(data);

    printf("\nSuccessfully deleted");
    system("color 04");
    getch();
}
