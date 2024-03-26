
#include "../headers/ArrayList.hpp"


int main() {
    ArrayList moviesList;
    moviesList.loadFromFile("projekt2_dane.csv");
    moviesList.mergeSort();
    moviesList.saveToFile("output.csv");
    
}

