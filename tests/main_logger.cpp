#include "bonus/logger.hpp"

int main() {
    Logger logger;

    logger.info("Application started.");
    logger.warning("Low disk space.");
    logger.error("File not found.");

    logger.setLevel(Logger::WARNING);
    logger.info("This message will not be shown.");
    logger.warning("This is a warning.");
    logger.error("This is an error.");

    return 0;
}
