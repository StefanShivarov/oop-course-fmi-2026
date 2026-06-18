#include <iostream>
using namespace std;

class Ingredient {
    char* name = nullptr;
    int quantity = 0;
    char* measuring_unit = nullptr;
    public:
    Ingredient() = default;
    Ingredient(const char* name, const int quantity, const char* measuring_unit) : quantity(quantity) {
        this -> name = new char[strlen(name) + 1];
        strcpy(this -> name, name);
        this -> measuring_unit = new char[strlen(measuring_unit) + 1];
        strcpy(this -> measuring_unit, measuring_unit);
    }
    Ingredient(const Ingredient& other) {
        name = new char[strlen(other.name) + 1];
        strcpy(this -> name, other.name);
        this -> quantity = other.quantity;
        this -> measuring_unit = new char[strlen(other.measuring_unit) + 1];
        strcpy(this -> measuring_unit, other.measuring_unit);
    }
    Ingredient& operator=(const Ingredient& other) {
        if (this != &other) {
            delete[] name;
            delete[] measuring_unit;
            this -> quantity = other.quantity;
            if (other.name) {
                this -> name = new char[strlen(other.name) + 1];
                strcpy(this -> name, other.name);
            }
            else {
                this -> name = nullptr;
            }
            if (other.measuring_unit) {
                this -> measuring_unit = new char[strlen(other.measuring_unit) + 1];
                strcpy(this -> measuring_unit, other.measuring_unit);
            }
            else {
                this -> measuring_unit = nullptr;
            }
        }
        return *this;
    }
    ~Ingredient() {
        delete[] name;
        delete[] measuring_unit;
    }
    string toString() {
        return format("Name: {}, quantity: {}, measuring unit: {}", name, quantity, measuring_unit);
    }
    string getName() const {
        return name;
    }
};
class Recipe {
    char* name = nullptr;
    char* description = nullptr;
    Ingredient* ingredients = nullptr;
    int ingredientCount = 0;
    static int nextId;
    int id;
    public:
    Recipe() : id(nextId++) {}
    Recipe(const char* name, const char* description) : id(nextId++) {
        this -> name = new char[strlen(name) + 1];
        strcpy(this -> name, name);
        this -> description = new char[strlen(description) + 1];
        strcpy(this -> description, description);
    }
    Recipe(const Recipe& other) : ingredientCount(other.ingredientCount), id(nextId++) {
        if (other.name) {
            name = new char[strlen(other.name) + 1];
            strcpy(this -> name, other.name);
        }
        else {
            this -> name = nullptr;
        }
        if (other.description) {
            description = new char[strlen(other.description) + 1];
            strcpy(this -> description, other.description);
        }
        else {
            this -> description = nullptr;
        }
        if (other.ingredients) {
            ingredients = new Ingredient[other.ingredientCount];
            for (int i = 0; i < other.ingredientCount; i++) {
                ingredients[i] = other.ingredients[i];
            }
        }
        else {
            this -> ingredients = nullptr;
        }
    }
    Recipe& operator=(const Recipe& other) {
        if (this != &other) {
            delete[] name;
            delete[] description;
            delete[] ingredients;
            id = nextId++;
            if (other.name) {
                name = new char[strlen(other.name) + 1];
                strcpy(this -> name, other.name);
            }
            else {
                this -> name = nullptr;
            }
            if (other.description) {
                description = new char[strlen(other.description) + 1];
                strcpy(this -> description, other.description);
            }
            else {
                this -> description = nullptr;
            }
            if (other.ingredients) {
                this -> ingredients = new Ingredient[other.ingredientCount];
                ingredientCount = other.ingredientCount;
                for (int i = 0; i < other.ingredientCount; i++) {
                    this -> ingredients[i] = other.ingredients[i];
                }
            }
            else {
                this -> ingredients = nullptr;
            }
        }
        return *this;
    }
    ~Recipe() {
        delete[] name;
        delete[] description;
        delete[] ingredients;
    }
    int getId() const {
        return id;
    }
    const char* getName() const {
        return name;
    }
    string toString() {
        string ingredientsString;
        for (int i = 0; i < ingredientCount - 1; i++) {
            ingredientsString += ingredients[i].getName() + ", ";
        }
        ingredientsString += ingredients[ingredientCount - 1].getName();
        return format("Name: {}, description: {}, ingredients: {}, id: {}", name, description, ingredientsString, id);
    }
    void addIngredient(const Ingredient& other) {
        auto* newIngredients = new Ingredient[this -> ingredientCount + 1];
        for (int i = 0; i < this -> ingredientCount; i++) {
            newIngredients[i] = this -> ingredients[i];
        }
        newIngredients[ingredientCount] = other;
        ingredientCount++;
        delete[] ingredients;
        ingredients = newIngredients;
    }
    bool deleteIngredient(const char* other) {
        int index = -1;
        for (int i = 0; i < ingredientCount; i++) {
            if (ingredients[i].getName() == other) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            return false;
        }
        auto* newIngredients = new Ingredient[ingredientCount - 1];
        for (int i = 0; i < ingredientCount - 1; i++) {
            if (i != index) {
                newIngredients[i] = this -> ingredients[i];
            }
        }
        newIngredients[index] = ingredients[ingredientCount - 1];
        delete[] ingredients;
        ingredients = newIngredients;
        ingredientCount--;
        return true;
    }
    bool containsIngredient(const char* other) const {
        for (int i = 0; i < ingredientCount; i++) {
            if (ingredients[i].getName() == other) {
                return true;
            }
        }
        return false;
    }
    int getIngredientCount() const {
        return ingredientCount;
    }
    string getIngredientNameAt(const int index) const {
        if (index > ingredientCount - 1 || index < 0) {
            return "";
        }
        return ingredients[index].getName();
    }
};
int Recipe::nextId = 0;
class RecipeBook {
    Recipe* recipes = nullptr;
    int recipesCount = 0;
    public:
    RecipeBook() = default;
    RecipeBook(const RecipeBook& other) : recipesCount(other.recipesCount) {
        if (other.recipes) {
            this -> recipes = new Recipe[other.recipesCount];
            for (int i = 0; i < other.recipesCount; i++) {
                this -> recipes[i] = other.recipes[i];
            }
        }
        else {
            this -> recipes = nullptr;
        }
    }
    RecipeBook& operator=(const RecipeBook& other) {
        if (this != &other) {
            delete[] recipes;
            recipesCount = other.recipesCount;
            if (other.recipes) {
                this -> recipes = new Recipe[other.recipesCount];
                for (int i = 0; i < other.recipesCount; i++) {
                    this -> recipes[i] = other.recipes[i];
                }
            }
            else {
                this -> recipes = nullptr;
            }
        }
        return *this;
    }
    void addRecipe(const Recipe& other) {
        auto* newRecipe = new Recipe[recipesCount + 1];
        for (int i = 0; i < recipesCount; i++) {
            newRecipe[i] = this -> recipes[i];
        }
        newRecipe[recipesCount] = other;
        recipesCount++;
        delete[] recipes;
        recipes = newRecipe;
    }
    bool deleteRecipe(const int id) {
        int index = -1;
        for (int i = 0; i < recipesCount; i++) {
            if (recipes[i].getId() == id) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            return false;
        }
        auto* newRecipe = new Recipe[recipesCount - 1];
        for (int i = 0; i < recipesCount - 1; i++) {
            if (i != index) {
                newRecipe[i] = this -> recipes[i];
            }
        }
        newRecipe[index] = recipes[recipesCount - 1];
        delete[] recipes;
        recipes = newRecipe;
        recipesCount--;
        return true;
    }
    void lookup(const char* name) const {
        for (int i = 0; i < recipesCount; i++) {
            if (strcmp(recipes[i].getName(), name) == 0) {
                println("{}", recipes[i].toString());
                break;
            }
        }
    }
    void lookup(const int id) const {
        for (int i = 0; i < recipesCount; i++) {
            if (recipes[i].getId() == id) {
                println("{}", recipes[i].toString());
                break;
            }
        }
    }
    void print() const {
        for (int i = 0; i < recipesCount; i++) {
            println("{}", recipes[i].toString());
        }
    }
    void filter(const char* other) const {
        println("Recipes using {}:", other);
        for (int i = 0; i < recipesCount; i++) {
            bool uses = false;
            for (int j = 0; j < recipes[i].getIngredientCount(); j++) {
                if (recipes[i].getIngredientNameAt(j) == other) {
                    uses = true;
                    break;
                }
            }
            if (uses) {
                println("{}", recipes[i].toString());
            }
        }
    }
};
int main() {
    Ingredient i1("Salt", 10, "g");
    Ingredient i2("Pepper", 50, "g");
    Ingredient i3("Tomato juice", 30, "ml");
    Ingredient i4("Cheese", 20, "g");
    println("{}", i1.toString());
    println("{}", i2.toString());
    println("{}", i3.toString());
    println("{}", i4.toString());
    Recipe r1("Shopska salad", "500g");
    Recipe r2("Ovcharska salad", "400g");
    r1.addIngredient(i1);
    r1.addIngredient(i2);
    r2.addIngredient(i3);
    r2.addIngredient(i4);
    println("{}", r1.toString());
    println("{}", r2.toString());
    RecipeBook book;
    book.addRecipe(r1);
    book.addRecipe(r2);
    println();
    book.print();
    println();
    book.deleteRecipe(6);
    book.print();
    println();
    book.lookup("Ovcharska salad");
    book.lookup(9);
    Ingredient i5("Svinsko", 100, "g");
    r2.addIngredient(i5);
    println("{}", r2.toString());
    r2.deleteIngredient("Cheese");
    println("{}", r2.toString());
    println("{}", r2.containsIngredient("Cheese"));
    println("{}", r2.containsIngredient("Svinsko"));
    book.filter("Salt");
    book.filter("Pepper");
    book.filter("Tomato juice");
    book.filter("Cheese");
    book.filter("Svinsko");
}