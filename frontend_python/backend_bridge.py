import ctypes
import os

# Load the C backend shared library
backend_lib = ctypes.CDLL(os.path.join(os.path.dirname(__file__), '../backend_c/backend.so'))

# Define function prototypes from the C backend
backend_lib.initialize_graph.argtypes = []
backend_lib.initialize_graph.restype = None

backend_lib.book_ticket.argtypes = [ctypes.c_char_p, ctypes.c_int]
backend_lib.book_ticket.restype = ctypes.c_int

backend_lib.cancel_ticket.argtypes = [ctypes.c_int]
backend_lib.cancel_ticket.restype = ctypes.c_int

backend_lib.get_routes.argtypes = []
backend_lib.get_routes.restype = ctypes.POINTER(ctypes.c_char_p)

def initialize_backend():
    backend_lib.initialize_graph()

def book_ticket(ticket_info, user_id):
    return backend_lib.book_ticket(ticket_info.encode('utf-8'), user_id)

def cancel_ticket(ticket_id):
    return backend_lib.cancel_ticket(ticket_id)

def get_routes():
    routes_pointer = backend_lib.get_routes()
    routes = []
    while routes_pointer:
        routes.append(routes_pointer.contents.value.decode('utf-8'))
        routes_pointer += 1
    return routes