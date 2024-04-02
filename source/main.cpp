
#include "../headers/ArrayList.hpp"
#include <chrono>
#include <ctime>

int main() {
    srand(time(nullptr));
    ArrayList moviesList;
    ArrayList moviesList2;
    ArrayList moviesList3;
    moviesList.loadFromFile("projekt2_dane.csv");
    moviesList2 = moviesList;
    moviesList3 = moviesList;
    auto start = std::chrono::high_resolution_clock::now();
    moviesList.quickSort();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    double qsTime = elapsed.count();

    start = std::chrono::high_resolution_clock::now();
    moviesList2.mergeSort();
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    double mergeTime = elapsed.count();

    start = std::chrono::high_resolution_clock::now();
    moviesList3.bucketSort();
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    double bucketTime = elapsed.count();
    moviesList.saveToFile("outputQS.csv");
    std::cout << "Merge time: " << mergeTime << " QS time: " << qsTime << " Bucket time: " << bucketTime;
}

