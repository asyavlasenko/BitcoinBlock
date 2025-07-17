#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>

class Transaction {
public:
    Transaction(const std::string& id, int sz, int f) : tx_id(id), size(sz), fee(f) {}
    double feePerByte() const { return static_cast<double>(fee) / size; }
    int getSize() const { return size; }
    int getFee() const { return fee; }
    std::string getId() const { return tx_id; }

private:
    std::string tx_id;
    int size;
    int fee;
};

class BlockBuilder {
public:
    BlockBuilder(const std::string& filename, int maxSize = 1000000) : maxBlockSize(maxSize) {
        readTransactions(filename);
    }

    void build() {
        auto start = std::chrono::high_resolution_clock::now();

        std::sort(transactions.begin(), transactions.end(),
                  [](const Transaction& a, const Transaction& b) {
                      return a.feePerByte() > b.feePerByte();
                  });

        int currentSize = 0;
        totalFee = 0;
        for (const auto& tx : transactions) {
            if (currentSize + tx.getSize() <= maxBlockSize) {
                block.push_back(tx);
                currentSize += tx.getSize();
                totalFee += tx.getFee();
            }
        }

        totalSize = currentSize;
        auto end = std::chrono::high_resolution_clock::now();
        durationMs = std::chrono::duration<double, std::milli>(end - start).count();
    }

    void printResults() const {
        std::cout << "\n========== Bitcoin Block Construction Result ==========\n";
        std::cout << "Total transactions included: " << block.size() << "\n";
        std::cout << "Final block size: " << totalSize << " bytes (" << totalSize / 1000.0 << " KB)\n";
        std::cout << "Total extracted fee: " << totalFee << " satoshis\n";
        std::cout << "Block construction time: " << durationMs << " ms\n";
        std::cout << "Estimated memory used: ~" 
                  << sizeof(Transaction) * transactions.capacity() / 1024 
                  << " KB (approximate)\n";
        std::cout << "Greedy algorithm used: sorted by fee-per-byte\n";
        std::cout << "--------------------------------------------------------\n";
        std::cout << "Included transaction IDs:\n";
        for (const auto& tx : block) {
            std::cout << "  " << tx.getId() << "\n";
        }
        std::cout << "========================================================\n";
    }

private:
    std::vector<Transaction> transactions;
    std::vector<Transaction> block;
    int maxBlockSize;
    int totalFee = 0;
    int totalSize = 0;
    double durationMs = 0.0;

    void readTransactions(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        std::getline(file, line);

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string id, sz_str, fee_str;
            if (std::getline(ss, id, ',') &&
                std::getline(ss, sz_str, ',') &&
                std::getline(ss, fee_str)) {
                int sz = std::stoi(sz_str);
                int fee = std::stoi(fee_str);
                transactions.emplace_back(id, sz, fee);
            }
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <transactions.csv>\n";
        return 1;
    }

    BlockBuilder builder(argv[1]);
    builder.build();
    builder.printResults();

    return 0;
}
