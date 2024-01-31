// headers/ Titles before every function are used for navigation

/*
    The code was writen in a UNIX based OS
    because of that i used system("clear"); instead of system("cls");
    for an optimised expirience one can replace it with system("cls");
    but ofcousre that is up to you
*/

/*
    While reading the code you'll notice that i use fflush(stdin) and getchar() after certain functions 
    or lines of code. That is either to clear the buffer to avoid it overflowing, or to temporarly pause
    the code until the user presses any key.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// to avoid having to remember the needed length of each variable
// the size of each array is high to avoid overflow
#define name_size 40
#define surn_size 50
#define card_size 30
#define uname_size 40 // uname is short for username
#define pass_size 25

#define total_num_of_routes 13

struct users
{

    char name[name_size];
    char surname[surn_size];
    unsigned int age;
    char card_number[card_size]; // size of array = 25 to avoid overflow
    int university_student;      // basically a boolean variable that can only have values 1 for true and 0 for false
    char username[uname_size];
    char password[pass_size];
    int sum_of_trips;           // Used to track the amount of trips a user has booked
    int at_least_one_completed; // boolean integer if 0 the user does not have any paid trips
                                // if 1 the user has at least one trip that is paid off
};

struct users user[30];
struct users temp; // used for get_new_user

struct route
{
    char harbor[12];
    char code[4];
    int deck;  // deck seat cost
    int fly;   // flight type seat
    int cabin; // cabin cost
    int car;   // cost to bring a car
};

// declaring a route variable that has the information of each destination stored inside of it
struct route routes[14] = {{"Kos", "KOS", 60, 80, 120, 100},
                           {"Rodos", "RHO", 80, 100, 140, 100},
                           {"Kalymnos", "KAL", 60, 80, 120, 100},
                           {"Patmos", "PAT", 55, 75, 115, 100},
                           {"Astypalaia", "AST", 50, 70, 110, 100},
                           {"Kasos", "KAS", 65, 85, 125, 100},
                           {"Katselorizo", "KST", 100, 120, 160, 120},
                           {"Leros", "LER", 60, 80, 120, 100},
                           {"Karpathos", "KAR", 70, 90, 130, 100},
                           {"Symi", "SYM", 80, 100, 140, 120},
                           {"Xalki", "XAL", 70, 90, 130, 100},
                           {"Tilos", "TIL", 75, 95, 135, 100},
                           {"Pserismos", "PSE", 60, 80, 120, 100}};

struct date
{
    int dd;   // day
    int mm;   // month
    int yyyy; // year
};

struct booked_trip
{
    char username_booked[40];
    char ID[40];
    float total_cost;
    struct date departure;  // outbound
    struct date inbound;    // only if the user want a round trip
    int trip_type;          // 1 if round trip 0 if one way
    char payment_situation; // P for pending payment and C for Complited payment
    int trip_booked;        /* Used to before the payment function to make sure that the user has booked at least one trip
                               VALUE MEANING:
                                 if it's value is 1 (true) then the current user has booked a trip
                                 if it's value is 0 (false) then the current user has not booked a trip
                               if the user has booked more than one trips then the current_user_index index pointer will point at the current user's account
                               each acount can have multiple booked trips. Using the current user's username we can locate every trip that he has booked.
                               If the first trip the code finds has the trip_booked variable set to 1 then that means that there is a posibility that the user has
                               booked more than one trip.
       
                               This is used to prevent a user that has no booked trips from chosing the payment opiton without having a booked trip
                             */
} trips[1500];

// used for user_login
char temp_login_uname[uname_size];
char temp_login_pass[pass_size];

int user_count = 0;     // user count
int current_user_index; // used to find the users information after they login / signup
int trip_count = 0;     // used to count the amount of trips that have been booked
int temp_car;           // used to see of the user wants to bring their car with them ( 1 for yes ,0 for no)
char temp_harbor[20];   // temporarly stores the code of the harbor the user want to travel to
char seat;              // temporarly stores the type of seat the user wants for their trip

// sign up
void user_signup();
void get_new_user();
int username_exists();

// login
void user_login();
int check_login(char uname_given[uname_size], char pass_given[pass_size]);

// booking a trip
void user_dashboard();
void view_route();
void book_trip();
int compare_trips();
int compare_trips_return(const char trip_ID[]);
void generate_trip_ID(char harbor[]);
void final_cost();
void payment();
void confirmed_trips();
void sort_ascening();
void sort_descending();
int Valid_date(const struct date *date);
int isLeapYear(int yyyy);
int Possible_date(const struct date *current_date);

// these are some funtions that i have in my own custom library that i included
// each one of them has a short explanation paragraph before their declaration
void replace_newline(char str[]);
int CheckStr(const char *str1, const char *str2);
int lengthof(char check_str[20]);
int isNum(char str[]);

// MAIN SCREEN
int main()
{

    /*
    Main function
    the user has three choices to :
                                    - Sign up (1)
                                    - Login (2)
                                    - Exit (0)

    the user is tasked with choosing a number acording to the task they want to perform
    */

    do
    {
        int choice;
        printf("        WELCOME TO DS FERRIES!! \n\n");
        printf(" Options: \n");
        printf(" 1) Sign up\n");
        printf(" 2) Login\n");
        printf(" 0) Exit\n");
        printf(" Please enter a number according to what you want ot do\n");
        printf("\t-> ");

        scanf("%d", &choice);

        if (choice == 1)
        {
            if (user_count + 1 == 30)
            {
                printf(" User Limit reached \n");
                break;
            }

            getchar();
            user_signup();
            getchar();
            system("clear");
            user_login();
            getchar(); // getchar used to remove a new line left behind by the user dashboard function
            continue;
        }

        if (choice == 2)
        {
            getchar();
            user_login();
            continue;
        }

        if (choice == 0)
        {
            system("clear");
            break;
        }

        else
        {
            printf("Not an option... Please try again \n");
        }
        user_count++;
    } while (user_count < 30);
}

// USER SIGNUP

void user_signup()
{
    /*
    User signup function:

        Copies the user's credentials into the array of structs, after that it sets the variable trip_booked to 1 since the user has not booked any trips yet

    */
    system("clear");
    get_new_user();

    strcpy(user[user_count].name, temp.name);
    strcpy(user[user_count].surname, temp.surname);
    strcpy(user[user_count].username, temp.username);
    strcpy(user[user_count].password, temp.password);
    strcpy(user[user_count].card_number, temp.card_number);
    user[user_count].age = temp.age;
    user[user_count].university_student = temp.university_student;
    user[user_count].sum_of_trips = 0;

    current_user_index = user_count;
    // if the user has just signed up and is now going to book a trip then their information can be found at index user_count in the array of structs

    trips[current_user_index].trip_booked = 1;
}

// GET NEW USER

void get_new_user()
{
    /*
    Get new user function:

        An extention of the user_sign up funtion. It stores the user's credentials into temprary values, makes sure that the user is not a minor,
        and performs a lot of different validation checks.

        This function uses multiple functions to break the tasks into small blocks and make the code more readable
    */
    printf(" Please Enter your name \n\t-> ");
    fgets(temp.name, name_size, stdin);
    replace_newline(temp.name);

    printf(" Please Enter your surname \n\t-> ");
    fgets(temp.surname, surn_size, stdin);
    replace_newline(temp.surname);

    printf(" Please Enter your age \n\t-> ");
    scanf("%u", &temp.age);

    while (temp.age < 18)
    {
        printf(" You must be 18 or older to have an account at DS Ferries. \n Please enter your age again : \n\t-> ");
        scanf("%d", &temp.age);
        if (temp.age == 0)
        {
            user_count--;
            /*
            if user is under 18 the index i is redused by 1
            that is to remove the name and surname the user entered at the begining
            how ?
                well by decreasing the index i by 1 the next name, surname and age to be inputed will replace the current ones
                further explanation int the ducumentation pdf
            */
            return; // end of the function
        }
    }

    getchar();
    printf(" Please Enter your username \n\t-> ");
    fgets(temp.username, uname_size, stdin);
    replace_newline(temp.username);

    while (username_exists() == 0)
    {
        printf(" Username Already exists. Please enter a different username.\n   -> ");
        fgets(temp.username, uname_size, stdin);
        replace_newline(temp.username);
    }

    printf(" Please Enter your password \n\t-> ");
    fgets(temp.password, pass_size, stdin);
    replace_newline(temp.password);

    while (lengthof(temp.password) < 7)
    // i made it so the password has to be longer than 7 characters long, for realistic purposes
    {
        printf(" Password must be longer than 7 characters \n\t-> ");
        fgets(temp.password, pass_size, stdin);
        replace_newline(temp.password);
    }

    //  do-while used to ensure that the variable has the correct length
    printf(" Please Enter your card number \n\t-> ");

    fgets(temp.card_number, card_size, stdin);
    replace_newline(temp.card_number);

    while (isNum(temp.card_number) == 1 || lengthof(temp.card_number) != 16)
    {

        printf(" Card number contains nonn numeric characters, or is not 16 digits long\n");
        printf(" Please Re-nter your card number \n\t-> ");
        fgets(temp.card_number, 17, stdin);
        replace_newline(temp.card_number);
    }

    printf(" Are you a university student ? \n Enter 1 if YES \n Enter 0 if NO \n\t-> ");
    scanf("%d", &temp.university_student);
    if ((temp.university_student != 1) && (temp.university_student != 0))
    {
        printf(" Not an option\n Try again\n");
        printf(" Are you a university student ? \n Enter 1 if YES \n Enter 0 if NO \n\t-> ");
        scanf("%d", &temp.university_student);
    }
}

int username_exists()
{
    /*
    Username exists function:

        When a new user enters their username it makes sure that it does not already belong to a different user

    */
    int j;
    for (j = 0; j <= user_count; j++) // checks every username that was entered before this current one
    {
        if (strcmp(temp.username, user[j].username) == 0)
        {
            return 0; // username exists
        }
    }

    return 1; // username does not exist
}

// USER LOGIN

void user_login()
{
    /*
    User login:

        When a user wants to login he is asked to enter their username and password, if either one of them is incorectly entered
        the user is asked to re-enter their cerentials or register if they have not yet
    */
    system("clear");
    printf(" Please Enter you Username: \n\t-> ");
    fgets(temp_login_uname, uname_size, stdin);
    replace_newline(temp_login_uname);

    printf(" Please Enter you Password: \n\t-> ");
    fgets(temp_login_pass, pass_size, stdin);
    replace_newline(temp_login_pass);

    char *unamePtr = temp_login_uname, *passPtr = temp_login_pass;
    while (check_login(unamePtr, passPtr) == 1)
    {
        char try_again;
        printf(" Account not found :\n Press 1 to register \n Press anything else to try again");
        if (getchar() == '1')
        {
            getchar(); // emptying the buffer
            user_signup();
            system("clear");
            return;
        }
        system("clear");
        printf(" Please Enter you Username: \n\t-> ");
        fgets(temp_login_uname, uname_size, stdin);
        replace_newline(temp_login_uname);

        printf(" Please Enter you Password: \n\t-> ");
        fgets(temp_login_pass, pass_size, stdin);
        replace_newline(temp_login_pass);
    }

    printf(" Press any key to continue");

    user_dashboard();
}

int check_login(char *uname_given, char *pass_given)
{
    /*
    Check login function:

        Compares the username the current user used to login with the username of every signed up user
    */
    int index;
    for (index = 0; index <= user_count; index++)
    {
        char *uname_test_ptr = user[index].username, *pass_test_ptr = user[index].password;
        if ((strcmp(uname_given, uname_test_ptr) == 0) && (strcmp(pass_given, pass_test_ptr) == 0))
        {
            current_user_index = index;
            // once the user's information has been found in the user array of structs the index at which their information is located is stored
            return 0; // both the password and the username are correct
        }
    }

    return 1; // one or both of them wrong dont match
}

// USER DASHBOARD
void user_dashboard()
{
    /*
    User Dashboard function:

        The user is asked to choose what they want to do ( view routes, book a trip, pay for a trip, see all of their confirmed trips)

        This function uses several other functions to perform each task, to imrove readability.
    */
    system("clear");
    char user_choice;
    do
    {
        getchar();

        printf(" a) View Available routes\n");
        printf(" b) Book trip\n");
        printf(" c) Payment\n");
        printf(" d) Confirmed Trips\n");
        printf(" e) Logout\n");
        printf(" Please enter the corisponding letter\n\t-> ");
        scanf("%c", &user_choice);

        switch (user_choice)
        {

        case 'a':
        {

            view_route();
            printf("\n Press enter to continue");
            getchar();
            break;
        }

        case 'b':
        {
            book_trip();
            trips[trip_count].trip_booked = 1; // user has at least one booked trip
            user[current_user_index].sum_of_trips++;
            
            system("clear");
            break;
        }

        case 'c':
        {
            payment();
            //system("clear");
            user[current_user_index].at_least_one_completed = 1;
            break;
        }

        case 'd':
        {
            getchar();
            if (user[current_user_index].at_least_one_completed == 1)
            {
                confirmed_trips();
            }

            else
            {
                printf(" You currently dont have any booked trips\n");
            }
            break;
            getchar();
            system("clear");
        }
        }
    } while (user_choice != 'e'); // If the user types e then he wants to logout

    system("clear");
}

// ROUTES
void view_route()
{

    /*
    View routes function:

        Printing the information about each trip, so the user can make a choice based on the cost of each trip

    */
    printf("\t*******************************************************************************************\n");
    printf("\t* Island/ Harbor * Harbor Code *                   Seat  cost                * Extra Cost *\n");
    printf("\t*******************************************************************************************\n");
    printf("\t*                *             * Deck Cost *  Flight type seat  * Cabin Cost *     Car    *\n");
    printf("\t*******************************************************************************************\n");
    printf("\t*                *             *           *                    *            *            *\n");
    int x;
    // using a for loop for asthetic purposes
    for (x = 0; x < 13; x++)
    {
        printf("\t* %-15s* %-12s* %-10d* %-19d* %-11d* %-11d*\n", routes[x].harbor, routes[x].code, routes[x].deck, routes[x].fly, routes[x].cabin, routes[x].car);
    }
    printf("\t*                *             *           *                    *            *            *\n");
    printf("\t*******************************************************************************************\n");
}

// BOOK TRIP
void book_trip()
{

    /*
    Book trip function:

        The user is tasked with choosing their trip's date of departure, harbor they want to go to, and more information regarding their trip.

        This function uses several other functions such as compare_trips ore final_cost to break the more specific tasks into seperate functions.
        This is to make the code more readable
    */
    strcpy(trips[trip_count].username_booked, user[current_user_index].username);
    if (trips[trip_count].trip_booked == 1)
    {
        while (compare_trips() == 0) //
        {
            printf(" Date unavailable, please try again.\n\n");
            do
            {
                fflush(stdin); // using fflush to clear the buffer
                printf(" Please choose departure date: \n");
                printf(" DAY: ");
                scanf("%d", &trips[trip_count].departure.dd);
                printf(" MONTH: ");
                scanf("%d", &trips[trip_count].departure.mm);
                printf(" YEAR: ");
                scanf("%d", &trips[trip_count].departure.yyyy);

                while (Possible_date(&trips[trip_count].departure) == 0) // checking if the date the user enered exists
                {
                    printf(" Date does not exists, Please choose a date that exists\n Press enter to try again");
                    getchar();

                    printf(" DAY: ");
                    scanf("%d", &trips[trip_count].departure.dd);
                    printf(" MONTH: ");
                    scanf("%d", &trips[trip_count].departure.mm);
                    printf(" YEAR: ");
                    scanf("%d", &trips[trip_count].departure.yyyy);
                }

                if (Valid_date(&trips[trip_count].departure) != 1)
                {
                    printf(" Time travel unavailable\n");
                }

            } while ((Valid_date(&trips[trip_count].departure) != 1));
        }
    }
    do
    {

        printf(" Please choose departure date: \n");
        printf(" DAY: ");
        scanf("%d", &trips[trip_count].departure.dd);
        printf(" MONTH: ");
        scanf("%d", &trips[trip_count].departure.mm);
        printf(" YEAR: ");
        scanf("%d", &trips[trip_count].departure.yyyy);

        while (Possible_date(&trips[trip_count].departure) == 0) // checking if the date the user enered exists
        {
            fflush(stdin); // using fflush to clear the buffer
            printf(" Date does not exists, Please choose a date that exists\n Press enter to try again");
            getchar();

            printf(" DAY: ");
            scanf("%d", &trips[trip_count].departure.dd);
            printf(" MONTH: ");
            scanf("%d", &trips[trip_count].departure.mm);
            printf(" YEAR: ");
            scanf("%d", &trips[trip_count].departure.yyyy);
        }

        if (Valid_date(&trips[trip_count].departure) != 1)
        {
            printf(" Time travel unavailable\n");
        }

        system("clear");

    } while ((Valid_date(&trips[trip_count].departure) != 1));

    view_route();
    getchar(); // clearing the buffer
    printf("\n HARBOR CODE: ");
    fgets(temp_harbor, sizeof(temp_harbor), stdin);
    replace_newline(temp_harbor);
    char same = 'F';
    do
    {
        int index;
        for (index = 0; index < total_num_of_routes; index++)
        {
            if (strcmp(temp_harbor, routes[index].code) == 0)
            {
                same = 'T';
                break;
            }
        }
        if (same == 'F')
        {
            system("clear");
            view_route();
            printf(" Not an option\n");
            printf("\n HARBOR: ");
            fgets(temp_harbor, sizeof(temp_harbor), stdin);
            replace_newline(temp_harbor);
        }
    } while (same == 'F');

    generate_trip_ID(temp_harbor);

    trip_count++;

    printf(" Select the type of seat you want\n Options :\n a) Deck\n b) flight\n c) Cabin\n Please chose the coresponding letter\n");
    printf(" SEAT: ");
    scanf("%c", &seat);
    getchar(); // avoiding buffer overflow
    while (seat != 'a' && seat != 'b' && seat != 'c')
    {
        printf(" Not an option\n Please try again\n");
        scanf("%c", &seat);
    }

    printf(" Would you like to bring your car?\n 1 for yes\n 0 for no\n");
    scanf("%d", &temp_car);
    while ((temp_car != 0) && (temp_car != 1))
    {
        printf(" Not an option\n Try again\n\n");
        printf(" Would you like to bring your car?\n 1 for yes\n 0 for no\n ");
        scanf("%d", &temp_car);
    }

    printf(" Would you like to book a round trip ?\n 1 for yes\n Anything else for no\n ");
    scanf("%d", &trips[trip_count].trip_type);

    fflush(stdin);

    if (trips[trip_count].trip_type == 1)
    {
        char correct_date = 'F';
        do
        {
            printf(" Please choose return date: \n");
            printf(" DAY: ");
            scanf("%d", &trips[trip_count].inbound.dd);
            printf(" MONTH: ");
            scanf("%d", &trips[trip_count].inbound.mm);
            printf(" YEAR: ");
            scanf("%d", &trips[trip_count].inbound.yyyy);
            
            if(compare_trips_return(trips[trip_count].ID) == 0)
            {
                correct_date = 'T';
                
            }

            else
            {
                
                printf(" Return date can not be before the departure date\n");
            }
        } while (correct_date == 'F');
    }

    getchar();

    final_cost();

    trips[trip_count].payment_situation = 'P';

    printf("\n%c\n", trips[trip_count].payment_situation);

    // printf("Payment Situation: %d\n", trips[index+1].payment_situation);

    printf(" Booking was succeful.\n Thank you for choosing us.\n Hope to see you again :)\n Press any key to Continue");
    getchar(); // clearing the buffer
}

int isLeapYear(int yyyy)
{
    return (yyyy % 4 == 0 && (yyyy % 100 != 0) || (yyyy % 400 == 0));
    /*
        If a year can be divided by 4 it might be a leap year,
        If a year can be evenly divided by 100 it is most likley not a leap year with one exeption,
        the exeption os when a year can be divided by 400

        Returns 1 (true) then the year is a leap year

        Returns 0 (false) then the year is not a leap year
    */
}

int Possible_date(const struct date *current_date)
{
    /*
    Possible date function:

        Makes sure that the date the user enteres exists, (e.g 25/30/2000 does not exist)

        This is accomplished by passing a pointer to a structs and checking wheter the month entered is in between 1-12 (January - December),
        making sure that depending on the month the user entered and if the year is a leap year, meaning checking if February has 28 or 29 days

    */
    if (current_date->mm < 1 || current_date->mm > 12)
    // if a month is NOT between 1 and 12  (January - December)
    {
        return 0;
    }

    int daysInMonth;

    // Determine the number of days in the given mm
    switch (current_date->mm)
    {
    case 2:
    {
        daysInMonth = isLeapYear(current_date->yyyy) ? 29 : 28; // if the year is a leap year it affects the amount of days in February
        break;
    }

    case 4:
    case 6:
    case 9:
    case 11:
    {
        //  4, 6, 9 or 11 (April, June, September, and November) they all have 30 days
        daysInMonth = 30;
        break;
    }
    default:
    {
        // January, March, May, July, August, October, December they all have 31 days in a month
        daysInMonth = 31;
        break;
    }
    }

    if (current_date->dd < 1 || current_date->dd > daysInMonth)
    {
        return 0;
    }

    return 1; // The date the user entered exists
}

int Valid_date(const struct date *date)
{
    /*
    Valid date function:

        Uses the current date to make sure that the user is booking for a date that in not in the past

        returns 1 (true) if the date is valid

        returns 0 (false) if the date is not valid
    */
    // This is used to get the current date
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // Comparing the user's input with the current date
    return (date->yyyy > timeinfo->tm_year + 1900 || (date->yyyy == timeinfo->tm_year + 1900 && date->mm > timeinfo->tm_mon + 1) || (date->yyyy == timeinfo->tm_year + 1900 && date->mm == timeinfo->tm_mon + 1 && date->dd >= timeinfo->tm_mday));
}

// CHECKING THE
int compare_trips()
{

    /*
    Compare trips function:

        Copying the user's date of departure ( day, month and year ) in temporary local integer variables
        and compare them to the user's past booked trip dates and make sure that their current booking is after their next trip ends

        This is done by locating all of the current user's booked trip and performing a linear search on all of the user's booked trip dates
        both to-go and to-come to find the latest trip date ( either one way or round trip ). After finding the latest trip dated it stores
        them in the integer variables max_day/month/year

        return 1 if the date is incorectly inputed

        return 0 if the date is corectly inputed
    */
    int index;
    int max_day = 0, max_month = 0, max_year = 0;

    int departure_day = trips[trip_count].departure.dd;
    int departure_month = trips[trip_count].departure.mm;
    int departure_year = trips[trip_count].departure.yyyy;

    for (index = 0; index < current_user_index + 1; index++)
    {
        if (strcmp(trips[index].username_booked, user[current_user_index].username) == 0)
        {
            if (trips[index].trip_type == 0) // if the trip is one way
            {
                if (trips[index].departure.yyyy > max_year)
                {
                    max_year = trips[index].departure.yyyy;
                    max_month = trips[index].departure.mm;
                    max_day = trips[index].departure.dd;
                }
                else if (trips[index].departure.yyyy == max_year && trips[index].departure.mm > max_month)
                {
                    max_month = trips[index].departure.mm;
                    max_day = trips[index].departure.dd;
                }
                else if (trips[index].departure.yyyy == max_year && trips[index].departure.mm == max_month && trips[index].departure.dd > max_day)
                {
                    max_day = trips[index].departure.dd;
                }
            }

            else // if its a round trip
            {
                if (trips[index].inbound.yyyy > max_year)
                {
                    max_year = trips[index].inbound.yyyy;
                    max_month = trips[index].inbound.mm;
                    max_day = trips[index].inbound.dd;
                }
                else if (trips[index].inbound.yyyy == max_year && trips[index].inbound.mm > max_month)
                {
                    max_month = trips[index].inbound.mm;
                    max_day = trips[index].inbound.dd;
                }
                else if (trips[index].inbound.yyyy == max_year && trips[index].inbound.mm == max_month && trips[index].inbound.dd > max_day)
                {
                    max_day = trips[index].inbound.dd;
                }
            }
        }
    }

    if (max_year > departure_year)
    {
        return 1;
    }

    if ((max_year == departure_year && max_month > departure_month))
    {
        return 1;
    }

    if ((max_year == departure_year && max_month == departure_month && max_day >= departure_day))
    {
        return 1;
    }

    return 0;
}

int compare_trips_return(const char trip_ID[])
{
    /*
    Compare trips function:

        Copying the user's date of departure ( day, month and year ) in temporary local integer variables
        and compare them to the user's past booked trip dates and make sure that their current booking is not before their departure date

        This is done by locating all of the current user's booked trip and performing a linear search on all of the user's booked trip dates
        both to-go and to-come to find the latest trip date ( either one way or round trip ). After finding the latest trip dated it stores
        them in the integer variables min_day/month/year

        return 1 if the date is incorectly inputed

        return 0 if the date is corectly inputed

    */
    int index;
    int return_day = trips[trip_count].inbound.dd;
    int return_month = trips[trip_count].inbound.mm;
    int return_year = trips[trip_count].inbound.yyyy;

    for (index = 0; index < trip_count ; index++)
    {
        if (strcmp(trips[index].username_booked, user[current_user_index].username) == 0)
        {
            if (strcmp(trips[index].ID, trips[current_user_index].ID) == 0)
            {
                if ((trips[index].departure.yyyy > return_year) || (trips[index].departure.yyyy == return_year && trips[index].departure.mm > return_month) || (trips[index].departure.yyyy == return_year && trips[index].departure.mm == return_month && trips[index].departure.dd > return_day))
                {
                    return 1;  // Return date is before departure date
                }
            }
        }
    }

    return 0; 
}

// TRIP ID
void generate_trip_ID(char harbor[])
{
    /*
    Get new user function:

        using the user's chosen departure date, the harbor that they want to to travel to and their username to produce a unique user trip ID
    */
    if (((trips[trip_count].departure.mm) / 10) == 0)
    // if the user enters 06 instead of 6 for the month of departure
    // the 0 infront tells c that the number is in the octal system (0,1,2,3,4,5,6,7)
    {
        sprintf(trips[trip_count].ID, "%d0%d%d%s-%s", trips[trip_count].departure.dd, trips[trip_count].departure.mm, trips[trip_count].departure.yyyy, harbor, trips[trip_count].username_booked);
    }
    else
    {
        sprintf(trips[trip_count].ID, "%d%d%d%s-%s", trips[trip_count].departure.dd, trips[trip_count].departure.mm, trips[trip_count].departure.yyyy, harbor, trips[trip_count].username_booked);
    }
    printf("\nYour unique trip ID is: %s\n", trips[trip_count].ID);
}

// CALCULATING THE FINAL COST
void final_cost()
{
    /*
    Final cost funtion:

        Calculates the total cost o a booked trip using the user's choices accoring their chosen destination,
        the type of seat they want, wheter or not they want to bring their vehicle with them and whether or not
        they want to book a return trip or a one way trip

        If the user is a university student the cost of their trip will be 50% of the original trip's price
    */
    int index;

    int harbor_index, car_cost, seat_cost;

    for (index = 0; index < 13; index++)
    {
        if (CheckStr(temp_harbor, routes[index].code) == 1)
        {
            harbor_index = index;
            break;
        }
    }

    car_cost = (temp_car == 1) ? routes[harbor_index].car : 0;

    // using the user's choice of seat to calculate the cost of their seat
    if (seat == 'a')
    {
        seat_cost = routes[harbor_index].deck;
    }
    else if (seat == 'b')
    {
        seat_cost = routes[harbor_index].cabin;
    }
    else if (seat == 'c')
    {
        seat_cost = routes[harbor_index].fly;
    }

    float depart_cost = (float)(seat_cost + car_cost); // typecasting the cost of departure to float so the user can know exactly how much they will have to pay
    float return_cost;

    if (trips[trip_count].trip_type == 1) // if the trip type is 1 then the user wants to book a return trip
    {
        return_cost = depart_cost * 0.75; // return cost is 75% of the cost for departure
    }
    else
    {
        return_cost = 0.00;
    }

    trips[trip_count].total_cost = (float)depart_cost + return_cost;

    if (user[current_user_index].university_student == 1)
    {
        trips[trip_count].total_cost = (float)(trips[trip_count].total_cost / 2);
    }

    trips[trip_count].total_cost = floor(trips[trip_count].total_cost * 100) / 100; // giving the user the cheapest possible cost

    printf(" \n total cost : %.2f\n", trips[trip_count].total_cost);
}

// PAYMENT

void payment()
{
    /*
    Payment function:

        First copies the username of the current user to a temporary username variable

        Using the temporary username the code finds all of the trips they have booked,
        and stores the index in which they are stored in the array of structs.
        That is acomplished by using a Pointer that points to an array of indexes(int).
        P.S. due to the fact that an array pointer points to the first index of the array
        after an index is stored (*idPtr = index;) we increase the idPtr by 1,
        the is so the pointer points to the next index of the array

        While in the loop the code outputs every payment found, ass well as it's ID and Payment Status

        Notifies the user if theu either have no booked or no pending trips

        By using the previously stored indexes, to locate the trips whos payments are pending
        and the payment_ID_choice variable, that stores the ID of the trip that the user wants to pay for.

    */
    char temp_payment_uname[uname_size];
    strcpy(temp_payment_uname, user[current_user_index].username);
    replace_newline(temp_payment_uname);

    int index, pending_count = 0, paid_off_count = 0, total_trips = 0, no_booked_trips = 1, trip_ID_indexes[30];
    // pending_count = total number pending payments, paid_off_count = total number completed payments
    // total_trips = total number of trips booked, no_booked_trips = boolean integer used to see if a user has any booked trips
    int *idPtr = trip_ID_indexes;

    // Finding booked trips and store their indexes
    for (index = 0; index < trip_count; index++)
    {
        if (strcmp(temp_payment_uname, trips[index].username_booked) == 0 && trips[index].trip_booked == 1)
        {
            no_booked_trips = 0;
            if (trips[index].payment_situation == 'C')
            {
                printf("Trip ID : %s\tCost : %.2f\tStatus: Payment Completed\n\n", trips[index].ID, trips[index].total_cost);
                *idPtr++ = index;
                paid_off_count++;
            }

            else
            {
                printf("Trip ID : %s\tCost : %.2f\tStatus: Pending Payment\n\n", trips[index].ID, trips[index].total_cost);
                *idPtr++ = index;
                pending_count++;
            }
            total_trips++;
        }
    }

    // Notify if no booked trips
    if (no_booked_trips != 0)
    {
        printf("You don't have any booked trips yet.\nPlease book a trip first.\nPress any key to continue ");
        getchar();
        return;
    }

    // Notify if no pending payments
    if (paid_off_count == total_trips)
    {
        printf("There are no pending payments.\n");
        return;
    }

    char payment_id_choice[40];
    char paid = 'F';

    getchar(); // clearing the buffer
    do
    {
        // Process payment
        printf("Please enter the ID of the trip you want to pay for:  ");

        fgets(payment_id_choice, sizeof(payment_id_choice), stdin);
        replace_newline(payment_id_choice);

        int i;
        for (i = 0; i < total_trips; i++)
        {
            // Compare without newline characters
            if (strcmp(payment_id_choice, trips[trip_ID_indexes[i]].ID) == 0)
            {
                if (trips[trip_ID_indexes[i]].payment_situation == 'C')
                {
                    printf("Trip has been paid fully\n");
                }
                else
                {
                    printf("Payment successful\nThank you for choosing DS Ferries\n Press any key to continue");
                    trips[trip_ID_indexes[i]].payment_situation = 'C';
                    paid = 'T';
                    break;
                }
            }
        }

        if (paid == 'F')
        {
            printf("Trip does not exist\n");
        }
    } while (paid == 'F');
}

// CONFIRMED TRIP
void confirmed_trips()
{
    /*
    Confirmed trips:

        The user chooses whether they want to view their confirmed trips in ascending or adescending order
    */
    system("clear");

    char sort_choice, sorted = 'F';
    do
    {
        printf(" Please Choose the way you want your booked trips presented to you:\n\t L for ascending \n\t H for Descending ->");
        scanf("%c", &sort_choice);

        if (sort_choice == 'L')
        {
            sort_ascening();
            sorted = 'T';
        }

        else if (sort_choice == 'H')
        {
            sort_ascening();
            sorted = 'T';
        }
    } while (sorted == 'F');

    printf("\n Press any key to continue");
    getchar();
}

void sort_ascening()
{
    /*
    Sort ascending function:

        A Selection sort algorithm, but with a different implementation to sort the dates of departure.
        As the name suggests it sorts the dates from earliest to latest
    */
    int n = user[current_user_index].sum_of_trips;
    int i, j, position, swap;
    for (i = 0; i < (n - 1); i++)
    {
        position = i;
        for (j = i + 1; j < n; j++)
        {
            if (trips[position].departure.yyyy > trips[j].departure.yyyy)
            {
                position = j;
                struct booked_trip swap;
                swap.departure = trips[i].departure;
                trips[i].departure = trips[position].departure;
                trips[position].departure = swap.departure;
            }

            else if (trips[position].departure.yyyy == trips[j].departure.yyyy && trips[position].departure.mm > trips[j].departure.mm)
            {
                position = j;
                struct booked_trip swap;
                swap.departure = trips[i].departure;
                trips[i].departure = trips[position].departure;
                trips[position].departure = swap.departure;
            }

            else if (trips[position].departure.yyyy == trips[j].departure.yyyy && trips[position].departure.mm == trips[j].departure.mm && trips[position].departure.dd > trips[j].departure.dd)
            {
                position = j;
                struct booked_trip swap;
                swap.departure = trips[i].departure;
                trips[i].departure = trips[position].departure;
                trips[position].departure = swap.departure;
            }
        }
    }

    for (i = 0; i < user[current_user_index].sum_of_trips; i++)
    {
        printf("\n %d)\tUsername: %s\t%d.%d.%d \n", i, user[current_user_index].username, trips[i].departure.dd, trips[i].departure.mm, trips[i].departure.yyyy);
    }
}

void sort_descending()
{
    /*
    Sort descending function:

        A Selection sort algorithm, but with a different implementation to sort the dates of departure.
        As the name suggests it sorts the dates from lates to earliest
    */
    int n = user[current_user_index].sum_of_trips;
    int i, j, position, swap;
    for (i = 0; i < (n - 1); i++)
    {
        position = i;
        for (j = i + 1; j < n; j++)
        {
            if (trips[position].departure.yyyy < trips[j].departure.yyyy)
            {
                position = j;
                struct booked_trip swap;
                swap.departure = trips[i].departure;
                trips[i].departure = trips[position].departure;
                trips[position].departure = swap.departure;
            }

            else if (trips[position].departure.yyyy == trips[j].departure.yyyy && trips[position].departure.mm < trips[j].departure.mm)
            {
                position = j;
                struct booked_trip swap;
                swap.departure = trips[i].departure;
                trips[i].departure = trips[position].departure;
                trips[position].departure = swap.departure;
            }

            else if (trips[position].departure.yyyy == trips[j].departure.yyyy && trips[position].departure.mm == trips[j].departure.mm && trips[position].departure.dd < trips[j].departure.dd)
            {
                position = j;
                struct booked_trip swap;
                swap.departure = trips[i].departure;
                trips[i].departure = trips[position].departure;
                trips[position].departure = swap.departure;
            }
        }
    }

    for (i = 0; i < user[current_user_index].sum_of_trips; i++)
    {
        printf("\n %d)\tUsername: %s\t%d.%d.%d \n", i, user[current_user_index].username, trips[i].departure.dd, trips[i].departure.mm, trips[i].departure.yyyy);
    }
}

void replace_newline(char str[])
{
    /*
    this funtion finds the all the new lines that fgets leavis stored in a string
    it then replaces it with \0
    */
    int length = lengthof(str);

    if (length > 0)
    {
        int i;
        for (i = 1; i < length; i++)
        {
            if (str[length - i] == '\n')
            {
                str[length - i] = '\0'; // Replace newline with null terminator
            }
        }
    }

    // an imprived version of the one used in the fisr project
}

int lengthof(char check_str[20])
{
    /*
    lengthof:
            - the function takes a string variable and calculates the amount of characters until '\0'
            (using the integer variable i)
            - afterwards it returns i
    */

    int length = 0;
    while (check_str[length] != '\0')
    {
        length++;
    }

    return length;
}

int CheckStr(const char *str1, const char *str2)
{
    /*
    basicaly my own non-case-sensitive version of strcmp
    i was having some problems when using strcmp to compare strings without caring if the letters are capital or lower case
    so i made my own version
    function was used in the last project this is an updated and better version

    returns 0 is the strings are not thee same

    returns 1 if the strings are the same

    i used cont char because the function is not intended to modify the strings.

    used tolower to aviod check every possible

    When comparing the strings i used unsigned char to avoid any possible errors
    */

    while (*str1 && *str2)
    {
        if (tolower((unsigned char)*str1) != tolower((unsigned char)*str2))
        {
            return 0;
        }
        str1++;
        str2++;
    }

    return 1;
}

int isNum(char str[])
{
    /*
    returns 0 is the string constains onlu numbers

    returns 1 if the string contains anything other than numbers (including spaces)
    */
    int j;
    int not_num_count = 0;
    for (j = 0; j < 16; j++)
    {
        if (str[j] < '0' || str[j] > '9')
        {
            return 1;
        }
    }

    return 0;
}
