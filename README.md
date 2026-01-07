# Inventory Management System

This project is a console-based Inventory Management System developed in C++ using Object-Oriented Programming (OOP) principles.  
It is designed for a small shop or store to manage products, handle billing, and maintain inventory records with role-based access.
The system supports Admin and Cashier roles, includes a Dashboard summary, and ensures data persistence using file handling.

## Features

### Dashboard
- Displays:
  - Total number of products
  - Number of low-stock items (quantity < 10)
- Automatically shown at program start
- Provides a quick overview of inventory status

### Role-Based Access

#### Admin
- Secure login authentication
- Add new products
- Update product quantities
- View inventory
- Save inventory data to file

#### Cashier
- View available products
- Search products by ID
- Create bill
- Automatic stock reduction after sales

### Billing System
- Validates stock before sale
- Calculates total bill
- Automatically updates inventory after purchase

### File Handling (Data Persistence)
- Inventory data stored in `inventory.txt`
- Data automatically loaded at program start
- Inventory auto-saved before program exit

### Input Handling Fix
- Correct handling of product names containing spaces  
  (e.g., *"Coca Cola"*) using `getline()` and `cin.ignore()`

## Technical Details
- **Language:** C++
- **Storage:** Text File (`inventory.txt`)
- **Interface:** Menu-driven console application

### OOP Concepts Used
- Classes & Objects  
- Encapsulation  
- Inheritance  
- Polymorphism  
- Abstraction  
- File Handling  
- Virtual & Pure Virtual Functions  

## Class Structure

### Product
- Attributes: ID, Name, Price, Quantity
- Functions:
  - Input
  - Display
  - Save to file
  - Load from file

### Inventory
- Manages an array of 100 products
- Features:
  - Add products
  - Search by ID
  - Update quantity
  - Display all products
  - Dashboard summary
  - Save & load inventory

### User (Abstract Class)
- Base class for system roles
- Uses pure virtual function `menu()`

### Admin (Derived from User)
- Login authentication
- Inventory management
- Data saving

### Cashier (Derived from User)
- Product search
- Billing
- Stock deduction

## Testing & Results

### Verified Features
- Dashboard shows correct inventory summary
- Product names with spaces handled correctly
- Billing deducts stock safely
- Inventory persists across multiple runs
- Admin and Cashier menus function correctly
- No crashes or input-buffer issues

### Testing Scenarios
1. Added multiple products (including names with spaces)
2. Restarted program to verify file loading
3. Verified billing totals manually
4. Tested low-stock conditions
5. Checked invalid product IDs and large quantity requests
