#include "Set.h"

// конструктор
Set::Set() : _root(nullptr) {}

// конструктор копирования
Set::Set(const Set& tree) : _root(nullptr) {
    _root = copy_tree(tree._root);
}

// деструктор
Set::~Set() { clear(_root); }

// вставки узла в дерево
bool Set::insert(const int& value) {
    return insert_(_root, value).second;
}

// вывод дерева в консоль
void Set::print() const {
    print_(_root);
}

// удаление узла из дерева
bool Set::erase(const int& value) {
    return erase_(_root, value);
}

// поиск узла в дереве
bool Set::contains(const int& value) const{
    return contains_(_root, value);
}

// рекурсивный метод для удаления всех узлов дерева
void Set::clear(TreeNode* root) {
    if (root) {
        clear(root->left);
        clear(root->right);
        delete root;
    }
}

// рекурсивный метод для копирования дерева
Set::TreeNode* Set::copy_tree(const TreeNode* root) {
    if (!root)
        return nullptr;

    TreeNode* copy_node = new TreeNode(root->value);
    copy_node->left = copy_tree(root->left);
    copy_node->right = copy_tree(root->right);
    return copy_node;
}

// рекурсивный метод для вставки узла в дерево
std::pair<Set::TreeNode*, bool> Set::insert_(TreeNode*& root, int value) {
    if (!root) {
        root = new TreeNode(value);
        return { root, true };
    }
    if (root->value == value)
        return { root, false };
    if (root->value > value)
        return insert_(root->left, value);
    else
        return insert_(root->right, value);
}

// рекурсивный метод для поиска узла в дереве
bool Set::contains_(const TreeNode* root, int value)  {
    if (!root)
        return false;
    if (root->value == value)
        return true;
    if (root->value > value)
        return contains_(root->left, value);
    else
        return contains_(root->right, value);
}

// рекурсивный метод для удаления узла из дерева
bool Set::erase_(TreeNode*& root, int value) {
    if (!root)
        return false;
    if (root->value == value) {
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
            // находим минимальный элемент в правом поддереве
            TreeNode* min_right_node = root->right;
            while (min_right_node->left) {
                min_right_node = min_right_node->left;
            }
            // меняем значение удаляемого узла на минимальный элемент в правом поддереве
            root->value = min_right_node->value;
            // удаляем минимальный элемент в правом поддереве
            erase_(root->right, min_right_node->value);
        }
        return true;
    }
    if (root->value > value) 
        return erase_(root->left, value);
    else 
        return erase_(root->right, value);
}

// рекурсивный метод для печати содержимого дерева
void Set::print_(const TreeNode* root)  {
    if (!root) return;

    print_(root->left);
    std::cout << root->value << " ";
    print_(root->right);
}

// оператор присваивания
Set& Set::operator=(const Set& tree) {
    if (this != &tree) {
        // очищаем текущее дерево
        clear(tree._root);
        // копируем корень дерева
        if (tree._root != nullptr)
            _root = new TreeNode(*tree._root);
        // копируем остальные узлы дерева
        copy_tree(tree._root);
    }
    return *this;
}

// рекурсивный метод для получения вектора из дерева
void Set::get_vector_(TreeNode* root, std::vector<int>& vector) const {
    if (root == nullptr) {
        return;
    }
    get_vector_(root->left, vector);
    vector.push_back(root->value);
    get_vector_(root->right, vector);
}

// получение вектора из дерева (множества)
void Set::get_vector(std::vector<int>& vector) const{get_vector_(_root, vector);}
