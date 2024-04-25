# Dr. Snuggles

Name TBD. Thesis project for ITP that will maybe change each time you play it.

# Set up

You will need the following:
- Microphone
- Speakers
- python version 3.11 or higher installed
- `ffmpeg` installed

## Installation
- `$ pip install -r requirements.txt`


If you get errors regarding pip being managed exernally and you don't care about messing with your local environment:
`$ rm /usr/lib/python3.11/EXTERNALLY-MANAGED`

If you want to be safer about it, you can also `mv` it to a new file name, such as
`$ mv /usr/lib/python3.11/EXTERNALLY-MANAGED /usr/lib/python3.11/EXTERNALLY-MANAGED.old`

## Linux instructions
If you're running this on Linux (as it is intended to be), you might need to do the following:
- Start PulseAudio
    - If `$ pacmd list-sources` returns an error stating the Daemon is not running, try starting it with `$ pulseaudio --start` (and if you need to stop it, you can use `$ pulseaudio --kill`)
- `$ apt-get install portaudio19-dev `
