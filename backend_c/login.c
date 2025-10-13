#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct
{
    char username[20];
    char password[20];
    char BckpQues[100];
    char BckpAns[20];
}Credentials; // a structure to store the user credentials
void Setup() // this helps in creating a new user account
{
    Credentials cr,new;
    FILE *ptr=NULL;
    while(1)
    {
        ptr=fopen("../data/loginfile.dat","rb");
        int f=0;
        printf("Enter the username: ");
        scanf("%[^\n]s",new.username);
        getchar();
        while(fread(&cr,sizeof(Credentials),1,ptr))
        {
            if(strcmp(cr.username,new.username)==0)
            {
                printf("username already exists\n");
                fclose(ptr);
                f++;
                break;
            }
        }
        if(f==0)
        break;
    }
    fclose(ptr);
    printf("Enter the password: ");
    scanf("%[^\n]s",new.password);
    getchar();
    printf("Enter the question to recover the credentials: ");
    scanf("%[^\n]s",new.BckpQues);
    getchar();
    printf("Enter the backup answer: ");
    scanf("%[^\n]s",new.BckpAns);
    getchar();
    ptr=fopen("../data/loginfile.dat","ab");
    fwrite(&new,sizeof(Credentials),1,ptr);
    fclose(ptr);
    printf("Account created successfully\n");
    return;
}
int Login() // this helps the registered user in loging in to the inventory management system
{
    Credentials cr;
    FILE *ptr=fopen("../data/loginfile.dat","rb");
    if(ptr == NULL)
    {
        printf("No credentials found. Let's set up your account\n");
        FILE *ptr=fopen("../data/loginfile.dat","ab");
        fclose(ptr);
        Setup();
        ptr=fopen("../data/loginfile.dat","rb");
    }
    else
    {
        fseek(ptr,0,SEEK_END);
        if(ftell(ptr)==0)
        {
            fclose(ptr);
            printf("Login file is empty. Setting up new account.\n");
            Setup();
            ptr=fopen("../data/loginfile.dat","rb");
        }
        else
        {
            rewind(ptr);
        }
    }
    char un[20],ps[20];
    printf("Enter Username: ");
    scanf("%[^\n]s",un);
    printf("Enter password: ");
    getchar();
    scanf("%[^\n]s",ps);
    while(fread(&cr,sizeof(Credentials),1,ptr))
    {
        if(strcmp(un,cr.username)==0 && strcmp(ps,cr.password)==0)
        {
            fclose(ptr);
            printf("Login Successful\n");
            return 1;
        }
    }
    fclose(ptr);
    printf("Invalid Credentials\n");
    return 0;
}
void changepass() // this provides password related assistance to the registered user
{
    Credentials cr;
    char user[50];
    int f=0;
    FILE *ptr=fopen("../data/loginfile.dat","rb");
    printf("Enter Username: ");
    scanf("%[^\n]s",user);
    while(fread(&cr,sizeof(Credentials),1,ptr))
    {
        if(strcmp(cr.username,user)==0)
        {
            f++;
            break;
        }
    }
    fclose(ptr);
    if(f==0)
    {
        printf("Username not found\n");
        return;
    }
    int ch;
    char a[20],npass[20];
    while(1){
        printf("1. See current password\n2. Change new password\n3.Go back to Main Menu\n\nEnter your choice: ");
        scanf("%d",&ch);
        if(ch==3)
        return;
        getchar();
        printf("Answer the Security Question:\n%s\n",cr.BckpQues);
        scanf("%[^\n]s",a);
        getchar();
        if(strcmp(a,cr.BckpAns)==0){
            switch(ch){
                case 1:
                printf("Your current Password is: %s",cr.password); break;
                case 2:
                printf("Enter new Password: ");
                scanf("%[^\n]s",npass);
                getchar();
                ptr=fopen("../data/loginfile.dat","rb");
                FILE *pt=fopen("../data/templogin.dat","wb");
                while(fread(&cr,sizeof(Credentials),1,ptr))
                {
                    if(strcmp(cr.username,user)==0)
                    {
                        strcpy(cr.password,npass);
                    }
                    fwrite(&cr,sizeof(Credentials),1,pt);
                }
                fclose(pt);
                fclose(ptr);
                remove("../data/loginfile.dat");
                rename("../data/templogin.dat","../data/loginfile.dat");
                printf("Password changed successfully\n"); break;
                default:
                printf("Invalid choice. Try again.\n");
            }
        }
        else
        printf("Wrong Answer\n");
        return;
    }
}
void changeuser() // this provides username related assistance to the registered user
{
    Credentials cr;
    char user[50];
    int f=0;
    FILE *ptr=fopen("../data/loginfile.dat","rb");
    printf("Enter Username: ");
    scanf("%[^\n]s",user);
    while(fread(&cr,sizeof(Credentials),1,ptr))
    {
        if(strcmp(cr.username,user)==0)
        {
            f++;
            break;
        }
    }
    fclose(ptr);
    if(f==0)
    {
        printf("Username not found\n");
        return;
    }
    int ch;
    char a[20],nuser[20];
    while(1){
        printf("1. See current username\n2. Change new username\n3.Go back to Main Menu\n\nEnter your choice: ");
        scanf("%d",&ch);
        if(ch==3)
        return;
        getchar();
        printf("Answer the Security Question:\n%s\n",cr.BckpQues);
        scanf("%[^\n]s",a);
        getchar();
        if(strcmp(a,cr.BckpAns)==0){
            switch(ch){
                case 1:
                printf("Your current Username is: %s\n",cr.username); break;
                case 2:
                printf("Enter new Username: ");
                scanf("%[^\n]s",nuser);
                getchar();
                ptr=fopen("../data/loginfile.dat","rb");
                int flag=0;
                while(fread(&cr,sizeof(Credentials),1,ptr))
                {
                    if(strcmp(cr.username,nuser)==0)
                    {
                        printf("username already exists\n");
                        flag++;
                        break;
                    }
                }
                fclose(ptr);
                if(flag!=0)
                break;
                ptr=fopen("../data/loginfile.dat","rb");
                FILE *pt=fopen("../data/templogin.dat","wb");
                while(fread(&cr,sizeof(Credentials),1,ptr))
                {
                    if(strcmp(cr.username,user)==0)
                    {
                        strcpy(cr.username,nuser);
                    }
                    fwrite(&cr,sizeof(Credentials),1,pt);
                }
                fclose(pt);
                fclose(ptr);
                remove("../data/loginfile.dat");
                rename("../data/templogin.dat","../data/loginfile.dat");
                printf("Username changed successfully\n"); break;
                default:
                printf("Invalid choice. Try again.\n");
            }
        }
        else
        printf("Wrong Answer\n");
        return;
    }
}
void newbackup() // this provides account backup related assistance to the registered user
{
    Credentials cr;
    int f=0;
    char un[20],ps[20],bq[100],ba[20];
    FILE *ptr=fopen("../data/loginfile.dat","rb");
    printf("Enter Username: ");
    scanf("%[^\n]s",un);
    getchar();
    while(fread(&cr,sizeof(Credentials),1,ptr))
    {
        if(strcmp(cr.username,un)==0)
        {
            f++;
            break;
        }
    }
    fclose(ptr);
    if(f==0)
    {
        printf("Username not found\n");
        return;
    }
    fclose(ptr);
    int ch;
    while(1){
        printf("1. See current security question\n2. Change new security question\n3.Go back to Main Menu\n\nEnter your choice: ");
        scanf("%d",&ch);
        getchar();
        if(ch==3)
        return;
        printf("Enter password: ");
        scanf("%[^\n]s",ps);
        getchar();
        if(strcmp(un,cr.username)==0 && strcmp(ps,cr.password)==0){
            switch(ch){
                case 1:
                printf("Current Security Question:\n");
                printf("%s\n%s",cr.BckpQues,cr.BckpAns); break;
                case 2:
                printf("Enter new Question: ");
                scanf("%[^\n]s",bq);
                getchar();
                printf("Enter the Answer: ");
                scanf("%[^\n]s",ba);
                getchar();
                ptr=fopen("../data/loginfile.dat","rb");
                FILE *pt=fopen("../data/templogin.dat","wb");
                while(fread(&cr,sizeof(Credentials),1,ptr))
                {
                    if(strcmp(cr.username,un)==0)
                    {
                        strcpy(cr.BckpQues,bq);
                        strcpy(cr.BckpAns,ba);
                    }
                    fwrite(&cr,sizeof(Credentials),1,pt);
                }
                fclose(pt);
                fclose(ptr);
                remove("../data/loginfile.dat");
                rename("../data/templogin.dat","../data/loginfile.dat");
                printf("Security question changed successfully\n"); break;
                default:
                printf("Invalid choice. Try again.\n");
            }
        }
        else
        printf("Incorrect Login Credentials\n");
        return;
    }
}
void deleteacc() // deletes an account from the records
{
    /*
        deletion is done by copying the content of the file "../data/loginfile.dat" to
        a temporary file "../data/templogin.dat" except for the account that is to be
        deleted, then the "../data/loginfile.dat" file is deleted and the "../data/templogin.dat"
        file is renamed to "../data/loginfile.dat"
    */
    char un[20],ps[20];
    int c,f=0;
    Credentials cr;
    FILE *ptr=fopen("../data/loginfile.dat","rb");
    printf("Enter username: ");
    scanf("%[^\n]s",un);
    getchar();
    printf("Enter password: ");
    scanf("%[^\n]s",ps);
    while(fread(&cr,sizeof(Credentials),1,ptr))
    {
        if(strcmp(un,cr.username)==0 && strcmp(ps,cr.password)==0)
        {
            f++;
            break;
        }
    }
    fclose(ptr);
    if(f==0)
    {
        printf("Account not found\n");
        return;
    }
    while(1)
    {
        printf("Are you sure you want to delete the account?\n1. Yes\n2. No (go back)\n\nEnter your choice: ");
        scanf("%d",&c);
        switch(c)
        {
            case 1:
            ptr=fopen("../data/loginfile.dat","rb");
            FILE *pt=fopen("../data/templogin.dat","wb");
            while(fread(&cr,sizeof(Credentials),1,ptr))
            {
                if(strcmp(un,cr.username)==0 && strcmp(ps,cr.password)==0)
                {
                    continue;
                }
                fwrite(&cr,sizeof(Credentials),1,pt);
            }
            fclose(pt);
            fclose(ptr);
            remove("../data/loginfile.dat");
            rename("../data/templogin.dat","../data/loginfile.dat");
            printf("Account deleted successfully\n");
            return;
            case 2:
            return;
            default:
            printf("Invalid Choice. Try Again");
        }
    }
}
int main() // the main menu function for login module
{
    int c;
    while(1)
    {
        printf("WELCOME TO THE LOGIN PORTAL\n\n");
        printf("1. Login\n2. Password related issues\n3. Username related issues\n4. Backup Question related issues\n5. Create new profile\n6. Delete a profile\n7. Exit\n\nEnter your choice: ");
        scanf("%d",&c);
        getchar();
        switch(c){
            case 1:
            return Login();
            case 2:
            changepass(); break;
            case 3:
            changeuser(); break;
            case 4:
            newbackup(); break;
            case 5:
            Setup(); break;
            case 6:
            deleteacc(); break;
            case 7:
            printf("Exiting.....");
            printf("\nThank You!");
            exit(0);
            default:
            printf("Invalid Choice. Try Again.\n");
            printf("..............................................\n");
        }
    }
}