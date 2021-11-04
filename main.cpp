
#include "customQueue.cpp"
#include "headers.h"
#include "testCases.h"

class SimplePoint {
   public:
    int x, y, val;

    SimplePoint() { return; }

    SimplePoint(int ax, int ay, int aval) {
        x = ax;
        y = ay;
        val = aval;
    }
    bool in(std::vector<SimplePoint> array) {
        for (const SimplePoint &point : array) {
            if (point.x == x && point.y == y) {
                return true;
            }
        }
        return false;
    }
};
bool operator==(const SimplePoint &lhs, const SimplePoint &rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}
std::ostream &operator<<(std::ostream &os, const SimplePoint &m) {
    return os << "(" << m.x << "," << m.y << ")"
              << " " << m.val << std::endl;
}

class Point : public SimplePoint {
   public:
    int saldo = 0;
    SimplePoint simple;
    std::vector<SimplePoint> neighbors, history;

    Point(int ax, int ay, int aval) {
        x = ax;
        y = ay;
        val = aval;
        simple = SimplePoint(ax, ay, aval);
    }
    Point(SimplePoint temp) {
        x = temp.x;
        y = temp.y;
        val = temp.val;
        simple = SimplePoint(temp.x, temp.y, temp.val);
    }

    std::vector<SimplePoint> getNeighbors(
        const std::vector<std::vector<int>> *maze) {
        std::vector<SimplePoint> temp;
        if (x != 0) {
            temp.push_back(SimplePoint(x - 1, y, (*maze)[y][x - 1]));
        }
        if (x != (*maze)[0].size() - 1) {
            temp.push_back(SimplePoint(x + 1, y, (*maze)[y][x + 1]));
        }
        if (y != 0) {
            temp.push_back(SimplePoint(x, y - 1, (*maze)[y - 1][x]));
        }
        if (y != (*maze).size() - 1) {
            temp.push_back(SimplePoint(x, y + 1, (*maze)[y + 1][x]));
        }
        return temp;
    }
};

std::ostream &operator<<(std::ostream &os, Point &m) {
    return os << "(" << m.simple.x << "," << m.simple.y << ")"
              << " " << m.val << std::endl
              << m.neighbors.size();
}

class Timer {
   public:
    // m_StartTime = std::chrono::high_resolution_clock::now();
    Timer() { m_StartTime = std::chrono::high_resolution_clock::now(); }
    ~Timer() { stop(); }
    void stop() {
        auto endTime = std::chrono::high_resolution_clock::now();

        auto start =
            std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTime)
                .time_since_epoch()
                .count();
        auto end =
            std::chrono::time_point_cast<std::chrono::microseconds>(endTime)
                .time_since_epoch()
                .count();
        auto us = end - start;
        double ms = us * 0.001;
        double s = ms * 0.0001;
        std::cout << "ms: " << ms << std::endl;
    }

   private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
};

int answer(std::vector<std::vector<int>> maze) {
    Timer timer;
    Point startPoint = Point(0, 0, 0);
    startPoint.neighbors = startPoint.getNeighbors(&maze);
    // Queue queue(startPoint);
    std::vector<Point> queue({startPoint});
    while (!queue.empty()) {
        // Point activePoint = *queue.pop();
        Point activePoint = queue.back();
        queue.pop_back();
        activePoint.history.push_back(activePoint.simple);
        if (activePoint.x == maze[0].size() - 1 &&
            activePoint.y == maze.size() - 1) {
            return activePoint.history.size();
        }
        for (SimplePoint &neighbor : activePoint.neighbors) {
            if (!neighbor.in(activePoint.history)) {
                Point temp = Point(neighbor);
                temp.history = activePoint.history;
                temp.neighbors = temp.getNeighbors(&maze);
                if (neighbor.val == 0) {
                    temp.saldo = activePoint.saldo;
                    // queue.append(temp);
                    queue.push_back(temp);
                } else {
                    if (activePoint.saldo < 1) {
                        temp.saldo += 1;
                        // queue.append(temp);
                        queue.push_back(temp);
                    }
                }
            }
        }
    }
    return 100000;
}

int main() { std::cout << answer(maze6) << std::endl; }
