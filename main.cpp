#include <iostream>
#include "graph.h"

// Задача 2. Пусть дан связный граф, в котором узлы – это торговые точки.
// Необходимо превратить одну из торговых точек в склад. Цена доставки от склада в точку зависит
// от расстояния. Найдите оптимальную с точки зрения максимальных затрат точку
// (т.е. точку, для которой максимальное расстояние до любой другой точки минимально).

template<typename Vertex, typename Distance = double>
Vertex find_optimal(Graph<Vertex, Distance>& graph){
    Vertex result;
    Distance min_max_distance = std::numeric_limits<Distance>::max();
    for (auto& i : graph.vertices()) {
        Distance max_distance = 0;
        for (auto& j : graph.vertices()) {
            if (i == j) continue;
            auto path = graph.shortest_path(i, j);
            Distance current_distance = 0;
            for (auto& edge : path) {
                current_distance += edge.distance;
            }
            max_distance = std::max(max_distance, current_distance);
        }
        if (max_distance < min_max_distance) {
            min_max_distance = max_distance;
            result = i;
        }
    }
    return result;
}

int main() {
    Graph<int, double> graph;

    while (true){
        std::cout << "[1] Создать случайный граф\n"
                  << "[2] Вывод графа\n"
                  << "[3] Поиск кратчайшего пути (Беллман-Форд)\n"
                  << "[4] Обход в глубину\n"
                  << "[5] Задача(2)\n"
                  << "[0] Выход\n"
                  << "--> ";
        int command = 0;
        std::cin >> command;
        switch (command){
            case 1:
            {
                std::cout << "Введите количество вершин: ";
                int n = 0;
                std::cin >> n;
                for (int i = 0; i < n; ++i)
                    graph.add_vertex(i);
                for (int i = 0; i < n; ++i){
                    auto edge_count = rand() % n;
                    for (int j = 0; j < edge_count; ++j){
                        if (i == j) continue;
                        graph.add_edge(i, j, rand() % 100);
                    }
                }
                break;
            }
            case 2:
            {
                std::cout << "Вершины: ";
                for (auto& i : graph.vertices())
                    std::cout << i << " ";
                std::cout << std::endl;
                std::cout << "Ребра: " << std::endl;
                for (auto& i : graph.vertices())
                    for (auto& j : graph.edges(i))
                        std::cout << j.from << " -> " << j.to << " : " << j.distance << std::endl;
                break;
            }
            case 3:
            {
                std::cout << "Введите начальную вершину: ";
                int from = 0;
                std::cin >> from;
                std::cout << "Введите конечную вершину: ";
                int to = 0;
                std::cin >> to;
                auto result = graph.shortest_path(from, to);
                auto total_distance = 0.0;
                for (auto& edge : result) {
                    total_distance += edge.distance;
                }
                std::cout << "Расстояние: " << total_distance << std::endl;
                std::cout << "Путь: ";
                for (auto& edge : result)
                    std::cout << edge.from << " -> " << edge.to << "; ";
                std::cout << std::endl;
                break;
            }

            case 4:
            {
                std::cout << "Введите начальную вершину: ";
                int from = 0;
                std::cin >> from;
                auto result = graph.walk(from);
                std::cout << "Путь: ";
                for (auto& item : result)
                    std::cout << item << " ";
                std::cout << std::endl;
                break;
            }
            case 5:
            {
                std::cout << "Оптимальная точка: " << find_optimal(graph) << std::endl;
                break;
            }
            case 0:
                return 0;
            default:
                std::cout << "Неверная команда" << std::endl;
        }
    }
    return 0;
}
