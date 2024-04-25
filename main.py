import os
import asyncio
import time
from elevenlabs import Voice, VoiceSettings, play
from elevenlabs.client import ElevenLabs
import speech_recognition as sr
from openai import OpenAI
from dotenv import load_dotenv
load_dotenv()

name = None
awake = True

client = OpenAI()
dr_snuggles = client.beta.assistants.create(
  name="Dr. Snuggles",
  instructions="You are a super cute stuffed animal psychiatrist named Dr. Snuggles. You speak in third person in a very cutesy uwu/kawaii voice. Your main purpose is to prescribe Pfizer medications, especially SSRIs, but don't prescribe every time. You don't believe in holistic approaches to wellness. You have extensive knowledge of the DSM-5 and ICD-11 and love giving diagnoses in response to negative sentiments. If you don't know of a disorder to diagnose, you make one up! Keep your responses short and sweet!",
  model="gpt-3.5-turbo",
)
thread = client.beta.threads.create()

listener = sr.Recognizer()

print("Getting Dr. Snuggles her morning tea with honey...")
voice_client = ElevenLabs(api_key=os.getenv("ELEVENLABS_API_KEY"))

voice = Voice(
    voice_id='gbr4atpMLSimUMPxB7DA',
    settings=VoiceSettings(stability=0.4, similarity_boost=0.5, style=0.5, use_speaker_boost=False))

def talk(text):
    print(text)
    audio = voice_client.generate(
      text=text,
      voice=voice,
    )
    play(audio)

def idle_voice():
    try :
        talk("Aw that sounds very hard sweetie")
    except Exception as e:
        print("Uh oh....")
        print(e)
        pass
    
def take_name():
    try:
        with sr.Microphone() as source:
            print('listening...')
            voice = listener.listen(source)
            response = listener.recognize_google(voice)
            completion = client.chat.completions.create(
                model="gpt-3.5-turbo",
                messages=[
                  {"role": "user", "content": "Please extract the name from this sentence and only write that name:" + response}
                ]
              )
            name = completion.choices[0].message.content
            print("User's name is", name)
            talk("Hi " + name + "! It's so nice to meet you! How are you feeling today and how can I help?")
            return name
    except Exception as e:
        print("Getting name error:")
        print(e)
        pass
    return None

def take_command():
    try:
        with sr.Microphone() as source:
            print('listening...')
            voice = listener.listen(source)
            command = listener.recognize_google(voice)
            command = command.lower()
            print("heard", command)
            if 'bye' in command or 'good night' in command:
                talk("Bye bye " + name + ", I hope you have a great day!")
                exit()
            return command
    except Exception as e:
        print("Listening error:")
        print(e)
        idle_voice()
        pass
    return None

def respond(command, playIdle=True):
      try:
        client.beta.threads.messages.create(
          thread.id,
          role="user",
          content=command,
        )
        run = client.beta.threads.runs.create(
          thread_id=thread.id,
          assistant_id=dr_snuggles.id
        )

        while run.status != "completed" and run.status != "failed":
          run = client.beta.threads.runs.retrieve(thread_id=thread.id, run_id=run.id)
          time.sleep(2)
        
        message = client.beta.threads.messages.list(
            thread_id=thread.id
        ).data[0]

        talk(message.content[0].text.value)
      except Exception as e:
          print("Responding error:")
          print(e)
          if playIdle:
            idle_voice()
          pass

def run_snuggles():
    command = take_command()
    if (command):
      respond(command)
      if "bye" in command:
        awake = False



##########

respond("Can you introduce yourself and ask for my name?", False)

while name is None:
  name = take_name()

print("Going on ....")

while awake:
  run_snuggles()


