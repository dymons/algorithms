#include "algorithms/AlgorithmsSort.hpp"

#include <iostream>
#include <random>
#include <vector>

#include <gtest/gtest.h>

class AlgorithmsSortTests : public ::testing::Test { };

TEST_F(AlgorithmsSortTests, insertion_sort_full)
{
  std::vector<int> full_reverse_sequence { };

  // instance
  for(int i = 10000; i > 0; --i) {
    full_reverse_sequence.push_back(i);
  }

  algorithms::insertion_sort(full_reverse_sequence.begin(), full_reverse_sequence.end());
  EXPECT_TRUE(std::is_sorted(full_reverse_sequence.begin(), full_reverse_sequence.end()));
}

TEST_F(AlgorithmsSortTests, insertion_sort_forward)
{
  // From: https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
  std::vector<int> mt19937_sequence { };
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<> distribution(0, 9999);
  std::generate_n(std::inserter(mt19937_sequence, mt19937_sequence.end()), 10000, [&](){return distribution(generator);});

  algorithms::insertion_sort(mt19937_sequence.begin(), mt19937_sequence.end());
  EXPECT_TRUE(std::is_sorted(mt19937_sequence.begin(), mt19937_sequence.end()));
  EXPECT_TRUE(!std::is_sorted(mt19937_sequence.rbegin(), mt19937_sequence.rend()));
}

TEST_F(AlgorithmsSortTests, insertion_sort_backward)
{
  // From: https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
  std::vector<int> mt19937_sequence { };
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<> distribution(0, 9999);
  std::generate_n(std::inserter(mt19937_sequence, mt19937_sequence.end()), 10000, [&](){return distribution(generator);});

  algorithms::insertion_sort(mt19937_sequence.rbegin(), mt19937_sequence.rend());
  EXPECT_TRUE(!std::is_sorted(mt19937_sequence.begin(), mt19937_sequence.end()));
  EXPECT_TRUE(std::is_sorted(mt19937_sequence.rbegin(), mt19937_sequence.rend()));
}

TEST_F(AlgorithmsSortTests, selection_sort_full)
{
  std::vector<int> full_reverse_sequence { };

  // instance
  for(int i = 10000; i > 0; --i) {
    full_reverse_sequence.push_back(i);
  }

  algorithms::selection_sort(full_reverse_sequence.begin(), full_reverse_sequence.end());
  EXPECT_TRUE(std::is_sorted(full_reverse_sequence.begin(), full_reverse_sequence.end()));
}

TEST_F(AlgorithmsSortTests, selection_sort_forward)
{
  std::vector<int> mt19937_sequence { };
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<> distribution(0, 9999);
  std::generate_n(std::inserter(mt19937_sequence, mt19937_sequence.end()), 10000, [&](){return distribution(generator);});

  algorithms::selection_sort(mt19937_sequence.begin(), mt19937_sequence.end());
  EXPECT_TRUE(std::is_sorted(mt19937_sequence.begin(), mt19937_sequence.end()));
  EXPECT_TRUE(!std::is_sorted(mt19937_sequence.rbegin(), mt19937_sequence.rend()));
}

TEST_F(AlgorithmsSortTests, selection_sort_backward)
{
  std::vector<int> mt19937_sequence { };
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<> distribution(0, 9999);
  std::generate_n(std::inserter(mt19937_sequence, mt19937_sequence.end()), 10000, [&](){return distribution(generator);});

  algorithms::selection_sort(mt19937_sequence.rbegin(), mt19937_sequence.rend());
  EXPECT_TRUE(!std::is_sorted(mt19937_sequence.begin(), mt19937_sequence.end()));
  EXPECT_TRUE(std::is_sorted(mt19937_sequence.rbegin(), mt19937_sequence.rend()));
}

TEST_F(AlgorithmsSortTests, merge_sort_full)
{
  std::vector<int> full_reverse_sequence { };

  // instance
  for(int i = 10000; i > 0; --i) {
    full_reverse_sequence.push_back(i);
  }

  algorithms::merge_sort(full_reverse_sequence.begin(), full_reverse_sequence.end());
  EXPECT_TRUE(std::is_sorted(full_reverse_sequence.begin(), full_reverse_sequence.end()));
}

TEST_F(AlgorithmsSortTests, merge_sort_forward)
{
  std::vector<int> mt19937_sequence { };
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<> distribution(0, 9999);
  std::generate_n(std::inserter(mt19937_sequence, mt19937_sequence.end()), 10000, [&](){return distribution(generator);});

  algorithms::merge_sort(mt19937_sequence.begin(), mt19937_sequence.end());
  EXPECT_TRUE(std::is_sorted(mt19937_sequence.begin(), mt19937_sequence.end()));
  EXPECT_TRUE(!std::is_sorted(mt19937_sequence.rbegin(), mt19937_sequence.rend()));
}

TEST_F(AlgorithmsSortTests, merge_sort_backward)
{
  std::vector<int> mt19937_sequence { };
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<> distribution(0, 9999);
  std::generate_n(std::inserter(mt19937_sequence, mt19937_sequence.end()), 10000, [&](){return distribution(generator);});

  algorithms::merge_sort(mt19937_sequence.rbegin(), mt19937_sequence.rend());
  EXPECT_TRUE(!std::is_sorted(mt19937_sequence.begin(), mt19937_sequence.end()));
  EXPECT_TRUE(std::is_sorted(mt19937_sequence.rbegin(), mt19937_sequence.rend()));
}

TEST_F(AlgorithmsSortTests, bubble_sort_full)
{
  std::vector<int> full_reverse_sequence { utility::generator<std::vector<int>>(10000, 0) };

  algorithms::bubble_sort(full_reverse_sequence.begin(), full_reverse_sequence.end());
  EXPECT_TRUE(std::is_sorted(full_reverse_sequence.begin(), full_reverse_sequence.end()));
}