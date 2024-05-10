#include "Coin.h"
 
 // implement functions for managing coins; this may depend on your design.
 Coin::Coin(Denomination denom, unsigned count) {
     this->denom = denom;
     this->count = count;
 }

int Coin::getValue() const {
    if (denom == FIVE_CENTS) {
        return 5;
    } else if (denom == TEN_CENTS) {
        return 10;
    } else if (denom == TWENTY_CENTS) {
        return 20;
    } else if (denom == FIFTY_CENTS) {
        return 50;
    } else if (denom == ONE_DOLLAR) {
        return 100;
    } else if (denom == TWO_DOLLARS) {
        return 200;
    } else if (denom == FIVE_DOLLARS) {
        return 500;
    } else if (denom == TEN_DOLLARS) {
        return 1000;
    } else if (denom == TWENTY_DOLLARS) {
        return 2000;
    } else {
        return 0;
    }
}