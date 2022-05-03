#include "catch2/catch.hpp"

#include <dsac/concurrency/coroutines/futures/awaiter.hpp>
#include <dsac/concurrency/coroutines/futures/promise.hpp>
#include <dsac/concurrency/executors/static_thread_pool.hpp>
#include <dsac/concurrency/futures/async_via.hpp>
#include <dsac/concurrency/futures/future.hpp>

using namespace dsac::concurrency;

dsac::Future<int> Coroutine(IExecutorPtr executor) {
  dsac::Future<int> future = dsac::AsyncVia(executor, []() { return 42; });
  co_return co_await std::move(future);
}

TEST_CASE("Stackless coroutine C++", "[awaiter]") {
  constexpr const std::size_t kNumberWorkers = 4U;
  auto                        executor(StaticThreadPool::Make(kNumberWorkers));

  auto future = Coroutine(executor);
  REQUIRE(std::move(future).Get().ValueOrThrow() == 42);

  executor->Join();
}