// src/utils/seedAdmin.js
import pool from "../config/db.js";
import bcrypt from "bcryptjs";
import dotenv from "dotenv";
dotenv.config();

const email = "admin@example.com";
const password = "admin123";
const name = "Admin";

async function run() {
  const hashed = await bcrypt.hash(password, 10);
  const [rows] = await pool.query("SELECT * FROM users WHERE email = ?", [email]);
  if (rows.length) {
    console.log("Admin already exists");
    process.exit(0);
  }
  const [res] = await pool.query("INSERT INTO users (name, email, password, role) VALUES (?, ?, ?, 'admin')", [name, email, hashed]);
  console.log("Admin created with id:", res.insertId);
  process.exit(0);
}

run().catch(err => { console.error(err); process.exit(1); });
