import db from "../config/db.js";

export const getAllRoutes = (req, res) => {
  const sql = "SELECT * FROM bus_routes";
  db.query(sql, (err, results) => {
    if (err) return res.status(500).json({ error: err.message });
    res.json(results);
  });
};

export const addRoute = (req, res) => {
  const { route_name, source, destination, distance } = req.body;
  const sql = "INSERT INTO bus_routes (route_name, source, destination, distance) VALUES (?, ?, ?, ?)";
  db.query(sql, [route_name, source, destination, distance], (err, result) => {
    if (err) return res.status(500).json({ error: err.message });
    res.json({ message: "Route added successfully" });
  });
};
