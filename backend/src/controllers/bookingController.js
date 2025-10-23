import db from "../config/db.js";

export const bookTicket = (req, res) => {
  const { user_id, schedule_id, seat_no, fare } = req.body;
  const sql =
    "INSERT INTO bookings (user_id, schedule_id, seat_no, fare) VALUES (?, ?, ?, ?)";
  db.query(sql, [user_id, schedule_id, seat_no, fare], (err, result) => {
    if (err) return res.status(500).json({ error: err.message });
    res.json({ message: "Ticket booked successfully", bookingId: result.insertId });
  });
};

export const getUserBookings = (req, res) => {
  const { userId } = req.params;
  const sql = "SELECT * FROM bookings WHERE user_id = ?";
  db.query(sql, [userId], (err, results) => {
    if (err) return res.status(500).json({ error: err.message });
    res.json(results);
  });
};
