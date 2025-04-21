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

## 🚀 How to Build and Run

1. Open terminal and navigate to the project root:
   ```bash
   cd path/to/project
   ```

2. Run the makefile:
   ```bash
   make
   ```

3. Run the simulation with an input config file:
   ```bash
   ./bin/warehouse ExampleInput.txt
   ```

> 💡 Ensure you're compiling and running on the university lab UNIX machine.


## ✍️ Author

- [Niv Yaakobov](https://github.com/Niv-Yaakobov)

> 📚 Created as part of the **Systems Programming** course at SPL University, Fall 2024.
