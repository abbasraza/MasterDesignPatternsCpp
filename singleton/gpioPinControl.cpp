/*
 * Author: Abbas Raza
 * Creation Date: 26-09-2023
 */

/**
 * This program demonstrates the use of the Singleton design pattern to manage GPIO pins.
 * The GPIOPinControl class is a Singleton class that provides thread-safe access to the GPIO pins.
 * The class provides methods to configure and toggle the state of the GPIO pins.
 * The program initializes the GPIO pin configuration, configures a GPIO pin as OUTPUT, and toggles its state.
 */
#include <iostream>
#include <map>
#include <string>
#include <mutex>

// GPIO Pin Control Manager Singleton
class GPIOPinControl {
public:
    // Returns the singleton instance of the GPIOPinControl class
    static GPIOPinControl& getInstance() {
        static GPIOPinControl instance; // Lazy initialization
        return instance;
    }

    // Configures the specified GPIO pin with the given mode
    void configurePin(int pinNumber, const std::string& mode) {
        std::lock_guard<std::mutex> lock(mutex); // Lock for thread safety
        pinConfig[pinNumber] = mode;
        // Perform low-level hardware configuration for the GPIO pin
        std::cout << "Configured GPIO Pin " << pinNumber << " as " << mode << std::endl;
    }

    // Toggles the state of the specified GPIO pin
    void togglePin(int pinNumber) {
        std::lock_guard<std::mutex> lock(mutex); // Lock for thread safety
        if (pinConfig.find(pinNumber) != pinConfig.end()) {
            // Toggle the state of the GPIO pin
            std::cout << "Toggled GPIO Pin " << pinNumber << std::endl;
        } else {
            std::cout << "GPIO Pin " << pinNumber << " is not configured." << std::endl;
        }
    }

private:
    // Private constructor to prevent instantiation of the class
    GPIOPinControl() {
        // Initialize GPIO pin configuration
    }

    // Delete copy constructor and assignment operator to prevent copying of the class
    GPIOPinControl(const GPIOPinControl&) = delete;
    GPIOPinControl& operator=(const GPIOPinControl&) = delete;

    std::map<int, std::string> pinConfig; // Map to store the configuration of each GPIO pin
    std::mutex mutex; // Mutex to ensure thread safety
};

int main() {
    GPIOPinControl& gpioControl = GPIOPinControl::getInstance();

    // Configure and toggle GPIO pins
    gpioControl.configurePin(4, "OUTPUT");
    gpioControl.togglePin(4);

    return 0;
}
