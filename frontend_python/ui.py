import tkinter as tk
from tkinter import messagebox
from api_handler import fetch_departure_arrival_times
from backend_bridge import book_ticket, cancel_ticket, get_routes

class BusTrainRouteFinderApp:
    def __init__(self, master):
        self.master = master
        master.title("Bus and Train Route Finder")

        self.label = tk.Label(master, text="Welcome to the Bus and Train Route Finder")
        self.label.pack()

        self.route_button = tk.Button(master, text="Find Routes", command=self.find_routes)
        self.route_button.pack()

        self.book_button = tk.Button(master, text="Book Ticket", command=self.book_ticket)
        self.book_button.pack()

        self.cancel_button = tk.Button(master, text="Cancel Ticket", command=self.cancel_ticket)
        self.cancel_button.pack()

        self.quit_button = tk.Button(master, text="Quit", command=master.quit)
        self.quit_button.pack()

    def find_routes(self):
        routes = get_routes()
        if routes:
            messagebox.showinfo("Available Routes", "\n".join(routes))
        else:
            messagebox.showwarning("No Routes", "No routes available.")

    def book_ticket(self):
        # Implement ticket booking logic here
        ticket_info = book_ticket()
        if ticket_info:
            messagebox.showinfo("Ticket Booked", f"Ticket booked successfully: {ticket_info}")
        else:
            messagebox.showwarning("Booking Failed", "Ticket booking failed.")

    def cancel_ticket(self):
        # Implement ticket cancellation logic here
        success = cancel_ticket()
        if success:
            messagebox.showinfo("Ticket Canceled", "Ticket canceled successfully.")
        else:
            messagebox.showwarning("Cancellation Failed", "Ticket cancellation failed.")

if __name__ == "__main__":
    root = tk.Tk()
    app = BusTrainRouteFinderApp(root)
    root.mainloop()