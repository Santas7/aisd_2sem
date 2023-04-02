#pragma once
#include <iostream>
#include <vector>

class Set {
private:
    struct TreeNode {
        int value;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int value) : value(value), left(nullptr), right(nullptr) {}
    };
    TreeNode* _root;
    // рекурсивный метод для удаления всех узлов дерева
    void clear(TreeNode* root);
    // рекурсивный метод для копирования дерева
    TreeNode* copy_tree(TreeNode* root);
    // рекурсивный метод для вставки узла в дерево
    std::pair<TreeNode*, bool> insert_(TreeNode*& root, int value);
    // рекурсивный метод для поиска узла в дереве
    bool contains_(TreeNode* root, int value) const;
    // рекурсивный метод для удаления узла из дерева
    bool erase_(TreeNode*& root, int value);
    // рекурсивный метод для печати содержимого дерева
    void print_(TreeNode* root) const;
    // оператор присваивания
    Set& operator=(const Set& tree);
    void get_vector_(TreeNode* root, std::vector<int>& vector);

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
    bool contains(const int& value);
    // формирование вектора из дерева
    void get_vector(std::vector<int>& vector);
};
