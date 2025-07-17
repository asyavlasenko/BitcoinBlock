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

## How to Run

```plaintext
g++ -std=c++17 -O2 main.cpp -o block
./block bitcoin.csv
