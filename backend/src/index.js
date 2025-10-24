import express from "express";
import cors from "cors";
import dotenv from "dotenv";
import db from "./config/db.js";
import cppRoutes from "./routes/cppRoutes.js";


import authRoutes from "./routes/auth.js";
import routeRoutes from "./routes/routes.js";
import scheduleRoutes from "./routes/schedules.js";
import bookingRoutes from "./routes/bookings.js";

dotenv.config();

const app = express();
app.use(cors());
app.use(express.json());

// Base API routes
app.use("/api/cpp", cppRoutes);
app.use("/api/auth", authRoutes);
app.use("/api/routes", routeRoutes);
app.use("/api/schedules", scheduleRoutes);
app.use("/api/bookings", bookingRoutes);

app.get("/", (req, res) => {
  res.send("🚍 Bus Route & Ticket Booking API is running...");
});

const PORT = process.env.PORT || 5000;
app.listen(PORT, () => console.log(`✅ Server running on port ${PORT}`));
