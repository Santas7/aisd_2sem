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
    /*
    bool insert_(TreeNode*& root, int value) {
        if (!root) {
            root = new TreeNode(value);
            return true;
        }
        if (root->value == value)
            return false;
        if (root->value > value)
            return insert_(root->left, value);
        else
            return insert_(root->right, value);
    }
    */
    // рекурсивный метод для поиска узла в дереве
    bool contains_(TreeNode* root, int value) const;
    // рекурсивный метод для удаления узла из дерева
    bool erase_(TreeNode*& root, int value);
    // рекурсивный метод для печати содержимого дерева
    void print_(TreeNode* root) const;
    // оператор присваивания
    Set& operator=(const Set& tree);

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

    // Задача (вар 2)
    void get_vector(TreeNode* root, std::vector<int>& vector);
    // метод пересечения двух множеств
    Set intersection_set(const Set& s_1, const Set& s_2);
    // метод объединения двух множеств
    Set union_set(const Set& s_1, const Set& s_2);
    // метод cимметрической разности двух множеств
    Set symmetric_difference(const Set& s1, const Set& s2);
};
