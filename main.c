#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

void gotoxy(int x,int y);
void password(char pwd[]);
void rectangle(int x,int y,int l,int b);
void title();
void welcome();

void admin();
void add_user();
void del_user();
void view_log();

void staff();
void flights();


FILE *fp,*fp2,*tfp;
struct
    {
        char uid[4];
        char name[30], nid[30];

    }user;


struct
{
    char name[30];
    char nid[20];
    char gender[5];
    char dob[15];
    char nation[15];

}info;





int main()
{
    welcome();
    char c;
    do
    {
        system("cls");
        rectangle(0,0,80,23);
        gotoxy(10,11);
        printf("Press A to Log in as ADMINISTRATOR or S to log in as STAFF\n");
        c=getche();

        if(c=='A'||c=='a')
        {
            admin();
            break;
        }
        if (c=='S'||c=='s')
        {
            staff();
            break;
        }
        if (c==27) exit(0);

    }while(1);


    return 0;
}




    void admin()
{

    char uname[30], pass[30]={0};

    int c=0,cnt=0;
    do
    {
    c=0;
    system("cls");
    gotoxy(7,5);printf("Only THREE attempts shall be allowed to enter username and password.");
    rectangle(10,8,70,15);
    gotoxy(23,10); printf("Enter User name : "); scanf("%s",uname);
    gotoxy(23,12); printf("Password        : "); password(pass);


    cnt++;
    if (cnt==3)
    {
        title();
        gotoxy(25,8); printf("Invalid User name or Password!\a");
        gotoxy(22,11);printf("Press any key to exit the program...");
        getch();


        exit(0);
    }
    if(strcmp(uname,"RAHAEM")==0&&strcmp(pass,"RHE")==0)
        c=1;
    else
    {
        title();
        gotoxy(25,10); printf("Invalid User name or Password!\a");
        getch();

    }

    } while(c!=1);

do
    {
    title();

    int ch,i;
    char ex,key;
    gotoxy(30,6);printf("1. Add User");
    gotoxy(30,7);printf("2. Delete User");
    gotoxy(30,8);printf("3. View Log");
    gotoxy(30,9);printf("4. Log in as staff");
    gotoxy(30,10);printf("5. Exit");
    gotoxy(23,15);printf(" Press a number between the range [1-4]  ");
    key=getche();//Reads a character entered by user andstroes in char variable key
    ch=key-48;//changes char key into integer ch eg. '1'(ascii value 49)--->49-48=1




    switch(ch)
    {
        case 1:

        add_user();


        break;
        case 2:


        del_user();


        break;
        case 3:

        view_log();


        break;


        case 4:
          staff();


        case 5:
        title();
        gotoxy(15,10); printf("Are you sure you want to exit? <Y/N> : ");
        ex=getche();
        if (ex=='Y'||ex=='y') exit(0);


        break;

        default:
        title();
        gotoxy(10,10); printf("Your input is out of range! Enter a choice between 1 to 5!");
        gotoxy(15,12); printf("Press ENTER to return to main menu...");
        getch();

    }

    } while(1);
    return;
}


void add_user()
{

int err=0,c=0;
        char str1[30],str2[30];
        do{
            title();
            err=0;
            gotoxy(25,8);printf("User Name        : ");
            scanf("%s",user.name);
            fp=fopen("USER.DAT","r");

        c=0;
                while(fscanf(fp,"%s %s\n",str1,str2)!=EOF)
                {

                    if(strcmp(str1,user.name)==0)
                        c++;
                }

                fclose(fp);
                if(c!=0)
                {
                    gotoxy(10,10);
                    printf("User name already exists! Please enter a new user name.\a");
                    getch();
                    err++;
                    continue;
                }




            gotoxy(25,10);printf("National Id      : ");
            scanf("%s",user.nid);


        }while(err!=0);


        fp=fopen("USER.DAT","a");

        fprintf(fp,"%s %s\n",user.name,user.nid);
        fclose(fp);

        title();
        gotoxy(25,10); printf("Record ADDED successfully!");
        getch();

}




void del_user()
{
   char str1[30],str2[30],ch;
    int c=0;

       title();

            gotoxy(25,8);printf("User Name    : ");
            scanf("%s",user.name);
            gotoxy(25,10);printf("National Id  : ");
             scanf("%s",user.nid);
        fp=fopen("USER.DAT","r");

         while(fscanf(fp,"%s %s\n",str1,str2)!=EOF)
         {

             if(strcmp(user.name,str1)==0&&strcmp(user.nid,str2)==0)
                c++;
         }

        fclose(fp);
        title();
        if (c==0)
        {

            gotoxy(10,10); printf("Cannot find the given combination of USER NAME and NATIONAL ID!\a");
            getch();
            return;
        }

            gotoxy(15,10); printf("Are you sure you want to DELETE this user? <Y/N> : ");
            ch=getche();
            if(ch=='Y'||ch=='y')
            {
                fp=fopen("USER.DAT","r");
                tfp=fopen("temp.dat","a");
                while(fscanf(fp,"%s %s\n",str1,str2)!=EOF)
                {
                    if(strcmp(user.name,str1)!=0||strcmp(user.nid,str2)!=0)
                       fprintf(tfp,"%s %s\n",str1,str2);
                }
                fclose(fp);
                fclose(tfp);
                system("del USER.DAT");
                system("ren temp.dat USER.DAT");



                title();
                gotoxy(25,10); printf("Record DELETED successfully!");
                getch();
            }

}
void view_log()
{
    char str1[100],str2[100];

    title();

printf("\n\n\n");
  fp=fopen("USER.DAT","r");


while (fscanf(fp,"%s %s",str1,str2)!=EOF)
{
        printf("\t%s %s\n",str1,str2);
}

getch();

        fclose(fp);



}

void staff()
{
   int i,ch;

    char str1[30],str2[30];
    int c=0;

    do
    {
        system("cls");
        rectangle(10,8,70,15);
        gotoxy(23,10); printf("Enter User name : "); scanf("%s",user.name);
        gotoxy(23,12); printf("National ID     : "); scanf("%s",user.nid);

        c=0;
        fp=fopen("USER.DAT","r");
        while(fscanf(fp,"%s %s\n",str1,str2)!=EOF)
        {

             if((strcmp(user.name,str1)==0)&&(strcmp(user.nid,str2)==0))
             {
                 c++;
             }
         }

        fclose(fp);

        title();
        if (c==0)
        {
            gotoxy(10,10); printf("ERROR USER NAME AND NATIONAL ID!\a");
            getch();
        }
        else break;
    } while(1);


       flights();

}


void flights()
{


    fflush(stdin);
gotoxy(16,4);printf("Enter your name: ");
gets(info.name);
fflush(stdin);
gotoxy(16,5);printf("Enter your national ID no: ");
gets(info.nid);
fflush(stdin);
gotoxy(16,6);printf("Enter your gender (M/F): ");
gets(info.gender);
fflush(stdin);
gotoxy(16,7);printf("Enter you date of birth (dd/mm/yy): ");
gets(info.dob);
fflush(stdin);
gotoxy(16,8);printf("Enter your nationality: ");
gets(info.nation);


    title();



    int ch1,ch2;
    char key1,key2;

    gotoxy(30,6);printf("1. Dhaka");
    gotoxy(30,7);printf("2. Chittagong");
    gotoxy(30,8);printf("3. Sylhet");
    gotoxy(30,9);printf("4. Cox's Bazar");
    gotoxy(30,10);printf("5. Jessore");
    gotoxy(30,11);printf("6. Rajhshahi");
    gotoxy(30,12);printf("7. Saidpur");
    gotoxy(30,14); printf("From:");
    gotoxy(23,15);printf(" Press a number between the range [1-7]  ");
    key1=getche();//Reads a character entered by user and stroes in char variable key
    ch1=key1-48;//changes char key into integer ch eg. '1'(ascii value 49)--->49-48=1
    gotoxy(30,17); printf("To:");
    gotoxy(23,18);printf(" Press a number between the range [1-7]  ");
    key2=getche();//Reads a character entered by user and stroes in char variable key
    ch2=key2-48;//changes char key into integer ch eg. '1'(ascii value 49)--->49-48=1
    title();




        int key3;
        char ch3;
    gotoxy(30,6);printf("1. Biman Bangladesh Airlines");
    gotoxy(30,7);printf("2. NovoAir");
    gotoxy(30,8);printf("3. Regent Airways");
    gotoxy(30,9);printf("4. Us-Bangla Airlines");

    gotoxy(30,14); printf("Select Airline");
    gotoxy(23,15);printf(" Press a number between the range [1-4]  ");
    key3=getche();//Reads a character entered by user and stroes in char variable key
    ch3=key3-48;//changes char key into integer ch eg. '1'(ascii value 49)--->49-48=1


title();


    int key4;
        char ch4;
    gotoxy(30,6);printf("1. 10.30 AM - 11.10 AM");
    gotoxy(30,7);printf("2. 01.10 PM - 02.50 PM");
    gotoxy(30,8);printf("3. 05.30 PM - 06.10 PM");
    gotoxy(30,9);printf("4. 08.10 PM - 09.50 PM");
    gotoxy(30,10);printf("5. 10.30 PM - 11.10 PM");
    gotoxy(23,13);printf(" Press a number between the range [1-4]  ");
key4=getche();//Reads a character entered by user and stroes in char variable key
    ch4=key4-48;//changes char key into integer ch eg. '1'(ascii value 49)--->49-48=1

title();

      char date[13],ex;
      gotoxy(24,6);printf("Enter the date (dd/mm/yy):  ");
      scanf("%s",&date);



title();


gotoxy(12,3);printf("Name: ");
puts(info.name);
gotoxy(12,4);printf("National ID: ");
puts(info.nid);
gotoxy(12,5);printf("Gender: ");
puts(info.gender);
gotoxy(12,6);printf("Date of Birth: ");
puts(info.dob);
gotoxy(12,7);printf("Nationality: ");
puts(info.nation);






if(ch1==1&&ch2==2){
    gotoxy(12,9);printf("From Dhaka To Chittagong");gotoxy(12,10);printf("Price: 3700 Taka");}
    else if(ch1==1&&ch2==3){
    gotoxy(12,9);printf("From Dhaka To Sylhet");gotoxy(12,10);printf("Price: 3500 Taka");}
        else if(ch1==1&&ch2==4){
        gotoxy(12,9);printf("From Dhaka To Cox's Bazar");gotoxy(12,10);printf("Price: 4300 Taka");}
        else if(ch1==1&&ch2==5){
        gotoxy(12,9);printf("From Dhaka To Jessore");gotoxy(12,10);printf("Price: 3700 Taka");}
        else if(ch1==1&&ch2==6){
        gotoxy(12,9);printf("From Dhaka To Rajshahi");gotoxy(12,10);printf("Price: 3900 Taka");}
        else if(ch1==1&&ch2==7){
        gotoxy(12,9);printf("From Dhaka To Saidpur");gotoxy(12,10);printf("Price: 3900 Taka");}

        else if(ch1==2&&ch2==1){
        gotoxy(12,9);printf("From Chittagong To Dhaka");gotoxy(12,10);printf("Price: 3700 Taka");}
        else if(ch1==2&&ch2==3){
        gotoxy(12,9);printf("From Chittagong To Sylhet");gotoxy(12,10);printf("Price: 4000 Taka");}
        else if(ch1==2&&ch2==4){
        gotoxy(12,9);printf("From Chittagong To Cox's Bazar");gotoxy(12,10);printf("Price: 2000 Taka");}
        else if(ch1==2&&ch2==5){
        gotoxy(12,9);printf("From Chittagong To Jessore");gotoxy(12,10);printf("Price: 3300 Taka");}
        else if(ch1==2&&ch2==6){
        gotoxy(12,9);printf("From Chittagong To Rajshahi");gotoxy(12,10);printf("Price: 4500 Taka");}
        else if(ch1==2&&ch2==7){
        gotoxy(12,9);printf("From Chittagong To Saidpur");gotoxy(12,10);printf("Price: 3500 Taka");}

        else if(ch1==3&&ch2==1){
        gotoxy(12,9);printf("From Sylhet To Dhaka");gotoxy(12,10);printf("Price: 3500 Taka");}
        else if(ch1==3&&ch2==2){
        gotoxy(12,9);printf("From Sylhet To Chittagong");gotoxy(12,10);printf("Price: 3900 Taka");}
        else if(ch1==3&&ch2==4){
        gotoxy(12,9);printf("From Sylhet To Cox's Bazar");gotoxy(12,10);printf("Price: 4000 Taka");}
        else if(ch1==3&&ch2==5){
        gotoxy(12,9);printf("From Sylhet To Jessore");gotoxy(12,10);printf("Price: 3700 Taka");}
        else if(ch1==3&&ch2==6){
        gotoxy(12,9);printf("From Sylhet To Rajshahi");gotoxy(12,10);printf("Price: 3900 Taka");}
        else if(ch1==3&&ch2==7){
        gotoxy(12,9);printf("From Sylhet To Saidpur");gotoxy(12,10);printf("Price: 3500 Taka");}

        else if(ch1==4&&ch2==1){
        gotoxy(12,9);printf("From Cox's Bazar To Dhaka");gotoxy(12,10);printf("Price: 4500 Taka");}
        else if(ch1==4&&ch2==2){
        gotoxy(12,9);printf("From Cox's Bazar To Chittagong");gotoxy(12,10);printf("Price: 2400 Taka");}
        else if(ch1==4&&ch2==3){
        gotoxy(12,9);printf("From Cox's Bazar To Sylhet");gotoxy(12,10);printf("Price: 4700 Taka");}
        else if(ch1==4&&ch2==5){
        gotoxy(12,9);printf("From Cox's Bazar To Jessore");gotoxy(12,10);printf("Price: 4500 Taka");}
        else if(ch1==4&&ch2==6){
        gotoxy(12,9);printf("From Cox's Bazar To Rajshahi");gotoxy(12,10);printf("Price: 4900 Taka");}
        else if(ch1==4&&ch2==7){
        gotoxy(12,9);printf("From Cox's Bazar To Saidpur");gotoxy(12,10);printf("Price: 4900 Taka");}

        else if(ch1==5&&ch2==1){
        gotoxy(12,9);printf("From Jessore To Dhaka");gotoxy(12,10);printf("Price: 3500 Taka");}
        else if(ch1==5&&ch2==2){
        gotoxy(12,9);printf("From Jessore To Chittagong");gotoxy(12,10);printf("Price: 3700 Taka");}
        else if(ch1==5&&ch2==3){
        gotoxy(12,9);printf("From Jessore To Sylhet");gotoxy(12,10);printf("Price: 3800 Taka");}
        else if(ch1==5&&ch2==4){
        gotoxy(12,9);printf("From Jessore To Cox's Bazar");gotoxy(12,10);printf("Price: 4000 Taka");}
        else if(ch1==5&&ch2==6){
        gotoxy(12,9);printf("From Jessore To Rajshahi");gotoxy(12,10);printf("Price: 4100 Taka");}
        else if(ch1==5&&ch2==7){
        gotoxy(12,9);printf("From Jessore To Saidpur");gotoxy(12,10);printf("Price: 3500 Taka");}

        else if(ch1==6&&ch2==1){
        gotoxy(12,9);printf("From Rajshahi To Dhaka");gotoxy(12,10);printf("Price: 3500 Taka");}
        else if(ch1==6&&ch2==2){
        gotoxy(12,9);printf("From Rajshahi To Chittagong");gotoxy(12,10);printf("Price: 4500 Taka");}
        else if(ch1==6&&ch2==3){
        gotoxy(12,9);printf("From Rajshahi To Sylhet");gotoxy(12,10);printf("Price: 3700 Taka");}
        else if(ch1==6&&ch2==4){
        gotoxy(12,9);printf("From Rajshahi To Cox's Bazar");gotoxy(12,10);printf("Price: 4900 Taka");}
        else if(ch1==6&&ch2==5){
        gotoxy(12,9);printf("From Rajshahi To Jessore");gotoxy(12,10);printf("Price: 3800 Taka");}
        else if(ch1==6&&ch2==7){
        gotoxy(12,9);printf("From Rajshahi To Saidpur");gotoxy(12,10);printf("Price: 3500 Taka");}

        else if(ch1==7&&ch2==1){
        gotoxy(12,9);printf("From Saidpur To Dhaka");gotoxy(12,10);printf("Price: 3500 Taka");}
        else if(ch1==7&&ch2==2){
        gotoxy(12,9);printf("From Saidpur To Chittagong");gotoxy(12,10);printf("Price: 3700 Taka");}
        else if(ch1==7&&ch2==3){
        gotoxy(12,9);printf("From Saidpur To Sylhet");gotoxy(12,10);printf("Price: 3600 Taka");}
        else if(ch1==7&&ch2==4){
        gotoxy(12,9);printf("From Saidpur To Cox's Bazar");gotoxy(12,10);printf("Price: 4000 Taka");}
        else if(ch1==7&&ch2==5){
        gotoxy(12,9);printf("From Saidpur To Jessore");gotoxy(12,10);printf("Price: 3500 Taka");}
        else if(ch1==7&&ch2==7){
        gotoxy(12,9);printf("From Saidpur To Rajshahi");gotoxy(12,10);printf("Price: 4000 Taka");}


if(ch3==1){
    gotoxy(12,8);printf("By Biman Bangladesh Airlines");}
    else if(ch3==2){
    gotoxy(12,8);printf("By NovoAir");}
    else if(ch3==3){
    gotoxy(12,8);printf("By Regent Airways");}
    else if(ch3==4){
    gotoxy(12,8);printf("By Us-Bangla Airlines");}


    if(ch4==1){
    gotoxy(12,11);printf("Departure time 10.30 AM - Arrival time 11.10 AM");}
    else if(ch4==2){
    gotoxy(12,11);printf("Departure time 01.10 PM - Arrival time 02.50 PM");}
    else if(ch4==3){
    gotoxy(12,11);printf("Departure time 05.30 PM - Arrival time 06.10 PM");}
    else if(ch4==4){
    gotoxy(12,11);printf("Departure time 08.10 PM - Arrival time 09.50 PM");}
    else if(ch4==5){
    gotoxy(12,11);printf("Departure time 08.10 PM - Arrival time 09.50 PM");}

gotoxy(12,12);printf("Date: %s",date);

gotoxy(10,15); printf("Press Y to SAVE or Press N to MAIN MENU or PRESS X to EXIT");
        ex=getche();
        if (ex=='Y'||ex=='y')
        {

fp2=fopen("USER2.txt","a");

        fprintf(fp2,"\nName:%s\nNational ID:%s\nGender:%s\nDate of Birth:%s\nNationality:%s\n",info.name,info.nid,info.gender,info.dob,info.nation);
        fclose(fp2);
fp2=fopen("USER2.txt","a");



if(ch3==1){
    fprintf(fp2,"By Biman Bangladesh Airlines");}
    else if(ch3==2){
    fprintf(fp2,"By NovoAir");}
    else if(ch3==3){
    fprintf(fp2,"By Regent Airways");}
    else if(ch3==4){
    fprintf(fp2,"By Us-Bangla Airlines");}



fprintf(fp2,"\n");


    if(ch1==1&&ch2==2){
    fprintf(fp2,"From Dhaka To Chittagong");fprintf(fp2,"\nPrice: 3700 Taka");}
    else if(ch1==1&&ch2==3){
    fprintf(fp2,"From Dhaka To Sylhet");fprintf(fp2,"\nPrice: 3500 Taka");}
        else if(ch1==1&&ch2==4){
        fprintf(fp2,"From Dhaka To Cox's Bazar");fprintf(fp2,"\nPrice: 4300 Taka");}
        else if(ch1==1&&ch2==5){
        fprintf(fp2,"From Dhaka To Jessore");fprintf(fp2,"\nPrice: 3700 Taka");}
        else if(ch1==1&&ch2==6){
        fprintf(fp2,"From Dhaka To Rajshahi");fprintf(fp2,"\nPrice: 3900 Taka");}
        else if(ch1==1&&ch2==7){
        fprintf(fp2,"From Dhaka To Saidpur");fprintf(fp2,"\nPrice: 3900 Taka");}

        else if(ch1==2&&ch2==1){
        fprintf(fp2,"From Chittagong To Dhaka");fprintf(fp2,"\nPrice: 3700 Taka");}
        else if(ch1==2&&ch2==3){
        fprintf(fp2,"From Chittagong To Sylhet");fprintf(fp2,"\nPrice: 4000 Taka");}
        else if(ch1==2&&ch2==4){
        fprintf(fp2,"From Chittagong To Cox's Bazar");fprintf(fp2,"\nPrice: 2000 Taka");}
        else if(ch1==2&&ch2==5){
        fprintf(fp2,"From Chittagong To Jessore");fprintf(fp2,"\nPrice: 3300 Taka");}
        else if(ch1==2&&ch2==6){
        fprintf(fp2,"From Chittagong To Rajshahi");fprintf(fp2,"\nPrice: 4500 Taka");}
        else if(ch1==2&&ch2==7){
        fprintf(fp2,"From Chittagong To Saidpur");fprintf(fp2,"\nPrice: 3500 Taka");}

        else if(ch1==3&&ch2==1){
        fprintf(fp2,"From Sylhet To Dhaka");fprintf(fp2,"\nPrice: 3500 Taka");}
        else if(ch1==3&&ch2==2){
        fprintf(fp2,"From Sylhet To Chittagong");fprintf(fp2,"\nPrice: 3900 Taka");}
        else if(ch1==3&&ch2==4){
        fprintf(fp2,"From Sylhet To Cox's Bazar");fprintf(fp2,"\nPrice: 4000 Taka");}
        else if(ch1==3&&ch2==5){
        fprintf(fp2,"From Sylhet To Jessore");fprintf(fp2,"\nPrice: 3700 Taka");}
        else if(ch1==3&&ch2==6){
        fprintf(fp2,"From Sylhet To Rajshahi");fprintf(fp2,"\nPrice: 3900 Taka");}
        else if(ch1==3&&ch2==7){
        fprintf(fp2,"From Sylhet To Saidpur");fprintf(fp2,"\nPrice: 3500 Taka");}

        else if(ch1==4&&ch2==1){
        fprintf(fp2,"From Cox's Bazar To Dhaka");fprintf(fp2,"\nPrice: 4500 Taka");}
        else if(ch1==4&&ch2==2){
        fprintf(fp2,"From Cox's Bazar To Chittagong");fprintf(fp2,"\nPrice: 2400 Taka");}
        else if(ch1==4&&ch2==3){
        fprintf(fp2,"From Cox's Bazar To Sylhet");fprintf(fp2,"\nPrice: 4700 Taka");}
        else if(ch1==4&&ch2==5){
        fprintf(fp2,"From Cox's Bazar To Jessore");fprintf(fp2,"\nPrice: 4500 Taka");}
        else if(ch1==4&&ch2==6){
        fprintf(fp2,"From Cox's Bazar To Rajshahi");fprintf(fp2,"\nPrice: 4900 Taka");}
        else if(ch1==4&&ch2==7){
        fprintf(fp2,"From Cox's Bazar To Saidpur");fprintf(fp2,"\nPrice: 4900 Taka");}

        else if(ch1==5&&ch2==1){
        fprintf(fp2,"From Jessore To Dhaka");fprintf(fp2,"\nPrice: 3500 Taka");}
        else if(ch1==5&&ch2==2){
        fprintf(fp2,"From Jessore To Chittagong");fprintf(fp2,"\nPrice: 3700 Taka");}
        else if(ch1==5&&ch2==3){
        fprintf(fp2,"From Jessore To Sylhet");fprintf(fp2,"\nPrice: 3800 Taka");}
        else if(ch1==5&&ch2==4){
        fprintf(fp2,"From Jessore To Cox's Bazar");fprintf(fp2,"\nPrice: 4000 Taka");}
        else if(ch1==5&&ch2==6){
        fprintf(fp2,"From Jessore To Rajshahi");fprintf(fp2,"\nPrice: 4100 Taka");}
        else if(ch1==5&&ch2==7){
        fprintf(fp2,"From Jessore To Saidpur");fprintf(fp2,"\nPrice: 3500 Taka");}

        else if(ch1==6&&ch2==1){
        fprintf(fp2,"From Rajshahi To Dhaka");fprintf(fp2,"\nPrice: 3500 Taka");}
        else if(ch1==6&&ch2==2){
        fprintf(fp2,"From Rajshahi To Chittagong");fprintf(fp2,"\nPrice: 4500 Taka");}
        else if(ch1==6&&ch2==3){
        fprintf(fp2,"From Rajshahi To Sylhet");fprintf(fp2,"\nPrice: 3700 Taka");}
        else if(ch1==6&&ch2==4){
        fprintf(fp2,"From Rajshahi To Cox's Bazar");fprintf(fp2,"\nPrice: 4900 Taka");}
        else if(ch1==6&&ch2==5){
        fprintf(fp2,"From Rajshahi To Jessore");fprintf(fp2,"\nPrice: 3800 Taka");}
        else if(ch1==6&&ch2==7){
        fprintf(fp2,"From Rajshahi To Saidpur");fprintf(fp2,"\nPrice: 3500 Taka");}

        else if(ch1==7&&ch2==1){
        fprintf(fp2,"From Saidpur To Dhaka");fprintf(fp2,"\nPrice: 3500 Taka");}
        else if(ch1==7&&ch2==2){
        fprintf(fp2,"From Saidpur To Chittagong");fprintf(fp2,"\nPrice: 3700 Taka");}
        else if(ch1==7&&ch2==3){
        fprintf(fp2,"From Saidpur To Sylhet");fprintf(fp2,"\nPrice: 3600 Taka");}
        else if(ch1==7&&ch2==4){
        fprintf(fp2,"From Saidpur To Cox's Bazar");fprintf(fp2,"\nPrice: 4000 Taka");}
        else if(ch1==7&&ch2==5){
        fprintf(fp2,"From Saidpur To Jessore");fprintf(fp2,"\nPrice: 3500 Taka");}
        else if(ch1==7&&ch2==7){
        fprintf(fp2,"From Saidpur To Rajshahi");fprintf(fp2,"\nPrice: 4000 Taka");}

fprintf(fp2,"\n");

    if(ch4==1){
    fprintf(fp2,"Departure time 10.30 AM - Arrival time 11.10 AM");}
    else if(ch4==2){
    fprintf(fp2,"Departure time 01.10 PM - Arrival time 02.50 PM");}
    else if(ch4==3){
    fprintf(fp2,"Departure time 05.30 PM - Arrival time 06.10 PM");}
    else if(ch4==4){
    fprintf(fp2,"Departure time 08.10 PM - Arrival time 09.50 PM");}
    else if(ch4==5){
    fprintf(fp2,"Departure time 08.10 PM - Arrival time 09.50 PM");}

fprintf(fp2,"\n");
    fprintf(fp2,"Date: %s",date);
fprintf(fp2,"\n");


fclose(fp2);
exit(0);
        }

       else if(ex=='N'||ex=='n')
       {
           title();
           flights();
       }
       else if(ex=='X'||ex=='x')
{
    exit(0);

}



        getch();




}


void password(char pwd[])
	{

	     	char c;
         	int pos = 0;
           	do
            	{
           		 c = getch();
            		if(isprint(c))
            		{
            			pwd[pos++] = c;
            			printf("%c", '*');
            		}
            		else if(c == 8)
            		{
                        pwd[pos--] = '\0';
            			printf("%s","\b \b");
           		}
            	}while(c != 13);

	}




void welcome()
{
    int i;
    system("cls");
    rectangle(0,0,80,23);
    gotoxy(23,4); printf("TRAVEL AGENCY MENEGMENT SYSTEM");
    gotoxy(23,5); for(i=0;i<30;i++) printf("%c",196);
    gotoxy(25,8); printf("Designed and Programmed by:");
    gotoxy(25,9);for(i=0;i<27;i++) printf("%c",196);
    gotoxy(30,11); printf("Kazi Ramisa Rifa");

    gotoxy(30,13); printf("Fariha Nur Hasin");
    gotoxy(29,15); printf("Shahnaz Akter Emon");
    gotoxy(24,20);

    printf("Press Any key to continue...");


getch();

}







void rectangle(int x,int y,int l,int b)
{
    int i,m;
    gotoxy(x,y); printf("%c",201);
    for(i=x+1;i<l-1;i++)
    {
        gotoxy(i,y);
        printf("%c",205);
    }
    gotoxy(i,y); printf("%c",187);

    for (m=y+1;m<b;m++)
    {
        gotoxy(x,m);
        for(i=x;i<l;i++)
        {
            if(i==x||i==l-1)
            {
                gotoxy(i,m); printf("%c",186);
            }

        }

    }

    gotoxy(x,m); printf("%c",200);
    for(i=x+1;i<l-1;i++)
    {
        gotoxy(i,m);
        printf("%c",205);
    }
    gotoxy(i,m); printf("%c",188);
}


void title()
{
    int i;

    system("cls");

    rectangle(0,0,80,23);
    gotoxy(25,1);
    printf("TRAVEL AGENCY MENEGMENT SYSTEM");
}
COORD coord = {0, 0};

void gotoxy (int x, int y)
        {
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        }


