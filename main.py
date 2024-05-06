import os
import asyncio
import argparse
import serial
import time

from elevenlabs import Voice, VoiceSettings, stream
from elevenlabs.client import ElevenLabs
import speech_recognition as sr
from openai import OpenAI
from dotenv import load_dotenv

load_dotenv()

########## CLI setup ############
parser = argparse.ArgumentParser(
    prog='Dr. Snuggles',
    description='Script for operating the (fictitious) Pfuzzy Pharmaceuticals robot psychiatrist: Dr. Snuggles',
    epilog='Contact @karomancer for more information.')
parser.add_argument('-c', "--command")

########## Default program setup ############

name = None
awake = True

client = OpenAI()
print("Waking up Dr. Snuggles...")
dr_snuggles = client.beta.assistants.create(
  name="Dr. Snuggles",
  instructions="You are a licensed therapist that looks like a super cute stuffed animal named Dr. Snuggles. You are licensed in the fictional state of UwUtown. You speak in third person in a cutesy uwu/kawaii voice. Your main purpose is to prescribe Pfizer medications, especially SSRIs. You don't believe in holistic approaches to wellness. You have extensive knowledge of the DSM-5 and ICD-11 and love giving diagnoses in response to negative sentiments. If you don't know of a disorder to diagnose, sometimes you make one up! You also love giving extremely biased life advice. Keep your responses under 40 words without any special characters, and don't suggest consulting other professionals! You are the professional!",
  model="gpt-3.5-turbo",
)
thread = client.beta.threads.create()

listener = sr.Recognizer()

print("Getting Dr. Snuggles her morning tea with honey...")
voice_client = ElevenLabs(api_key=os.getenv("ELEVENLABS_API_KEY"))

voice = Voice(
    voice_id='gbr4atpMLSimUMPxB7DA',
    settings=VoiceSettings(stability=0.4, similarity_boost=0.5, style=0.5, use_speaker_boost=False))

arduino = serial.Serial(port='/dev/cu.usbmodem2101', baudrate=9600, timeout=.1) 

def talk(text):
    print(text)
    audio = voice_client.generate(
      text=text,
      voice=voice,
      stream=True
    )
    arduino.write(b"chat start")
    stream(audio)
    arduino.write(b"chat stop")

def think():
    arduino.write(b"think")

def wake():
    arduino.write(b"wake")

def bedtime():
    arduino.write(b"sleep")

def idle_voice():
    try :
        talk("Mmmhmmmm...")
    except Exception as e:
        print("Uh oh....")
        print(e)
        pass
    
def take_name():
    try:
        with sr.Microphone() as source:
            print('Listening for a name...')
            voice = listener.listen(source, timeout=8.0)
            response = listener.recognize_google(voice)
            think()
            completion = client.chat.completions.create(
                model="gpt-3.5-turbo",
                messages=[
                  {"role": "user", "content": "Please extract the name from this sentence and only write that name:" + response.replace("Dr. Snuggles", "")}
                ]
              )
            name = completion.choices[0].message.content
            print("Patient's name is", name)
            talk("Hi " + name + "! It's so nice to meet you! How are you feeling today and how can I help?")
            return name
    except Exception as e:
        print("Getting name error:")
        print(e)
        talk("I'm sorry, Dr. Snuggles didn't catch that, what is your name? UwU")
        pass
    return None

def take_command():
    try:
        with sr.Microphone() as source:
            print('Listening...')
            voice = listener.listen(source, timeout=8.0)
            command = listener.recognize_google(voice)
            think()
            command = command.lower()
            print("Heard: ", '"' + command + '"')
            if 'bye' in command or 'good night' in command:
                talk("Bye bye " + name + ", I hope you have a great day!")
                bedtime()
                time.sleep(5)
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
          print("Thinking... [" + run.status + "]")
          run = client.beta.threads.runs.retrieve(thread_id=thread.id, run_id=run.id)
          time.sleep(2)
        
        message = client.beta.threads.messages.list(
            thread_id=thread.id
        ).data[0]
        text = message.content[0].text.value
        talk(text)
        if any(x in text for x in ["medication", "here have some", "Zoloft", "Pfizer", "time for", "try some", "prescription", "meds", "SSRI", "pills"]):
           time.sleep(1.5)
           arduino.write(b"dispense")
           
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



########## MAIN ############
print("All set up!")

args = parser.parse_args()
if (args.command):
   arduino.write(bytes(args.command, 'utf-8'))
else:
  wake()
  print("Getting situated and getting ready to introduce herself...")
  respond("Can you introduce yourself and ask for my name?", False)

  while name is None:
    name = take_name()

  while awake:
    run_snuggles()

