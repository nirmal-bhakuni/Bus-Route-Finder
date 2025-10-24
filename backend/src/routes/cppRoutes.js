import express from "express";
import { runCpp } from "../utils/runCpp.js";

const router = express.Router();

router.post("/find", (req, res) => {
  const { source, destination } = req.body;

  if (!source || !destination) {
    return res.status(400).json({ error: "Source and destination required" });
  }

  runCpp(source, destination, (result) => {
    if (result.error) {
      return res.status(500).json(result);
    }
    res.json(result);
  });
});

export default router;
