#pragma once

#include <dsac/memory/shared_ptr.hpp>
#include "fwd.hpp"

namespace dsac {

/*!
    \brief
        Create a static thread pool.

    \param workers
        Number of worker threads in static thread pool

    \ingroup
        DsacConcurrency

    \code
        auto executor = dsac::make_static_thread_pool(4U);
        executor->submit([](){ do_some_work(); });
        executor->join();
    \endcode
*/
[[nodiscard]] auto make_static_thread_pool(std::size_t workers) -> dsac::shared_ptr<iexecutor>;

}  // namespace dsac
