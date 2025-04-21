# C++ Food Warehouse Management System

This project is a simulation of a food warehouse system written in C++. It was developed as part of a university assignment in Systems Programming, with a strong focus on object-oriented design, memory management, and proper use of the Rule of 5.

## 🎯 Assignment Goal

To implement a real-time warehouse management simulator where customers place food orders and volunteers (collectors and drivers) fulfill them through a multi-stage flow.

The simulation is controlled through commands typed by the user and reflects each change in the state of the warehouse.

## ⚙️ Features

- Object-oriented implementation of customers, volunteers, and warehouse logic
- Supports various volunteer types (Collector, Limited Collector, Driver, Limited Driver)
- Rule of 5 implemented where needed
- Dynamic command-based interaction (e.g., `order`, `step`, `status`, `close`, etc.)
- Memory-safe (tested with Valgrind)
- Uses STL (e.g., vectors, strings) and enum types
- Configurable through an input file

## 🧠 Technologies Used

- C++ (C++11 standard)
- Valgrind (for memory leak checks)
- Makefile (for compilation)
- Unix/Linux (tested on university lab machines)

## 📂 Project Structure

