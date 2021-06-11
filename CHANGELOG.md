## 1.41-beta
 - Updated for 1.41 (beta)
 - Support for loading multiple soundbanks
 - Fixed closed windows affecting sounds on exterior camera
 - Fixed handbrake sounds being reversed

## 1.40.1
 - Updated for 1.40
 - Fixed engine brake
    - Stopped engine brake from playing when in neutral or when throttle/clutch is pressed
    - Added support for different levels of engine brake

## 1.39.6
 - Added rudimentary audio level customization
 - Fixed interior sounds being played when on an exterior view

## 1.39.5
 - Added support for more interior events:
    - interior/stick_hazard_warning
    - interior/stick_high_beam
    - interior/stick_light_horn
    - interior/stick_lights
    - interior/stick_wipers
 - Fixed so indicator event plays when switching between left/right indicator.
 - Switched to using busses to control volume/pause state instead of events individually

## 1.39.4
- Support for 1.39 turbo event, older sound mods that used the turbo parameter should still work but without turbo sounds

## 1.39.3
- Fixed playing incorrect event when indicator stick going back to default position

## 1.39.2
- Added support for the echo sounds when under bridges, in tunnels, etc...

## 1.39.1
- Initial Code commit
