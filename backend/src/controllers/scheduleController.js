import db from "../config/db.js";

export const getSchedules = (req, res) => {
  const sql = "SELECT * FROM bus_schedules";
  db.query(sql, (err, results) => {
    if (err) return res.status(500).json({ error: err.message });
    res.json(results);
  });
};

export const addSchedule = (req, res) => {
  const { route_id, bus_no, departure_time, arrival_time, fare } = req.body;
  const sql =
    "INSERT INTO bus_schedules (route_id, bus_no, departure_time, arrival_time, fare) VALUES (?, ?, ?, ?, ?)";
  db.query(sql, [route_id, bus_no, departure_time, arrival_time, fare], (err, result) => {
    if (err) return res.status(500).json({ error: err.message });
    res.json({ message: "Schedule added successfully" });
  });
};
