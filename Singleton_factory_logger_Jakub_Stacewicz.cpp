#include <iostream>
#include <vector>
#include <memory>
#include <string>
 
// Klasa Logger - tutaj robimy Singletona
// Logger to taka klasa, która zapisuje wszystkie logi (czyli wiadomości o działaniu programu).
// Singleton oznacza, że mamy tylko jeden taki Logger w całym programie.
class Logger {
private:
    static std::shared_ptr<Logger> instance; // Tutaj trzymamy jedyną instancję Loggera
    std::vector<std::string> logs;          // Lista wszystkich logów, które zapiszemy
 
    Logger() {} // Konstruktor prywatny, żeby nikt nie mógł sobie tworzyć Loggera poza klasą
 
public:
    // Funkcja do pobrania tej jedynej instancji Loggera
    static std::shared_ptr<Logger> getInstance() {
        if (!instance) {
            // Jak jeszcze nie ma Loggera, to go tworzymy
            instance = std::shared_ptr<Logger>(new Logger());
        }
        return instance;
    }
 
    // Funkcja, która dodaje log do listy
    // type - typ logu (info, warning, error)
    // message - treść logu
    void logMessage(const std::string& type, const std::string& message) {
        std::string fullMessage = "[" + type + "] " + message; // Składamy typ + treść
        logs.push_back(fullMessage); // Wrzucamy log do listy
    }
 
    // Wyświetlanie wszystkich logów, które zapisaliśmy
    void displayLogs() const {
        for (const auto& log : logs) {
            std::cout << log << "\n"; // po kolei, pokazanie wszystkich logów
        }
    }
};
 
// Statyczna zmienna Loggera - na start jest pusta (nullptr)
std::shared_ptr<Logger> Logger::instance = nullptr;
 
// Klasa bazowa dla wszystkich logów
// To taka podstawka dla różnych typów logów, np. InfoLog, WarningLog
class Log {
public:
    virtual ~Log() = default;                      // Wirtualny destruktor 
    virtual std::string getMessage() const = 0;    // Funkcja, która zwraca treść logu - tutaj jest abstrakcyjna
};
 
// Klasa logów typu Info - czyli zwykłe informacje
class InfoLog : public Log {
    std::string message;
public:
    explicit InfoLog(const std::string& msg) : message("INFO: " + msg) {} // Dodajemy "INFO: " do treści
    std::string getMessage() const override { return message; } // Zwracamy gotowy tekst logu
};
 
// Klasa logów typu Warning - ostrzeżenia
class WarningLog : public Log {
    std::string message;
public:
    explicit WarningLog(const std::string& msg) : message("WARNING: " + msg) {} // Dodajemy "WARNING: "
    std::string getMessage() const override { return message; } // Zwracamy gotowy tekst logu
};
 
// Klasa logów typu Error - błędy
class ErrorLog : public Log {
    std::string message;
public:
    explicit ErrorLog(const std::string& msg) : message("ERROR: " + msg) {} // Dodajemy "ERROR: "
    std::string getMessage() const override { return message; } // Zwracamy gotowy tekst logu
};
 
// Fabryka logów - coś jak "taśma produkcyjna"
// W zależności od podanego typu (info/warning/error) tworzymy odpowiedni log
class LogFactory {
public:
    static std::shared_ptr<Log> createLog(const std::string& type, const std::string& message) {
        if (type == "info") {
            return std::make_shared<InfoLog>(message);    // Tworzymy InfoLog
        } else if (type == "warning") {
            return std::make_shared<WarningLog>(message); // Tworzymy WarningLog
        } else if (type == "error") {
            return std::make_shared<ErrorLog>(message);   // Tworzymy ErrorLog
        }
        return nullptr; // Jak coś pójdzie nie tak, to zwracamy nullptr
    }
};
 
int main() {
    auto logger = Logger::getInstance(); // Pobieramy naszego jedynego Loggera
 
    int choice = 0; // Opcja wybrana w menu
    while (choice != 3) {
        // Menu dla użytkownika
        std::cout << "Menu:\n";
        std::cout << "1. Dodaj log\n";
        std::cout << "2. Wyswietl logi\n";
        std::cout << "3. Wyjdz\n";
        std::cout << "Wybierz opcje: ";
        std::cin >> choice;
 
        if (choice == 1) {
            std::string type, message;
            std::cout << "Podaj typ logu (info/warning/error): ";
            std::cin >> type;
            std::cin.ignore(); // Czyścimy bufor wejścia
            std::cout << "Podaj tresc logu: ";
            std::getline(std::cin, message);
 
            // Tworzymy log przy pomocy fabryki
            auto log = LogFactory::createLog(type, message);
            if (log) {
                // Dodajemy log do Loggera
                logger->logMessage(type, log->getMessage());
            } else {
                std::cerr << "Nieprawidlowy typ logu: " << type << "\n";
            }
        } else if (choice == 2) {
            logger->displayLogs(); // Wyświetlamy wszystkie logi
        } else if (choice != 3) {
            std::cerr << "Nieprawidlowy wybor. Sprobuj ponownie.\n";
        }
    }
 
    return 0; // Zakończenie programu
}