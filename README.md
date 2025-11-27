# Noodle Extensions

A port of the Noodle Extensions mod made originally for the PC version of Beat Saber to the Oculus Quest platform.

## 1.40.8 To-Do

### This list is not final and will continue to grow

- [x] Fix note jump animation (notes simply pop into existence rather than flying into view)
- [x] Fix notes being invisible on pretty much all modcharts. Perhaps notes that are on a track?
- [x] Fix audio being drowned out for seemingly no reason. Common in Doppelganger. Perhaps an issue with walls?
- [x] Fix notes looking towards (0, 0, 0). Maybe calculated in `src/hooks/NoteJump.cpp`
- [x] Fix start beat offset
- [ ] Fix no badcut
- [x] Fix crashes when restarting a modchart
- [ ] Fix crash when Replay tries to load a modchart replay
- [ ] Remove wall adjustments. Not only do they look different, but they were first added to get around poorly acting distortion effects, which is a solved problem with GraphicsTweaks
- [x] Investigate jump distance / speed
- [ ] Implement saber trail parenting to player track
- [X] Fix parenting inconsistencies (likely order based e.g "Make a Wish")
- [X] Fix obstacle spawn, duration and speed e.g `Try This` the arrows are in the lane before moved. 
- [ ] Fix obstacle rotation e.g flower in `Try`.
- [ ] Fix Chroma not removing pieces of environment

### [Recorded](https://drive.google.com/drive/folders/1XNpSEJ44uwEr9L9W3qukeGNnQX24wF0U?usp=drive_link) Maps

- [ ] [Analys](https://beatsaver.com/maps/d00c) (25/11/25)
  - [ ] 0:50 The obstacles next to the player may not be positioned correctly
  - [ ] 0:56 Track does not rotate smoothly
  - [ ] 1:34 Circle of arrows despawn or does not follow player (Also 1.37)
- [ ] [BSSDHUYR Megamix 2023](https://beatsaver.com/maps/39736) (25/11/25)
  - [ ] Crashes
- [ ] [Centipede](https://beatsaver.com/maps/293ab) (26/11/25)
  - [ ] [Awaiting analysis]
- [ ] [Change of Scene](https://beatsaver.com/maps/3f19a) (25/11/25)
  - [ ] Environment pieces aren't being removed
  - [ ] Player is slightly elevated above the track
  - [ ] Note colors frequently don't change
  - [ ] 0:00 Title shows as CHANGE OF SCE--:
  - [ ] 1:49 Track doesn't follow player
  - [ ] Find more issues once environment pieces can be cleared
- [ ] [C18H27NO3 (Mawntee)](https://beatsaver.com/maps/17d7e) (26/11/25)
  - [ ] [Awaiting analysis]
- [ ] [Disaster](https://beatsaver.com/maps/1dc64) (26/11/25)
  - [ ] [Awaiting analysis]
- [ ] [Doppelganger](https://beatsaver.com/maps/d53c) (25/11/25)
  - [x] Audio being drowned out
  - [x] Obstacles are scaled weirdly
  - [x] Exaggerated note movement
  - [x] Note dissolve isn't removed
  - [ ] 1:23 Obstacle is positioned weirdly
  - [ ] 2:08 Obstacles are at the wrong Y position
  - [ ] 3:04 Obstacle timing issues
  - [x] 3:04 Track teleports with no smoothing
- [ ] [Echo](https://beatsaver.com/maps/269a7) (25/11/25)
  - [ ] [Awaiting analysis]
- [ ] [Glorious Octagon of Destiny](https://beatsaver.com/maps/26ad0) (26/11/25)
  - [ ] 0:19 "VIVA" text comes in from top and bottom rather than spinning in from sides
  - [ ] 0:25 Obstacle field is missing (Also 1.37)
  - [ ] 0:39 Obstacles are missing
  - [ ] 0:47 Note arrows don't disappear on cut (Also 1.37)
  - [ ] 0:52 Unintentional hyper walls
  - [x] 1:16 The two tracks are positioned on top of each other
  - [ ] 1:30 Unintentional fast walls
  - [x] 1:44 Track doesn't rotate with player
  - [ ] 1:44 More hyper walls
  - [ ] 1:47 Wall text doesn't move
  - [ ] 2:32 Large note is normal scale in mirror
  - [ ] 2:46 Some walls are unintentionally hyper, some aren't
  - [ ] 3:05 Wall text is missing or offscreen
  - [ ] 3:14 Notes are missing
  - [ ] 3:14 Obstacles are missing
  - [ ] 4:00 "321" wall text is delivered as several very large grains of sugar in succession on the main track
  - [x] 4:10 Notes and Super Hexagon obstacles are missing
  - [ ] 4:31 "LEVEL FAILED" text is either further away or smaller than normal
  - [ ] 4:31 Notes are missing
  - [ ] 4:52 Wall text is missing
  - [ ] 5:21 Unintentional hyper walls
  - [ ] 5:21 The "printing" obstacle doesn't move
  - [ ] 5:33 Wall sign is missing
  - [ ] 5:42 Notes are missing
  - [x] 5:57 Wall arrows are on top of each other
  - [ ] 5:57 Wall arrows don't duplicate (Also 1.37)
  - [ ] 6:09 Wall arrows don't disappear (Also 1.37)
  - [x] 6:26 Notes are positioned next to player
  - [ ] 6:51 Unintentional hyper walls in Papyrus section
  - [ ] 7:27 Wall text missing letters (Also 1.37)
- [x] [IGDWUTSWHWHMTC (QueenChief)](https://beatsaver.com/maps/20bc7) (26/11/25)
- [ ] [Make a Wish](https://beatsaver.com/maps/1a32d) (26/11/25)
  - [ ] [Awaiting analysis]
- [ ] [Midnight Lady](https://beatsaver.com/maps/da60) (26/11/25)
  - [ ] [Awaiting analysis]
- [ ] [Noodle Animation Stuff](https://beatsaver.com/maps/1a53c) (25/11/25)
  - [ ] [Awaiting analysis]
- [ ] [NULCTRL Meiso Flip](https://beatsaver.com/maps/ed2a) (25/11/25)
  - [ ] [Awaiting analysis]
- [ ] [Paradigm](https://beatsaver.com/maps/3bbb0) (25/11/25)
  - [ ] Crashes
- [ ] [PAUSE](https://beatsaver.com/maps/17e36) (25/11/25)
  - [x] Notes are missing during the pause effect
  - [ ] 1:18 Unintentional hyper walls
- [x] [Real or Lie (Pixelguy)](https://beatsaver.com/maps/126e4) (26/11/25)
- [ ] [Signager](https://beatsaver.com/maps/12498) (26/11/25)
  - [ ] [Awaiting analysis]
- [ ] [Six Forty Seven (Reddek)](https://beatsaver.com/maps/2c89c) (25/11/25)
  - [ ] [Awaiting analysis]
- [ ] [Six Forty Seven (SuperMemer417, nasafrasa)](https://beatsaver.com/maps/2a2bd) (26/11/25)
  - [ ] Environment pieces aren't being removed
- [ ] [Try](https://beatsaver.com/maps/14d64) (26/11/25)
  - [ ] [Awaiting analysis]
- [ ] [Try This](https://beatsaver.com/maps/decf) (26/11/25)
  - [x] Arrow walls disappear early
  - [ ] 0:31 Unintentional hyper wall
- [ ] [Up & Down](https://beatsaver.com/maps/11cf8) (25/11/25)
  - [ ] Environment pieces aren't being removed
  - [x] 1:00 Animated notes spawn in late
- [ ] [Up & Down (Remastered)](https://beatsaver.com/maps/2c2f4) (26/11/25)
  - [ ] Environment arrows are missing, perhaps a lighting issue
  - [ ] Environment pieces aren't being removed
  - [ ] 0:00 Platform underneath the player is missing
  - [x] 0:03 Track doesn't rotate with the player
  - [ ] 0:33 Decorative obstacles are missing
  - [ ] 0:33 Half the notes are missing
  - [ ] 1:05 Notes are supposed to change color, instead aren't visible
  - [ ] 1:54 Tease notes are missing

## Bonus 1.40.8 fixes / features

These would be nice to fix and implement, but were already broken / missing in 1.37 and therefore aren't required if I'm simply going for 1.37 parity.

- [ ] Iirc saber animation was broken


## FAQ (Frequently Asked Questions)
- Why are the wall colors not the same as PC (desaturated, transparent etc.)?
  - Due to the Quest not having distortion on walls, Noodle Extensions will attempt to change the walls materials to solid if these conditions are met:
    - Wall color alpha (controlled by Chroma) is greater than or equal 0
    - Dissolve animation is being applied
- Bombs are not coloring/are always black
  - A bug specific to Quest causes bombs to lose their color/default to black when dissolve animation is being applied. It is not certain if this bug will be fixed or worked around.
- Why does Noodle Extensions disable my Qosmetics notes/walls?
  - Qosmetics notes/walls drastically reduce performance especially in Noodle maps and also ruin the artistic experience. 
- Why do you suggest disabling Mapping Extensions? It works fine for me
  - While it _could_ work, we didn't extensively test the impact of performance or stability using Mapping Extensions. It's at your discretion if you choose to use Mapping Extensions simultaneously with Noodle.
  - While some maps do "require" both Noodle Extensions and Mapping Extensions, this is not a supported scenario in either PC or Quest and should be discouraged.
- Where are Tracks/CustomJSONData QMod downloads?
  - Noodle Extensions and Chroma will download these dependencies automatically
- Noodle Extensions isn't loading/working and PinkCore says I don't have the mod installed
  - Try to reinstall Noodle Extensions and update Chroma to at least version 2.5.7 or newer.
- I found a map that doesn't work!!!!11!!11!/Noodle is missing a feature
  - You most likely downloaded the wrong map as most Noodle features are supported (no exceptions except the TODO)
  - In the case you are absolutely certain you found a bug/missing feature, report it in GitHub issues along with a log and steps to reproduce the issue. Footage of said map is also recommended being provided.

## Building from Source

You'll need [qpm_rust](https://github.com/RedBrumbler/QuestPackageManager-Rust), Powershell, Ninja, and CMake in `PATH`.

You'll also need the latest Android NDK. Create a file called `ndkpath.txt` containing the path to the directly where you extracted the ndk to.

```sh
qpm-rust restore
qpm-rust cache legacy-fix
pwsh ./build.ps1
pwsh ./createqmod.ps1 noodle_extensions
```

## What still needs to be done?
- Left handed mode
- Beatmap note/obstacle/bomb count (includes fakes)
- Some maps such as Centipede by totally balloon have fake notes registered as real notes
- Make Noodle only run on Noodle maps
