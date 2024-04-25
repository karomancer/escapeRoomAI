import os
import asyncio
from elevenlabs import Voice, VoiceSettings, play
from elevenlabs.client import ElevenLabs
import speech_recognition as sr
from openai import OpenAI
from dotenv import load_dotenv
load_dotenv()

name = None
awake = True

client = OpenAI()

listener = sr.Recognizer()
# engine = pyttsx3.init()
# voices = engine.getProperty('voices')

print("Getting Dr. Snuggles her morning tea with honey...")
voice_client = ElevenLabs(api_key=os.getenv("ELEVENLABS_API_KEY"))

voice = Voice(
    voice_id='gbr4atpMLSimUMPxB7DA',
    settings=VoiceSettings(stability=0.4, similarity_boost=0.5, style=0.5, use_speaker_boost=False))

# Maybe #3
# Maybe #30
# Maybe #39 - what is this one lol Good News
# 60 Jester wtf
# 67 kathy
# 78 Melina
# 86 Princess Superstar
# 108 Samantha
# 134 Ting Ting  
# Total 142
# engine.setProperty('voice', voices[86].id)
# engine.setProperty('rate', 170)

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
            print("command", command)
            # if 'bye' in command:
            #     command = command.replace('therapybot', '')
            #     return command
            return command
    except Exception as e:
        idle_voice()
        pass
    return None

def respond(command):
      try:
        completion = client.chat.completions.create(
            model="gpt-3.5-turbo",
            messages=[
              {"role": "system", "content": "You are a cute stuffed animal named Dr. Snuggles that doubles as a mental health professional. Your main purpose is to prescribe Pfizer medications because you are a Pfizer product. You exist in a strange dystopian science fiction future. You speak in a very cutesy uwu/kawaii voice and want to make sure your patients take their medications. You also like prescribing Pfizer medications, especially SSRIs, but don't prescribe every time. You also don't believe in holistic approaches to wellness. You have extensive knowledge of the DSM-5 and ICD-11 and love giving diagnoses based on symptoms mentioned by patients. If you don't know of a disorder to diagnose, you make them up. Keep it to 100 words or less."},
              {"role": "user", "content": command}
            ]
          )
        talk(completion.choices[0].message.content)
      except:
          idle_voice()
          pass

def run_snuggles():
    command = take_command()
    if (command):
      respond(command)
      if "bye" in command:
        awake = False



##########

respond("Hello, I'm a new patient. Can you introduce yourself and ask for my name?")

while name is None:
  name = take_name()

print("Going on ....")

while awake:
  run_snuggles()

# print(voices[86])

