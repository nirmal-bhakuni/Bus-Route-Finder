import { exec } from "child_process";

export const runCpp = (input, callback) => {
  exec(`./pathfinder.exe ${input}`, (error, stdout, stderr) => {
    if (error) {
      console.error("Error executing C++:", stderr);
      callback(error, null);
    } else {
      callback(null, stdout);
    }
  });
};
