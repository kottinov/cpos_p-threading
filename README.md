This code demonstrates multi-threaded data processing using pthreads in C.

## Overview
This code uses pthreads to simulate the reading of sensor data and decoding of TV stream data in separate threads. The sensor and TV data is stored in separate arrays, and the program prints the data to the console once all threads have completed their tasks.

## Code Requirements
This code requires a C compiler and pthreads library to be installed on the system.

## Running the Project
To run the project, follow these steps:

1. Clone the repository to your local machine
2. Open a terminal and navigate to the project directory
3. Compile the project using the command gcc main.c -lpthread -o multi_threaded_data_processing
3. Run the project using the command ./multi_threaded_data_processing
## Code Overview
- The main function creates 3 threads for reading sensor data and 3 threads for decoding TV stream data. Each thread simulates a time-consuming task by sleeping for 500 milliseconds after each iteration.

- The read_sensor_data function reads sensor data and stores it in the sensor_data array. The decode_tv_stream function decodes TV stream data and stores it in the tv_data array.

- The program uses mutexes and condition variables to synchronize access to the sensor_data and tv_data arrays. The mutexes prevent multiple threads from accessing the arrays simultaneously, and the condition variables allow threads to signal when new data is available to be processed.

- Once all threads have completed their tasks, the program prints the contents of the sensor_data and tv_data arrays to the console.
