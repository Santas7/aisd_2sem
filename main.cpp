/*
* Laboratory work number 1, option 14(2)
* Panyshkin Andrei Mikhailovich, group 6213-100503D 
*/

#include <iostream>
#include "Set.h"

int main()
{
    Set tree;
    // пример работы кода
    // заполняем дерево
    tree.insert(4);
    tree.insert(5);
    tree.insert(2);
    tree.insert(1);
    tree.insert(6);

    // вывод всего дерева в консоль
    tree.print();

    // проверка наличия элемента
    std::cout << tree.contains(2) << std::endl;
    std::cout << tree.contains(8) << std::endl;
    std::cout << "\n+1\n";
    tree.print();

    // удаление элемента
    tree.erase(2);
    tree.erase(8);
    std::cout << "\n+2\n";
    tree.print();

    return 0;
}
