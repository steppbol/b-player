# Requirements Document
### 1\. Intoduction
There are a lot of music players, but most of them significantly burden the system due to the large amount of resources, and this is perhaps one of the most important qualities.

And what if you create a music player that will be lightly loaded with various skins and add-ins, and also play all the popular digital audio formats? The answer to this question is only this project - B-Player.

### 2\. User Requierements
#### 2.1\. Software Interfaces
The project uses the Qt framework and does not interact with external systems and services.
#### 2.2\. User Interfaces
The GUI of the project is presented with the help of mocaps [main window](https://github.com/steppbol/B-Player/blob/master/docs/Project%20Documentation/mockups/MainWindow.png) and [volume control method](https://raw.githubusercontent.com/steppbol/B-Player/master/docs/Project%20Documentation/mockups/ShowVolume.png).
The main window requires a separate view:
Button | Event
--- | ---
"Volume" | A scroll bar pops up, with which you can adjust the sound
"Play" | Playback of the selected
"Stop" | Stop playing audio recordings
"Next" | Play next audio file
"Play" | Play a previous audio file
"Add" | An explorer is opened, through which you can select audio files for playback
"Remove" | Delete selected audio from playlist
"Random" | Changing the order of audio playback

#### 2.3\. User Characteristics
This project is designed for a novice user who needs a small audio player. A simple and intuitive interface does not take long to understand how the program works.
#### 2.4\. Assumptions and Dependencies
When you run this project on Linux, you need to use files with the extension ".wav", because the files with the extension ".mp3" are not supported by the QMediaPlayer element of the Qt framework.
### 3\. System Requierements
Run the application on the following operating systems:
* Windows
* Linux
#### 3.1\. Functional Requierements
  1\. Adding audio files to a playlist.
  2\. Delete an audio from a playlist.
  3\. Change the volume of the audio used in the program.
  4\. Reorder the playback of audio.
  5\. The ability to play an audio recording again, at the end of it.
  6\. The ability to rewind the audio.
  7\. The ability to switch to the next or previous audio recording.
#### 3.2\. Non-Functional Requierements
* mouse presence
* presence of a sound reproduction system
##### 3.2.1\. Software Quality Attributes
The most important criterion for this application should be the responsiveness to the change in the state of the button. That is, the delay between pressing a key and starting the playback of a music file (by stopping it) should be minimal and not noticeable by ear.
### 4\. Analogues
This project is in some way a simplified version ["AIMP"](http://www.aimp.ru/) and ["JetAudio" company "Cowon"](http://www.jetaudio.com/), that greatly simplifies the use of.
