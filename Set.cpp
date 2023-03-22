#include "Set.h"
#include <algorithm>



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
bool Set::contains(const int& value) {
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
Set::TreeNode* Set::copy_tree(TreeNode* root) {
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
bool Set::contains_(TreeNode* root, int value) const {
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
            TreeNode* min_right_node = root->right;
            while (min_right_node->left) {
                min_right_node = min_right_node->left;
            }
            root->value = min_right_node->value;
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
void Set::print_(TreeNode* root) const {
    if (!root) return;

    print_(root->left);
    std::cout << root->value << " ";
    print_(root->right);
}
// оператор присваивания
Set& Set::operator=(const Set& tree) {
    if (this != &tree) {
        // Очищаем текущее дерево
        clear(tree._root);
        // Копируем корень дерева
        if (tree._root != nullptr) 
            _root = new TreeNode(*tree._root);
        // Копируем остальные узлы дерева
        copy_tree(tree._root);
    }
    return *this;
}

// Задача к Л/Р (вар 2)

void Set::get_vector(TreeNode* root, std::vector<int>& vector) {
    if (root == nullptr) {
        return;
    }
    get_vector(root->left, vector);
    vector.push_back(root->value);
    get_vector(root->right, vector);
}

// метод пересечения двух множеств
Set Set::intersection_set(const Set& s_1, const Set& s_2) {
    Set result_set; // создаем результирующее множество
    std::vector<int> vector_for_set_1, vector_for_set_2, result_vector;

    // формируем два вектора для каждого множества
    get_vector(s_1._root, vector_for_set_1);
    get_vector(s_2._root, vector_for_set_2);

    // изменяем размер результируещего вектора
    result_vector.resize(vector_for_set_1.size() + vector_for_set_2.size());

    for (const auto& item1 : vector_for_set_1) {
        for (const auto& item2 : vector_for_set_2) {
            if (item1 == item2) {
                result_vector.push_back(item1);
                break;
            }
        }
    }
    
    // заполнение нового множества на основе результирующего вектора 
    for (int i = 0; i < result_vector.size(); i++)
        result_set.insert(result_vector[i]);

    return result_set;
}
// метод объединения двух множеств
Set Set::union_set(const Set& s_1, const Set& s_2) {
    Set result_set; // создаем результирующее множество
    std::vector<int> vector_for_set_1, vector_for_set_2, result_vector;
    
    // формируем два вектора для каждого множества
    get_vector(s_1._root, vector_for_set_1);
    get_vector(s_2._root, vector_for_set_2);
    
    // изменяем размер результируещего вектора
    result_vector.resize(vector_for_set_1.size() + vector_for_set_2.size());
    
    // объединяем векторы 
    std::merge(vector_for_set_1.begin(), vector_for_set_1.end(), vector_for_set_2.begin(), vector_for_set_2.end(), result_vector.begin());
    
    // удаляем дубликаты элементов
    result_vector.erase(std::unique(result_vector.begin(), result_vector.end()), result_vector.end());
    
    // заполнение нового множества на основе результирующего вектора 
    for (int i = 0; i < result_vector.size(); i++) 
        result_set.insert(result_vector[i]);

    return result_set;
}
// метод cимметрической разности двух множеств
Set Set::symmetric_difference(const Set& s_1, const Set& s_2) {
    Set result_set;
    Set tmp1 = Set().union_set(s_1, s_2);
    Set tmp2 = Set().intersection_set(s_1, s_2);

    std::vector<int> vector_for_tmp_1, vector_for_tmp_2, result_vector;

    // формируем два вектора для каждого множества
    get_vector(tmp1._root, vector_for_tmp_1);
    get_vector(tmp2._root, vector_for_tmp_2);

    // изменяем размер результируещего вектора
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
