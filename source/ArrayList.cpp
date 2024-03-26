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
void ArrayList::addFirst(Movie movie) { // Dodanie elementu na poczatek tablicy
    if(size_ >= capacity_) { // Stworzenie nowej, dwa razy wiekszej tablicy oraz skopiowanie starej tablicy do nowej z przesunieciem elementow o 1 w prawo
        int newCapacity = capacity_ * 2;
        Movie* newArray = new Movie[newCapacity];
        for (int i = 0; i < size_; i++) {
            newArray[i+1] = array_[i];
        }
        delete[] array_;
        array_ = newArray;
        capacity_ = newCapacity;
    } else { // Przesuniecie elementów o 1 w prawo
        for (int i = size_; i > 0; i--) {
                array_[i] = array_[i-1];
            }
    }
    array_[0] = movie;
    size_++;
}
void ArrayList::addAt(int index, Movie movie) // Dodanie elementu na okreslonym indeksie
{
    if (index >= 0 && index <= size_) { // Stworzenie nowej, dwa razy wiekszej tablicy oraz skopiowanie starej tablicy do nowej z przesunieciem 
    // elementow za indeksem o 1, w prawo (po to, aby zrobic miejsce na element)                                                                                                        
        if(size_ >= capacity_) {
            int newCapacity = capacity_ * 2;
            Movie* newArray = new Movie[newCapacity];

            for (int i = 0; i < index; i++) { // tutaj nie ma potrzeby iteracji od konca, poniewaz i tak kopiujemy elementy do nowej tablicy
                newArray[i] = array_[i];
            }
            newArray[index] = movie;
            for (int i = index; i < size_; i++) {
                newArray[i+1] = array_[i];
            }

            delete[] array_;
            array_ = newArray;
            capacity_ = newCapacity;
        } else { // Przesuniecie elementow za indeksem o 1, w prawo
            for (int i = size_; i > index; i--) { // iteracja od konca
                array_[i] = array_[i-1];
            }
            array_[index] = movie;
        }
        size_++;
    } else {
        std::cout << "Niepoprawny index.";
    }

}

void ArrayList::removeLast() { // Usuniecie ostatniego elementu
    if (size_ > 0) {
        if(size_ - 1 <= capacity_ / 2 && capacity_ > initialCapacity_) {
            int newCapacity = capacity_ / 2;
            Movie* newArray = new Movie[newCapacity];
            for (int i = 0; i < size_ - 1; i++) {
                newArray[i] = array_[i];
            }
            delete[] array_;
            array_ = newArray;
            capacity_ = newCapacity;
        }
        size_--;
    }
}
void ArrayList::removeFirst() { // Usuniecie pierwszego elementu
    if (size_ > 0) {
        if(size_-1 <= capacity_ / 2 && capacity_ > initialCapacity_) { 
            int newCapacity = capacity_ / 2;
            Movie* newArray = new Movie[newCapacity];
            for (int i = 0; i < size_ - 1; i++) {
                newArray[i] = array_[i+1];
            }
            delete[] array_;
            array_ = newArray;
            capacity_ = newCapacity;
        } else { // Przesuniecie elementów o 1 w lewo
            for (int i = 0; i < size_ - 1; i++) {
                array_[i] = array_[i+1];
            }
        }
        size_--;
    }
}
void ArrayList::removeFrom(int index) {
    if (size_ > 0 && index >= 0 && index <= size_) {
        if (size_ - 1 <= capacity_ / 2 && capacity_ > initialCapacity_) {
            int newCapacity = capacity_ / 2;
            Movie* newArray = new Movie[newCapacity];
            for (int i = 0; i < index; i++) {
                newArray[i] = array_[i];
            }
            for (int i = index; i < size_ - 1; i++) {
                newArray[i] = array_[i+1];
            }
            delete[] array_;
            array_ = newArray;
            capacity_ = newCapacity;
        } else { // Przesuniecie elementów o 1 w lewo, zaczynajac dopiero od tego ktory chcemy usunac
            for (int i = index; i < size_ - 1; i++) {
                array_[i] = array_[i+1];
            }
        }
        size_--;
    } else {
        std::cout << "Niepoprawny index.";
    }
}

ArrayList::Movie ArrayList::findElement(std::string title) {
    Movie nullMovie;
    for (int i = 0; i < size_; i++) {
        if (array_[i].title == title) {
            return array_[i];
        }
    }
    return nullMovie;
}
void ArrayList::display() {
    for(int i = 0; i < size_; i++) {
        std::cout << i << ": " << array_[i].title << " " << array_[i].rating <<  std::endl;
    }
}
void ArrayList::loadFromFile(std::string inputFilePath, int size) {
    std::ifstream inputFile(inputFilePath);

    if (!inputFile.is_open()) {
        std::cerr << "Nie mozna otworzyc pliku!";
        return;
    }

    std::string line;
    std::getline(inputFile, line); // Pierwsza linijka - naglowek
    int loadedLines = 0;
    int deletedLines = 0;
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
        Movie err;
        err.title = "NULL";
        err.rating = 0;
        return err;
    }
    return array_[index];
}
int ArrayList::getSize() {
    return size_;
}
int ArrayList::getCapacity() {
    return capacity_;
}

// ALGORYTMY SORTUJACE

void ArrayList::mergeSort() {
    mergeSortHelper(0, size_ - 1);
}
void ArrayList::mergeSortHelper(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(left, mid);
        mergeSortHelper(mid + 1, right);
        merge(left, mid, right);
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
    // Bucket sort implementation
}

