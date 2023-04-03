#include <iostream>
#include <vector>

void intertion_sort(std::vector<int> &vec);
void shaker_sort(std::vector<int> &vec);
void pyramidal_sort(std::vector<int> &vec);
void sift_down(std::vector<int> &vec, int i, int n);

int main() {
    // 14(10) -> 112(3)
    std::vector<int> vec1, vec2, vec3;

    // fill vector
    for (int i = 0; i < 5; ++i){
        int value = 0;
        std::cin >> value;
        vec1.push_back(i);
    }
    for (int i = 0; i < 5; ++i){
        int value = 0;
        std::cin >> value;
        vec2.push_back(i);
    }
    for (int i = 0; i < 5; ++i){
        int value = 0;
        std::cin >> value;
        vec3.push_back(i);
    }
    // sort
    intertion_sort(vec1);
    // output vector
    for (int i = 0; i < 5; ++i)
        std::cout << vec1[i] << " ";
    shaker_sort(vec2);
    // output vector
    for (int i = 0; i < 5; ++i)
        std::cout << vec2[i] << " ";
    pyramidal_sort(vec3);
    // output vector
    for (int i = 0; i < 5; ++i)
        std::cout << vec3[i] << " ";
    
    return 0;
}

void intertion_sort(std::vector<int> &vec) {
    for (int i = 1; i < vec.size(); ++i) {
        for (int j = i; j > 0 && vec[j - 1] > vec[j]; --j)
            std::swap(vec[j - 1], vec[j]);
    }
}

void shaker_sort(std::vector<int> &vec) {
    int left = 0;
    int right = vec.size() - 1;
    while (left < right) {
        for (int i = left; i < right; ++i)
            if (vec[i] > vec[i + 1])
                std::swap(vec[i], vec[i + 1]);
        --right;
        for (int i = right; i > left; --i)
            if (vec[i - 1] > vec[i])
                std::swap(vec[i - 1], vec[i]);
        ++left;
    }
}

void sift_down(std::vector<int> &vec, int i, int n) {
    while (2 * i + 1 < n) {
        int j = 2 * i + 1;
        if (j + 1 < n && vec[j + 1] > vec[j])
            ++j;
        if (vec[i] >= vec[j])
            break;
        std::swap(vec[i], vec[j]);
        i = j;
    }
}

void pyramidal_sort(std::vector<int> &vec) {
    for (int i = vec.size() / 2 - 1; i >= 0; --i)
        sift_down(vec, i, vec.size());
    for (int i = vec.size() - 1; i > 0; --i) {
        std::swap(vec[0], vec[i]);
        sift_down(vec, 0, i);
    }
}
