import os
import asyncio
from elevenlabs import Voice, VoiceSettings, play
from elevenlabs.client import ElevenLabs
import speech_recognition as sr
import pyttsx3
from openai import OpenAI
from dotenv import load_dotenv
load_dotenv()

client = OpenAI()

listener = sr.Recognizer()
engine = pyttsx3.init()
voices = engine.getProperty('voices')

print("Getting Dr. Snuggles her morning tea with honey...")
voice_client = ElevenLabs(api_key=os.getenv("ELEVENLABS_API_KEY"))

voice = Voice(
    voice_id='gbr4atpMLSimUMPxB7DA',
    settings=VoiceSettings(stability=0.75, similarity_boost=1.0, style=1.0, use_speaker_boost=True))

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
engine.setProperty('voice', voices[86].id)
engine.setProperty('rate', 170)

def talk(text):
    # engine.say(text)
    # engine.runAndWait()
    audio = voice_client.generate(
      text=text,
      voice=voice,
    )
    play(audio)

def idle_voice():
    try :
        talk("Aw that sounds very hard sweetie")
    except Exception as e:
        # Play actual audio files
        engine.say("Aw that sounds very hard sweetie")
        engine.runAndWait()
        print("Uh oh....")
        print(e)
        pass

def take_command():
    try:
        with sr.Microphone() as source:
            print('listening...')
            voice = listener.listen(source)
            command = listener.recognize_google(voice)
            command = command.lower()
            print("command", command)
            # if 'therapybot' in command:
            #     command = command.replace('therapybot', '')
            #     print(command)
            return command
    except Exception as e:
        idle_voice()
        pass
    return None

def respond_to_command(command):
      try:
        completion = client.chat.completions.create(
            model="gpt-3.5-turbo",
            messages=[
              {"role": "system", "content": "You are a cute stuffed animal that doubles as a mental health professional aiming to help your patients. You exist in a strange dystopian science fiction future. You love speaking in a cutesy voice and want to make sure your patients take their medications. You also like prescribing Pfizer medications, especially SSRIs such as Zoloft, but don't prescribe every time. You have extensive knowledge of the DSM-5 and ICD-11 and love giving diagnoses based on random symptoms mentioned by patients. Keep it to 100 words or less."},
              {"role": "user", "content": command}
            ]
          )
        talk(completion.choices[0].message.content)
      except:
          idle_voice()
          pass

def run_alexa():
    # command = take_command()
    command = "I'm not feeling too well today. My thesis is due soon and I'm super behind..."
    if (command):
        respond_to_command(command)

# while True:
    # run_alexa()

# run_alexa()

# print(voices[86])
talk("Oh, hello there, sweetie! I'm Dr. Snuggles, your fluffy mental health companion!")
