#include "graph.h"

// Задача 2. Пусть дан связный граф, в котором узлы – это торговые точки.
// Необходимо превратить одну из торговых точек в склад. Цена доставки от склада в точку зависит
// от расстояния. Найдите оптимальную с точки зрения максимальных затрат точку
// (т.е. точку, для которой максимальное расстояние до любой другой точки минимально).

// функция для поиска оптимальной вершины графа
// алгоритм Беллмана-Форда
template<typename Vertex, typename Distance = double>
Vertex find_optimal(const Graph<Vertex, Distance>& graph) {
    if (graph.order() == 0)
        throw std::invalid_argument("Ошибка! Пустой граф не имеет центра.\n");
    // инициализация
    std::unordered_map<Vertex, Distance> distances;
    for (auto& item : graph.vertices())
        distances[item] = std::numeric_limits<Distance>::max();
    // произвольная вершина
    Vertex start = graph.vertices()[0];
    distances[start] = 0;
    // алгоритм
    for (size_t i = 0; i < graph.order() - 1; ++i)
        for (auto& item : graph.vertices())
            for (auto& item2 : graph.edges(item))
                if (distances[item2.from] + item2.distance < distances[item2.to])
                    distances[item2.to] = distances[item2.from] + item2.distance;
    // поиск максимального расстояния
    Distance max_distance = 0;
    for (auto& item : distances)
        if (item.second > max_distance)
            max_distance = item.second;
    // поиск вершины с минимальным максимальным расстоянием
    Vertex result;
    Distance min_max_distance = std::numeric_limits<Distance>::max();
    for (auto& item : distances)
        if (item.second < min_max_distance) {
            min_max_distance = item.second;
            result = item.first;
        }
    return result;
}

// меню1
void text_menu1(){
    std::cout << "\n[1] Создать случайный граф\n"
              << "[2] Вывод графа\n"
              << "[3] Поиск кратчайшего пути (Беллман-Форд)\n"
              << "[4] Обход в глубину\n"
              << "[5] Задача(2)\n"
              << "[6] Конфигурация графа\n"
              << "[0] Выход\n"
              << "--> ";
}

// меню2
void text_menu2(){
    std::cout << "\n[1] Добавить ребро/вершину\n"
              << "[2] Проверить ребро/вершину\n"
              << "[3] Удалить ребро/вершину\n"
              << "[4] Получить все ребра, выходящих из вершины\n"
              << "[5] Порядок графа\n"
              << "[6] Степень графа\n"
              << "[0] Назад в главное меню\n"
              << "--> ";
}

int main() {
    Graph<int, double> graph;
    while (true){
        text_menu1();
        int command;
        std::cin >> command;
        switch (command) {
            case 1:
            {
                std::cout << "Введите количество вершин: ";
                size_t count;
                std::cin >> count;
                // генерация случайного графа
                graph.generate_random_graph(count);
                break;
            }
            case 2:
            {
                std::cout << "Вывод графа:\n" << std::endl;
                graph.print();
                break;
            }
            case 3:
            {
                std::cout << "Введите начальную вершину: ";
                int start_from;
                std::cin >> start_from;
                std::cout << "Введите конечную вершину: ";
                int end_to;
                std::cin >> end_to;
                std::cout << "Кратчайший путь: " << std::endl;
                auto vector = graph.shortest_path(start_from, end_to);
                for (auto item : vector)
                    std::cout << item.from << "->" << item.to << " " << item.distance << std::endl;
                std::cout << std::endl;
                break;
            }
            case 4:
            {
                std::cout << "Введите начальную вершину: ";
                int start_from;
                std::cin >> start_from;
                std::cout << "Обход в глубину: " << std::endl;
                auto vector = graph.walk(start_from);
                for (auto i : vector)
                    std::cout << i << "->";
                std::cout << std::endl;
                break;
            }
            case 5:
            {
                std::cout << "Оптимальная вершина: " << find_optimal(graph) << std::endl;
                break;
            }
            case 6:
            {
                while (true){
                    text_menu2();
                    int command2;
                    std::cin >> command2;
                    if (command2 == 0)
                        break;
                    switch (command2) {
                        case 1:
                        {
                            while (true){
                                std::cout << "[1] Добавить вершину\n"
                                          << "[2] Добавить ребро\n"
                                          << "[0] Назад\n"
                                          << "--> ";
                                int command3;
                                std::cin >> command3;
                                if (command3 == 0){
                                    text_menu2();
                                    break;
                                }

                                switch (command3) {
                                    case 1:
                                    {
                                        std::cout << "Введите вершину: ";
                                        int vertex;
                                        std::cin >> vertex;
                                        graph.add_vertex(vertex);
                                        break;
                                    }
                                    case 2:
                                    {
                                        std::cout << "Введите начальную вершину: ";
                                        int start_vertex;
                                        std::cin >> start_vertex;
                                        std::cout << "Введите конечную вершину: ";
                                        int end_vertex;
                                        std::cin >> end_vertex;
                                        std::cout << "Введите вес ребра: ";
                                        double weight;
                                        std::cin >> weight;
                                        graph.add_edge(start_vertex, end_vertex, weight);
                                        break;
                                    }
                                    case 0:
                                    {
                                        break;
                                    }
                                    default:
                                    {
                                        std::cout << "Неверная команда!\n";
                                        break;
                                    }
                                }
                            }
                            break;
                        }
                        case 2:
                        {
                            while (true){
                                std::cout << "[1] Проверить вершину\n"
                                          << "[2] Проверить ребро\n"
                                          << "[0] Назад\n"
                                          << "--> ";
                                int command3;
                                std::cin >> command3;
                                if (command3 == 0){
                                    text_menu2();
                                    break;
                                }
                                switch (command3) {
                                    case 1:
                                    {
                                        std::cout << "Введите вершину: ";
                                        int vertex;
                                        std::cin >> vertex;
                                        if (graph.has_vertex(vertex))
                                            std::cout << "Вершина есть в графе!\n";
                                        else
                                            std::cout << "Вершины нет в графе!\n";
                                        break;
                                    }
                                    case 2:
                                    {
                                        std::cout << "Введите начальную вершину: ";
                                        int start_vertex;
                                        std::cin >> start_vertex;
                                        std::cout << "Введите конечную вершину: ";
                                        int end_vertex;
                                        std::cin >> end_vertex;
                                        if (graph.has_edge(start_vertex, end_vertex))
                                            std::cout << "Ребро есть в графе!\n";
                                        else
                                            std::cout << "Ребра нет в графе!\n";
                                        break;
                                    }
                                    case 0:
                                    {
                                        break;
                                    }
                                    default:
                                    {
                                        std::cout << "Неверная команда!\n";
                                        break;
                                    }
                                }
                            }
                        }
                        case 3:
                        {
                            while (true){
                                std::cout << "[1] Удалить вершину\n"
                                          << "[2] Удалить ребро\n"
                                          << "[0] Назад\n"
                                          << "--> ";
                                int command3;
                                std::cin >> command3;
                                if (command3 == 0){
                                    text_menu2();
                                    break;
                                }
                                switch (command3) {
                                    case 1:
                                    {
                                        std::cout << "Введите вершину: ";
                                        int vertex;
                                        std::cin >> vertex;
                                        graph.remove_vertex(vertex);
                                        break;
                                    }
                                    case 2:
                                    {
                                        std::cout << "Введите начальную вершину: ";
                                        int start_vertex;
                                        std::cin >> start_vertex;
                                        std::cout << "Введите конечную вершину: ";
                                        int end_vertex;
                                        std::cin >> end_vertex;
                                        graph.remove_edge(start_vertex, end_vertex);
                                        break;
                                    }
                                    case 0:
                                    {
                                        break;
                                    }
                                    default:
                                    {
                                        std::cout << "Неверная команда!\n";
                                        break;
                                    }
                                }
                            }
                            break;
                        }
                        case 4:
                        {
                            std::cout << "Введите вершину: ";
                            int vertex;
                            std::cin >> vertex;
                            std::cout << "Все ребра вершины ("<< vertex << "): " << std::endl;
                            auto vector = graph.edges(vertex);
                            for (auto item : vector)
                                std::cout << item.from << "->" << item.to << " " << item.distance << std::endl;
                            break;
                        }
                        case 5:
                        {
                            std::cout << "Порядок графа: " << graph.order() << std::endl;
                            break;
                        }
                        case 6:
                        {
                            std::cout << "Степень графа: " << graph.degree() << std::endl;
                            break;
                        }
                        case 0:
                        {
                            break;
                        }
                        default:
                        {
                            std::cout << "Неверная команда!\n";
                            break;
                        }
                    }
                }
                break;
            }
            case 0:
            {
                std::cout << "Выход из программы!\n";
                return 0;
            }
            default:
            {
                std::cout << "Неверная команда!\n";
                break;
            }
        }

    }
    return 0;
}
