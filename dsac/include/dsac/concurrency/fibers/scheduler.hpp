#pragma once

#include <dsac/memory/shared_ptr.hpp>

#include <dsac/concurrency/fibers/routine/routine.hpp>

namespace dsac {

class fiber_scheduler final {
public:
  // Constructors

  explicit fiber_scheduler(fiber_routine entry_routine);

  // Modifiers

  auto schedule() -> void;

  auto submit(fiber_routine routine) -> void;

private:
  class fiber_scheduler_pimpl;
  shared_ptr<fiber_scheduler_pimpl> pimpl_;
};

}  // namespace dsac
