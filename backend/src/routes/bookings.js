import express from "express";
import { bookTicket, getUserBookings } from "../controllers/bookingController.js";
const router = express.Router();

router.post("/", bookTicket);
router.get("/:userId", getUserBookings);

export default router;
