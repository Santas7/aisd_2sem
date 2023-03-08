/*
* Laboratory work number 1, option 14 
* Panyshkin Andrei Mikhailovich, group 6213-100503D 
*/

#include <iostream>

class Set { 
private:
    struct TreeNode {
        int data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int x) : data(x), left(nullptr), right(nullptr) {}
    };
    TreeNode* root = nullptr;

public:
    // конструктор
    Set() = default;

    // конструктор копирования
    Set(const Set& obj) = default;

    // деструктор
    ~Set() = default;

    TreeNode* get_root() const { return root; }

    // оператор присваивания
    /*
    * data - array datas
    Set& operator=(const Set& other) {
        if (this != &other) {
            data.clear();
            for (int num : other.data) {
                data.push_back(num);
            }
        }
        return *this;
    }
    */

    // метод для вставки элемента
    TreeNode* insert(TreeNode* root, int value) {
        if (root == nullptr) 
            return new TreeNode(value);
        if (value < root->data)
            root->left = insert(root->left, value);
        else if (value > root->data)
            root->right = insert(root->right, value);
        return root;
    }
    // метод удаления элемента из дерева
    TreeNode* erase(TreeNode* root, int value) {
        if (root == nullptr) 
            return nullptr;
        if (value < root->data)
            root->left = erase(root->left, value);
        else if (value > root->data)
            root->right = erase(root->right, value);
 
        else {
            if (root->left == nullptr) {
                TreeNode* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }
            TreeNode* temp = root->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            root->data = temp->data;
            root->right = erase(root->right, temp->data);
        }
        return root;
    }

    // метод проверки наличия элемента
    bool contains(TreeNode* root, int value) {
        if (root == nullptr) 
            return false;
        if (value == root->data)
            return true;
        else if (value < root->data)
            return contains(root->left, value);
        else 
            return contains(root->right, value);
    }

    // очистка дерева
    void clear(TreeNode* root) {
        if (root != nullptr) {
            clear(root->left);
            clear(root->right);
            delete root;
        }
    }
    
    // метод вывода дерева в консоль
    void print(TreeNode* root) {
        if (root == nullptr) 
            return;
        std::cout << root->data << " ";
        print(root->left);
        print(root->right);
    }
};

int main() {
    Set tree1;
    tree1.insert(tree1.get_root(), 1);
    tree1.insert(tree1.get_root(), 2);
    tree1.insert(tree1.get_root(), 3);

    tree1.print(tree1.get_root());
	return 0;
}
