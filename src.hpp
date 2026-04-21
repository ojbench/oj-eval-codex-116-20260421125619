// Implementation for Problem 116 - GreedySnake
#ifndef SRC_HPP
#define SRC_HPP

#include <iostream>
#include <utility>
#include <vector>

struct Map;
enum class instruction { UP, DOWN, LEFT, RIGHT, NONE };

// Helpers provided by the driver via free functions
bool is_food(Map* map, int x, int y);
bool is_wall(Map* map, int x, int y);
void eat_food(Map* map, int x, int y);
int get_height(Map* map);
int get_width(Map* map);

const int MaxWidth = 20;

struct Snake {
  // Body from head (index 0) to tail (last index)
  std::vector<std::pair<int, int>> body;
  // Current moving direction
  instruction dir = instruction::NONE;
  // Occupancy grid for fast self-collision checks
  bool occ[MaxWidth][MaxWidth]{};

  void clear_occ() {
    for (int i = 0; i < MaxWidth; ++i)
      for (int j = 0; j < MaxWidth; ++j)
        occ[i][j] = false;
  }

  void initialize(int x, int y, instruction ins) {
    // (x,y) is the position of the head, ins is initial orientation
    clear_occ();
    body.clear();
    body.emplace_back(x, y);
    if (x >= 0 && x < MaxWidth && y >= 0 && y < MaxWidth) {
      occ[x][y] = true;
    }
    dir = ins;
  }

  int get_length() {
    return static_cast<int>(body.size());
  }

  static bool is_opposite(instruction a, instruction b) {
    return (a == instruction::UP && b == instruction::DOWN) ||
           (a == instruction::DOWN && b == instruction::UP) ||
           (a == instruction::LEFT && b == instruction::RIGHT) ||
           (a == instruction::RIGHT && b == instruction::LEFT);
  }

  bool move(Map* map, instruction next) {
    // Reject immediate reverse direction
    if (next != instruction::NONE) {
      if (dir != instruction::NONE && is_opposite(dir, next)) {
        return false;
      }
      dir = next;
    }

    // Cannot move without a direction
    if (dir == instruction::NONE) return false;

    // Compute next head position
    int hx = body.front().first;
    int hy = body.front().second;
    int nx = hx, ny = hy;
    switch (dir) {
      case instruction::UP:    nx = hx - 1; break;
      case instruction::DOWN:  nx = hx + 1; break;
      case instruction::LEFT:  ny = hy - 1; break;
      case instruction::RIGHT: ny = hy + 1; break;
      default: break;
    }

    // Boundary check
    int H = get_height(map);
    int W = get_width(map);
    if (nx < 0 || nx >= H || ny < 0 || ny >= W) return false;

    // Wall check
    if (is_wall(map, nx, ny)) return false;

    bool will_grow = is_food(map, nx, ny);

    // Self-collision check (allow stepping into current tail if not growing)
    std::pair<int, int> tail = body.back();
    bool occupies = occ[nx][ny];
    if (occupies) {
      if (will_grow || (nx != tail.first || ny != tail.second)) {
        return false;
      }
    }

    // Move: add new head
    body.insert(body.begin(), {nx, ny});
    occ[nx][ny] = true;

    if (will_grow) {
      eat_food(map, nx, ny);
      // length increases, keep tail
    } else {
      // remove tail
      occ[tail.first][tail.second] = false;
      body.pop_back();
    }
    return true;
  }

  std::pair<int, std::pair<int, int>*> get_snake() {
    int len = get_length();
    auto* arr = new std::pair<int, int>[len];
    for (int i = 0; i < len; ++i) arr[i] = body[i];
    return {len, arr};
  }
};

struct Map {
  bool wall[MaxWidth][MaxWidth]{};
  bool food[MaxWidth][MaxWidth]{};
  int width = 0, height = 0;

  int get_height() { return height; }
  int get_width() { return width; }

  bool is_food(int x, int y) { return food[x][y]; }
  void eat_food(int x, int y) { food[x][y] = false; }
  bool is_wall(int x, int y) { return wall[x][y]; }

  void initialize(Snake* snake) {
    // Read height and width
    std::cin >> height >> width;
    // Clear arrays
    for (int i = 0; i < MaxWidth; ++i)
      for (int j = 0; j < MaxWidth; ++j) {
        wall[i][j] = false;
        food[i][j] = false;
      }

    char str[MaxWidth + 5];
    int head_x = -1, head_y = -1;
    for (int i = 0; i < height; ++i) {
      std::cin >> str;
      for (int j = 0; j < width; ++j) {
        char c = str[j];
        if (c == '#') wall[i][j] = true;
        else if (c == '*') food[i][j] = true;
        else if (c == '@') { head_x = i; head_y = j; }
        // '.' or other characters are treated as empty
      }
    }

    // Read initial direction
    std::cin >> str;
    instruction ins = instruction::NONE;
    switch (str[0]) {
      case 'U': ins = instruction::UP; break;
      case 'D': ins = instruction::DOWN; break;
      case 'L': ins = instruction::LEFT; break;
      case 'R': ins = instruction::RIGHT; break;
      default: ins = instruction::NONE; break;
    }

    snake->initialize(head_x, head_y, ins);
  }

  void print(Snake* snake) {
    // Build a buffer of the map
    std::vector<std::string> grid(height, std::string(width, '.'));
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        if (wall[i][j]) grid[i][j] = '#';
        else if (food[i][j]) grid[i][j] = '*';
      }
    }

    auto snake_body = snake->get_snake();
    int len = snake_body.first;
    auto* arr = snake_body.second;
    for (int idx = 0; idx < len; ++idx) {
      int x = arr[idx].first;
      int y = arr[idx].second;
      if (x >= 0 && x < height && y >= 0 && y < width) {
        grid[x][y] = (idx == 0 ? '@' : 'o');
      }
    }
    delete[] arr;

    for (int i = 0; i < height; ++i) {
      std::cout << grid[i] << std::endl;
    }
  }
};

struct Game {
  Map* map;
  Snake* snake;
  int score;
  int round;

  void initialize() {
    map = new Map();
    snake = new Snake();
    map->initialize(snake);
    score = 0;
    round = 0;
  }

  bool step() {
    char str[MaxWidth];
    if (!(std::cin >> str)) return false;
    instruction ins;
    switch (str[0]) {
      case 'U': ins = instruction::UP; break;
      case 'D': ins = instruction::DOWN; break;
      case 'L': ins = instruction::LEFT; break;
      case 'R': ins = instruction::RIGHT; break;
      default:  ins = instruction::NONE; break;
    }
    if (snake->move(map, ins)) {
      score++;
      return true;
    }
    return false;
  }

  void print() {
    std::cout << "Round: " << round << std::endl;
    map->print(snake);
  }

  void play() {
    while (step()) {
      round++;
      print();
    }
    score += snake->get_length();
    std::cout << "Game Over" << std::endl;
    std::cout << "Score: " << score << std::endl;
  }
};

#endif // SRC_HPP
