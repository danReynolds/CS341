#include <iostream>
#include <vector>
#include <deque>
#include <math.h>

struct point {
  int x;
  int y;
  int radius;
  int color;
  std::vector<int> adjacencies;
};

int main() {
  int n;

  std::cin >> n;

  std::vector<point> points(n);
  std::deque<point> bfsq;
  point cur;

  for (int i = 0; i < n; i++) {
    std::cin >> points[i].x;
    std::cin >> points[i].y;
    std::cin >> points[i].radius;
    points[i].color = 0;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j && pow(points[i].x - points[j].x, 2.0) + pow(points[i].y - points[j].y, 2.0) <= pow(points[i].radius + points[j].radius, 2.0)) {
        points[i].adjacencies.push_back(j);
      }
    }
  }

  // Explore each separate BFS
  // A "visited" node is represented by having a non-zero color.
  for (int x = 0; x < n; x++) {
    if (!points[x].color) {
      points[x].color = 1;
      bfsq.push_back(points[x]);
    }
    else {
      break;
    }

    // Create BFS
    while(!bfsq.empty()) {
      cur = bfsq.front();
      bfsq.pop_front();

      for (std::vector<int>::iterator it = cur.adjacencies.begin(); it != cur.adjacencies.end(); it++) {
        if (!points[*it].color) {
          points[*it].color = cur.color % 2 + 1;

          bfsq.push_back(points[*it]);
        }
        else if (points[*it].color == cur.color) {
          std::cout << 0 << std::endl;
          return 0;
        }
      }
    }
  }

  for (std::vector<point>::iterator it = points.begin(); it != points.end(); it++) {
    if (it != points.end() - 1) {
      std::cout << it->color << " ";
    }
    else {
      std::cout << it->color << std::endl;
    }
  }

  return 0;
}

