#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#pragma once

class ArrayList {
private:
    int initialCapacity_;
    int capacity_;
    int size_; 
public:
    struct Movie {
        std::string title;
        double rating;
    };
    
    ArrayList(int capacity = 10);
    ~ArrayList();

    // FUNKCJE DO ZARZĄDZANIA TABLICĄ
    void addLast(Movie movie);
    void addFirst(Movie movie);
    void addAt(int index, Movie movie);
    void removeLast();
    void removeFirst();
    void removeFrom(int index);
    Movie findElement(std::string title);
    void display();
    void saveToFile(std::string outputFilePath);
    void loadFromFile(std::string inputFilePath, int size = -1);
    Movie getElement(int index);
    int getSize();
    int getCapacity();

    // ALGORYTMY SORTUJACE
    void mergeSortHelper(int left, int right);
    void merge(int left, int mid, int right);
    void mergeSort();
    void quickSort();
    void bucketSort();


protected:
    Movie* array_;
    void merge(Movie* leftArray, Movie* rightArray);
};