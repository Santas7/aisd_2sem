/*
* Laboratory work number 1, option 14(2)
* Panyshkin Andrei Mikhailovich, group 6213-100503D 
*/
#include <iostream>
#include "Set.h"

int main()
{
    Set set_1, set_2;
    // пример работы кода
    // заполняем дерево
    set_1.insert(4);
    set_1.insert(5);
    set_1.insert(2);
    set_1.insert(1);
    set_1.insert(6);

    set_2.insert(5);
    set_2.insert(3);
    set_2.insert(6);
    // вывод всего дерева в консоль
    set_1.print();
    set_2.print();

    // проверка наличия элемента
    std::cout << set_1.contains(2) << std::endl;
    std::cout << set_1.contains(8) << std::endl;
    std::cout << "\n+1\n";
    set_1.print();

    // удаление элемента
    set_1.erase(2);
    set_1.erase(8);
    std::cout << "\n+2\n";
    set_1.print();

    // объединение множеств
    Set set_3 = Set().union_set(set_1, set_2);
    set_3.print();

    // cимметрическая разность двух множеств
    Set set_3 = Set().symmetric_difference(set_1, set_2);
    set_3.print();
    return 0;
}
