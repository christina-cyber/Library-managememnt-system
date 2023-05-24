#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

struct books{
    int id;
    char bookName[50];
    char authorName[50];
    char date[12];
    int vol;
}a;

struct student{
    int id;
    char sName[50];
    char sClass[50];
    int sRoll;
    char bookName[50];
    char date[12];

}s;

FILE *fp;
void addBook(){
    system("cls");

    fp = fopen("books.txt", "ab");

    printf("Enter book id: ");
    scanf("%d", &a.id);

    printf("Enter book name: ");
    fflush(stdin);
    gets(a.bookName);


    printf("Enter author name: ");
    fflush(stdin);
    gets(a.authorName);

    printf("Published year : ");
    fflush(stdin);
    gets(a.date);

    printf("NO. of books available: ");
    fflush(stdin);
    scanf("%d",&a.vol);



    printf("Book Added Successfully");

    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);
}


void booksList(){

    system("cls");
    printf("Available Books at MMC Library\n\n");
    printf( "\nBook id \t Book Name\t Author \t Published year \t volume");

    fp = fopen("books.txt", "rb");
    while(fread(&a, sizeof(a), 1, fp) == 1){
        printf("\n%d \t %s \t %s \t %S \t %d\n", a.id, a.bookName, a.authorName, a.date, a.vol);
    }

    fclose(fp);
}

void del(){
    int id, f=0;
    system("cls");
    printf(" Remove Books \n\n");
    printf("Enter Book id to remove: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("books.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while(fread(&a, sizeof(a), 1, fp) == 1){
        if(id == a.id){
            f=1;
        }else{
            fwrite(&a, sizeof(a), 1, ft);
        }
    }

    if(f==1){
        printf("\n\nDeleted Successfully.");
    }else{
        printf("\n\nRecord Not Found !");
    }

    fclose(fp);
    fclose(ft);

    remove("books.txt");
    rename("temp.txt", "books.txt");

}


void issueBook(){

    int f=0;

    system("cls");
    printf("Issue Books \n\n");

    printf("Enter Book id to issue: ");
    scanf("%d", &s.id);

    //Check if we have book of given id
    fp = fopen("books.txt", "rb");

    while(fread(&a, sizeof(a), 1, fp) == 1){
        if(a.id == s.id){
            strcpy(s.bookName, a.bookName);
            f=1;
            break;
        }
    }

    if(f==0){
        printf("No book found with this id\n");
        printf("Please try again...\n\n");
        return;
    }

    fp = fopen("issue.txt", "ab");

    printf("Enter Student Name: ");
    fflush(stdin);
    gets(s.sName);

    printf("Enter Student Faculy: ");
    fflush(stdin);
    gets(s.sClass);

    printf("Enter Student Roll: ");
    scanf("%d", &s.sRoll);

    printf("Enter today's date: ");
    gets(s.date);

    printf("Book Issued Successfully\n\n");

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
}

void issueList(){
    system("cls");
    printf(" Book Issue List \n\n");

    printf("%s\t %s\t %s\t %s\t %s\t %s\n\n", "S.id", "Name", "Class", "Roll", "Book Name", "Date");

    fp = fopen("issue.txt", "rb");
    while(fread(&s, sizeof(s), 1, fp) == 1){
        printf("%d\t %s\t %s\t %d\t %s\t %s\n", s.id, s.sName, s.sClass, s.sRoll, s.bookName, s.date);
    }

    fclose(fp);
}
void menu()
{
 printf(" MMC Library Management System \n");
        printf("1.Add Book\n");
        printf("2.Books List\n");
        printf("3.Remove Book\n");
        printf("4.Issue Book\n");
        printf("5.Issued Book List\n");
        printf("0.Exit\n\n");

}

int main(){

    int ch;


    do{
        menu();
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch(ch){
        case 0:
            exit(0);

        case 1:
            addBook();
            break;

        case 2:
            booksList();
            break;

        case 3:
            del();
            break;

        case 4:
            issueBook();
            break;

        case 5:
            issueList();
            break;

        default:
            printf("Invalid Choice...\n\n");

        }
        printf("Press Any Key To Continue...");
        getch();
    }while(ch!=0);

    return 0;
}


