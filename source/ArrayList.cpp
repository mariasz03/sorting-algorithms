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
        std::cerr << "Nie mozna otworzyc pliku!";
        return;
    }

    std::string line;
    std::getline(inputFile, line); // Pierwsza linijka - naglowek
    int loadedLines = 0; // Licznik załadownych linijek
    int deletedLines = 0; // Licznik usuniętych linijek
    int i = 0;
    
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
            std::cout << movie.title << ": rating is empty. Line deleted." << std::endl;
            deletedLines++;
        } else {
            movie.rating = std::stod(ratingString);
            addLast(movie);
            loadedLines++;
        }
        i++;
    }
    std::cout << std::endl << "Loading completed."  << std::endl << "Lines deleted: " << deletedLines << std::endl << "Lines loaded: " << loadedLines << std::endl << "Total: " << 
    deletedLines + loadedLines << std::endl;
    inputFile.close();
}
void ArrayList::saveToFile(std::string outputFilePath) {
    std::ofstream outputFile(outputFilePath);
    if (!outputFile.is_open()) {
        std::cerr << "Nie mozna otworzyc pliku!";
        return;
    }
    for(int i = 0; i < size_; i++) {
        outputFile << i << ": " << array_[i].title << " " << array_[i].rating <<  std::endl;
    }
}
ArrayList::Movie ArrayList::getElement(int index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index out of range.");
    }
    return array_[index];
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
        if (leftArray[i].rating <= rightArray[j].rating) {
            array_[k] = leftArray[i];
            i++;
        } else {
            array_[k] = rightArray[j];
            j++;
        }
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
        int pivotIndex = partition(left, right);
        quickSortHelper(left, pivotIndex - 1);
        quickSortHelper(pivotIndex + 1, right);
    }
}

int ArrayList::partition(int left, int right) {
    int pivotIndex = left + (right - left) / 2;
    Movie pivotValue = array_[pivotIndex];
    int i = left - 1;
    int j = right + 1;

    while (true) {
        do {
            i++;
        } while (array_[i].rating < pivotValue.rating);

        do {
            j--;
        } while (array_[j].rating > pivotValue.rating);

        if (i >= j) {
            return j;
        }

        swap(i, j);
    }
}
