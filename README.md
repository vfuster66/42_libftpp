# libftpp - Advanced C++ Library

## Description
A comprehensive C++ toolbox implementing various design patterns, data structures, and utilities.

## Environment Setup

### Prerequisites
- Docker
- Docker Compose

### First Time Setup
```bash
# Give execution permission to the development script
chmod +x dev.sh

# Build and start the Docker container
./dev.sh up

# Access the container shell
./dev.sh shell

# Compile the library
make

# Clean object files
make clean

# Clean everything (objects and library)
make fclean

# Recompile everything
make re

# Run tests
make test

# Exit the container shell
exit

# Stop the Docker container
./dev.sh dev down
```

### Script Commands Reference

```bash
./dev.sh up - Start the container
./dev.sh down - Stop the container
./dev.sh shell - Access container shell
./dev.sh build - Run make inside container
./dev.sh clean - Run make clean inside container
./dev.sh test - Run tests inside container
```

### Development Workflow

1. Start a working session:


- Run chmod +x dev.sh to make script executable
- Start container with ./dev.sh up
- Access container shell with ./dev.sh shell


2. Inside the container, use Make commands:


- make - Compile the library
- make clean - Clean object files
- make fclean - Clean everything (objects and library)
- make re - Recompile everything
- make test - Run tests


3. End a working session:


 - Exit container shell with exit
 - Stop container with ./dev.sh down

### Project structure
```
libftpp/
├── include/             # Header files
│   ├── data_structures/
│   ├── design_patterns/
│   ├── threading/
│   ├── network/
│   └── mathematics/
├── src/                # Source files
├── tests/             # Test files
└── libftpp.hpp        # Main header
```
