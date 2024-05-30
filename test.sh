#!/bin/bash

# Add Food test
# Test the add food functionality
./ftt ./tests/addFoodTest/addFood.actual_foods ./data/coins.dat < ./tests/addFoodTest/addFood.input > ./tests/addFoodTest/addFood.actual_output
diff -w ./tests/addFoodTest/addFood.expected_output ./tests/addFoodTest/addFood.actual_output
diff -w ./tests/addFoodTest/addFood.actual_foods ./tests/addFoodTest/after/foods.dat
if [ $? -eq 0 ]
then
    echo "Add Food Test: Passed"
else
    echo "Add Food Test: Failed"
fi
# Overwrite actual_foods to reset
cp ./tests/addFoodTest/before/addFood.actual_foods ./tests/addFoodTest/addFood.actual_foods

# Display Menu test
# Test the display menu functionality
./ftt ./data/foods.dat ./data/coins.dat < ./tests/displayMenuTest/displayMenu.input > ./tests/displayMenuTest/displayMenu.actual_output
diff -w ./tests/displayMenuTest/displayMenu.expected_output ./tests/displayMenuTest/displayMenu.actual_output
if [ $? -eq 0 ]
then
    echo "Display Menu Test: Passed"
else
    echo "Display Menu Test: Failed"
fi

# Incorrect Cash test
# Test the incorrect cash functionality
./ftt ./data/foods.dat ./data/coins.dat < ./tests/incorrectCashTest/incorrectCash.input > ./tests/incorrectCashTest/incorrectCash.actual_output
diff -w ./tests/incorrectCashTest/incorrectCash.expected_output ./tests/incorrectCashTest/incorrectCash.actual_output
if [ $? -eq 0 ]
then
    echo "Incorrect Cash Test: Passed"
else
    echo "Incorrect Cash Test: Failed"
fi

# Incorrect Desc test
# Test the incorrect description functionality
./ftt ./data/foods.dat ./data/coins.dat < ./tests/incorrectDescTest/incorrectDesc.input > ./tests/incorrectDescTest/incorrectDesc.actual_output
diff -w ./tests/incorrectDescTest/incorrectDesc.expected_output ./tests/incorrectDescTest/incorrectDesc.actual_output
if [ $? -eq 0 ]
then
    echo "Incorrect Desc Test: Passed"
else
    echo "Incorrect Desc Test: Failed"
fi

# Incorrect Price test
# Test the incorrect price functionality
./ftt ./data/foods.dat ./data/coins.dat < ./tests/incorrectPriceTest/incorrectPrice.input > ./tests/incorrectPriceTest/incorrectPrice.actual_output
diff -w ./tests/incorrectPriceTest/incorrectPrice.expected_output ./tests/incorrectPriceTest/incorrectPrice.actual_output
if [ $? -eq 0 ]
then
    echo "Incorrect Price Test: Passed"
else
    echo "Incorrect Price Test: Failed"
fi

# Purchase Food test
# Test the purchase food functionality
./ftt ./data/foods.dat ./data/coins.dat < ./tests/purchaseFoodTest/purchaseFood.input > ./tests/purchaseFoodTest/purchaseFood.actual_output
diff -w ./tests/purchaseFoodTest/purchaseFood.expected_output ./tests/purchaseFoodTest/purchaseFood.actual_output
if [ $? -eq 0 ]
then
    echo "Purchase Food Test: Passed"
else
    echo "Purchase Food Test: Failed"
fi

# Save&Exit test
# Test the save and exit functionality
./ftt ./tests/saveExitTest/saveExit.actual_foods ./tests/saveExitTest/saveExit.actual_coins < ./tests/saveExitTest/saveExit.input > ./tests/saveExitTest/saveExit.actual_output
diff -w ./tests/saveExitTest/saveExit.expected_output ./tests/saveExitTest/saveExit.actual_output
diff -w ./tests/saveExitTest/saveExit.actual_foods ./tests/saveExitTest/after/foods.dat
diff -w ./tests/saveExitTest/saveExit.actual_coins ./tests/saveExitTest/after/coins.dat
if [ $? -eq 0 ]
then
    echo "Save&Exit Test: Passed"
else
    echo "Save&Exit Test: Failed"
fi
# Overwrite actual_foods and actual_coins to reset
cp ./tests/saveExitTest/before/saveExit.actual_foods ./tests/saveExitTest/saveExit.actual_foods
cp ./tests/saveExitTest/before/saveExit.actual_coins ./tests/saveExitTest/saveExit.actual_coins

# Update Balance test
# Test the update balance functionality
./ftt ./data/foods.dat ./data/coins.dat < ./tests/updateBalanceTest/updateBalance.input > ./tests/updateBalanceTest/updateBalance.actual_output
diff -w ./tests/updateBalanceTest/updateBalance.expected_output ./tests/updateBalanceTest/updateBalance.actual_output
if [ $? -eq 0 ]
then
    echo "Update Balance Test: Passed"
else
    echo "Update Balance Test: Failed"
fi

# viewBalance test
# Test the view balance functionality
./ftt ./data/foods.dat ./data/coins.dat < ./tests/viewBalanceTest/viewBalance.input > ./tests/viewBalanceTest/viewBalance.actual_output
diff -w ./tests/viewBalanceTest/viewBalance.expected_output ./tests/viewBalanceTest/viewBalance.actual_output
if [ $? -eq 0 ]
then
    echo "View Balance Test: Passed"
else
    echo "View Balance Test: Failed"
fi


# End-to-End test
# Test all functionalities together
./ftt ./tests/end2EndTest/end2End.actual_foods ./tests/end2EndTest/end2End.actual_coins < ./tests/end2EndTest/end2End.input > ./tests/end2EndTest/end2End.actual_output
diff -w ./tests/end2EndTest/end2End.expected_output ./tests/end2EndTest/end2End.actual_output
diff -w ./tests/end2EndTest/end2End.actual_foods ./tests/end2EndTest/after/foods.dat
diff -w ./tests/end2EndTest/end2End.actual_coins ./tests/end2EndTest/after/coins.dat
if [ $? -eq 0 ]
then
    echo "End-to-End Test: Passed"
else
    echo "End-to-End Test: Failed"
fi
# Overwrite actual_foods and actual_coins to reset
cp ./tests/end2EndTest/before/end2End.actual_foods ./tests/end2EndTest/end2End.actual_foods
cp ./tests/end2EndTest/before/end2End.actual_coins ./tests/end2EndTest/end2End.actual_coins
