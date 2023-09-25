/*
 * Author: Abbas Raza
 * Creation Date: 26-09-2023
 */

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>

/**
 * @brief A singleton class that manages configuration settings loaded from a file.
 */
class ConfigurationManager {
public:
    /**
     * @brief Returns the singleton instance of ConfigurationManager.
     * 
     * @return ConfigurationManager& The singleton instance of ConfigurationManager.
     */
    static ConfigurationManager& getInstance() {
        static ConfigurationManager instance;
        return instance;
    }

    /**
     * @brief Loads configuration settings from a file.
     * 
     * @param configFile The path to the configuration file.
     */
    void loadConfiguration(const std::string& configFile) {
        std::ifstream file(configFile);
        if (file.is_open()) {
            settings.clear();
            std::string line;
            while (std::getline(file, line)) {
                // Parse and store configuration settings
                size_t pos = line.find('=');
                if (pos != std::string::npos) {
                    std::string key = line.substr(0, pos);
                    std::string value = line.substr(pos + 1);
                    settings[key] = value;
                }
            }
            file.close();
        }
    }

    /**
     * @brief Returns the value of a configuration setting.
     * 
     * @param key The key of the configuration setting.
     * @return std::string The value of the configuration setting.
     */
    std::string getValue(const std::string& key) {
        if (settings.find(key) != settings.end()) {
            return settings[key];
        }
        return ""; // Default value if key not found
    }

private:
    ConfigurationManager() {} // Private constructor
    ConfigurationManager(const ConfigurationManager&) = delete;
    ConfigurationManager& operator=(const ConfigurationManager&) = delete;

    std::unordered_map<std::string, std::string> settings;
};

/**
 * @brief The main function that uses ConfigurationManager to load and access configuration settings.
 * 
 * @return int The exit status of the program.
 */
int main() {
    ConfigurationManager& configManager = ConfigurationManager::getInstance();

    // Load configuration settings from a file
    configManager.loadConfiguration("config.txt");

    // Access and use configuration settings
    std::string databaseHost = configManager.getValue("DatabaseHost");
    std::string apiKey = configManager.getValue("ApiKey");

    std::cout << "Database Host: " << databaseHost << std::endl;
    std::cout << "API Key: " << apiKey << std::endl;

    return 0;
}

/*

Output:
Database Host: localhost
API Key: your-api-key-here

*/