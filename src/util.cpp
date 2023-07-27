#include "util.hpp"

namespace letMeSee
{
    size_t getNowTimestampMs()
    {
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto milliseconds = timestamp.time_since_epoch().count();
        return milliseconds;
    }
}
