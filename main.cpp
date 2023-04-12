#include <iostream>
#include <vector>
#include <chrono>

struct Stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

class Sorter {
public:
    virtual Stats sort(std::vector<int>& vec) = 0;
    Stats stats;
};

// сортировка вставками
class InsertionSorter : public Sorter {
public:
    InsertionSorter() = default;
    Stats sort(std::vector<int>& vec) override {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 1; i < vec.size(); ++i) {
            for (int j = i; j > 0 && vec[j - 1] > vec[j]; --j) {
                std::swap(vec[j - 1], vec[j]);
                ++stats.copy_count;
            }
            ++stats.comparison_count;
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::micro> elapsed_seconds = end - start;
        std::cout << "Время сортировки вставками: " << elapsed_seconds.count() << "us" << std::endl;
        return stats;
    }
};
// шейкерная сортировка
class ShakerSorter : public Sorter {
public:
    ShakerSorter() = default;
    Stats sort(std::vector<int>& vec) override {
        auto start = std::chrono::high_resolution_clock::now();
        int left = 0; // левая граница
        int right = vec.size() - 1; // правая граница
        while (left <= right) { // пока левая граница не пересекла правую
            for (int i = left; i < right; ++i) { 
                if (vec[i] > vec[i + 1]) { 
                    std::swap(vec[i], vec[i + 1]);
                    ++stats.copy_count;
                }
                ++stats.comparison_count;
            }
            --right; // сдвигаем правую границу
            for (int i = right; i > left; --i) {
                if (vec[i - 1] > vec[i]) {
                    std::swap(vec[i - 1], vec[i]);
                    ++stats.copy_count;
                }
                ++stats.comparison_count;
            }
            ++left; // сдвигаем левую границу
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::micro> elapsed_seconds = end - start;
        std::cout << "Время шейкерной сортировки: " << elapsed_seconds.count() << "us" << std::endl;
        return stats;
    }
};
// сортировка пузырьком
class BubbleSorter : public Sorter {
public:
    BubbleSorter() = default;
    Stats sort(std::vector<int>& vec) override {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < vec.size(); ++i) {
            for (int j = 0; j < vec.size() - i - 1; ++j) {
                if (vec[j] > vec[j + 1]) {
                    std::swap(vec[j], vec[j + 1]);
                    ++stats.copy_count;
                }
                ++stats.comparison_count;
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::micro> elapsed_seconds = end - start;
        std::cout << "Время сортировки пузырьком: " << elapsed_seconds.count() << "us" << std::endl;
        return stats;
    }
};

// генератор случайных чисел
int lcg() {
    static int x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}

// заполнение вектора
void fill_vector(std::vector<int>& vector) {
    for (size_t i = 0; i < vector.size(); ++i) 
        vector[i] = lcg();
}

// вывод вектора
void output_vector(std::vector<int>& vector) {
    for (const auto& item : vector)
        std::cout << item << " ";
    std::cout << std::endl;
}
// тестирование
void testing_code_1(){
    std::vector<int> vector(0);
    //int size = 1000;
    int size2= 0;
    unsigned long long count_comp = 0;
    unsigned long long count_copy = 0;

    std::vector<unsigned long long> comp;
    std::vector<unsigned long long> copy;
    
    InsertionSorter insertion_sorter;
    ShakerSorter shaker_sorter;
    BubbleSorter bubble_sorter;

    while (true){
        std::cout << "[1] - Сортировка вставками\n"
                  << "[2] - Шейкерная сортировка\n"
                  << "[3] - Сортировка пузырьком\n"
                  << "[4] - Назад в главное меню\n--> ";
        int command = 0;
        std::cin >> command;
        switch (command){
            case 1:
                for (int size = 1000; size <= 100000; size += 1000){
                    vector.resize(size);
                    for (size_t j = 0; j < 100; ++j) {
                        for (size_t i = 0; i < vector.size(); ++i) {
                            vector[i] = lcg();
                        }
                        insertion_sorter.sort(vector);
                        count_comp += insertion_sorter.stats.comparison_count;
                        count_copy += insertion_sorter.stats.copy_count;
                    }
                    comp.push_back(count_comp / 100);
                    copy.push_back(count_copy / 100);
                    count_comp = 0;
                    count_copy = 0;
                    std::cout << "Пройден успешно " << size << std::endl;
                    vector.clear();
                }
                std::cout << "Среднее количество сравнений" << std::endl;
                for (const auto& item : comp)
                    std::cout << item << " ";
                std::cout << std::endl;
                std::cout << "Среднее количество копирований" << std::endl;
                for (const auto& item : copy)
                    std::cout << item << " ";
                std::cout << std::endl;
                comp.clear();
                copy.clear();
                break;
            case 2:
                for (int size = 1000; size <= 100000; size += 1000){
                    vector.resize(size);
                    for (size_t j = 0; j < 100; ++j) {
                        for (size_t i = 0; i < vector.size(); ++i) {
                            vector[i] = lcg();
                        }
                        shaker_sorter.sort(vector);
                        count_comp += shaker_sorter.stats.comparison_count;
                        count_copy += shaker_sorter.stats.copy_count;
                    }
                    comp.push_back(count_comp / 100);
                    copy.push_back(count_copy / 100);
                    count_comp = 0;
                    count_copy = 0;
                    std::cout << "Пройден успешно " << size << std::endl;
                    vector.clear();
                }
                std::cout << "Среднее количество сравнений" << std::endl;
                for (const auto& item : comp)
                    std::cout << item << " ";
                std::cout << std::endl;
                std::cout << "Среднее количество копирований" << std::endl;
                for (const auto& item : copy)
                    std::cout << item << " ";
                std::cout << std::endl;
                comp.clear();
                copy.clear();
                break;
            case 3:
                for (int size = 1000; size <= 100000; size += 1000){
                    vector.resize(size);
                    for (size_t j = 0; j < 100; ++j) {
                        for (size_t i = 0; i < vector.size(); ++i) {
                            vector[i] = lcg();
                        }
                        bubble_sorter.sort(vector);
                        count_comp += bubble_sorter.stats.comparison_count;
                        count_copy += bubble_sorter.stats.copy_count;
                    }
                    comp.push_back(count_comp / 100);
                    copy.push_back(count_copy / 100);
                    count_comp = 0;
                    count_copy = 0;
                    std::cout << "Пройден успешно " << size << std::endl;
                    vector.clear();
                }
                std::cout << "Среднее количество сравнений" << std::endl;
                for (const auto& item : comp)
                    std::cout << item << " ";
                std::cout << std::endl;
                std::cout << "Среднее количество копирований" << std::endl;
                for (const auto& item : copy)
                    std::cout << item << " ";
                std::cout << std::endl;
                comp.clear();
                copy.clear();
                break;
            case 4:
                return;
            default:
                std::cout << "Неверная команда" << std::endl;
                break;
        }
    }
}


void testing_code_2(){
    std::vector<int> vector(0);
    int size2= 0;
    unsigned long long count_comp = 0;
    unsigned long long count_copy = 0;

    std::vector<unsigned long long> comp;
    std::vector<unsigned long long> copy;
    
    InsertionSorter insertion_sorter;
    ShakerSorter shaker_sorter;
    BubbleSorter bubble_sorter;

    while (true){
        std::cout << "[1] - Сортировка вставками\n"
                  << "[2] - Шейкерная сортировка\n"
                  << "[3] - Сортировка пузырьком\n"
                  << "[4] - Назад в главное меню\n--> ";
        int command = 0;
        std::cin >> command;
        switch (command){
            case 1:
                for (int size = 1000; size <= 100000; size += 1000){
                    vector.resize(size);
                    for (size_t i = 0; i < vector.size(); ++i) {
                        vector[i] = (int)i;
                    }
                    insertion_sorter.sort(vector);
                    count_comp += insertion_sorter.stats.comparison_count;
                    count_copy += insertion_sorter.stats.copy_count;
                    comp.push_back(count_comp / 100);
                    copy.push_back(count_copy / 100);
                    count_comp = 0;
                    count_copy = 0;
                    std::cout << "Пройден успешно " << size << std::endl;
                    vector.clear();
                }
                std::cout << "Среднее количество сравнений" << std::endl;
                for (const auto& item : comp)
                    std::cout << item << " ";
                std::cout << std::endl;
                std::cout << "Среднее количество копирований" << std::endl;
                for (const auto& item : copy)
                    std::cout << item << " ";
                std::cout << std::endl;
                comp.clear();
                copy.clear();
                break;
            case 2:
                for (int size = 1000; size <= 100000; size += 1000){
                    vector.resize(size);
                    for (size_t i = 0; i < vector.size(); ++i) {
                        vector[i] = (int)i;
                    }
                    shaker_sorter.sort(vector);
                    count_comp += shaker_sorter.stats.comparison_count;
                    count_copy += shaker_sorter.stats.copy_count;
                    comp.push_back(count_comp / 100);
                    copy.push_back(count_copy / 100);
                    count_comp = 0;
                    count_copy = 0;
                    std::cout << "Пройден успешно " << size << std::endl;
                    vector.clear();
                }
                std::cout << "Среднее количество сравнений" << std::endl;
                for (const auto& item : comp)
                    std::cout << item << " ";
                std::cout << std::endl;
                std::cout << "Среднее количество копирований" << std::endl;
                for (const auto& item : copy)
                    std::cout << item << " ";
                std::cout << std::endl;
                comp.clear();
                copy.clear();
                break;
            case 3:
                for (int size = 1000; size <= 100000; size += 1000){
                    vector.resize(size);
                    for (size_t i = 0; i < vector.size(); ++i) {
                        vector[i] = (int)i;
                    }
                    bubble_sorter.sort(vector);
                    count_comp += bubble_sorter.stats.comparison_count;
                    count_copy += bubble_sorter.stats.copy_count;
                    comp.push_back(count_comp / 100);
                    copy.push_back(count_copy / 100);
                    count_comp = 0;
                    count_copy = 0;
                    std::cout << "Пройден успешно " << size << std::endl;
                    vector.clear();
                }
                std::cout << "Среднее количество сравнений" << std::endl;
                for (const auto& item : comp)
                    std::cout << item << " ";
                std::cout << std::endl;
                std::cout << "Среднее количество копирований" << std::endl;
                for (const auto& item : copy)
                    std::cout << item << " ";
                std::cout << std::endl;
                comp.clear();
                copy.clear();
                break;
            case 4:
                return;
            default:
                std::cout << "Неверная команда" << std::endl;
                break;
        }
    }
}
void testing_code_3(){
    std::vector<int> vector(0);
    int size2= 0;
    unsigned long long count_comp = 0;
    unsigned long long count_copy = 0;

    std::vector<unsigned long long> comp;
    std::vector<unsigned long long> copy;
    
    InsertionSorter insertion_sorter;
    ShakerSorter shaker_sorter;
    BubbleSorter bubble_sorter;
    int command = 0;
    while (true){
        std::cout << "[1] - Сортировка вставками\n"
                  << "[2] - Шейкерная сортировка\n"
                  << "[3] - Сортировка пузырьком\n"
                  << "[4] - Назад в главное меню\n--> ";
        std::cin >> command;
        switch (command){
            case 1:
                for (int size = 1000; size <= 100000; size += 1000){
                    vector.resize(size);
                    std::fill_n(vector.begin(), size, 0);
                    for (size_t i = vector.size() - 1; i != 0; --i) {
                        vector[i] = (int)i;
                    }
                    insertion_sorter.sort(vector);
                    count_comp += insertion_sorter.stats.comparison_count;
                    count_copy += insertion_sorter.stats.copy_count;
                    comp.push_back(count_comp / 100);
                    copy.push_back(count_copy / 100);
                    count_comp = 0;
                    count_copy = 0;
                    std::cout << "Пройден успешно " << size << std::endl;
                    vector.clear();
                }
                std::cout << "Среднее количество сравнений" << std::endl;
                for (const auto& item : comp)
                    std::cout << item << " ";
                std::cout << std::endl;
                std::cout << "Среднее количество копирований" << std::endl;
                for (const auto& item : copy)
                    std::cout << item << " ";
                std::cout << std::endl;
                comp.clear();
                copy.clear();
                break;
            case 2:
                for (int size = 1000; size <= 100000; size += 1000){
                    vector.resize(size);
                    for (size_t i = vector.size() - 1; i != 0; --i) {
                        vector[i] = (int)i;
                    }
                    shaker_sorter.sort(vector);
                    count_comp += shaker_sorter.stats.comparison_count;
                    count_copy += shaker_sorter.stats.copy_count;
                    comp.push_back(count_comp / 100);
                    copy.push_back(count_copy / 100);
                    count_comp = 0;
                    count_copy = 0;
                    std::cout << "Пройден успешно " << size << std::endl;
                    vector.clear();
                }
                std::cout << "Среднее количество сравнений" << std::endl;
                for (const auto& item : comp)
                    std::cout << item << " ";
                std::cout << std::endl;
                std::cout << "Среднее количество копирований" << std::endl;
                for (const auto& item : copy)
                    std::cout << item << " ";
                std::cout << std::endl;
                comp.clear();
                copy.clear();
                break;
            case 3:
                for (int size = 1000; size <= 100000; size += 1000){
                    vector.resize(size);
                    for (size_t i = vector.size() - 1; i != 0; --i) {
                        vector[i] = (int)i;
                    }
                    bubble_sorter.sort(vector);
                    count_comp += bubble_sorter.stats.comparison_count;
                    count_copy += bubble_sorter.stats.copy_count;
                    comp.push_back(count_comp / 100);
                    copy.push_back(count_copy / 100);
                    count_comp = 0;
                    count_copy = 0;
                    std::cout << "Пройден успешно " << size << std::endl;
                    vector.clear();
                }
                std::cout << "Среднее количество сравнений" << std::endl;
                for (const auto& item : comp)
                    std::cout << item << " ";
                std::cout << std::endl;
                std::cout << "Среднее количество копирований" << std::endl;
                for (const auto& item : copy)
                    std::cout << item << " ";
                std::cout << std::endl;
                comp.clear();
                copy.clear();
                break;
            case 4:
                return;
            default:
                std::cout << "Неверная команда" << std::endl;
                break;
        }
    }
}


int main() {
    // 14(10) -> 112(3) вариант задания
    std::vector<int> vector(0);
    int size = 0, command2 = 0;
    InsertionSorter insertion_sorter;
    ShakerSorter shaker_sorter;
    BubbleSorter bubble_sorter;
    
    // главное меню программы
    while (true){
        std::cout << "[1] - Создать случайный вектор\n"
                  << "[2] - Вывести вектор\n"
                  << "[3] - Сортировка вставками\n"
                  << "[4] - Шейкерная сортировка\n"
                  << "[5] - Сортировка пузырьком\n"
                  << "[6] - Тестирование\n"
                  << "[7] - Выход\n--> ";
        int command = 0;
        std::cin >> command;
        switch (command){
            case 1:
                std::cout << "размер: ";
                std::cin >> size;
                vector.resize(size);
                fill_vector(vector);
                break;
            case 2:
                output_vector(vector);
                break;
            case 3:
                insertion_sorter.sort(vector);
                std::cout << "Количество сравнений: " << insertion_sorter.stats.comparison_count << std::endl;
                std::cout << "Количество копирований: " << insertion_sorter.stats.copy_count << std::endl;
                break;
            case 4:
                shaker_sorter.sort(vector);
                std::cout << "Количество сравнений: " << shaker_sorter.stats.comparison_count << std::endl;
                std::cout << "Количество копирований: " << shaker_sorter.stats.copy_count << std::endl;
                break;
            case 5:
                bubble_sorter.sort(vector);
                std::cout << "Количество сравнений: " << bubble_sorter.stats.comparison_count << std::endl;
                std::cout << "Количество копирований: " << bubble_sorter.stats.copy_count << std::endl;
                break;
            case 6:
                std::cout << "[1] - сред.число сравнений и копирований для 100 массивов из N элементов\n"
                          << "[2] - сред.число сравнений и копирований для полностью отсортированного массива\n"
                          << "[3] - сред.число сравнений и копирований для обратно отсортированного массива\n"
                          << "[4] - Назад в главное меню\n--> ";
                std::cin >> command2;
                switch (command2) {
                    case 1:
                        // тест 1 (а)
                        testing_code_1();
                        break;
                    case 2:
                        // тест 2 (б)
                        testing_code_2();
                        break;
                    case 3:
                        // тест 3 (в)
                        testing_code_3();
                        break;
                    case 4:
                        break;
                    default:
                        std::cout << "Неверная команда!" << std::endl;
                }
                break;
            case 7:
                return 0;
            default:
                std::cout << "Неверная команда!" << std::endl;
        }
    }
    return 0;
}
