
#include "../headers/ArrayList.hpp"
#include <chrono>
#include <ctime>

const int DATA_SETS_INTERVAL = 10000;

int main() {
    ArrayList movieList;
    movieList.loadFromFile("projekt2_dane.csv");
    movieList.deleteEmptyRatings();
    movieList.saveToFile("x.csv");

    // srand(time(nullptr));

    // std::ofstream outputMergeTimes("measured_times/measuredMergeTimes.txt");
    // std::ofstream outputBucketTimes("measured_times/measuredBucketTimes.txt");
    // std::ofstream outputQSTimes("measured_times/measuredQSTimes.txt");
    // std::ofstream outputMergeStats("measured_stats/measuredMergeStats.txt");
    // std::ofstream outputBucketStats("measured_stats/measuredBucketStats.txt");
    // std::ofstream outputQSStats("measured_stats/measuredQSStats.txt");
    // std::ofstream outputDeleteTimes("deleteTimes.txt");
    // ArrayList unsortedMoviesList1, unsortedMoviesList2;
    // unsortedMoviesList1.loadFromFile("projekt2_dane.csv");
    // unsortedMoviesList2.loadElements(unsortedMoviesList1);
    // unsortedMoviesList1.deleteEmptyRatings();
    // int amountOfDataSets = floor(unsortedMoviesList1.getSize()/DATA_SETS_INTERVAL);
    // for (int j = 0; j < 3; j++) {
    //     for (int i = 0; i < amountOfDataSets+1; i++) {
    //         double sortTime;
    //         ArrayList moviesList;
    //         if (i == amountOfDataSets) {
    //             moviesList.loadElements(unsortedMoviesList1);
    //         } else {
    //             moviesList.loadElements(unsortedMoviesList1, (i+1)*DATA_SETS_INTERVAL);
    //         }
    //         // Pomiar czasu sortowania
    //         auto start = std::chrono::high_resolution_clock::now();
    //         switch (j) {
    //             case 0: moviesList.mergeSort(); break;
    //             case 1: moviesList.bucketSort(); break;
    //             case 2: moviesList.quickSort(); break;
    //         }
    //         auto end = std::chrono::high_resolution_clock::now();
    //         std::chrono::duration<double> elapsed = end - start;
    //         sortTime = elapsed.count();

    //         switch (j) {
    //             case 0:
    //                 outputMergeTimes << moviesList.getSize() << ", " << sortTime << std::endl;
    //                 outputMergeStats << moviesList.getSize() << ", " << moviesList.ratingAverage() << ", " << moviesList.ratingMedian() << std::endl;
    //                 break;
    //             case 1: 
    //                 outputBucketTimes << moviesList.getSize() << ", " << sortTime << std::endl; 
    //                 outputBucketStats << moviesList.getSize() << ", " << moviesList.ratingAverage() << ", " << moviesList.ratingMedian() << std::endl;
    //                 break;
    //             case 2: 
    //                 outputQSTimes << moviesList.getSize() << ", " << sortTime << std::endl;
    //                 outputQSStats << moviesList.getSize() << ", " << moviesList.ratingAverage() << ", " << moviesList.ratingMedian() << std::endl;
    //                 break;
    //         }
    //     }
    // }
    // outputMergeTimes.close();
    // outputBucketTimes.close();
    // outputQSTimes.close();
    // outputMergeStats.close();
    // outputBucketStats.close();
    // amountOfDataSets = floor(unsortedMoviesList2.getSize()/DATA_SETS_INTERVAL);
    // for (int i = 0; i < amountOfDataSets+1; i++) {
    //     double deleteTime;
    //     ArrayList moviesList;
    //     if (i == amountOfDataSets) {
    //         moviesList.loadElements(unsortedMoviesList2);
    //     } else {
    //         moviesList.loadElements(unsortedMoviesList2, (i+1)*DATA_SETS_INTERVAL);
    //     }
    //     int size = moviesList.getSize();
    //     // Pomiar czasu filtrowania
    //     auto start = std::chrono::high_resolution_clock::now();
    //     moviesList.deleteEmptyRatings();
    //     auto end = std::chrono::high_resolution_clock::now();
    //     std::chrono::duration<double> elapsed = end - start;
    //     deleteTime = elapsed.count();
    //     outputDeleteTimes << size << ", " << deleteTime << std::endl;
    // }
    // outputQSStats.close();
    // outputDeleteTimes.close();
}   




