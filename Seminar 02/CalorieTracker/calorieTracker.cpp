#include <fstream>
#include <format>
#include <iostream>
#include <print>

using std::println;
using std::format;
using std::ostream;
using std::cout;

// the Date class from the getters/setters example
class Date {
private:
    int year = 1970;
    int month = 1;
    int day = 1;

    // Index 0 -> January, ..., Index 11 -> December
    const int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    bool isLeapYear(int y) const {
        return (y % 4 == 0) && (y % 100 != 0 || y % 400 == 0);
    }

    int getMaxDaysForMonth(int y, int m) const {
        if (m < 1 || m > 12) {
            return 0;
        }

        if (m == 2) {
            if (isLeapYear(y)) {
                return 29;
            }
            return 28;
        }

        return daysInMonth[m - 1];
    }

    bool isValidCombination(int y, int m, int d) const {
        if (y < 1900 || y > 2100) {
            return false;
        }
        if (m < 1 || m > 12) {
            return false;
        }

        int maxDays = getMaxDaysForMonth(y, m);
        if (d < 1 || d > maxDays) {
            return false;
        }

        return true;
    }

public:
    bool setAll(int y, int m, int d) {
        if (!isValidCombination(y, m, d)) {
            return false;
        }
        year = y;
        month = m;
        day = d;
        return true;
    }

    bool setYear(int y) {
        if (!isValidCombination(y, month, day)) {
            return false;
        }
        year = y;
        return true;
    }

    bool setMonth(int m) {
        if (!isValidCombination(year, m, day)) {
            return false;
        }
        month = m;
        return true;
    }

    bool setDay(int d) {
        if (!isValidCombination(year, month, d)) {
            return false;
        }
        day = d;
        return true;
    }

    int getYear() const {
        return year;
    }

    int getMonth() const {
        return month;
    }

    int getDay() const {
        return day;
    }
};

class MealEntry {
private:
    char name[32] = "";
    int calories = 0;

public:
    bool setName(const char* s) {
        if (s == nullptr) { return false; }
        if (strlen(s) == 0) { return false; }
        if (strlen(s) >= sizeof(name)) { return false; }
        strcpy(name, s);
        return true;
    }

    bool setCalories(int c) {
        if (c < 0) { return false; }
        calories = c;
        return true;
    }

    const char* getName() const { return name; }

    int getCalories() const { return calories; }
};

class CalorieTracker {
private:
    // nested declaration of a class, that way it is only accessible inside CalorieTracker
    class PersonalMetrics {
    private:
        int weightKg = 78;   // 30..300
        int heightCm = 175;  // 120..230
        int age = 18;        // 1..120
        int activityLevel = 0;    // 0..2 (you can also make it an enum)

        mutable bool goalValid = false;
        mutable int cachedGoal = 0;

        bool inRange(int x, int min, int max) const {
            return x >= min && x <= max;
        }

        void invalidateGoalCache() {
            goalValid = false;
        }

    public:
        bool setWeightKg(int w) {
            if (!inRange(w, 30, 300)) {
                return false;
            }
            weightKg = w;
            invalidateGoalCache();
            return true;
        }

        bool setHeightCm(int h) {
            if (!inRange(h, 120, 230)) {
                return false;
            }
            heightCm = h;
            invalidateGoalCache();
            return true;
        }

        bool setAge(int a) {
            if (!inRange(a, 1, 120)) {
                return false;
            }
            age = a;
            invalidateGoalCache();
            return true;
        }

        bool setActivity(int act) {
            if (!inRange(act, 0, 2)) {
                return false;
            }
            activityLevel = act;
            invalidateGoalCache();
            return true;
        }

        int getWeightKg() const {
            return weightKg;
        }

        int getHeightCm() const {
            return heightCm;
        }

        int getAge() const {
            return age;
        }

        int getActivityLevel() const {
            return activityLevel;
        }

        int getGoalCalories() const {
            if (goalValid) {
                return cachedGoal;
            }

            // some weird formula
            int base = 24 * weightKg;
            int heightAdj = (heightCm - 170) * 5;
            int ageAdj = (age - 30) * 10;
            int goal = base + heightAdj - ageAdj + activityLevel * 200;

            cachedGoal = goal;
            goalValid = true;
            return cachedGoal;
        }
    };

    PersonalMetrics metrics;
    MealEntry meals[32];
    int mealsCount = 0;
    int totalCalories = 0;

public:
    // Encapsulation-friendly forwarded setters
    bool setWeightKg(int w) {
        return metrics.setWeightKg(w);
    }

    bool setHeightCm(int h) {
        return metrics.setHeightCm(h);
    }

    bool setAge(int a) {
        return metrics.setAge(a);
    }

    bool setActivity(int act) {
        return metrics.setActivity(act);
    }

    int getGoalCalories() const {
        return metrics.getGoalCalories();
    }

    void resetDay() {
        mealsCount = 0;
        totalCalories = 0;
    }

    bool addMeal(const MealEntry& meal) {
        if (mealsCount >= 32) { return false; }
        meals[mealsCount] = meal;
        totalCalories += meal.getCalories();
        mealsCount++;
        return true;
    }

    bool undoLastMeal() {
        if (mealsCount == 0) {
            return false;
        }

        mealsCount--;
        totalCalories -= meals[mealsCount].getCalories();
        return true;
    }

    int getMealsCount() const {
        return mealsCount;
    }

    int getTotalCalories() const {
        return totalCalories;
    }

    bool isOverGoal() const {
        return totalCalories > metrics.getGoalCalories();
    }

    // Saves record to "YYYY-MM-DD.txt"
    bool writeDailyRecord(const Date& date, ostream& os) const {
        // Showcasing println, which is the more modern approach
        println(os, "Date: {}", format("{:04d}-{:02d}-{:02d}", date.getYear(), date.getMonth(), date.getDay()));
        println(os, "Personal metrics:");
        println(os, "  Weight (kg): {}", metrics.getWeightKg());
        println(os, "  Height (cm): {}", metrics.getHeightCm());
        println(os, "  Age: {}", metrics.getAge());
        println(os, "  Activity level: {}", metrics.getActivityLevel());
        println(os, "  Goal kcal: {}", metrics.getGoalCalories());

        println(os, "Meals:");
        for (int i = 0; i < mealsCount; i++) {
            println(os, "  - name: {}, {} kcal", meals[i].getName(), meals[i].getCalories());
        }

        println(os, "Balance: {} / {}", totalCalories, metrics.getGoalCalories());
        println(os, "Over goal: {}", isOverGoal() ? "yes" : "no");

        return true;
    }

    bool saveDailyRecordToFile(const Date& date) const {
        std::ofstream ofs(format("{:04d}-{:02d}-{:02d}.txt", date.getYear(), date.getMonth(), date.getDay()));
        if (!ofs.is_open()) {
            return false;
        }

        // reusing the function from above (code reusability)!!!
        // that way we can also print it in the same format to the console, not only to a file
        writeDailyRecord(date, ofs);
        ofs.close();
        return true;
    }
};

int main() {
    Date d;
    if (!d.setAll(2026, 2, 24)) {
        println("Invalid date");
        return 1;
    }

    CalorieTracker t;
    t.resetDay();

    if (!t.setWeightKg(78)) {
        println("Invalid weight");
        return 1;
    }
    if (!t.setHeightCm(174)) {
        println("Invalid height");
        return 1;
    }
    if (!t.setAge(23)) {
        println("Invalid age");
        return 1;
    }
    if (!t.setActivity(1)) {
        println("Invalid activity");
        return 1;
    }

    MealEntry m1;
    m1.setName("mazilka");
    m1.setCalories(290);
    t.addMeal(m1);

    MealEntry m2;
    m2.setName("tortichka");
    m2.setCalories(750);
    t.addMeal(m2);

    MealEntry m3;
    m3.setName("chicken breast");
    m3.setCalories(430);
    t.addMeal(m3);

    if (!t.saveDailyRecordToFile(d)) {
        println("Failed to save");
        return 1;
    }

    t.writeDailyRecord(d, cout);
}
