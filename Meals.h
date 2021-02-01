#ifndef MEALS_H_INCLUDED
#define MEALS_H_INCLUDED
// class that is eventually put into meals map
class Meals
{
private:
   string mealName;
   int calories;
   short protein;
   short vitamins;
public:
    Meals (string mn, int cal, short pro, short vit)
    {
        mn = "Default";
        cal = 0;
        pro = 0;
        vit = 0;
    }
    Meals ()
    {
        setMealName("Default");
        setCalories(0);
        setProtein(0);
        setVitamins(0);
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

#endif // MEALS_H_INCLUDED
