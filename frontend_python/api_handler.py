import requests
import json

class APIHandler:
    def __init__(self, api_url):
        self.api_url = api_url

    def fetch_departure_times(self, route):
        try:
            response = requests.get(f"{self.api_url}/departures/{route}")
            response.raise_for_status()
            return response.json()
        except requests.exceptions.RequestException as e:
            print(f"Error fetching departure times: {e}")
            return None

    def fetch_arrival_times(self, route):
        try:
            response = requests.get(f"{self.api_url}/arrivals/{route}")
            response.raise_for_status()
            return response.json()
        except requests.exceptions.RequestException as e:
            print(f"Error fetching arrival times: {e}")
            return None

    def fetch_mock_data(self, mock_data_file):
        try:
            with open(mock_data_file, 'r') as file:
                return json.load(file)
        except FileNotFoundError:
            print(f"Mock data file not found: {mock_data_file}")
            return None

# Example usage:
# api_handler = APIHandler("http://example.com/api")
# departures = api_handler.fetch_departure_times("route1")
# arrivals = api_handler.fetch_arrival_times("route1")
# mock_data = api_handler.fetch_mock_data("mock_data.json")