// Michael Tucholski
// mjt107@zips.uakron.edu
// purpose is to display understanding of concepts learned in CS2
#include <cassert>
#include <iosfwd>
#include <iostream>
#include <iomanip>
#include <limits>  // numeric_limits<std::streamsize> for validations
#include<ctime>
#include <fstream>
#include <string>
#include<string.h>
#include <map>
#include <vector>

#include "Restaurant.h"
#include "linkedList.h"
#include "Meals.h"

// these are declarations - prefer this or std:: prefix
using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::left;
using std::right;
using std::string;
using std::ofstream;
using std::ifstream;
using std::vector;
using std::map;

static int uChoose = 0;
//prototypes
int
mainMenu();

void
taskA();

void
taskB();

void
taskC();

void
taskD();

void
taskE();

int
taskF();

void
OutputToFile(Restaurant );

string
getZeros (int );

int
largestInt(int [],int );

int
getLargest2D (int [][24]);

int
getDay(string );

string
calcualateAMorPM (int );

struct Test_myCode
{
    void
    default_beg()
    {
        uChoose = mainMenu();
        assert(!(std::cin.fail()));
    }
    void
    whatAction()
    {
        switch (uChoose)
        {
        case (1):
            taskA();
            break;
        case (2):
            taskB();
            break;
        case (3):
            taskC();
            break;
        case (4):
            taskD();
            break;
        case (5):
            taskE();
            break;
        case (6):
            taskF();
            break;
        default:
            cout << "no case";
        }
    }

    // The test runner for this test class.
    void
    run()
    {
        default_beg();
        whatAction();
    }

};


int
main()
{
    Test_myCode test;
    while (true)
    {
        test.run();
    }

}



int
mainMenu()
{
    // heading, input section
    bool endProgram = false;
    while(!endProgram)
    {
        cout << endl;
        cout << setw(68) << "__________________________________________________________________ " << endl;
        cout << setw(68) << "|------------------------------------------------------------------|" << endl;
        cout << setw(68) << "|                               Mike's                             |" << endl;
        cout << setw(68) << "|                    healthy food choices (HFC) system             |" << endl;
        cout << setw(68) << "|__________________________________________________________________|" << endl;
        cout << left << setw(2) << "|" << setw(21) << " " << setw(43) << "   MAIN MENU"
             << right << setw(2) << "|" << endl;
        cout << left << setw(2) << "|" << setw(21) << " " << setw(43) << "1) Request Table"
             << right << setw(2) << "|" << endl;
        cout << left << setw(2) << "|" << setw(21) << " " << setw(43) << "2) Free up a Table"
             << right << setw(2) << "|" << endl;
        cout << left << setw(2) << "|" << setw(21) << " " << setw(43) << "3) Find a Patron"
             << right << setw(2) << "|" << endl;
        cout << left << setw(2) << "|" << setw(21) << " " << setw(43) << "4) Display Restaurant Usage"
             << right << setw(2) << "|" << endl;
        cout << left << setw(2) << "|" << setw(21) << " " << setw(43) << "5) Print Transaction Log"
             << right << setw(2) << "|" << endl;
        cout << left << setw(2) << "|" << setw(21) << " " << setw(43) << "6) Quit"
             << right << setw(2) << "|" << endl;
        cout << setw(68) << "|__________________________________________________________________|" << endl;
        cout << endl;
        int userChoice = 0;
        // take and validate the user entry

        cout << "Please enter a choice from the menu, 6 to quit: "; // output stream a message
        cin >> userChoice;
        while (cin.fail() || userChoice<1 || userChoice>8)
        {
            cout << "You must enter a positive numeric value between 1 and 6.";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin >> userChoice;
        }
        if (userChoice == 6)
        {
            endProgram = true;
            break;
        }
        return userChoice;
    }
}
// PLACE CODE HERE FOR EACH TASK
// Number of meals
// Global Constants
// Number of restaurants
const int NUMHFCS = 8;
// Number of tables in each restaurant
int HFCSIZES[NUMHFCS] = {19, 15, 24, 33, 61, 17, 55, 37};
// Names of restaurant
const	std::string RESTAURANT[NUMHFCS] = {"The Salubrious Bistro", "What the Kale?", "Lettuce Enjoy", "Vegan Nights", "Pasta is a Planet", "The Meatless Miracle", "The Pesky Pescatarian", " The Fine Fettle"};

const int NUMMEALS = 10;
// Names of restaurant
const	std::string MEALNAMES[NUMMEALS] = {"Mexican Quinoa Salad", "Kale and Eggs", "Chickpea Vegetable Curry", "Vegetable Pot Pie",
                                           "Eggplant Carbonara", "Butternut Squash Black Bean Chili", "Seafood Medley", " Sweet Potato Black Bean Enchiladas", "Pesto Pasta Salad",
                                           "Tomato Soup and Salad Supremo"
                                        };
// calories (int)
const	int CALORIES[NUMMEALS]
    = {202, 119, 304, 398, 215, 157, 222, 341, 143, 233};
// grams of protein (short)
const	short int PROTEIN[NUMMEALS]
    = {1, 12, 16, 22, 17, 7, 11, 20, 27, 9};
// milligrams of vitamins (short)
const	short int VITAMINS[NUMMEALS]
    = {12, 10, 23, 31, 20, 17, 24, 19, 22, 13};

linkedList<Restaurant> RestaurantLinkedLists [NUMHFCS]; // array of different linked links for the different restaurant
Restaurant arrayOfRestaurants [NUMHFCS]; // array of the restaurants
map<short, Meals> mealsMap; // map for meals
map<short, Meals> :: const_iterator mapIterator = mealsMap.begin(); // iterator for meals map


// TASK A CODE

// precondition takes in a valid restaurant object
//postcondition outputs object information to a text file
void OutputToFile(Restaurant newGuest) // outputs  the new restaurant object to the file
{
    ofstream projectOutputFile;
    projectOutputFile.open("output.txt", std::fstream::out | std::fstream::app);
    if (!projectOutputFile) // fail sequence
    {
        cout << "File open Failure" << endl;
    }
    projectOutputFile << newGuest.getPatronName() << "," ;
    projectOutputFile << newGuest.getMealTime()<< "," ;
    projectOutputFile << newGuest.getMealNumber()<< "," <<newGuest.getMealName()<< ",";
    projectOutputFile << newGuest.getRestaurantNumber()<<","<<newGuest.getCalories()<< ","<< newGuest.getProtein()<< ","<<newGuest.getVitamins()<< endl;
}

// precondition takes in an integer value
//postcondition returns a string with an appropriate amount of zeros compared to the int number it takes in
string getZeros (int idnumber) // finds out how many zeros to put before the ID number, for leading zeros
{
    string zeros;
    if (idnumber<10)
    {
        zeros = "00000";
    }
    else if (idnumber>=10 && idnumber<100)
    {
        zeros = "0000";
    }
    else if (idnumber >=100 && idnumber < 1000)
    {
        zeros = "000";
    }
    else if (idnumber >=1000 && idnumber < 10000)
    {
        zeros = "00";
    }
    else if (idnumber >=10000 && idnumber < 100000)
    {
        zeros = "0";
    }
    else if (idnumber >=100000 && idnumber < 1000000)
    {
        zeros = "";
    }
    return zeros;
}


// precondition there are valid classes such as restaurant and meals, and valid helper functions
//postcondition creates a games object, meals object and puts a new node on the linked list
void
taskA()
{
    cout << "Please enter the restaurant choice from 1 through 8: " ;
    int restaurantNumber;
    cin >> restaurantNumber;
    while (cin.fail() || restaurantNumber<1 || restaurantNumber>8) // input validation
    {
        cout << "You must enter a positive numeric value between 1 and 8.";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> restaurantNumber;
    }
    cout << endl;
    cout << "You have chosen " << RESTAURANT[restaurantNumber-1]<< endl;
    // if there are no tables open, option A will not execute
    if ((RestaurantLinkedLists [restaurantNumber-1].getAmountofNodes()+1)> HFCSIZES[restaurantNumber-1])
    {
        cout << "The restaurant is at full capacity, no tables are left at this time. Please try again later." <<endl;
        cout << "Hit enter  to be directed back to the main menu." << endl;
        cin.get();
    }
    // if there is a table open, this will execute
    else
    {
        Restaurant* newGuest = new Restaurant;
        newGuest->setPatronID();
        string zeros = getZeros(newGuest->getPatronID());
        int tempTable = RestaurantLinkedLists [restaurantNumber-1].getAmountofNodes() +1;
        cout << "Your table number is " << tempTable  << " and your ID number is " <<  zeros <<newGuest->getPatronID() << endl;
        cin.ignore();
        cout << "Please enter the name of the Patron: ";
        string guestName;
        getline(cin, guestName);
        while (guestName.size()<1)// makes sure the user enters a name
        {
            cout << "You must enter a name. " << endl;
            cin.clear();
            cin.ignore();
            getline(cin, guestName);
        }
        newGuest->setPatronName(guestName); // uses input to fill Restaurant object with data
        newGuest->setRestaurantNumber(restaurantNumber);
        newGuest->setMealTime();
        newGuest->setTableNumber(tempTable);

        cout <<"Please enter the meal number from the following choices " << endl;
        for (int i = 0; i< NUMMEALS; i++)
        {
            cout << i+1<< ")    " << MEALNAMES[i] << endl;
        }
        cout << "Meal : ";
        short mealNumber;
        cin >> mealNumber;
        while (cin.fail() || mealNumber<1 || mealNumber>10) // input validation for meal number
        {
            cout << "You must enter a positive numeric value between 1 and 10.";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin >> mealNumber;
        }
        newGuest->setMealNumber(mealNumber);
        newGuest->setMealName(MEALNAMES[mealNumber-1]);
        newGuest->setCalories(CALORIES[mealNumber-1]);
        newGuest->setProtein(PROTEIN[mealNumber-1]);
        newGuest->setVitamins(VITAMINS[mealNumber-1]);
        //    RestaurantLinkedLists[restaurantNumber-1].insertNode(*newGuest);
        RestaurantLinkedLists[restaurantNumber-1].insertAtBack(*newGuest);
        cout << "Your choice was the " << newGuest->getMealName()<< endl;
        cout <<newGuest->getCalories() << " calories, " << newGuest->getProtein() << " grams of protein, and " << newGuest->getProtein()<< " vitamins" << endl;
        //  creates map of meal information
        Meals* newGuestMeal = new Meals;
        newGuestMeal->setMealName(MEALNAMES[mealNumber-1]);
        newGuestMeal->setCalories(CALORIES[mealNumber-1]);
        newGuestMeal->setProtein(PROTEIN[mealNumber-1]);
        newGuestMeal->setVitamins(VITAMINS[mealNumber-1]);
        for (mapIterator = (mealsMap.begin()); mapIterator!=(mealsMap.end()); ++mapIterator)
        {
            mapIterator -> first ;
            mapIterator -> second;
        }
        // mealsMap.insert(std::make_pair(newGuest->getMealNumber(), newGuestMeal));
        mealsMap [newGuest->getMealNumber()]= *newGuestMeal;

        OutputToFile(*newGuest);
        cout << "Hit enter for the next selection" <<endl;
        cin.get();
    }
}


// PLACE CODE HERE FOR EACH TASK
// TASK B CODE
// precondition there is a valid linked list function
//postcondition deletes a node from the linked list
void
taskB()
{
    cout << "Please enter the restaurant choice from 1 through 8: " ;
    short restaurantNumber;
    cin >> restaurantNumber;
    while (cin.fail() || restaurantNumber<1 || restaurantNumber>8) // input validation for restaurant number
    {
        cout << "You must enter a positive numeric value between 1 and 8.";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> restaurantNumber;
    }
    cout << endl;
    cout << "Please enter the table number. " ;
    short BtableNumber;
    cin >> BtableNumber;
    while (cin.fail() || BtableNumber<1 || BtableNumber>HFCSIZES[restaurantNumber]) // input validation for table number
    {
        cout << "You must enter a positive numeric value between 1 and " << HFCSIZES[restaurantNumber] << ". "<< endl ;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> BtableNumber;
    }
    int foundNode =0;
    RestaurantLinkedLists [restaurantNumber-1].current = RestaurantLinkedLists [restaurantNumber-1].head;
    while (foundNode <1) // will run until the node is found
    {
        if (BtableNumber> RestaurantLinkedLists [restaurantNumber-1].getAmountofNodes() ) // checks if the table is already empty
        {
            cout << "The table is already empty. " << endl;
            break;
        }
        if ( RestaurantLinkedLists [restaurantNumber-1].current ->value.getTableNumber() != BtableNumber)
        {
            RestaurantLinkedLists [restaurantNumber-1].current = RestaurantLinkedLists [restaurantNumber-1].current->next;
        }
        else if (RestaurantLinkedLists [restaurantNumber-1].current ->value.getTableNumber() == BtableNumber) // finds the node with the table number that needs to be deleted
        {
            cout << RestaurantLinkedLists [restaurantNumber -1].current ->value.getPatronName()  << " has enjoyed another meal...bye!" << endl;
            RestaurantLinkedLists[restaurantNumber -1].deleteNode(RestaurantLinkedLists [restaurantNumber -1].current ->value);
            RestaurantLinkedLists[restaurantNumber -1].NumberOfNodes--;
            foundNode++;
        }
    }
    cout << "Hit enter for the next selection"<< endl;
    cin.get();
}

// precondition takes in a valid array of ints, and the size of the array
//postcondition retuns the index of the largest number as an int
int largestInt(int arr[],int sizeOf) // returns index of largest number
{
    int largestNum;
    int test;
    int i=0;
    test=i;
    largestNum=arr[i];
    while(i<sizeOf)
    {
        if (largestNum < arr[i])
        {
            largestNum=arr[i];
            test=i;
        }
        i++;
    }
    return test;
}

// precondition takes in a valid 2D array
//postcondition returns index of the largest element
int getLargest2D (int dayandhour[7][24]) // gets index of largest number from 2D array
{
    int largest = 0;
    int index = 0;
    for (int i =0; i<7; i++)
    {
        for (int j =0; j<24; j++)
        {
            if (dayandhour[i][j]>largest)
            {
                largest = dayandhour[i][j];
                index = j;
            }
        }
    }
    return index;
}
// PLACE CODE HERE FOR EACH TASK
// TASK C CODE
// precondition there is a valid text file
//postcondition outputs the favorite food of the user inputted- name
void
taskC()
{
    int mealOccurances[NUMHFCS];
    for (int i=0; i< NUMHFCS; i++)
    {
        mealOccurances[i] = 0;
    }
    ifstream projectInputFile;
    projectInputFile.open("output.txt"); // opens text file
    if (!projectInputFile) // fail sequence
    {
        cout << "File open Failure" << endl;
    }
    cout << "Please enter the patron by name: ";
    cin.ignore();
    string guestName;
    getline(cin, guestName);

    string wholeLine;
    string name;
    string date;
    string foodChoice;
    string  restaurantNumber;
    string foodInfo;
    string  mealNumber ;

    int foundName = 0;
    while (!projectInputFile.eof())
    {
        getline(projectInputFile, name, ',');
        getline(projectInputFile, date, ',');
        getline(projectInputFile, mealNumber, ',');
        getline(projectInputFile, foodChoice, ',');
        getline(projectInputFile, restaurantNumber, ',');
        getline(projectInputFile, foodInfo);

        if (name ==guestName)
        {
            foundName++;
            for (int i =0; i<NUMHFCS; i++)
            {
                if (foodChoice == MEALNAMES[i])
                {
                    mealOccurances[i]++;
                }
            }
        }

    }
    int largestIndex = 0;
    if (foundName >0)
    {
        largestIndex = largestInt(mealOccurances,8);
        cout << guestName << " likes " << MEALNAMES[largestIndex] << endl;
    }
    else if (foundName ==0) // if name is not found
    {
        cout << guestName << " has no favorite " << endl;
    }
    cout << "Hit enter for the next selection"<< endl;
    cin.get();
}

// PLACE CODE HERE FOR EACH TASK
// precondition takes in a valid string
//postcondition returns the index of the correct day
int getDay(string day) // returns number of day of week
{
    if (day.at(0) == 'M')
    {
        return 0;
    }
    else if (day.at(0) == 'T' && day.at(1) == 'u')
    {
        return 1;
    }
    else if (day.at(0) == 'W')
    {
        return 2;
    }
    else if (day.at(0) == 'T' && day.at(1) == 'h')
    {
        return 3;
    }
    else if (day.at(0) == 'F')
    {
        return 4;
    }
    else if (day.at(0) == 'S' && day.at(1) == 'a')
    {
        return 5;
    }
    else if (day.at(0) == 'S' && day.at(1) == 'u')
    {
        return 6;
    }
    else
    {
        return 0;
    }
}

string calcualateAMorPM (int number)
{
    string amOrpm;
    if (number<12) //determines whether to print AM or PM
    {
        amOrpm = "AM";
    }
    else
    {
        amOrpm = "PM";
    }
    return amOrpm;
}

// TASK D CODE
// precondition there is a valid text file called output
//postcondition reports various bits of information based on user input
void
taskD()
{
    ifstream projectInputFile;
    projectInputFile.open("output.txt"); // opens text file
    if (!projectInputFile) // fail sequence
    {
        cout << "File open Failure" << endl;
    }
    string wholeLine;
    string name;
    string date;
    string foodChoice;
    string  restaurantNumber;
    string foodInfo;
    string  mealNumber ;
    int restaurantTally[NUMHFCS];
    int mealTally [NUMHFCS];
    int dayTally [7];
    int intMealNumber;
    int intRestaurantNumber;
    int dayAndHour [7][24];
    for (int j = 0; j<7; j++) // sets each value to zero
    {
        for (int i = 0; i<24; i++)
        {
            dayAndHour[j][i]=0;
        }
    }
    string day;
    string time;
    string daysOfTheWeek[7]= {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    for (int i=0; i< NUMHFCS; i++)// sets each value to zero
    {
        restaurantTally[i]=0;
        mealTally[i] = 0;
    }
    for (int i =0; i<NUMHFCS; i++)//sets each value to zero
    {
        dayTally[i] = 0;
    }
    while (!projectInputFile.eof()) // stores info from data file into variables
    {
        getline(projectInputFile, name, ',');
        getline(projectInputFile, date, ',');
        day = date.substr(0,2);
        time = date.substr(11,12);
        int convertedDay = getDay(day);
        int intTime = stoi(time.substr(0,2));
        dayTally[convertedDay]++;
        dayAndHour[convertedDay] [intTime]++;
        getline(projectInputFile, mealNumber, ',');
        intMealNumber = std::stoi(mealNumber);
        mealTally[intMealNumber]++;
        getline(projectInputFile, foodChoice, ',');
        getline(projectInputFile, restaurantNumber, ',');
        intRestaurantNumber = std::stoi(restaurantNumber);
        restaurantTally[intRestaurantNumber-1]++;
        getline(projectInputFile, foodInfo);
    }
    cout << "A) Favorite Restaurants"<<endl;
    cout << "B) Favorite Meals"<< endl;
    cout << "C) Favorite days and times"<< endl;
    cout << endl;
    cout << "Pick your favorite report from the list:" << endl;
    char answer;
    cin >> answer;
    if (answer == 'a' || answer == 'A')
    {
        int firstRestaurant = largestInt(restaurantTally, NUMHFCS);
        cout << "The first most favorite restaurant is "<<  RESTAURANT[firstRestaurant]<<   endl;
        restaurantTally[firstRestaurant] = 0; // sets largest to 0, so the second largest now becomes the largest
        int secondRestaurant = largestInt(restaurantTally, NUMHFCS);
        cout << "The second most favorite restaurant is "<< RESTAURANT[secondRestaurant]<<  endl;
        restaurantTally[secondRestaurant] = 0;
        int thirdRestaurant = largestInt(restaurantTally, NUMHFCS);
        cout << "The third most favorite restaurant is "<< RESTAURANT[thirdRestaurant]<<   endl;
    }
    else if (answer == 'b' || answer =='B')
    {
        int firstMeal = largestInt(mealTally, NUMHFCS);
        cout << "The first most favorite meal is " <<MEALNAMES[firstMeal-1]<<   endl;
        mealTally[firstMeal] = 0;
        int secondMeal = largestInt(mealTally, NUMHFCS);
        cout << "The second most favorite meal is "<<MEALNAMES[secondMeal-1]<<  endl;
        mealTally[secondMeal] = 0;
        int thirdMeal = largestInt(mealTally, NUMHFCS);
        cout << "The third most favorite meal is "<< MEALNAMES[thirdMeal-1]<<  endl;
    }

    else if (answer == 'c' || answer =='C')
    {
        int firstDay = largestInt(dayTally, 7);
        int firstHour = getLargest2D(dayAndHour);
        string amOrpm;
        amOrpm = calcualateAMorPM(firstHour);
        int outputHour;
        if (firstHour > 12) // converts military time to normal time
        {
            outputHour = firstHour -12;
        }
        else
        {
            outputHour = firstHour;
        }
        cout << "The first most favorite day and times are " << daysOfTheWeek[firstDay] << " between " << outputHour << " and " << outputHour +1 << " "<< amOrpm << endl;
        dayTally[firstDay]=0;
        dayAndHour[firstDay][firstHour] = 0;
        int secondDay = largestInt(dayTally, 7);
        int secondHour = getLargest2D(dayAndHour);
        int secondOutputHour;
        amOrpm = calcualateAMorPM(secondHour);
        if (secondHour > 12)
        {
            secondOutputHour = secondHour -12;
        }
        else
        {
            secondOutputHour = secondHour;
        }

        cout << "The second most favorite day and times are " << daysOfTheWeek[secondDay] << " between " << secondOutputHour << " and " << secondOutputHour +1 << " "<< amOrpm << endl;
        dayTally[secondDay]=0;
        dayAndHour[secondDay][secondHour] = 0;

        int thirdHour = getLargest2D(dayAndHour);
        int thirdDay = largestInt(dayTally, 7);
        int thirdOutputHour;
        amOrpm = calcualateAMorPM(thirdHour);

        if (thirdHour > 12)
        {
            thirdOutputHour = thirdHour -12;
        }
        else
        {
            thirdOutputHour = thirdHour;
        }
        cout << "The third most favorite day and times are " << daysOfTheWeek[thirdDay] << " between " << thirdOutputHour << " and " << thirdOutputHour +1 << " "<< amOrpm << endl;
    }
    cout << "Hit enter for the next selection"<< endl;
    cin.get();
}

// PLACE CODE HERE FOR EACH TASK
// TASK E CODE
// precondition there is a valid text file called output
//postcondition outputs all information from text file, organized by restaurant and is also in chronological order
void
taskE()
{
    cout << "----------------Transaction Log----------------" << endl;
    ifstream projectInputFile;
    projectInputFile.open("output.txt"); // opens text file
    if (!projectInputFile) // fail sequence
    {
        cout << "File open Failure" << endl;
    }
    string wholeLine;
    string name;
    string date;
    string mealNumber;
    string foodChoice;
    string restaurantNumber;
    string foodInfo;
    string arrayOfstrings [20];
    int intRestaurantNumber =0;
    cout << "Customer Name " << "Date and Time " << "Meal Number " << "Food Choice " << "Restaurant Number " << "Food Info " << endl;
    for (int i =1; i<=NUMHFCS; i++)
    {
        cout << endl;
        cout << "Restaurant Name : " << RESTAURANT[i] << endl;
        cout << endl;
        while (!projectInputFile.eof())
        {

            getline(projectInputFile, name, ',');
            getline(projectInputFile,date, ',');
            getline(projectInputFile,mealNumber, ',');
            getline(projectInputFile, foodChoice, ',');
            getline(projectInputFile,restaurantNumber, ',');
            intRestaurantNumber = stoi(restaurantNumber);
            getline(projectInputFile, foodInfo);
            if (intRestaurantNumber == i)
            {
                cout << name << " " << date << " " << foodChoice  << " " << restaurantNumber << " "  << foodInfo << endl;
            }
        }
        projectInputFile.clear();
        projectInputFile.seekg(0);
    }

    cout << "Hit enter for the next selection"<< endl;
    cin.get();
}

// precondition user input is 6
//postcondition ends program by throwing exception
int
taskF()
{
    cout << "End of program usage. Have a nice day!" << endl;
    throw std::exception();
}


