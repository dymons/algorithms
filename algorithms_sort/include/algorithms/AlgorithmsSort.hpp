#pragma once

#ifndef ALGORITHMS_ALGORITHMS_SORT_HPP_
#define ALGORITHMS_ALGORITHMS_SORT_HPP_

#include <deque>
#include <utility>
#include <iterator>
#include <algorithm>

namespace algorithms {
  template<class Iterator>
    void insertion_sort(Iterator t_begin, Iterator t_end)
    {
      // From: https://en.cppreference.com/w/cpp/algorithm/rotate
      for(Iterator itr = t_begin; itr != t_end; ++itr) {
        std::rotate(std::upper_bound(t_begin, itr, *itr), itr, std::next(itr));
      }
    }

  template<class Iterator>
    void selection_sort(Iterator t_begin, Iterator t_end)
    {
      for(Iterator itr = t_begin; itr != t_end; ++itr) {
        auto min = std::min_element(itr, t_end);
        std::swap(*itr, *min);
      }
    }

  template<class Iterator>
    void merge_sort(Iterator t_begin, Iterator t_end)
    {
      // Recursion ends when the sequence becomes 1
      if(std::distance(t_begin, t_end) < 2) {
        return;
      }

      Iterator middle = t_begin + static_cast<std::size_t>((std::distance(t_begin, t_end) / 2));
      merge_sort(t_begin, middle);
      merge_sort(middle, t_end);
      std::merge(t_begin, middle, middle, t_end, t_begin);
    }

  template<class Iterator>
    void bubble_sort(Iterator t_begin, Iterator t_end)
    {
      for(Iterator itr = t_begin; itr != t_end; ++itr) {
        for(Iterator it = t_begin; it != (t_end - std::distance(t_begin, itr)); ++it) {
          if(*it > *std::next(it)) {
            std::swap(*it, *std::next(it));
          }
        }
      }
    }
} // namespace algorithms
#endif // ALGORITHMS_ALGORITHMS_SORT_HPP_