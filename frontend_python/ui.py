from backend_bridge import add_stop, add_route, display_graph
from api_handler import fetch_departure_arrival_times

def main_menu():
    while True:
        print("\nBusTrainRouteFinder Menu")
        print("1. Add Stop")
        print("2. Add Route")
        print("3. Display Graph")
        print("4. Fetch Departure/Arrival Times")
        print("5. Exit")
        choice = input("Enter choice: ")
        if choice == "1":
            stop = input("Enter stop name: ")
            add_stop(stop)
        elif choice == "2":
            start = input("Start stop ID: ")
            end = input("End stop ID: ")
            cost = input("Cost: ")
            time = input("Time (min): ")
            add_route(start, end, cost, time)
        elif choice == "3":
            display_graph()
        elif choice == "4":
            route_id = input("Route ID: ")
            times = fetch_departure_arrival_times(route_id)
            print(f"Departure: {times['departure']}, Arrival: {times['arrival']}")
        elif choice == "5":
            print("Exiting.")
            break
        else:
            print("Invalid choice.")

if __name__ == "__main__":
    main_menu()