#include <iostream>
#include <vector>
#include <limits>

struct point {
  int x;
  int y;
  int color;
  // 1 indicates blue
  // 0 indicates red
};

int dominanceCount(std::vector<point> points) {
  int total = 0;
  for (int x = 0; x < points.size(); x++) {
    for (int y = 0; y < points.size(); y++) {
      if (x != y && points[x].x > points[y].x && points[x].y > points[y].y && points[x].color == 0 && points[y].color == 1) {
        total++;
      }
    }
  }
  return total;
}

int main() {
  int n;

  std::cin >> n;

  std::vector<point> points(n);

  for (int i = 0; i < n; i++) {
    std::cin >> points[i].x;
    std::cin >> points[i].y;
    std::cin >> points[i].color;
  }

  std::cout << dominanceCount(points);

  return 0;
}