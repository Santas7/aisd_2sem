/*
* Laboratory work number 1, option 14 
* Panyshkin Andrei Mikhailovich, group 6213-100503D 
*/

#include <iostream>

class Set {
private:
    struct TreeNode {
        int value;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int value) : value(value), left(nullptr), right(nullptr) {}
    };
    TreeNode* _root;

    // рекурсивная функция для удаления всех узлов дерева
    void clear(TreeNode* root) {
        if (root) {
            clear(root->left);
            clear(root->right);
            delete root;
        }
    }

    // рекурсивная функция для копирования дерева
    TreeNode* copy_tree(TreeNode* root) {
        if (!root) 
            return nullptr; 

        TreeNode* copy_node = new TreeNode(root->value);
        copy_node->left = copy_tree(root->left);
        copy_node->right = copy_tree(root->right);
        return copy_node;
    }

    // рекурсивная функция для вставки узла в дерево
    bool insert_(TreeNode*& root, int key) {
        if (!root) {
            root = new TreeNode(key);
            return true;
        }
        if (root->value == key) 
            return false;
        
        if (root->value > key) 
            return insert_(root->left, key);
  
        else 
            return insert_(root->right, key);
    }

    // рекурсивная функция для поиска узла в дереве
    bool contains_(TreeNode* root, int key) const {
        if (!root) 
            return false;

        if (root->value == key) 
            return true;

        if (root->value > key)  
            return contains_(root->left, key);

        else  
            return contains_(root->right, key);
    }

    // рекурсивная функция для удаления узла из дерева
    bool erase_(TreeNode*& root, int key) {
        if (!root) 
            return false;

        if (root->value == key) {
            if (!root->left) {
                TreeNode* right_child = root->right;
                delete root;
                root = right_child;
            }
            else if (!root->right) {
                TreeNode* left_child = root->left;
                delete root;
                root = left_child;
            }
            else {
                TreeNode* min_right_node = root->right;
                while (min_right_node->left) {
                    min_right_node = min_right_node->left;
                }
                root->value = min_right_node->value;
                erase_(root->right, min_right_node->value);
            }
            return true;
        }
        if (root->value > key) {
            return erase_(root->left, key);
        }
        else {
            return erase_(root->right, key);
        }
    }

    // рекурсивная функция для печати содержимого дерева
    void print_(TreeNode* root) const {
        if (!root) return;
        
        print_(root->left);
        std::cout << root->value << " ";
        print_(root->right);
    }

    Set& operator=(const Set& tree) {
        if (this != &tree) {
            // Очищаем текущее дерево
            clear(tree._root);

            // Копируем корень дерева
            if (tree._root != nullptr) {
                _root = new TreeNode(*tree._root);
            }

            // Копируем остальные узлы дерева
            copy_tree(tree._root);
        }

        return *this;
    }

public:
    Set() : _root(nullptr) {}
    Set(const Set& tree) : _root(nullptr) {
        _root = copy_tree(tree._root);
    }
    ~Set() { clear(_root); }

    bool insert(const int& key) {
        return insert_(_root, key);
    }

    void print() const {
        print_(_root);
    }

    bool erase(const int& key) {
        return erase_(_root, key);
    }

    bool contains(const int& key) {
        return contains_(_root, key);
    }
};

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
