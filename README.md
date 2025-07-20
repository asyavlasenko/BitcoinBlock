# ⛏️ Backpack with Bitcoin Transactions

## About the Project

This is a C++ command-line application that simulates constructing a Bitcoin block by selecting the most profitable subset of transactions under the 1MB block size limit. It solves a simplified version of the **0/1 Knapsack Problem** using a **greedy algorithm** based on the **fee-per-byte ratio**.

---

## 🧠 Description

Each Bitcoin transaction has a unique ID, size (in bytes), and fee (in satoshis).  
Your goal is to include as many valuable transactions into the block as possible without exceeding the block size limit (1,000,000 bytes).

This tool:
- Reads a CSV file with thousands of transactions
- Sorts them by **fee per byte**
- Greedily selects the best subset that fits
- Outputs summary statistics and included transaction IDs

---

## 🚀 How to Run

```bash
g++ -std=c++17 -O2 main.cpp -o block
./block bitcoin.csv
```

Replace `bitcoin.csv` with your transaction file.  

---

## 🧮 Time Complexity (Big O)

- Reading transactions from CSV: **O(N)**
- Sorting transactions by fee-per-byte: **O(N log N)**
- Greedy selection of transactions for block: **O(N)**

> **Overall time complexity:**  
> \> `O(N log N)` — dominated by the sorting step

This greedy approach is efficient and works well in practice, especially when:
- Transactions are independent (no dependencies like in real Bitcoin mempool)
- You only aim to maximize fee-per-byte ratio

> Note: This is not optimal for the general 0/1 Knapsack Problem, but is a **fast and practical heuristic** for large datasets.

---
