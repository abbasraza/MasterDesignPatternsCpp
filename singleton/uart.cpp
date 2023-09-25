/*
 * Author: Abbas Raza
 * Creation Date: 26-09-2023
 */

#include <iostream>
#include <mutex>

/**
 * @brief Singleton class for UART communication.
 * 
 * This class provides a thread-safe implementation of UART communication.
 * It uses lazy initialization to create a single instance of the class.
 * The class provides methods to configure, send and receive data via UART.
 */
class UART {
public:
    /**
     * @brief Returns the singleton instance of the UART class.
     * 
     * This method returns the singleton instance of the UART class.
     * It uses lazy initialization to create the instance.
     * 
     * @return UART& - Reference to the singleton instance of the UART class.
     */
    static UART& getInstance() {
        static UART instance; // Lazy initialization
        return instance;
    }

    /**
     * @brief Configures the UART with the specified baud rate.
     * 
     * This method configures the UART with the specified baud rate.
     * It uses a mutex lock for thread safety.
     * 
     * @param baudRate - The baud rate to configure the UART with.
     */
    void configure(int baudRate) {
        std::lock_guard<std::mutex> lock(mutex); // Lock for thread safety
        // Perform hardware-specific UART configuration
        std::cout << "UART configured with baud rate " << baudRate << std::endl;
    }

    /**
     * @brief Sends data via UART.
     * 
     * This method sends data via UART.
     * It uses a mutex lock for thread safety.
     * 
     * @param data - The data to be transmitted via UART.
     */
    void sendData(const std::string& data) {
        std::lock_guard<std::mutex> lock(mutex); // Lock for thread safety
        // Transmit data via UART
        std::cout << "Transmitted data: " << data << std::endl;
    }

    /**
     * @brief Receives data via UART.
     * 
     * This method receives data via UART.
     * It uses a mutex lock for thread safety.
     * 
     * @return std::string - The data received via UART.
     */
    std::string receiveData() {
        std::lock_guard<std::mutex> lock(mutex); // Lock for thread safety
        // Receive data via UART (placeholder)
        std::string receivedData = "Received data from UART";
        std::cout << "Received data: " << receivedData << std::endl;
        return receivedData;
    }

private:
    /**
     * @brief Private constructor for the UART class.
     * 
     * This constructor initializes the UART hardware.
     */
    UART() {
        // Initialize UART hardware
    }

    UART(const UART&) = delete;
    UART& operator=(const UART&) = delete;

    std::mutex mutex; /**< Mutex for thread safety. */
};

/**
 * @brief Main function to test the UART class.
 * 
 * This function creates an instance of the UART class and tests its methods.
 * 
 * @return int - Returns 0 on successful execution.
 */
int main() {
    UART& uart = UART::getInstance();

    uart.configure(9600); // Configure UART with a baud rate of 9600
    uart.sendData("Hello, UART!"); // Send data via UART
    std::string receivedData = uart.receiveData(); // Receive data via UART

    return 0;
}
