#include <iostream>
#include <vector>
#include <string>
#include <mutex>

class DatabaseConnection {
    // Simulated database connection class
public:
    DatabaseConnection(const std::string& connectionString) : connectionString(connectionString) {
        // Initialize the connection here
    }

    void executeQuery(const std::string& query) {
        // Execute a database query
        std::cout << "Executing query: " << query << std::endl;
    }

private:
    std::string connectionString;
};

class DatabaseConnectionPool {
public:
    static DatabaseConnectionPool& getInstance() {
        static DatabaseConnectionPool instance; // Lazy initialization
        return instance;
    }

    DatabaseConnection& getConnection() {
        std::lock_guard<std::mutex> lock(mutex); // Lock for thread safety

        if (availableConnections.empty()) {
            // If no connections are available, create a new one
            std::string connectionString = "your_database_connection_string_here";
            connections.push_back(DatabaseConnection(connectionString));
            return connections.back();
        } else {
            // Reuse an available connection
            DatabaseConnection& connection = availableConnections.back();
            availableConnections.pop_back();
            return connection;
        }
    }

    void releaseConnection(DatabaseConnection& connection) {
        std::lock_guard<std::mutex> lock(mutex); // Lock for thread safety
        availableConnections.push_back(connection);
    }

private:
    DatabaseConnectionPool() {
        // Initialize the connection pool with a few connections
        for (int i = 0; i < initialPoolSize; ++i) {
            std::string connectionString = "your_database_connection_string_here";
            connections.push_back(DatabaseConnection(connectionString));
            availableConnections.push_back(connections.back());
        }
    }

    DatabaseConnectionPool(const DatabaseConnectionPool&) = delete;
    DatabaseConnectionPool& operator=(const DatabaseConnectionPool&) = delete;

    std::vector<DatabaseConnection> connections;
    std::vector<DatabaseConnection> availableConnections;
    std::mutex mutex;
    const int initialPoolSize = 5; // Initial number of connections in the pool
};

int main() {
    DatabaseConnectionPool& pool = DatabaseConnectionPool::getInstance();

    // Get a database connection
    DatabaseConnection& connection1 = pool.getConnection();
    connection1.executeQuery("SELECT * FROM Customers");

    // Release the connection when done
    pool.releaseConnection(connection1);

    // Get another connection (which might be the same one)
    DatabaseConnection& connection2 = pool.getConnection();
    connection2.executeQuery("INSERT INTO Orders VALUES (...)");

    // Release the connection when done
    pool.releaseConnection(connection2);

    return 0;
}
