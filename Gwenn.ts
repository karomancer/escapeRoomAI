import fs from "fs";
import OpenAI from "client";
import path from "path";

require("dotenv").config();

const AI_STARTING_DESCRIPTION = fs.readFileSync(
  path.resolve(__dirname, "./roles/starting-description.txt"),
  "utf8"
);

class Gwenn {
  client: OpenAI;
  assistant?: OpenAI.Beta.Assistant;
  thread?: OpenAI.Beta.Thread;

  constructor() {
    this.client = new OpenAI({
      apiKey: process.env.OPENAI_API_KEY,
    });
  }

  public async setupRoom(instructions: string = AI_STARTING_DESCRIPTION) {
    this.assistant = await this.client.beta.assistants.create({
      name: "GWENN",
      instructions,
      model: "gpt-3.5-turbo",
    });

    this.thread = await this.client.beta.threads.create();
  }

  public async startAppointment() {
    // message = client.beta.threads.messages.create(
    //     thread_id=thread.id,
    //     role="user",
    //     content="I need to solve the equation `3x + 11 = 14`. Can you help me?"
    // )
  }

  public async interact(
    userContent: string,
    aiPrompt: string,
    aiSentiment: string = "calm, caring, and professional"
  ) {
    const completion = await this.client.chat.completions.create({
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
}

export default Gwenn;
