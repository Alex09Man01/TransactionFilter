#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream>

struct Transaction {
    std::string id;
    std::string data;
    std::string type;
    double sum;
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Please specify the name of the CSV file.\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Could not open the CSV file: " << argv[1] << "\n";
        return 1;
    }

    std::string line;
    std::vector<Transaction> transactionsInput;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, data, type, sumStr;

        std::getline(ss, id, ',');
        std::getline(ss, data, ',');
        std::getline(ss, type, ',');
        std::getline(ss, sumStr, ',');

        double sum = std::stod(sumStr);

        if (type == "INTRARE") {
            transactionsInput.push_back({id, data, type, sum});
        }
    }

    double total = 0;
    std::cout << "Filtered transactions:\n";

    for (const auto& tr : transactionsInput) {
        std::cout << tr.id << " | " << tr.data << " | "
              << std::fixed << std::setprecision(2) << tr.sum << "\n";
        total += tr.sum;
    }

    std::cout << "\nTotal INTRARE: " << std::fixed << std::setprecision(2) << total << "\n";
    return 0;
}
