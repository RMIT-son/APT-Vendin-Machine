//
// Created by Son on 5/11/2024.
//

#ifndef FOOD_H
#define FOOD_H
#include "LinkedList.h"




class Food {
public:
    /**
     *@brief Default constructor for the Food class
     *@details This constructor will create a new Food object with no food items in it.
     */
    Food();

    /**
     *@brief Default destructor for the Food class
     *@details This destructor will destroy the Food object and free up any memory that was allocated for it.
     */
    ~Food();

    /**
     *@brief Add a new food item to the food object
     *@details This function will add a new food item to the food object.
     *@param newFood A shared pointer to the new food item to be added.
     *@return True if the food item was added successfully, false otherwise.
     */
    bool addFood(std::shared_ptr<FoodItem> newFood);

    /**
     *@brief Purchase a food item from the food object
     *@details This function will purchase a food item from the food object.
     *@param id The id of the food item to be purchased.
     *@return True if the food item was purchased successfully, false otherwise.
     */
    bool purchaseFood(std::string& id);

    /**
     *@brief Restock a food item in the food object
     *@details This function will restock a food item in the food object.
     *@param id The id of the food item to be restocked.
     *@return True if the food item was restocked successfully, false otherwise.
     */
    bool sortFood();
    bool clearFood();
    bool removeFood(std::string& id);
    FoodItem* findFood(const std::string& id) const;
    unsigned getFoodCount() const;
    LinkedList readFromFile(const std::string& filename);
    bool writeToFile(const std::string& filename);
private:

};




#endif //FOOD_H
