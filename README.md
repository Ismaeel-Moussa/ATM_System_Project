# ATM Simulation Project

This project simulates the core functionalities of an Automated Teller Machine (ATM) using C++ and a text file-based database system. It is implemented using functional programming principles.

---

## Features

- **Login System**  
  Users can log in by providing their account number and PIN.

- **Menu Options**  
  The following options are available in the main menu:
  1. Quick Withdraw  
  2. Normal Withdraw  
  3. Deposit  
  4. Check Balance  
  5. Logout

- **Text File-Based Database**  
  - Account details are stored and managed in text files.
  - Ensures data persistence without the need for an external database system.

---

## Screenshots

### Login Screen

![Screenshot 2025-01-25 224331](https://github.com/user-attachments/assets/9fba5d63-54a6-4769-b41b-821bc0185412)

### Main Menu
![Screenshot 2025-01-25 224354](https://github.com/user-attachments/assets/3301b0e7-5c7e-4b0e-bc4c-5ea615b11d76)

---

## Requirements

- A C++ compiler (e.g., GCC, MSVC, or Clang)
- Basic knowledge of C++ syntax and functional programming

---

## How It Works

1. **Account Management**  
   User account data is read from a text file that acts as a database. Each account has:
   - An account number
   - A PIN code
   - A balance

2. **Functional Design**  
   The project is structured around functions for each feature (e.g., `login`, `withdraw`, `deposit`). This ensures modularity and simplicity.

3. **Transactions**  
   - Deposits and withdrawals update the balance directly in the text file.
   - Balance inquiries fetch the latest data from the text file.

---

## Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/Ismaeel-Moussa/ATM_System_Project.git
