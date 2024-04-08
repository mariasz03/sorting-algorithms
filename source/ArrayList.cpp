#include "../headers/ArrayList.hpp"

ArrayList::ArrayList(int initialCapacity) : initialCapacity_(initialCapacity), capacity_(initialCapacity), size_(0) {
    array_ = new Movie[capacity_];
}
ArrayList::~ArrayList() {
    delete[] array_;
}

void ArrayList::addLast(Movie movie) { // Dodanie elementu na koniec tablicy
    if(size_ >= capacity_) { // Stworzenie nowej, dwa razy wiekszej tablicy oraz skopiowanie starej tablicy do nowej
        int newCapacity = capacity_ * 2;
        Movie* newArray = new Movie[newCapacity];
        for (int i = 0; i < size_; i++) {
            newArray[i] = array_[i];
        }
        delete[] array_;
        array_ = newArray;
        capacity_ = newCapacity;
    }
    array_[size_] = movie;
    size_++;
}

void ArrayList::swap(int index1, int index2) {
    Movie temp;
    temp = array_[index1];
    array_[index1] = array_[index2];
    array_[index2] = temp;
}
ArrayList::Movie ArrayList::findElement(std::string title) {
    for (int i = 0; i < size_; i++) {
        if (array_[i].title == title) {
            return array_[i];
        }
    }
    throw std::runtime_error("Movie with given title not found!");
}

void ArrayList::loadFromFile(std::string inputFilePath, int size) {
    std::ifstream inputFile(inputFilePath);

    if (!inputFile.is_open()) {
        std::cerr << "Error occured while opening file.";
        return;
    }

    std::string line;
    std::getline(inputFile, line); // Pierwsza linijka - naglowek
    int i = 0;
    int properLines = 0; // Licznik załadownych linijek
    int emptyRatingLines = 0; // Licznik usuniętych linijek
    while (std::getline(inputFile, line) && (size < 0 || i < size)) {
        Movie movie;
        std::istringstream iss(line);

        std::string ratingString;
        std::string tempLine;
        
        std::getline(iss, tempLine, ',');
        
        if (line.find('"') != std::string::npos) { // Obsługa przypadku, gdy w linijce jest cudzysłów - czyli występują przecinki w tytule
            std::getline(iss, tempLine);
            tempLine = tempLine.substr(1, tempLine.size());
            for (char c : tempLine) {
                if (c == '"') {
                    break;
                }
                movie.title.append(1, c);
            }
            if ((tempLine.substr(tempLine.size() - 3, tempLine.size())).find('"') != std::string::npos) { // 3 ostatnie cyfry to rating (jezeli nie zawieraja cudzyslowu)
                ratingString = "";
            } else {
                ratingString = tempLine.substr(tempLine.size() - 3, tempLine.size());
            } 
        } else { // W innym wypadku używaj separatora ','
            std::getline(iss, movie.title, ',');
            std::getline(iss, ratingString, ',');
        }
        if (ratingString.empty()) {
            movie.rating = -1;
            emptyRatingLines++;
        } else {
            movie.rating = std::stod(ratingString);
            properLines++;
        }
        addLast(movie);
        i++;
    }
    std::cout << std::endl << "Loading from file completed."  << std::endl << "Lines with empty rating: " << emptyRatingLines << std::endl << "Proper lines: " << properLines << std::endl
    << "Total: " << emptyRatingLines + properLines;
    inputFile.close();
}
void ArrayList::saveToFile(std::string outputFilePath) {
    std::ofstream outputFile(outputFilePath);
    if (!outputFile.is_open()) {
        std::cerr << "Can't open a file!";
        return;
    }
    for(int i = 0; i < size_; i++) {
        outputFile << i << ": " << array_[i].title << " " << array_[i].rating <<  std::endl;
    }
}

void ArrayList::loadElements(ArrayList& array, int size) { // Funkcja ładująca size elementow z array
    if (size == -1) {
        size = array.getSize();
    } 
    for(int i = 0; i < size; i++) {
        addLast(array.getElement(i));
    }
}

void ArrayList::deleteEmptyRatings() {
    int nonEmptyCount = 0;
    for (int i = 0; i < size_; i++) {
        if (array_[i].rating != -1) {
            nonEmptyCount++;
        }
    }
    Movie* newArray = new Movie[nonEmptyCount];
    int newIndex = 0;
    for (int i = 0; i < size_; i++) {
        if (array_[i].rating != -1) {
            newArray[newIndex] = array_[i];
            newIndex++;
        }
    }
    delete[] array_;
    int deletedCount = size_ - nonEmptyCount;
    array_ = newArray;
    size_ = nonEmptyCount;
    capacity_ = nonEmptyCount;
    std::cout << std::endl << "Filtering data completed. Deleted " << deletedCount << " movies with no rating.";
}

ArrayList::Movie ArrayList::getElement(int index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index out of range.");
    }
    return array_[index];
}

float ArrayList::ratingAverage() {
    float sum = 0;
    for (int i = 0; i < size_; i++) {
        sum += array_[i].rating;
    }
    return (sum/size_);
}

float ArrayList::ratingMedian() {
    if (size_ % 2) {
        int midIndex = ceil(size_/2);
        return array_[midIndex].rating;
    } else {
        int midIndex = size_/2;
        double a = array_[midIndex].rating;
        double b = array_[midIndex-1].rating;
        return (a+b)/2;
    }
}

int ArrayList::getSize() {
    return size_;
}
int ArrayList::getCapacity() {
    return capacity_;
}
int ArrayList::getRating(int index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index out of range.");
    }
    return array_[index].rating;
}
int ArrayList::getMax() { // Zwraca najwieksza wartosc z pola rating
    int max = 0;
    for(int i = 0; i < size_; i++) {
        if (array_[i].rating > max) {
            max = int(array_[i].rating);
        }
    }
    return max;
}
int ArrayList::getMin() { // Zwraca najmniejsza wartosc z pola rating
    int min = 10;
    for(int i = 0; i < size_; i++) {
        if (array_[i].rating < min) {
            min = int(array_[i].rating);
        }
    }
    return min;
}

// ALGORYTMY SORTUJACE
void ArrayList::mergeSort() {
    mergeSortHelper(0, size_ - 1); // Wywołanie dla całej listy
}

void ArrayList::mergeSortHelper(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(left, mid); // Wywołanie rekurencyjne dla lewej strony listy
        mergeSortHelper(mid + 1, right); // Wywołanie rekurencyjne dla prawej strony listy
        merge(left, mid, right); // Sortowanie i scalenie
    }
}

void ArrayList::merge(int left, int mid, int right) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    Movie* leftArray = new Movie[leftSize];
    Movie* rightArray = new Movie[rightSize];

    for (int i = 0; i < leftSize; i++) {
        leftArray[i] = array_[left + i];
    }
    for (int j = 0; j < rightSize; j++) {
        rightArray[j] = array_[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < leftSize && j < rightSize) {
        if (leftArray[i].rating < rightArray[j].rating) {
            array_[k] = leftArray[i];
            i++;
        } else {
            array_[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < leftSize) {
        array_[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < rightSize) {
        array_[k] = rightArray[j];
        j++;
        k++;
    }

    delete[] leftArray;
    delete[] rightArray;
}

void ArrayList::bucketSort() {
    // int min = getMin();
    // int max = getMax();
    // int bucketsNumber = getMax() - getMin() + 1;
    int bucketsNumber = 11;

    ArrayList* bucket[bucketsNumber];
    for (int i = 0; i < bucketsNumber; i++) {
        bucket[i] = new ArrayList;
    }

    for (int i = 0; i < size_; i++) {
        bucket[int(array_[i].rating)]->addLast(array_[i]);
    }

    // for (int i = 0; i < bucketsNumber; i++) {
    //     if (bucket[i]->size_ > 0) { // Sprawdzenie, czy bucket nie jest pusty
    //         bucket[i]->mergeSort();
    //     }
    // } // Sortowanie kubelkow w tym przypadku jest zbedne, poniewaz i tak kazdy kubelek ma rankingi o tej samej wartosci

    int k = 0;
    for (int i = 0; i < bucketsNumber; i++) {
        for (int j = 0; j < bucket[i]->size_; j++) {
            array_[k] = bucket[i]->array_[j];
            k++;
        }
        delete bucket[i];
    }
}


void ArrayList::quickSort() {
    quickSortHelper(0, size_ - 1);
}

void ArrayList::quickSortHelper(int left, int right) {
    if (left < right) {
        int pivotIndex = 
        rand() % (right - left + 1) + left;
        Movie pivot = array_[pivotIndex];
        
        int i = left, j = right;
        while (j >= i) {
            while(array_[i].rating < pivot.rating) i++;
            while (array_[j].rating > pivot.rating) j--;
            if (i <= j) {
                swap(i, j);
                i++;
                j--;
            }
        }
        
        quickSortHelper(i, right);
        quickSortHelper(left, j);
    }
}


