#include "util.hpp"

namespace letMeSee
{
    size_t getNowTimestampMs()
    {
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        return timestamp.time_since_epoch().count();
    }

    size_t getNowTimestampMic()
    {
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch());
        return timestamp.count();
    }
}
