/*
* Laboratory work number 1, option 14(2)
* Panyshkin Andrei Mikhailovich, group 6213-100503D 
*/
#include <iostream>
#include "Set.h"


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

    for (int i = 0; i < result_vector.size(); i++)
        result_set.insert(result_vector[i]);

    return result_set;
}

Set symmetric_difference(Set& s_1, Set& s_2) {
    Set result_set;
    Set tmp1 = union_set(s_1, s_2);
    Set tmp2 = intersection_set(s_1, s_2);

    std::vector<int> vector_for_tmp_1, vector_for_tmp_2, result_vector;

    s_1.get_vector(vector_for_tmp_1);
    s_2.get_vector(vector_for_tmp_2);

    result_vector.resize(vector_for_tmp_1.size() + vector_for_tmp_2.size());

    bool flag = false;
    for (int i = 0; i < vector_for_tmp_1.size(); i++) {
        flag = false;
        for (int j = 0; j < vector_for_tmp_2.size(); j++)
            if (vector_for_tmp_1[i] == vector_for_tmp_2[j])
                flag = true;
        if (!flag)
            result_set.insert(vector_for_tmp_1[i]);
    }
    return result_set;
}



int main()
{
    Set set_1, set_2;
    int element;

    while (true){
        int command;
        int command2;
        std::cout << "[1] Добавить элемент\n[2] Удалить элемент\n[3] Проверить наличие элемента\n[4] Вывод множества\n[5] Найти объединение двух множеств\n[6] Найти симметрическую разность\n--> ";
        std::cin >> command;
        switch (command){
            case 1:
                while (true){
                    std::cout << "[1] первое множество\n[2] второе множество\n[3] назад\n--> ";
                    std::cin >> command2;
                    if (command2 == 3){std::cout << "\n[1] Добавить элемент\n[2] Удалить элемент\n[3] Проверить наличие элемента\n[4] Вывод множества\n[5] Найти объединение двух множеств\n[6] Найти симметрическую разность\n--> ";
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
                    if (command2 == 3){std::cout << "\n[1] Добавить элемент\n[2] Удалить элемент\n[3] Проверить наличие элемента\n[4] Вывод множества\n[5] Найти объединение двух множеств\n[6] Найти симметрическую разность\n--> ";
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
                    if (command2 == 3){std::cout << "\n[1] Добавить элемент\n[2] Удалить элемент\n[3] Проверить наличие элемента\n[4] Вывод множества\n[5] Найти объединение двух множеств\n[6] Найти симметрическую разность\n--> ";
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
                    if (command2 == 3){std::cout << "\n[1] Добавить элемент\n[2] Удалить элемент\n[3] Проверить наличие элемента\n[4] Вывод множества\n[5] Найти объединение двух множеств\n[6] Найти симметрическую разность\n--> ";
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
                        std::cout << "\n[1] Добавить элемент\n[2] Удалить элемент\n[3] Проверить наличие элемента\n[4] Вывод множества\n[5] Найти объединение двух множеств\n[6] Найти симметрическую разность\n--> ";
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
                        std::cout << "\n[1] Добавить элемент\n[2] Удалить элемент\n[3] Проверить наличие элемента\n[4] Вывод множества\n[5] Найти объединение двух множеств\n[6] Найти симметрическую разность\n--> ";
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
            default:
                std::cout << "error command\n";
        }
    }
    return 0;
}
