/*
* Laboratory work number 1, option 14(2)
* Panyshkin Andrei Mikhailovich, group 6213-100503D 
*/
#include <iostream>
#include "Set.h"
#include <chrono>


// пересечение множеств
Set intersection_set(Set& s_1, Set& s_2) {
    Set result_set;
    std::vector<int> vector_for_set_1, vector_for_set_2, result_vector;

    // получение векторов из множеств
    s_1.get_vector(vector_for_set_1);
    s_2.get_vector(vector_for_set_2);

    result_vector.resize(vector_for_set_1.size() + vector_for_set_2.size());

    // пересечение векторов
    for (const auto& item1 : vector_for_set_1) {
        for (const auto& item2 : vector_for_set_2) {
            if (item1 == item2) {
                result_vector.push_back(item1);
                break;
            }
        }
    }

    // добавление элементов в множество
    for (const auto& item : result_vector)
        result_set.insert(item);

    return result_set;
}

// объединение множеств
Set union_set(Set& s_1, Set& s_2)  {
    Set result_set;
    std::vector<int> vector_for_set_1, vector_for_set_2, result_vector;

    // получение векторов из множеств
    s_1.get_vector(vector_for_set_1);
    s_2.get_vector(vector_for_set_2);

    result_vector.resize(vector_for_set_1.size() + vector_for_set_2.size());

    // объединение векторов
    std::merge(vector_for_set_1.begin(), vector_for_set_1.end(), vector_for_set_2.begin(), vector_for_set_2.end(), result_vector.begin());

    // удаление дубликатов
    result_vector.erase(std::unique(result_vector.begin(), result_vector.end()), result_vector.end());

    // добавление элементов в множество
    for (const auto& item : result_vector)
        result_set.insert(item);

    return result_set;
}

// симметрическая разность множеств
// симметрическая разность = объединение - пересечение
Set symmetric_difference(Set& s_1, Set& s_2) {
    Set result_set;
    Set tmp1 = union_set(s_1, s_2);
    Set tmp2 = intersection_set(s_1, s_2);

    std::vector<int> vector_for_tmp_1, vector_for_tmp_2, result_vector;

    // получение векторов из множеств
    s_1.get_vector(vector_for_tmp_1);
    s_2.get_vector(vector_for_tmp_2);

    result_vector.resize(0);

    // добавление элементов из первого вектора в результирующий вектор соблюдая условие
    bool flag = false;
    for (const auto& item1 : vector_for_tmp_1) {
        for (const auto& item2 : vector_for_tmp_2) {
            if (item1 == item2) {
                flag = true;
                break;
            }
        }
        if (!flag)
            result_vector.push_back(item1);
        flag = false;
    }

    // добавление остаточных элементов из второго вектора в результирующий вектор
    for (const auto& item1 : vector_for_tmp_2) {
        for (const auto& item2 : vector_for_tmp_1) {
            if (item1 == item2) {
                flag = true;
                break;
            }
        }
        if (!flag)
            result_vector.push_back(item1);
        flag = false;
    }

    // запись результата в множество
    for (const auto& item : result_vector)
        result_set.insert(item);
    return result_set;
}

size_t lcg(size_t& i) {
    return (i * 1021 + 24631) % 116640;
}

void testing_code(){
    Set set1000, set10000, set100000;

    std::cout << "For my set:\n";
    std::cout << "Test1 - 1000\n";
    // test 1 - 1000
    // insert
    auto start = std::chrono::high_resolution_clock::now(); // запоминаем время начала выполнения
    for (size_t j = 0; j < 100; j++)
        for (size_t i = 0; i < 1000; i++)
            set1000.insert(lcg(i));
    auto end = std::chrono::high_resolution_clock::now(); // запоминаем время завершения выполнения
    std::chrono::duration<double, std::micro> duration = (end - start); // вычисляем время выполнения в микросекундах
    std::cout << "Среднее время заполнения для 1000: " << (double)duration.count() / 100 << " us" << std::endl;

    // search (contains)
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < 1000; i++)
        set1000.contains(lcg(i));
    end = std::chrono::high_resolution_clock::now();
    duration = (end - start);
    std::cout << "Среднее время поиска для 1000: " << (double)duration.count() / 1000 << " ms" << std::endl;

    // remove (erase)
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < 1000; i++)
        set1000.erase(lcg(i));
    end = std::chrono::high_resolution_clock::now();
    duration = (end - start);
    std::cout << "Среднее время удаления для 1000: " << (double)duration.count() / 1000 << " ms" << std::endl;

    std::cout << "Test2 - 10000\n";
    // test 2 - 10000
    // insert
    start = std::chrono::high_resolution_clock::now();
    for (size_t j = 0; j < 100; j++)
        for(size_t i = 0; i < 10000; i++)
            set10000.insert(lcg(i));
    end = std::chrono::high_resolution_clock::now();
    duration = (end - start);
    std::cout << "Среднее время заполнения для 10000: " << (double)duration.count() / 100  << " ms" << std::endl;

    // search (contains)
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < 1000; i++)
        set10000.contains(lcg(i));
    end = std::chrono::high_resolution_clock::now();
    duration = (end - start);
    std::cout << "Среднее время поиска для 10000: " << (double)duration.count() / 1000 << " ms" << std::endl;

    // remove (erase)
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < 1000; i++)
        set10000.erase(lcg(i));
    end = std::chrono::high_resolution_clock::now();
    duration = (end - start);
    std::cout << "Среднее время удаления для 10000: " << (double)duration.count() / 1000 << " ms" << std::endl;

    std::cout << "Test3 - 100000\n";
    // test 3 - 100000
    // insert
    start = std::chrono::high_resolution_clock::now();
    for (size_t j = 0; j < 100; j++)
        for(size_t i = 0; i < 100000; i++)
            set100000.insert(lcg(i));
    end = std::chrono::high_resolution_clock::now();
    duration = (end - start);
    std::cout << "Среднее время заполнения для 100000: " << (double)duration.count() / 100 << " ms" << std::endl;

    // search (contains)
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < 1000; i++)
        set100000.contains(lcg(i));
    end = std::chrono::high_resolution_clock::now();
    duration = (end - start);
    std::cout << "Среднее время поиска для 100000: " << (double)duration.count() / 1000 << " ms" << std::endl;

    // remove (erase)
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < 1000; i++)
        set100000.erase(lcg(i));
    end = std::chrono::high_resolution_clock::now();
    duration = (end - start);
    std::cout << "Среднее время удаления для 100000: " << (double)duration.count() / 1000 << " ms" << std::endl;

    std::cout << "\nFor std::vector:\n";
    // std::set<int> std_set1000, std_set10000, std_set100000;
    std::vector<int> std_set1000, std_set10000, std_set100000;
    std::cout << "Test1 - 1000\n";
    // test 1 - 1000
    // insert
    start = std::chrono::high_resolution_clock::now();
    for (size_t j = 0; j < 100; j++)
        for (size_t i = 0; i < 1000; i++)
            std_set1000.push_back(lcg(i));
    end = std::chrono::high_resolution_clock::now();
    duration = (end - start);
    std::cout << "Среднее время заполнения для 1000: " << (double)duration.count() / 100 << " ms" << std::endl;

    // search (contains)
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < 1000; i++)
        std::find(std_set1000.begin(), std_set1000.end(), lcg(i));
    end = std::chrono::high_resolution_clock::now();
    duration = (end - start);
    std::cout << "Среднее время поиска для 1000: " << (double)duration.count() / 1000 << " ms" << std::endl;

    // remove
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < 1000; i++)
        std_set1000.erase(std::find(std_set1000.begin(), std_set1000.end(), lcg(i)));
    end = std::chrono::high_resolution_clock::now();
    duration = (end - start);
    std::cout << "Среднее время удаления для 1000: " << (double)duration.count() / 1000 << " ms" << std::endl;

    std::cout << "Test2 - 10000\n";
    // test 2 - 10000
    // insert
    start = std::chrono::high_resolution_clock::now();
    for (size_t j = 0; j < 100; j++)
        for (size_t i = 0; i < 10000; i++)
            std_set10000.push_back(lcg(i));
    end = std::chrono::high_resolution_clock::now();
    duration = (end - start);
    std::cout << "Среднее время заполнения для 10000: " << (double)duration.count() / 100 << " ms" << std::endl;

    // search (contains)
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < 1000; i++)
        std::find(std_set10000.begin(), std_set10000.end(), lcg(i));
    end = std::chrono::high_resolution_clock::now();
    duration = (end - start);
    std::cout << "Среднее время поиска для 10000: " << (double)duration.count() / 1000 << " ms" << std::endl;

    // remove (erase)
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < 1000; i++)
        std_set10000.erase(std::find(std_set10000.begin(), std_set10000.end(), lcg(i)));
    end = std::chrono::high_resolution_clock::now();
    duration = (end - start);
    std::cout << "Среднее время удаления для 10000: " << (double)duration.count() / 1000 << " ms" << std::endl;

    std::cout << "Test3 - 100000\n";
    // test 3 - 100000
    // insert
    start = std::chrono::high_resolution_clock::now();
    for (size_t j = 0; j < 100; j++)
        for (size_t i = 0; i < 100000; i++)
            std_set100000.push_back(lcg(i));
    end = std::chrono::high_resolution_clock::now();
    duration = (end - start);
    std::cout << "Среднее время заполнение для 100000: " << (double)duration.count() / 100 << " ms" << std::endl;

    // search (contains)
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < 1000; i++)
        std::find(std_set100000.begin(), std_set100000.end(), lcg(i));
    end = std::chrono::high_resolution_clock::now();
    duration = (end - start);
    std::cout << "Среднее время поиска для 100000: " << (double)duration.count() / 1000 << " ms" << std::endl;

    // remove (erase)
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < 1000; i++)
        std_set100000.erase(std::find(std_set100000.begin(), std_set100000.end(), lcg(i)));
    end = std::chrono::high_resolution_clock::now();
    duration = (end - start);
    std::cout << "Среднее время удаления для 100000: " << (double)duration.count() / 1000 << " ms" << std::endl;
}

int main()
{
    Set set_1, set_2;
    int element;
    while (true){
        int command;
        int command2;
        std::cout << "\n[0] Заполнить множество\n[1] Добавить элемент\n[2] Удалить элемент\n[3] Проверить наличие элемента\n[4] Вывод множества\n[5] Найти объединение двух множеств\n[6] Найти симметрическую разность\n[7] Тестирование\n--> ";
        std::cin >> command;
        switch (command){
            case 0:
                while (true){
                    std::cout << "\n[1] первое множество\n[2] второе множество\n[3] назад\n--> ";
                    std::cin >> command2;
                    if (command2 == 3){std::cout << "\n[0] Заполнить множество\n[1] Добавить элемент\n[2] Удалить элемент\n[3] Проверить наличие элемента\n[4] Вывод множества\n[5] Найти объединение двух множеств\n[6] Найти симметрическую разность\n[7] Тестирование\n--> ";
                        break;}
                    switch (command2) {
                        case 1:
                            std::cout << "Введите количество добавляемых элементов: ";
                            int count1;
                            std::cin >> count1;
                            for (int i = 0; i < count1; i++){
                                std::cout << "значение: ";
                                std::cin >> element;
                                set_1.insert(element);
                            }
                            break;
                        case 2:
                            std::cout << "Введите количество добавляемых элементов: ";
                            int count2;
                            std::cin >> count2;
                            for (int i = 0; i < count2; i++){
                                std::cout << "значение: ";
                                std::cin >> element;
                                set_2.insert(element);
                            }
                            break;
                        default:
                            std::cout << "error command\n";
                    }
                }
                break;
            case 1:
                while (true){
                    std::cout << "\n[1] первое множество\n[2] второе множество\n[3] назад\n--> ";
                    std::cin >> command2;
                    if (command2 == 3){std::cout << "\n[0] Заполнить множество\n[1] Добавить элемент\n[2] Удалить элемент\n[3] Проверить наличие элемента\n[4] Вывод множества\n[5] Найти объединение двух множеств\n[6] Найти симметрическую разность\n[7] Тестирование\n--> ";
                        break;}
                    switch (command2) {
                        case 1:
                            std::cout << "значение: ";
                            std::cin >> element;
                            set_1.insert(element);
                            break;
                        case 2:
                            std::cout << "значение: ";
                            std::cin >> element;
                            set_2.insert(element);
                            break;
                        default:
                            std::cout << "error command\n";
                    }
                }
                break;
            case 2:
                while (true){
                    std::cout << "\n[1] первое множество\n[2] второе множество\n[3] назад\n--> ";
                    std::cin >> command2;
                    if (command2 == 3){std::cout << "\n[0] Заполнить множество\n[1] Добавить элемент\n[2] Удалить элемент\n[3] Проверить наличие элемента\n[4] Вывод множества\n[5] Найти объединение двух множеств\n[6] Найти симметрическую разность\n[7] Тестирование\n--> ";
                        break;}
                    switch (command2) {
                        case 1:
                            std::cout << "значение: ";
                            std::cin >> element;
                            set_1.erase(element);
                            break;
                        case 2:
                            std::cout << "значение: ";
                            std::cin >> element;
                            set_2.erase(element);
                            break;
                        default:
                            std::cout << "error command\n";
                    }
                }
                break;

            case 3:
                while (true){
                    std::cout << "[1] первое множество\n[2] второе множество\n[3] назад\n--> ";
                    std::cin >> command2;
                    if (command2 == 3){std::cout << "\n[0] Заполнить множество\n[1] Добавить элемент\n[2] Удалить элемент\n[3] Проверить наличие элемента\n[4] Вывод множества\n[5] Найти объединение двух множеств\n[6] Найти симметрическую разность\n[7] Тестирование\n--> ";
                        break;}
                    switch (command2) {
                        case 1:
                            std::cout << "значение: ";
                            std::cin >> element;
                            std::cout << set_1.contains(element) << std::endl;
                            break;
                        case 2:
                            std::cout << "значение: ";
                            std::cin >> element;
                            std::cout << set_2.contains(element) << std::endl;
                            break;
                        default:
                            std::cout << "error command\n";
                    }
                }
                break;
            case 4:
                while (true){
                    std::cout << "\n[1] первое множество\n[2] второе множество\n[3] назад\n--> ";
                    std::cin >> command2;
                    if (command2 == 3){std::cout << "\n[0] Заполнить множество\n[1] Добавить элемент\n[2] Удалить элемент\n[3] Проверить наличие элемента\n[4] Вывод множества\n[5] Найти объединение двух множеств\n[6] Найти симметрическую разность\n[7] Тестирование\n--> ";
                        break;}
                    switch (command2) {
                        case 1:
                            set_1.print();
                            break;
                        case 2:
                            set_2.print();
                            break;
                        default:
                            std::cout << "error command\n";
                    }
                }
                break;
            case 5:
                while (true) {
                    std::cout << "\n[1] Объединить множества\n[3] назад\n--> ";
                    std::cin >> command2;
                    if (command2 == 3) {
                        std::cout << "\n[0] Заполнить множество\n[1] Добавить элемент\n[2] Удалить элемент\n[3] Проверить наличие элемента\n[4] Вывод множества\n[5] Найти объединение двух множеств\n[6] Найти симметрическую разность\n[7] Тестирование\n--> ";
                        break;
                    }
                    switch (command2) {
                        case 1:
                            union_set(set_1, set_2).print();
                            break;
                        default:
                            std::cout << "error command\n";
                    }
                }
                break;
            case 6:
                while (true) {
                    std::cout << "\n[1] Симметрическая разность\n[3] назад\n--> ";
                    std::cin >> command2;
                    if (command2 == 3) {
                        std::cout << "\n[0] Заполнить множество\n[1] Добавить элемент\n[2] Удалить элемент\n[3] Проверить наличие элемента\n[4] Вывод множества\n[5] Найти объединение двух множеств\n[6] Найти симметрическую разность\n[7] Тестирование\n--> ";
                        break;
                    }
                    switch (command2) {
                        case 1:
                            symmetric_difference(set_1, set_2).print();
                            break;
                        default:
                            std::cout << "error command\n";
                    }
                }
                break;
            case 7:
                testing_code();
                break;
            default:
                std::cout << "error command\n";
        }
    }
    return 0;
}
