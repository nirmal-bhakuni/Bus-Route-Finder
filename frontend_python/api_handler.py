import json
import os

def fetch_departure_arrival_times(route_id):
    json_path = os.path.join(os.path.dirname(__file__), "mock_data.json")
    with open(json_path, "r") as f:
        data = json.load(f)
    departures = data.get("mock_api_response", {}).get("data", {}).get("departures", [])
    for dep in departures:
        if dep["route_id"] == int(route_id):
            return {
                "departure": dep["departure_time"],
                "arrival": dep["arrival_time"]
            }
    return {"departure": "N/A", "arrival": "N/A"}