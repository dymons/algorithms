#ifndef CONCURRENCY_ATOMIC_HPP
#error This file may only be included from atomic.hpp
#endif

extern "C" void atomic_store_seq_cst(volatile std::int64_t* cell, std::int64_t value);

extern "C" std::int64_t atomic_load_seq_cst(const volatile std::int64_t* cell);

extern "C" std::int64_t atomic_exchange_seq_cst(volatile std::int64_t* cell, std::int64_t value);

namespace dsac {

void atomic<std::int64_t>::store(value_type value, memory_order order) noexcept {
  switch (order) {
    case memory_order::memory_order_relaxed:
      break;
    case memory_order::memory_order_consume:
      break;
    case memory_order::memory_order_acquire:
      break;
    case memory_order::memory_order_release:
      break;
    case memory_order::memory_order_acq_rel:
      break;
    case memory_order::memory_order_seq_cst:
      atomic_store_seq_cst(&cell_, value);
      break;
  }
}

atomic<std::int64_t>::value_type atomic<std::int64_t>::load(memory_order order) const noexcept {
  switch (order) {
    case memory_order::memory_order_relaxed:
      break;
    case memory_order::memory_order_consume:
      break;
    case memory_order::memory_order_acquire:
      break;
    case memory_order::memory_order_release:
      break;
    case memory_order::memory_order_acq_rel:
      break;
    case memory_order::memory_order_seq_cst:
      break;
  }

  return atomic_load_seq_cst(&cell_);
}

auto atomic<std::int64_t>::exchange(value_type new_value, memory_order order) noexcept -> value_type {
  switch (order) {
    case memory_order::memory_order_relaxed:
      break;
    case memory_order::memory_order_consume:
      break;
    case memory_order::memory_order_acquire:
      break;
    case memory_order::memory_order_release:
      break;
    case memory_order::memory_order_acq_rel:
      break;
    case memory_order::memory_order_seq_cst:
      break;
  }

  return atomic_exchange_seq_cst(&cell_, new_value);
}

}  // namespace dsac
