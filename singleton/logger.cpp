
/*
 * Author: Abbas Raza
 * Creation Date: 26-09-2023
 */

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>

/**
 * @brief A Logger class that provides a thread-safe way to log messages to a file.
 */
/**
 * @brief A singleton class that logs messages to a file.
 * 
 * This class provides a thread-safe way to log messages to a file.
 * It uses the Singleton design pattern to ensure that only one instance of the class is created.
 */
class Logger {
public:
    /**
     * @brief Logs a message to the log file.
     * 
     * @param message The message to be logged.
     */
    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex); // Lock to ensure thread safety
        logFile << message << std::endl;
    }

    /**
     * @brief Gets the single instance of the Logger class.
     * 
     * @return A reference to the Logger instance.
     */
    static Logger& getInstance() {
        static Logger instance; // Lazy initialization
        return instance;
    }

private:
    /**
     * @brief Private constructor to prevent external instantiation.
     * 
     * Opens the log file in append mode.
     */
    Logger() {
        logFile.open("application.log", std::ios::app); // Open log file in append mode
    }

    // The copy constructor and assignment operator
    // are defined as deleted, which means that you
    // can't make a copy of singleton.

    /**
     * @brief Private copy constructor to prevent cloning.
     */
    Logger(const Logger&) = delete;

    /**
     * @brief Private assignment operator to prevent cloning.
     */
    Logger& operator=(const Logger&) = delete;

    std::ofstream logFile; // Log file stream
    std::mutex mutex;      // Mutex for thread safety
};

/**
 * @brief The main function that demonstrates the usage of the Logger class.
 * 
 * Creates two instances of the Logger class and logs messages using them.
 * Checks if the two instances are the same.
 * 
 * @return 0 on success.
 */
int main() {
    Logger& logger = Logger::getInstance();

    logger.log("This is a log message.");
    logger.log("Another log message.");

    Logger& logger2 = Logger::getInstance();
    logger2.log("Another log message from logger2 instance");

    if (&logger == &logger2)
        std::cout << "logger and logger2 are the same instance" << std::endl;
    else
        std::cout << "logger and logger2 are not the same instance" << std::endl;
    
    return 0;
}

/* Output:
getInstance called
Logger instance created
getInstance called
logger and logger2 are the same instance
*/