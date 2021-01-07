#include "logger.hpp"

const Logger& getLogger() {
    static const Logger logger((ModInfo){ID, VERSION});
    return logger;
}
