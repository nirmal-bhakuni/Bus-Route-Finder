# BusTrainRouteFinder

## Project Overview
BusTrainRouteFinder is a comprehensive application designed to facilitate the planning and management of bus and train routes. The application provides users with the ability to find routes, book tickets, and manage their bookings efficiently. It consists of a C backend that handles core logic and a Python frontend that offers a user-friendly interface.

## Features
- Route finding using graph algorithms (BFS/DFS).
- Ticket booking and management system.
- User interface built with Python (Tkinter or menu-driven).
- Integration with real or mock APIs for departure and arrival times.
- Comprehensive testing suite for both backend and frontend components.

## Project Structure
The project is organized into several directories:
- **backend_c**: Contains the core logic implemented in C.
- **frontend_python**: Contains the Python user interface.
- **data**: Stores route data.
- **tests**: Contains unit tests for various components.

## Setup Instructions

### Prerequisites
- Ensure you have a C compiler installed (e.g., GCC).
- Python 3.x installed with pip.

### Backend Setup
1. Navigate to the `backend_c` directory.
2. Compile the C files using the provided Makefile:
   ```
   make
   ```

### Frontend Setup
1. Navigate to the `frontend_python` directory.
2. Install the required Python dependencies:
   ```
   pip install -r ../requirements.txt
   ```

### Running the Application
1. Start the backend server (if applicable).
2. Run the Python UI:
   ```
   python ui.py
   ```

## Testing
To run the tests, navigate to the `tests` directory and compile the test files in the `backend_c` directory. Use the following commands:
```
make test_routes
make test_booking
```
For Python UI tests, run:
```
python test_ui.py
```

## Contribution
Contributions are welcome! Please fork the repository and submit a pull request for any enhancements or bug fixes.

## License
This project is licensed under the MIT License. See the LICENSE file for details.