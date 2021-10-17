#include <catch2/catch.hpp>
#include <vector>
#include <algorithm>

#include <heap_sort.hpp>

TEST_CASE("Сортировка c использованием алгоритма пирамидальной сортировки",
          "[heap_sort]") {
  using Testcase = std::vector<int>;
  using Testcases = std::vector<Testcase>;

  // clang-format off
  Testcases testcases
  {
      {},
      {1},
      {2,1},
      {3,1,2},
      {1, 2, 3, 4, 5},
      {10, 9, 8, 7, 6},
      {-5, 10, -3, 2, -8, 15, 4, 0, 0, -5, 4},
      {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
  };
  // clang-format on

  for (Testcase& testcase : testcases) {
    algo::sort::HeapSort(testcase);
    REQUIRE(std::is_sorted(testcase.begin(), testcase.end()));
  }
}