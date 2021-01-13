#include "logger.hpp"

Logger& getLogger() {
    static auto logger = new Logger((ModInfo){ID, VERSION});
    return *logger;
}
