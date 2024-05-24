Information for compiling and running the program.

The program is written in C++ and uses the C++ standard library. It should compile with any C++ compiler that supports C++11 or later. The program has been tested with the GNU Compiler Collection (g++) version 4.8.4 and the Clang compiler version 3.5.0.
To compile the program you need to run this compiling command at the root of the project:
g++ -Wall -Werror -std=c++14 -O -o ftt ./code/*.cpp

To run the program you need to run this command at the root of the project:
./ftt <foods_file> <coins_file> (e.g. ./ftt data/foods.dat data/coins.dat)

To run tests you can run these commands at the root of the project:
./ftt <foods_file> <coins_file> < <test.input> > test.actual_output
diff -w test.actual_output test.expected_output

Or alternatively you can run this command at the root of the project (Remember to give execution permissions to the script with chmod +x test.sh):
./test.sh

