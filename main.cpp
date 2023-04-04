#include <iostream>
#include <vector>

struct Stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

// сортировка вставками (O(n^2))
Stats intertion_sort(std::vector<int>& vec) {
    Stats stats;
    for (int i = 1; i < vec.size(); ++i) {
        for (int j = i; j > 0 && vec[j - 1] > vec[j]; --j) {
            std::swap(vec[j - 1], vec[j]);
            ++stats.copy_count;
            ++stats.comparison_count;
        }
    }
}

// шейкерная сортировка (O(n^2))
Stats shaker_sort(std::vector<int>& vec) {
    /*
     Шейкерная сортировка представляет собой двунаправленную пузырьковую сортировку.
     Идем по массиву сначала слева направо, перемещая наибольший элемент в конец массива, а затем справа налево,
     перемещая наименьший элемент в начало массива.
     */
    Stats stats;
    int left = 0; // левая граница
    int right = vec.size() - 1; // правая граница
    while (left <= right) { // пока левая граница не сомкнется с правой
        for (int i = left; i < right; ++i) {
            if (vec[i] > vec[i + 1]) {
                std::swap(vec[i], vec[i + 1]);
                ++stats.copy_count;
            }
            ++stats.comparison_count;
        }
        --right; // сдвигаем правую границу
        for (int i = right; i > left; --i) {
            if (vec[i - 1] > vec[i]) {
                std::swap(vec[i - 1], vec[i]);
                ++stats.copy_count;
            }
            ++stats.comparison_count;
        }
        ++left; // сдвигаем левую границу
    }
}

// заполнение вектора
void fill_vector(std::vector<int>& vec, int size) {
    for (int i = 0; i < size; ++i) {
        int value = 0;
        std::cout << "Enter value: ";
        std::cin >> value;
        vec.push_back(value);
    }
}

// вывод вектора
void output_vector(std::vector<int>& vec) {
    for (int i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
}

int main() {
    // 14(10) -> 112(3) вариант задания
    std::vector<int> vec1, vec2;
    int size = 0;
    // menu for user switch case
    while (true){
        std::cout << "[1] - Заполнение вектора\n[2] - Вывод вектора\n[3] - Сортировка вставками\n[4] - Шейкерная сортировка\n[5] - Тестирование\n--> ";
        int command;
        std::cin >> command;
        switch (command) {
            case 1:
                std::cout << "[1] - Вектор 1\n[2] - Вектор 2\n[3] Назад\n--> ";
                int command2;
                std::cin >> command2;
                switch (command2) {
                    case 1:
                        std::cout << "Размер вектора: ";
                        std::cin >> size;
                        fill_vector(vec1, size);
                        break;
                    case 2:
                        std::cout << "Размер вектора: ";
                        std::cin >> size;
                        fill_vector(vec2, size);
                        break;
                    case 3:
                        break;
                    default:
                        std::cout << "Error command\n";
                        break;
                }
                break;
            case 2:
                std::cout << "[1] - Вектор 1\n[2] - Вектор 2\n[3] Назад\n--> ";
                int command3;
                std::cin >> command3;
                switch (command3) {
                    case 1:
                        output_vector(vec1);
                        break;
                    case 2:
                        output_vector(vec2);
                        break;
                    case 3:
                        break;
                    default:
                        std::cout << "Error command\n";
                        break;
                }
                break;
            case 3:
                std::cout << "[1] - Вектор 1\n[2] - Вектор 2\n[3] Назад\n--> ";
                int command4;
                std::cin >> command4;
                switch (command4) {
                    case 1:
                        intertion_sort(vec1);
                        break;
                    case 2:
                        intertion_sort(vec2);
                        break;
                    case 3:
                        break;
                    default:
                        std::cout << "Error command\n";
                        break;
                }
                break;
            case 4:
                std::cout << "[1] - Вектор 1\n[2] - Вектор 2\n[3] Назад\n--> ";
                int command5;
                std::cin >> command5;
                switch (command5) {
                    case 1:
                        shaker_sort(vec1);
                        break;
                    case 2:
                        shaker_sort(vec2);
                        break;
                    case 3:
                        break;
                    default:
                        std::cout << "Error command\n";
                        break;
                }
                break;
            case 5:
                // тестирование
                break;
            default:
                std::cout << "Error command\n";
                break;
        }
    }
    return 0;
}
