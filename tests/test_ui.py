import unittest
from frontend_python.ui import main_menu, book_ticket, cancel_ticket

class TestUI(unittest.TestCase):

    def test_main_menu(self):
        # Test if the main menu displays correctly
        result = main_menu()
        self.assertIn("Welcome to Bus Train Route Finder", result)
        self.assertIn("1. Book Ticket", result)
        self.assertIn("2. Cancel Ticket", result)
        self.assertIn("3. Exit", result)

    def test_book_ticket(self):
        # Test ticket booking functionality
        ticket_info = {
            'route': 'Route A',
            'passenger_name': 'John Doe',
            'seat_number': 5
        }
        result = book_ticket(ticket_info)
        self.assertTrue(result['success'])
        self.assertEqual(result['message'], "Ticket booked successfully.")

    def test_cancel_ticket(self):
        # Test ticket cancellation functionality
        ticket_id = 1  # Assuming ticket ID 1 exists
        result = cancel_ticket(ticket_id)
        self.assertTrue(result['success'])
        self.assertEqual(result['message'], "Ticket cancelled successfully.")

if __name__ == '__main__':
    unittest.main()