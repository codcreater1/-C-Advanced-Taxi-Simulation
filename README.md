Advanced Taxi Simulation (C++)

This project is a Taxi Dispatch System simulation written in C++ using Object-Oriented Programming (OOP). It demonstrates classes, inheritance, polymorphism, vectors, and file handling. The program allows multiple passengers to request rides, assigns available taxis automatically, calculates fares based on distance and driver rating, and saves ride details to a file.

There are two types of taxis: Standard and VIP. Each driver has a rating from 0 to 5, which slightly affects the fare. The system randomly chooses an available taxi for the passenger. After each ride, the taxi becomes available again. All rides are saved in rides.txt in CSV format including passenger name, destination, distance, driver, taxi type, plate, and fare.

To run the program, compile it with a C++ compiler supporting C++17 and run the executable. The program will display available taxis, ask for passenger information, assign a taxi, calculate the fare, and show ride details. You can repeat this process for multiple passengers. To exit, type exit as the passenger name.

The project structure is simple: the main code is in taxi_simulation.cpp and rides are saved in rides.txt.

This project is useful for practicing OOP concepts in C++, including classes, inheritance, polymorphism, dynamic objects, vectors, and file input/output. Future improvements could include allowing passengers to choose the taxi type, updating driver ratings after each ride, and showing ride history on request.
