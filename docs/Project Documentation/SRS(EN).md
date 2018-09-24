# Requirements Document
### Contents
1. [Introduction](#1)
2. [User Requirements](#2) <br>
  2.1. [Software Interfaces](#2.1) <br>
  2.2. [User Interfaces](#2.2) <br>
  2.3. [User Characteristics](#2.3) <br>
  2.4. [Assumptions and Dependencies](#2.4) <br>
3. [System Requirements](#3.) <br>
  3.1 [Functional Requirements](#3.1) <br>
  3.2 [Non-Functional Requierements](#3.2) <br>
    3.2.1 [Software Quality Attributes](#3.2.1) <br>
4. [Analogues](#4) <br>
### 1\. Intoduction <a name="1"></a>
There are a lot of music players, but most of them significantly burden the system due to large amount of resources they use, which is probably one of the most essential qualities. 

So, why not create a music player which can be lightly loaded with various skins and add-ins, and which is able to play all the popular digital audio formats? The only one answer to this question is the following project - B-Player.

### 2\. User Requirements <a name="2"></a>
#### 2.1\. Software Interfaces <a name="2.1"></a>
The project uses the Qt framework and does not interact with external systems and services.
#### 2.2\. User Interfaces <a name="2.2"></a>
The GUI of the project is presented with the help of mocaps [main window](https://github.com/steppbol/B-Player/blob/master/docs/Project%20Documentation/mockups/MainWindow.png) and [volume control method](https://raw.githubusercontent.com/steppbol/B-Player/master/docs/Project%20Documentation/mockups/ShowVolume.png).
The main window requires a separate view:

Button | Event
--- | ---
"Volume" | A scroll bar pops up, with which you can adjust the sound
"Play" | Play of the selected
"Stop" | Stop playing audio recordings
"Next" | Play next audio file
"Play" | Play a previous audio file
"Add" | An explorer is opened, through which you can select audio files for play
"Remove" | Delete selected audio from playlist
"Random" | Changing the order of audio playback

#### 2.3\. User Characteristics <a name="2.3"></a>
This project is designed for a novice user who needs a small audio player. A simple and intuitive interface does not take long to understand how the program works.
#### 2.4\. Assumptions and Dependencies <a name="2.4"></a>
When you run this project on Linux, you need to use files with the extension ".wav", because the files with the extension ".mp3" are not supported by the QMediaPlayer element of the Qt framework.
### 3\. System Requirements <a name="3"></a>
Run the application on the following operating systems:
* Windows
* Linux
#### 3.1\. Functional Requirements <a name="3.1"></a>
The user has the following options:
  1. Adding audio files to a playlist.
  2. Delete an audio from a playlist.
  3. Change the volume of the audio used in the program.
  4. Reorder the playback of audio.
  5. The ability to play an audio recording again, at the end of it.
  6. The ability to rewind the audio.
  7. The ability to switch to the next or previous audio recording.
#### 3.2\. Non-Functional Requierements <a name="3.2"></a>
* mouse presence
* presence of a sound reproduction system
  ##### 3.2.1\. Software Quality Attributes <a name="3.2.1"></a>
The most important criterion for this application should be the responsiveness to the change in the state of the button. That is, the delay between pressing a key and starting the playback of a music file (by stopping it) should be minimal and not noticeable by ear.
### 4\. Analogues <a name="4"></a>
This project is in some way a simplified version ["AIMP"](http://www.aimp.ru/) and ["JetAudio" company "Cowon"](http://www.jetaudio.com/), that greatly simplifies the use of.
