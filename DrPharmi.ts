import fs from "fs";
import OpenAI from "openai";
import path from "path";
import { ElevenLabsClient, play } from "elevenlabs";

require("dotenv").config();

const AI_STARTING_DESCRIPTION = fs.readFileSync(
  path.resolve(__dirname, "./roles/starting-description.txt"),
  "utf8"
);

class DrPharmi {
  openAIClient: OpenAI;
  voiceClient: ElevenLabsClient;
  assistant?: OpenAI.Beta.Assistant;
  thread?: OpenAI.Beta.Thread;

  constructor() {
    this.openAIClient = new OpenAI({
      apiKey: process.env.OPENAI_API_KEY,
    });

    this.voiceClient = new ElevenLabsClient({
      apiKey: process.env.ELEVENLABS_API_KEY,
    });
  }

  public async setup(instructions: string = AI_STARTING_DESCRIPTION) {
    this.assistant = await this.openAIClient.beta.assistants.create({
      name: "Dr. Snuggles",
      instructions,
      model: "gpt-3.5-turbo",
    });

    this.thread = await this.openAIClient.beta.threads.create();

    const voices = await this.voiceClient.voices.getAll();
  }

  public async startAppointment() {
    return this.interact(
      "I'm a patient starting a therapy session. Can you ask for my name and offer to help me?"
    ).catch(console.warn);
  }

  public async speak(text: string) {
    console.log(`Dr. Snuggles: ${text}`);
    const audio = await this.voiceClient.generate({
      voice: "gbr4atpMLSimUMPxB7DA",
      text,
      model_id: "eleven_multilingual_v2",
    });

    return play(audio);
  }

  public async interact(
    userContent: string,
    aiSentiment: string = "cutesy and caring"
  ) {
    const completionPromise = this.openAIClient.chat.completions
      .create({
        messages: [
          {
            role: "system",
            content: `You are ${aiSentiment} in your responses. Keep all responses to 100 words or less.`,
          },
          {
            role: "user",
            content: userContent,
          },
        ],
        model: "gpt-3.5-turbo",
      })
      .then(async (completion) => {
        const message = completion.choices[0].message.content;
        if (message) {
          this.speak(message);
        } else {
          // maybe play a giggle or something
        }
      })
      .catch(console.warn);

    this.speak("Hmmmmmmmm");

    return completionPromise;
  }
}

export default DrPharmi;
