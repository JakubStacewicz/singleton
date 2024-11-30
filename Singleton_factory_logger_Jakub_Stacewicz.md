#include <iostream>
#include <vector>
#include <memory>
#include <string>
 
// Klasa Logger - tutaj ogarniamy Singletona
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
            std::cout << log << "\n"; // po kolei, pokazujemy logi
        }
    }
};
 
// Statyczna zmienna Loggera - na start jest pusta (nullptr)
std::shared_ptr<Logger> Logger::instance = nullptr;
 
// Klasa bazowa dla wszystkich logów
// np. InfoLog, WarningLog
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
 
// w tym miejscu tworzymi logi
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
 #include <iostream>
#include <vector>
#include <memory>
#include <string>
 
// Klasa Logger - Singleton
// Logger jest klasą odpowiedzialną za zarządzanie logami w aplikacji.
// Wzorzec Singleton zapewnia, że istnieje tylko jedna instancja tej klasy w programie.
class Logger {
private:
    static std::shared_ptr<Logger> instance; // Statyczna instancja klasy Logger (Singleton)
    std::vector<std::string> logs;          // Lista logów przechowywana wewnątrz Loggera
 
    Logger() {} // Prywatny konstruktor uniemożliwia tworzenie obiektów poza klasą
 
public:
    // Statyczna metoda zwracająca jedyną instancję Loggera
    static std::shared_ptr<Logger> getInstance() {
        if (!instance) {
            instance = std::shared_ptr<Logger>(new Logger()); // Tworzenie instancji przy pierwszym wywołaniu
        }
        return instance;
    }
 
    // Dodawanie logów do listy
    // Parametry:
    // - type: typ logu (info, warning, error)
    // - message: treść logu
    void logMessage(const std::string& type, const std::string& message) {
        std::string fullMessage = "[" + type + "] " + message;
        logs.push_back(fullMessage); // Dodanie logu do listy
    }
 
    // Wyświetlanie wszystkich logów zapisanych w Loggerze
    void displayLogs() const {
        for (const auto& log : logs) {
            std::cout << log << "\n"; // Wyświetlanie każdego logu
        }
    }
};
 
// Inicjalizacja statycznej instancji Loggera jako nullptr
std::shared_ptr<Logger> Logger::instance = nullptr;
 
// Klasa bazowa Log
// Reprezentuje wspólną podstawę dla wszystkich typów logów.
class Log {
public:
    virtual ~Log() = default;                      // Wirtualny destruktor
    virtual std::string getMessage() const = 0;    // Metoda abstrakcyjna zwracająca treść logu
};
 
// Klasa InfoLog
// Reprezentuje logi informacyjne.
class InfoLog : public Log {
    std::string message;
public:
    explicit InfoLog(const std::string& msg) : message("INFO: " + msg) {}
    std::string getMessage() const override { return message; } // Zwraca treść logu
};
 
// Klasa WarningLog
// Reprezentuje logi ostrzegawcze.
class WarningLog : public Log {
    std::string message;
public:
    explicit WarningLog(const std::string& msg) : message("WARNING: " + msg) {}
    std::string getMessage() const override { return message; } // Zwraca treść logu
};
 
// Klasa ErrorLog
// Reprezentuje logi błędów.
class ErrorLog : public Log {
    std::string message;
public:
    explicit ErrorLog(const std::string& msg) : message("ERROR: " + msg) {}
    std::string getMessage() const override { return message; } // Zwraca treść logu
};
 
// tutaj tworzą się logi LogFactory
// Tworzy obiekty różnych typów logów w zależności od podanego parametru.
class LogFactory {
public:
    // Metoda tworząca obiekt logu
    // Parametry:
    // - type: typ logu (info, warning, error)
    // - message: treść logu
    static std::shared_ptr<Log> createLog(const std::string& type, const std::string& message) {
        if (type == "info") {
            return std::make_shared<InfoLog>(message);    // Tworzenie logu informacyjnego
        } else if (type == "warning") {
            return std::make_shared<WarningLog>(message); // Tworzenie logu ostrzegawczego
        } else if (type == "error") {
            return std::make_shared<ErrorLog>(message);   // Tworzenie logu błędu
        }
        return nullptr; // Zwraca nullptr, jeśli typ jest nieznany
    }
};
 
int main() {
    auto logger = Logger::getInstance(); // Pobranie jedynej instancji Loggera
 
    int choice = 0; // Zmienna do wyboru opcji w menu
    while (choice != 3) {
        // Wyświetlanie menu użytkownika
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
            std::cin.ignore(); // Czyszczenie bufora wejścia
            std::cout << "Podaj tresc logu: ";
            std::getline(std::cin, message);
 
            // Tworzenie logu i dodanie go do Loggera
            auto log = LogFactory::createLog(type, message);
            if (log) {
                logger->logMessage(type, log->getMessage());
            } else {
                std::cerr << "Nieprawidlowy typ logu: " << type << "\n";
            }
        } else if (choice == 2) {
            logger->displayLogs(); // Wyświetlanie wszystkich logów
        } else if (choice != 3) {
            std::cerr << "Nieprawidlowy wybor. Sprobuj ponownie.\n";
        }
    }
 
    return 0; // Zakończenie programu
}
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
