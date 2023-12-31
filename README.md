# Student Management System

## Description
A comprehensive system for managing student and teacher data in an educational setting. This system allows for tracking student attendance, assignments, and grades, as well as teacher's subject schedule, etc.

## Prerequisites
- **CMake** (version 3.14 or higher)
- A C++ compiler (e.g., **GCC**)

## Building The Project Im using Ninja as my project manager you might have to configure that in your cmake -G

Follow these steps to build the project: 

1. Run these commands in the terminal (You have to use Ninja as the project manager)

    ```bash
    mkdir build #only if the build directory doesn't exist
    cd build
    cmake -G "Ninja" ..
    cmake ..
    cmake --build .
    ```

## Usage (Run Application)

The executable file (`.exe`) is located in the `bin` folder. To run it, either double-click the file in the folder or execute the following command in the terminal while in the build folder:

```bash
    ..\bin\StudentManagementSystem.exe
```

## How to Use the Program

Running the Student Management System, you will be presented with a menu preloaded with Data. Use the following credentials to access the respective menus:

### Student Menu

- `2303693` - Diego's Student Menu
- `2303694` - Cassandra's Student Menu
- `2303695` - John Wick's Student Menu
- `2303696` - Bob Frank's Student Menu
- `2303697` - Sally Sue's Student Menu
- `2303698` - John Doe's Student Menu

### Teacher Menu

Accessing a Teacher Menu provides entry to the Class Menus that the teacher is associated with.

- `2000` - Melahut's Teacher Menu (Access to Math 2413 Class Menu)
- `2001` - Jakavitch's Teacher Menu (Access to Biology 1302 Class Menu)
- `2002` - Holly Smith's Teacher Menu (Access to English 1301 Class Menu)
- `2003` - Carlos's Teacher Menu (Access to Computer Science 1301 Class Menu)

### Admin Menu
- `admin` or `Admin` - Access to admin Menu
-  Gives you the ability to add new students or classes into the global maps and json files

### Troubleshooting
Encountering compiler-related errors during the build process is a issue, especially when multiple C++ compilers are installed on the system. This can lead to conflicts in the build process. Below are the steps to fix that error.

Step 1: Clear CMake Cache
- Navigate to the build directory in your terminal and execute the following command to remove the CMake cache:

```bash
rm .\CmakeCache.txt
```
Step 2: Reconfigure CMake
- Return to your CMakeLists.txt file and save it. This retriggers the reconfiguration of the compiler settings.

Step 3: Rebuild the Project
 ```bash
    mkdir build #only if the build directory doesn't already exist
    cd build
    cmake -G "Ninja" ..
    cmake ..
    cmake --build .
```
# Student Management System

## Description
A comprehensive system for managing student and teacher data in an educational setting. This system allows for tracking student attendance, assignments, and grades, as well as teacher's subject schedule, etc.

## Prerequisites
- **CMake** (version 3.14 or higher)
- A C++ compiler (e.g., **GCC**)

## Building The Project Im using Ninja as my project manager you might have to configure that in your cmake -G

Follow these steps to build the project: 

1. Run these commands in the terminal (You have to use Ninja as the project manager)

    ```bash
    mkdir build #only if the build directory doesn't exist
    cd build
    cmake -G "Ninja" ..
    cmake ..
    cmake --build .
    ```

## Usage (Run Application)

The executable file (`.exe`) is located in the `bin` folder. To run it, either double-click the file in the folder or execute the following command in the terminal while in the build folder:

```bash
    ..\bin\StudentManagementSystem.exe
```

## How to Use the Program

Running the Student Management System, you will be presented with a menu preloaded with Data. Use the following credentials to access the respective menus:

### Student Menu

- `2303693` - Diego's Student Menu
- `2303694` - Cassandra's Student Menu
- `2303695` - John Wick's Student Menu
- `2303696` - Bob Frank's Student Menu
- `2303697` - Sally Sue's Student Menu
- `2303698` - John Doe's Student Menu

### Teacher Menu

Accessing a Teacher Menu provides entry to the Class Menus that the teacher is associated with.

- `2000` - Melahut's Teacher Menu (Access to Math 2413 Class Menu)
- `2001` - Jakavitch's Teacher Menu (Access to Biology 1302 Class Menu)
- `2002` - Holly Smith's Teacher Menu (Access to English 1301 Class Menu)
- `2003` - Carlos's Teacher Menu (Access to Computer Science 1301 Class Menu)

### Admin Menu
- `admin` or `Admin` - Access to admin Menu
-  Gives you the ability to add new students or classes into the global maps and json files

### Troubleshooting
Encountering compiler-related errors during the build process is a issue, especially when multiple C++ compilers are installed on the system. This can lead to conflicts in the build process. Below are the steps to fix that error.

Step 1: Clear CMake Cache
- Navigate to the build directory in your terminal and execute the following command to remove the CMake cache:

```bash
rm .\CmakeCache.txt
```
Step 2: Reconfigure CMake
- Return to your CMakeLists.txt file and save it. This retriggers the reconfiguration of the compiler settings.

Step 3: Rebuild the Project
 ```bash
    mkdir build #only if the build directory doesn't already exist
    cd build
    cmake -G "Ninja" ..
    cmake ..
    cmake --build .
```