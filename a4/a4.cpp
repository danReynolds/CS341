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

  // Create all of the disks
  for (int i = 0; i < n; i++) {
    std::cin >> points[i].x;
    std::cin >> points[i].y;
    std::cin >> points[i].radius;
    points[i].color = 0;
  }

  // Determine all of the adjacencies for each disk, 
  // adding them to the list of adjacencies for that disk.
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j && pow(points[i].x - points[j].x, 2.0) + pow(points[i].y - points[j].y, 2.0) <= pow(points[i].radius + points[j].radius, 2.0)) {
        points[i].adjacencies.push_back(j);
      }
    }
  }

  // Run BFS on each separate component.
  // A "visited" node is represented by having a non-zero color.
  for (int x = 0; x < n; x++) {
    if (!points[x].color) {
      points[x].color = 1;
      bfsq.push_back(points[x]);
    }
    else {
      break;
    }

    // Create the BFS for this component
    while(!bfsq.empty()) {
      cur = bfsq.front();
      bfsq.pop_front();

      // Add the adjacencies for the current node to the BFS queue
      for (std::vector<int>::iterator it = cur.adjacencies.begin(); it != cur.adjacencies.end(); it++) {
        // If the node is unvisited, assign it a color.
        if (!points[*it].color) {
          points[*it].color = cur.color % 2 + 1;

          bfsq.push_back(points[*it]);
        }
        // If the node has been visited, then if it shares our color, no bipartition can be formed.
        else if (points[*it].color == cur.color) {
          std::cout << 0;
          return 0;
        }
      }
    }
  }

  // Print out the bipartitions
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

