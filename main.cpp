/*
* Laboratory work number 1, option 14(2)
* Panyshkin Andrei Mikhailovich, group 6213-100503D 
*/
#include <iostream>
#include "Set.h"
#include <chrono>


Set intersection_set(Set& s_1, Set& s_2) {
    Set result_set;
    std::vector<int> vector_for_set_1, vector_for_set_2, result_vector;

    s_1.get_vector(vector_for_set_1);
    s_2.get_vector(vector_for_set_2);

    result_vector.resize(vector_for_set_1.size() + vector_for_set_2.size());

    for (const auto& item1 : vector_for_set_1) {
        for (const auto& item2 : vector_for_set_2) {
            if (item1 == item2) {
                result_vector.push_back(item1);
                break;
            }
        }
    }

    for (int i = 0; i < result_vector.size(); i++)
        result_set.insert(result_vector[i]);

    return result_set;
}

Set union_set(Set& s_1, Set& s_2) {
    Set result_set;
    std::vector<int> vector_for_set_1, vector_for_set_2, result_vector;

    s_1.get_vector(vector_for_set_1);
    s_2.get_vector(vector_for_set_2);

    result_vector.resize(vector_for_set_1.size() + vector_for_set_2.size());

    std::merge(vector_for_set_1.begin(), vector_for_set_1.end(), vector_for_set_2.begin(), vector_for_set_2.end(), result_vector.begin());

    result_vector.erase(std::unique(result_vector.begin(), result_vector.end()), result_vector.end());

    for (const auto& item : result_vector)
        result_set.insert(item);

    return result_set;
}

Set symmetric_difference(Set& s_1, Set& s_2) {
    Set result_set;
    Set tmp1 = union_set(s_1, s_2);
    Set tmp2 = intersection_set(s_1, s_2);

    std::vector<int> vector_for_tmp_1, vector_for_tmp_2, result_vector;

    s_1.get_vector(vector_for_tmp_1);
    s_2.get_vector(vector_for_tmp_2);

    result_vector.resize(0);


    // symmetric difference = union - intersection
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

    // write result to set
    for (const auto& item : result_vector)
        result_set.insert(item);
    return result_set;
}

size_t lcg(size_t& i) {
    return (i * 1021 + 24631) % 116640;
}

void testing_code(){
    int test1 = 1000;
    int test2 = 10000;
    int test3 = 100000;
    Set set1000, set10000, set100000;

    std::cout << "Test1 - 1000\n";
    // test 1 - 1000
    // insert
    auto start = std::chrono::high_resolution_clock::now(); // запоминаем время начала выполнения
    for (size_t i = 0; i < test1; i++)
        set1000.insert(lcg(i));
    auto end = std::chrono::high_resolution_clock::now(); // запоминаем время завершения выполнения
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); // вычисляем время выполнения в микросекундах
    std::cout << "Время заполнения для 1000: " << duration.count() << " ms" << std::endl;

    // search (contains)
    start = std::chrono::high_resolution_clock::now(); 
    for (size_t i = 0; i < test1; i++)
        size_t value = lcg(i);
    end = std::chrono::high_resolution_clock::now(); 
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); 
    std::cout << "Время поиска для 1000: " << duration.count() << " ms" << std::endl;

    // remove (erase)
    start = std::chrono::high_resolution_clock::now(); 
    for (size_t i = 0; i < test1; i++)
        set1000.erase(lcg(i));
    end = std::chrono::high_resolution_clock::now(); 
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); 
    std::cout << "Время удаления для 1000: " << duration.count() << " ms" << std::endl;

    std::cout << "Test2 - 10000\n";
    // test 2 - 10000
    // insert
    start = std::chrono::high_resolution_clock::now(); 
    for(size_t i = 0; i < test2; i++)
        set10000.insert(lcg(i));
    end = std::chrono::high_resolution_clock::now(); 
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); 
    std::cout << "Время заполнения для 10000: " << duration.count() << " ms" << std::endl;

    // search (contains)
    start = std::chrono::high_resolution_clock::now(); 
    for (size_t i = 0; i < test2; i++)
        size_t value = lcg(i);
    end = std::chrono::high_resolution_clock::now(); 
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); 
    std::cout << "Время поиска для 10000: " << duration.count() << " ms" << std::endl;

    // remove (erase)
    start = std::chrono::high_resolution_clock::now(); 
    for (size_t i = 0; i < test2; i++)
        set10000.erase(lcg(i));
    end = std::chrono::high_resolution_clock::now(); 
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); 
    std::cout << "Время удаления для 10000: " << duration.count() << " ms" << std::endl;

    std::cout << "Test3 - 100000\n";
    // test 3 - 100000
    // insert
    start = std::chrono::high_resolution_clock::now(); 
    for(size_t i = 0; i < test3; i++)
        set100000.insert(lcg(i));
    end = std::chrono::high_resolution_clock::now(); 
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); 
    std::cout << "Время заполнения для 100000: " << duration.count() << " ms" << std::endl;

    // search (contains)
    start = std::chrono::high_resolution_clock::now(); 
    for (size_t i = 0; i < test3; i++)
        size_t value = lcg(i);
    end = std::chrono::high_resolution_clock::now(); 
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); 
    std::cout << "Время поиска для 100000: " << duration.count() << " ms" << std::endl;

    // remove (erase)
    start = std::chrono::high_resolution_clock::now(); 
    for (size_t i = 0; i < test3; i++)
        set100000.erase(lcg(i));
    end = std::chrono::high_resolution_clock::now(); 
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); 
    std::cout << "Время удаления для 100000: " << duration.count() << " ms" << std::endl;
}

int main()
{
    Set set_1, set_2;
    int element;
    while (true){
        int command;
        int command2;
        std::cout << "[1] Добавить элемент\n[2] Удалить элемент\n[3] Проверить наличие элемента\n[4] Вывод множества\n[5] Найти объединение двух множеств\n[6] Найти симметрическую разность\n[7] Тестирование\n--> ";
        std::cin >> command;
        switch (command){
            case 1:
                while (true){
                    std::cout << "[1] первое множество\n[2] второе множество\n[3] назад\n--> ";
                    std::cin >> command2;
                    if (command2 == 3){std::cout << "\n[1] Добавить элемент\n[2] Удалить элемент\n[3] Проверить наличие элемента\n[4] Вывод множества\n[5] Найти объединение двух множеств\n[6] Найти симметрическую разность\n[7] Тестирование\n--> ";
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
                    std::cout << "[1] первое множество\n[2] второе множество\n[3] назад\n--> ";
                    std::cin >> command2;
                    if (command2 == 3){std::cout << "\n[1] Добавить элемент\n[2] Удалить элемент\n[3] Проверить наличие элемента\n[4] Вывод множества\n[5] Найти объединение двух множеств\n[6] Найти симметрическую разность\n[7] Тестирование\n--> ";
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
                    if (command2 == 3){std::cout << "\n[1] Добавить элемент\n[2] Удалить элемент\n[3] Проверить наличие элемента\n[4] Вывод множества\n[5] Найти объединение двух множеств\n[6] Найти симметрическую разность\n[7] Тестирование\n--> ";
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
                    std::cout << "[1] первое множество\n[2] второе множество\n[3] назад\n--> ";
                    std::cin >> command2;
                    if (command2 == 3){std::cout << "\n[1] Добавить элемент\n[2] Удалить элемент\n[3] Проверить наличие элемента\n[4] Вывод множества\n[5] Найти объединение двух множеств\n[6] Найти симметрическую разность\n[7] Тестирование\n--> ";
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
                    std::cout << "[1] Объединить множества\n[3] назад\n--> ";
                    std::cin >> command2;
                    if (command2 == 3) {
                        std::cout << "\n[1] Добавить элемент\n[2] Удалить элемент\n[3] Проверить наличие элемента\n[4] Вывод множества\n[5] Найти объединение двух множеств\n[6] Найти симметрическую разность\n[7] Тестирование\n--> ";
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
                    std::cout << "[1] Симметрическая разность\n[3] назад\n--> ";
                    std::cin >> command2;
                    if (command2 == 3) {
                        std::cout << "\n[1] Добавить элемент\n[2] Удалить элемент\n[3] Проверить наличие элемента\n[4] Вывод множества\n[5] Найти объединение двух множеств\n[6] Найти симметрическую разность\n[7] Тестирование\n--> ";
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
