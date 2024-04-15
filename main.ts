import fs from "fs";
import path from "path";
import OpenAI from "openai";
require("dotenv").config();

const AI_STARTING_DESCRIPTION = fs.readFileSync(
  path.resolve(__dirname, "./roles/starting-description.txt"),
  "utf8"
);

const openai = new OpenAI({
  apiKey: process.env.OPENAI_API_KEY,
});

const assistant = openai.beta.assistants.create({
    name: "Math Tutor",
    instructions: AI_STARTING_DESCRIPTION,
    model: "gpt-3.5-turbo",
})

async function main() {
  interact("Can you welcome the patient AI_STARTING_DESCRIPTION);
}

async function interact(
  userContent: string,
  aiPrompt: string,
  aiSentiment: string = "calm, caring, and professional"
) {
  const completion = await openai.chat.completions.create({
    messages: [
      {
        role: "system",
        content: `${aiPrompt}. You are ${aiSentiment} in your responses. Keep all responses to 100 words or less.`,
      },
      {
        role: "user",
        content: userContent,
      },
    ],
    model: "gpt-3.5-turbo",
  });

  return completion.choices[0].message;
}

main();
