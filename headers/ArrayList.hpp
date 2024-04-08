#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>

#pragma once

class ArrayList {
private:
    struct Movie {
        std::string title;
        double rating;
    };
    Movie* array_;
    void mergeSortHelper(int left, int right);
    void merge(int left, int mid, int right);
    void quickSortHelper(int left, int right);
    int partition(int left, int right);
    int initialCapacity_;
    int capacity_;
    int size_; 
public:
    ArrayList(int capacity = 10);
    ~ArrayList();

    // FUNKCJE DO ZARZĄDZANIA TABLICĄ
    void addLast(Movie movie);
    void addFirst(Movie movie);
    void addAt(int index, Movie movie);
    void removeLast();
    void removeFirst();
    void removeFrom(int index);
    void swap(int index1, int index2);
    Movie findElement(std::string title);
    Movie getElement(int index);
    float ratingAverage();
    float ratingMedian();
    int getSize();
    int getCapacity();
    int getRating(int index);
    int getMax();
    int getMin();
    void display();
    void saveToFile(std::string outputFilePath);
    void loadFromFile(std::string inputFilePath, int size = -1); 
    void loadElements(ArrayList& array, int size = -1);
    void deleteEmptyRatings();

    // ALGORYTMY SORTUJACE
    void mergeSort();
    void bucketSort();
    void quickSort();

};