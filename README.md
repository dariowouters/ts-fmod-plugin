# FMOD sound plugin for ATS/ETS2

A telemetry plugin for ATS/ETS2 that includes an FMOD instance so that you can use FMOD sound mods.

This is pretty useless in singleplayer because you could just load the mod directly in the game.<br>
But since I'm mostly playing TruckersMP, where sound mods are not supported (which are much better than the base game sounds), this is something I kinda quickly put together after the broken sounds in 1.37 TruckersMP, and then didn't really update it once it worked except for fixing some bugs and making it compatible with the newer versions, so it is pretty basic.

Currently this uses a mix of the telemetry channels provided by the SCS sdk and directly reading values from the game's memory.

I'm not that great at c(++) and reverse engineering so it might just stay this way, and also with more reverse engineering making updating slower and more complicated.

# Some limitations/issues
- Will keep playing sound even when alt-tabbed.
- Sound level/direction does not change with the camera, the sound is always as if you are in the truck looking forward, with the exception of interior sounds not being played when on an exterior camera.
- You will need to mute or lower some of the in-game audio channels for your truck (or you will hear double audio).
- Can (and most probably will) break and possibly crash your game with every major game update because it needs to read some values directly from memory, and this structure can change with updates.
- Only very basic volume control (might look into something better/easier in the future).
- Probably some more that I forgot.

# How to use
Download the [latest release](https://github.com/dariowouters/ts-fmod-plugin/releases/latest), copy the `ts-fmod-plugin.dll` and the `ts-fmod-plugin` folder to `<game_install_location>/bin/win_x64/plugins`. (if the `plugins` folder does not exists, you can create one)<br>
Copy the master.bank file from the Release for the specific game you are installing it to and copy it to the `ts-fmod-plugin` folder.

Here's the correct folder structure:

```python
<game_install_location>/bin/win_x64/
│   eurotrucks2.exe # or amtrucks.exe for ATS
│   ... # hidden to keep this list smaller
│
└───plugins # create if not exists
    │   ts-fmod-plugin.dll # copy from release
    │
    └───ts-fmod-plugin # copy from release
            master.bank # copy from specific game folder in release
            selected.bank.txt # copy from release | edit text in file with sound mod filename(s) you want
            sound_levels.txt # copy from release | edit the sound levels to your liking
            the_sound_mod_you_want_to_use.bank # example of sound mod
            the_sound_mod_you_want_to_use.bank.guids # example of sound mod
```

For any sound mods you want to add you have to copy the (usually located in `/sound/truck/`) `<sound_mod_name>.bank` and the `<sound_mod_name>.bank.guids` files from the mod to the `ts-fmod-plugin` folder, and then open the `selected.bank.txt` file in a text editor and change the text in the file to the filename of the mod (without the file extension).<br>
So for example if the sound mod files are named `sound_mod.bank` and `sound_mod.bank.guids` you have to change the text in the `selected.bank.txt` file to `sound_mod`.

You can load multiple sound banks at the same time by having the sound banks in selected.bank.txt each on a new line. These sound banks will be loaded top to bottom.
If multiple sound banks include the same sound event it will only load the event from the first sound bank.

Now you can load the game and the sound should work when you start your truck.

### Some extra info

You will generally need to mute/lower the truck engine, exhaust and turbo sound channels in the in-game settings to prevent double sounds. If the sound mod you're using includes interior sounds you will also have to mute/lower them in-game.

If you have the developer console enabled in-game you can switch sound mods without restarting by changing the filename in `selected.bank.txt` and then in the game console enter `sdk reload`. This will reload all telemetry plugins and cause this plugin to load the newly selected sound mod.

You can change the sound levels in the `sound_levels.txt` file, you will just kind of need to play with them until you get something you like. Again you can use the `sdk reload` console command after you've changed these to reload the plugin with these new values.

# Supported FMOD events and parameters
Events:
- engine/engine
- engine/exhaust
- engine/turbo
- interior/air_warning
- interior/blinker_on (and off)
- interior/stick_blinker (and off)
- interior/stick_park_brake (and off)
- interior/stick_retarder
- interior/stick_hazard_warning
- interior/stick_high_beam
- interior/stick_light_horn
- interior/stick_lights
- interior/stick_wipers
- and_then_exit_left
- and_then_exit_right
- and_then_go_straight
- and_then_keep_left
- and_then_keep_right
- and_then_turn_left
- and_then_turn_right
- compound_exit_left
- compound_exit_right
- compound_go_straight
- compound_keep_left
- compound_keep_right
- compound_turn_left
- compound_turn_right
- exit_left
- exit_now
- exit_right
- finish
- go_straight
- keep_left
- keep_right
- prepare_exit_left
- prepare_exit_right
- prepare_turn_left
- prepare_turn_right
- recomputing
- roundabout_1
- roundabout_2
- roundabout_3
- roundabout_4
- roundabout_5
- roundabout_6
- speed_signal
- speed_warning
- start
- turn_left
- turn_right
- u_turn


Parameters:
- brake
- load
- rpm
- wnd_left (and right)
- surr_type
- cabin_rot
- cabin_out
