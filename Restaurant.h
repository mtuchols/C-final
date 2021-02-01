#ifndef RESTAURANT_H_INCLUDED
#define RESTAURANT_H_INCLUDED

#include <time.h>
#include<ctime>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::left;
using std::right;
using std::string;

//generates a random number between a minimum and maximum
int randNum(int min, int max)
{
   return rand() % max + min;
}

class Restaurant
{
private:
    short restaurantNumber;
    int tableNumber;
    int patronID;
    string patronName;
    short mealNumber;
    char mealTime[20];
    string mealName;
    int calories;
    int protein;
    int vitamins;
public:
        Restaurant (short rn, int tn, int id, string pn, char mt[20], short mn, string men, int cal, int pro, int vit)
    {
        rn = 0;
        tn = 0;
        id = 00000;
        pn = "Default";
        mn = 0;
        time_t now = time(0);
        // convert now to c-string form
        char* timeOf = ctime(&now);
        // we want a way to limit the size to be just 20 in length
        timeOf[20] = '\0'; // this effectively truncates the c-string
        for (int i = 0; i < 20; i++)
        {
            mt[i] = timeOf[i];
        }
        men = "Default";
        cal = 0;
        pro = 0;
        vit = 0;

    }

    Restaurant () // default constructor
    {
        setRestaurantNumber(0);
        setTableNumber(1);
        setPatronID();
        setPatronName("Default");
        setMealNumber(0);
        setMealName("Default");
        setCalories(0);
        setProtein(0);
        setVitamins(0);
    }

    short getRestaurantNumber() const // get functions, get name, type and cost
    {
        return restaurantNumber;
    }
    int getTableNumber() const
    {
        return tableNumber;
    }
    int getPatronID () const
    {
     //   return randNum(00000, 99999);
     return patronID;
    }
    string getPatronName() const
    {
        return patronName;
    }
    char* getMealTime()
    {
        return mealTime;
    }
    short getMealNumber() const
    {
        return mealNumber;
    }
    string getMealName() const
    {
        return mealName;
    }
    int getCalories () const
    {
        return calories;
    }
    int getProtein () const
    {
        return protein;
    }
    int getVitamins() const
    {
        return vitamins;
    }

    void setRestaurantNumber(short rn) // set functions, set the name, type and cost
    {
        restaurantNumber = rn;
    }
    void setTableNumber(int tn)
    {
        tableNumber = tn;

    }
    void setPatronID ()
    {
    srand (time(NULL));
    rand() % 99999 + 00000;
    patronID = rand();
    }
    void setPatronName (string pn)
    {
        patronName = pn;
    }
   void setMealTime ( )
    {
        time_t now = time(0);
        char* timeOf = ctime(&now);
        timeOf[20] = '\0'; // this effectively truncates the c-string
        for (int i = 0; i<20; i++)
        {
            mealTime[i] = timeOf[i];
        }
    }
    void setMealNumber(short mn)
    {
        mealNumber = mn;
    }
    void setMealName(string men)
    {
        mealName =men;
    }
    void setCalories(int cal)
    {
        calories = cal;
    }
    void setProtein(int pro)
    {
        protein = pro;
    }
    void setVitamins(int vit)
    {
        vitamins = vit;
    }
};


#endif // RESTAURANT_H_INCLUDED
