import express from "express";
import { getSchedules, addSchedule } from "../controllers/scheduleController.js";
const router = express.Router();

router.get("/", getSchedules);
router.post("/", addSchedule);

export default router;
