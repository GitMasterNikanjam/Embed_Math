/**
 * @file test_vector2.cpp
 * @brief Minimal standalone test for Vector2 (no gtest).
 *
 * Build (Linux/Mingw):
 *   mkdir -p ./bin && g++ -std=c++11 -O2 -Wall -Wextra test_vector2.cpp ../vector2.cpp -o ./bin/test_vector2
 *
 * Run:
 *   ./bin/test_vector2
 */

#include <iostream>
#include <cmath>
#include "../vector2.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static int g_fail = 0;

#define CHECK(cond, msg) do { \
  if (cond) std::cout << "[ OK ] " << msg << "\n"; \
  else { std::cerr << "[FAIL] " << msg << "\n"; ++g_fail; } \
} while (0)

static inline bool nearf(float a, float b, float tol=1e-4f) {
  return std::fabs(a-b) <= tol;
}

int main() {
  using V = Vector2f;

  std::cout << "=== Vector2 basic tests ===\n";

  // 1) length / normalize
  {
    V v{3.0f, 4.0f};
    CHECK(nearf(v.length(), 5.0f), "length(3,4) == 5");
    v.normalize();
    CHECK(nearf(v.length(), 1.0f, 1e-5f), "normalize sets length ~= 1");
  }

  // 2) dot / cross
  {
    V ex{1,0}, ey{0,1};
    CHECK(nearf(ex * ey, 0.0f), "dot((1,0),(0,1)) == 0");
    CHECK(nearf(ex % ey, 1.0f), "cross((1,0),(0,1)) == 1");
  }

  // 3) angle between vectors + angle of a vector
  {
    V ex{1,0}, ey{0,1};
    float a = ex.angle(ey);          // ~ pi/2
    CHECK(nearf(a, float(M_PI/2), 1e-5f), "angle((1,0),(0,1)) ~= pi/2");
    CHECK(nearf(ey.angle(), float(M_PI/2), 1e-5f), "angle((0,1)) ~= pi/2");
  }

  // 4) projection
  {
    V v{2,2}, axis{1,0};
    V p = v.projected(axis);         // should drop Y, keep X
    CHECK(nearf(p.x, 2.0f) && nearf(p.y, 0.0f), "projected((2,2) onto x-axis) -> (2,0)");
  }

  // 5) segment intersection
  {
    V s1a{0,0}, s1b{2,0};
    V s2a{1,-1}, s2b{1,1};
    V inter{};
    bool hit = V::segment_intersection(s1a, s1b, s2a, s2b, inter);
    CHECK(hit, "segment_intersection finds crossing");
    CHECK(nearf(inter.x, 1.0f) && nearf(inter.y, 0.0f), "intersection ~ (1,0)");
  }

  // 6) circle–segment intersection (center at origin, r=1)
  {
    V a{-2,0}, b{ 2,0}, c{0,0}, inter{};
    bool hit = V::circle_segment_intersection(a, b, c, 1.0f, inter);
    CHECK(hit, "circle_segment_intersection hits");
    // Your implementation returns the first valid root in [0,1]; for this setup
    // that's x~=+1. (Either +1 or -1 is acceptable for correctness.)
    CHECK(nearf(std::fabs(inter.x), 1.0f) && nearf(inter.y, 0.0f),
          "intersection lies on the unit circle on X axis");
  }

  // 7) closest point on segment
  {
    V p{2,1}, v{0,0}, w{4,0};
    V cp = V::closest_point(p, v, w);
    CHECK(nearf(cp.x, 2.0f) && nearf(cp.y, 0.0f), "closest_point to (2,1) on [0,0]-[4,0] is (2,0)");
  }

  // 8) rotate
  {
    V v{1,0};
    v.rotate(float(M_PI/2));
    CHECK(nearf(v.x, 0.0f, 1e-5f) && nearf(v.y, 1.0f, 1e-5f), "rotate (1,0) by 90deg -> (0,1)");
  }

  // 9) offset_bearing
  {
    V p{0,0};
    p.offset_bearing(0.0f,  1.0f);   // east
    p.offset_bearing(90.0f, 1.0f);   // north
    CHECK(nearf(p.x, 1.0f, 1e-4f) && nearf(p.y, 1.0f, 1e-4f), "offset_bearing 0° then 90° by 1 m each -> (1,1)");
  }

  std::cout << "=== Done. Failures: " << g_fail << " ===\n";
  return g_fail ? 1 : 0;
}
