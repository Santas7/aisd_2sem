#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

class Set {
private:
    struct TreeNode {
        int value; // значение узла
        TreeNode* left; // левый потомок
        TreeNode* right; // правый потомок
        TreeNode(int value) : value(value), left(nullptr), right(nullptr) {}
    };
    TreeNode* _root; // корень дерева
    // рекурсивный метод для удаления всех узлов дерева
    void clear(TreeNode* root);
    // рекурсивный метод для копирования дерева
    static TreeNode* copy_tree(const TreeNode* root);
    // рекурсивный метод для вставки узла в дерево
    static std::pair<TreeNode*, bool> insert_(TreeNode*& root, int value);
    // рекурсивный метод для поиска узла в дереве
    static bool contains_(const TreeNode* root, int value);
    // рекурсивный метод для удаления узла из дерева
    static bool erase_(TreeNode*& root, int value);
    // рекурсивный метод для печати содержимого дерева
    static void print_(const TreeNode* root);
    // оператор присваивания
    Set& operator=(const Set& tree);
    // рекурсивный метод для получения вектора из дерева
    void get_vector_(TreeNode* root, std::vector<int>& vector) const;
public:
    // конструктор
    Set();
    // конструктор копирования
    Set(const Set& tree);
    // деструктор
    ~Set();
    // вставки узла в дерево
    bool insert(const int& value);
    // вывод дерева в консоль
    void print() const;
    // удаление узла из дерева
    bool erase(const int& value);
    // поиск узла в дереве
    bool contains(const int& value) const;
    // получение вектора из дерева
    void get_vector(std::vector<int>& vector) const;
};
