# FMOD sound plugin for ATS/ETS2

### Only supports 1.39

A telemetry plugin for ATS/ETS2 that includes an FMOD instance so that you can use FMOD sound mods.

This is pretty useless in singleplayer because you could just load the mod directly in the game.<br>
But I'm mostly playing TruckersMP, where fmod is still kinda broken and also doesn't support sound mods, which are much better than the base game sounds.

So this is something I kinda quickly put together after the broken sounds in 1.37 TruckersMP, and then didn't really update it once it worked except for making it compatible with the newer versions, so it is pretty basic.

Currently this uses a mix of the telemetry channels provided by the SCS sdk and directly reading values from the game's memory.

I'm not that great at c(++) and reverse engineering so it might just stay this way, and also with more reverse engineering making updating slower and more complicated.

# Some limitations/issues
- No echo when driving in tunnels (will require reverse engineering to figure out)
- Will keep playing sound even when alt-tabbed
- Sound level/direction does not change with the camera, the sound is always as if you are in the truck looking forward.
- You will need to mute or lower the in-game audio channels for your truck (or you will hear double audio), but this will also mute all truck sounds from other players
- Can (and most probably will) break and (possibly) crash you game with every (major) game update because it needs to read some values directly from memory, and this structure can change with updates
- No volume control (not sure how to add this except for adding imgui or something like it)
- Probably some more that I forgot

# How to use
Download the [latest release](https://github.com/dariowouters/ts-fmod-plugin/releases/latest), copy the `ts-fmod-plugin.dll` and the `ts-fmod-plugin` folder to `<game_install_location>/bin/win_x64/plugins`. (if the `plugins` folder does not exists, you can create one)<br>
Copy the master.bank file from the Release for the specific game you are installing it to and copy it to the `ts-fmod-plugin` folder.

Here's the correct folder structure:

```python
<game_install_location>/bin/win_x64/
│   eurotrucks2.exe # or amtrucks.exe for ATS
│   ... # removed to keep this list smaller
│
└───plugins # create if not exists
    │   ts-fmod-plugin.dll # copy from release
    │
    └───ts-fmod-plugin # copy from release
            master.bank # copy from specific game folder in release
            selected.bank.txt # edit text in file with sound mod filename you want
            the_sound_mod_you_want_to_use.bank # example of sound mod
            the_sound_mod_you_want_to_use.bank.guids # example of sound mod
```

For any sound mods you want to add you have to copy the (usually located in `/sound/truck/`) `<sound_mod_name>.bank` and the `<sound_mod_name>.bank.guids` files from the mod to the `ts-fmod-plugin` folder, and then open the `selected.bank.txt` file in a text editor and change the text in the file to the filename of the mod (without the file extension).<br>
So for example if the sound mod files are named `sound_mod.bank` and `sound_mod.bank.guids` you have to change the text in the `selected.bank.txt` file to `sound_mod`.

Now you can load the game and the sound should work when you start your truck.

### Some extra info

If you have the developer console enabled in-game you can switch sound mods without restarting by changing the filename in `selected.bank.txt` and then in the game console enter `sdk reload`. This will reload all telemetry plugins and cause this plugin to load the newly selected sound mod.

When the game updates you might need to update the `master.bank` file, it is located in the base.scs file for the specific game, in that file it is located in `/sound/master/`

# Supported FMOD events and parameters
Events:
- engine/engine
- engine/exhaust
- interior/air_warning
- interior/blinker_on (and off)
- interior/stick_blinker (and off)
- interior/stick_park_brake (and off)
- interior/stick_retarder

Parameters:
- brake
- load
- rpm
- turbo
- wnd_left (and right)
