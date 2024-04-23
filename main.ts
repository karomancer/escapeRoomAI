import fs from "fs";
import path from "path";
import OpenAI from "openai";
require("dotenv").config();

import DrPharmi from "./DrPharmi";

async function main() {
  const dr = new DrPharmi();
  dr.setup();
  await dr.startAppointment();
}

main();
