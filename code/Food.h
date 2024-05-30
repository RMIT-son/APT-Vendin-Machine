//
// Created by Son on 5/11/2024.
//

#ifndef FOOD_H
#define FOOD_H
#include <fstream>
#include <unordered_set>
#include "LinkedList.h"
#include "Helper.h"

#define FOOD_DELIM '|'
#define ID_LENGTH 5
#define ID_PREFIX 'F'
#define ID_DIGITS 4
#define FOOD_FIELDS 4


class Food {
public:
    /**
     *@brief Default constructor for the Food class
     *@details This constructor will create a new Food object with no food items in it.
     */
    Food();

    /**
     *@brief Default destructor for the Food class
     *@details This destructor will destroy the Food object and
     * free up any memory that was allocated for it.
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
    bool removeFood(const std::string& id);

    /**
     *@brief Sort the food items in the food object
     *@details This function will sort the food items in the food object.
     */
    bool sortFood();

    /**
     *@brief Clear all the food items from the food object
     *@details This function will clear all the food items from the food object.
     */
    bool clearFood();

    /**
     *@brief Find a food item in the food object
     *@details This function will find a food item in the food object.
     *@param id The id of the food item to be found.
     *@return A pointer to the food item if it was found, nullptr otherwise.
     */
    [[nodiscard]] FoodItem* findFood(const std::string& id) const;

    /**
     *@brief Get the number of food items in the food object
     *@details This function will return the number of food items in the food object.
     *@return The number of food items in the food object.
     */
    [[nodiscard]] unsigned getFoodCount() const;

    /**
     *@brief Read food items from a file
     *@details This function will read food items from a file and add them to the food object.
     *@param filename The name of the file to read the food items from.
     */
    void readFromFile(const std::string& filename);

    /**
     *@brief Write food items to a file
     *@details This function will write the food items in the food object to a file.
     *@param filename The name of the file to write the food items to.
     *@return True if the food items were written successfully, false otherwise.
     */
    [[nodiscard]] bool writeToFile(const std::string& filename) const;

    /**
     * @brief Generate a unique ID for a food item
     * @details This function will generate the smallest unique ID for a food item.
     * @return String containing the unique ID
     */
    [[nodiscard]] std::string generateID() const;

    /**
     * @brief Get the head of the list
     * @return The head of the list
     */
    [[nodiscard]] Node* getHead() const;
private:
    // the beginning of the list
    LinkedList foodList;
    // how many nodes are there in the list
    unsigned count = 0;
};

#endif //FOOD_H
