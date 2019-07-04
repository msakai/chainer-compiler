#include "runtime/meminfo.h"

#ifdef CHAINER_COMPILER_ENABLE_CUDA
#include <cuda_runtime.h>
#endif  // CHAINER_COMPILER_ENABLE_CUDA

namespace chainer_compiler {
namespace runtime {

bool g_meminfo_enabled = false;

nonstd::optional<std::pair<int64_t, int64_t>> GetMemoryUsageInBytes() {
#ifdef CHAINER_COMPILER_ENABLE_CUDA
    if (!g_meminfo_enabled) return nonstd::nullopt;
    size_t free, total;
    if (cudaMemGetInfo(&free, &total) != cudaSuccess) {
        return nonstd::nullopt;
    }
    return std::pair<int64_t, int64_t>(total - free, total);
#else
    return nonstd::nullopt;
#endif  // CHAINER_COMPILER_ENABLE_CUDA
}

}  // namespace runtime
}  // namespace chainer_compiler
