### Content
1. [Introduction](#1)
2. [Testing Object](#2)
3. [Quality Attributes](#3)
4. [Risks](#4)
5. [Testing Aspects](#5)<br>
5.1. [Ability to start playing audio recordings](#001)<br>
5.2. [Ability to stop audio playback](#002)<br>
5.3. [Ability to switch to the next or previous audio recording](#003)<br>
5.4. [Ability to upload all audio files to a playlist](#004)<br>
5.5. [Ability to delete an audio recording from a playlist](#005)<br>
5.6. [Change the playback volume](#006)<br>
5.7. [Ability to play the playlist again when it ends](#007)<br>
5.8. [Playing audio recordings in different sequences](#008)<br>
6. [Testing Approaches](#6)
7. [Presentation of Results](#7)
8. [Conclusions](#8)


<a name="1"></a>
### 1. Introduction
This plan is intended for testing the "B-Player" application. The purpose of testing is to check the performance and suitability of the application for practical use.
This plan uses the terminology that corresponds to this annex, please read the [glossary of the "B-Player"](https://github.com/steppbol/B-Player/blob/master/docs/Project%20Documentation/Glossary(EN).md) before reading it. 

<a name="2"></a>
### 2. Testing Object
As test objects, we can distinguish the quality attributes of the platform according to ISO 25010:
1. functionality
-functional completeness: the application must perform all the declared functions
- functional correctness: the application must perform all the declared functions correctly
- functional feasibility: there are no non-declared functions that would prevent the application from performing the originally assigned tasks
2. ease of use
- user interface aesthetics: object controls should always be available to the user
- user error protection: request user confirmation when making significant changes to objects.

These attributes were taken taking into account the specifics of the application.

The application under test contains 1 module created to perform a certain functionality:
- main window (the window with the application).

<a name="3"></a>
### 3. Quality Attributes
1. Functionality:
- Functional completeness: The application must meet all the functional requirements stated in [SRS](https://github.com/steppbol/B-Player/blob/master/docs/Project%20Documentation/SRS(EN).md);
- functional feasibility: there are no non-declared functions that would prevent the application from performing the assigned tasks
2. Ease of use:
- Simple user interface: the interface should be simple enough for intuitive use by a new user.
3. Cross-platform:
- correct operation of the application on platforms:
- Windows
- Linux.

<a name="4"></a>
### 4. Risks
The application uses the system tools to play sound, which is why the sound playback on different operating systems may differ. Also, different codecs are available on different operating systems, so playback of some formats may not be available.


<a name="5"></a>
### 5. Aspects of testing
This testing is integration testing, i.e. software modules are tested in a group, it is also smoke testing, and will be conducted in a "Black box" type, i.e. without access to the source code.<br>
During testing, it is planned to check the implementation of the main functions of the application, conduct positive and negative tests, as well as check non-functional requirements. The main functions include the following items:

- ability to start playing an audio recording;
- ability to stop audio recording playback;
- ability to switch to the next or previous audio recording:
- ability to upload all audio files to a playlist;
- ability to delete an audio recording from a playlist;
- change the playback volume;
- the ability to play the playlist again, when it ends;
- playback of audio recordings in different sequences.

#### Functional requirements:

<a name="001"></a>
##### Ability to start playing an audio recording
This use case should be tested on:
1. The app's response to an attempt to start playing an audio recording.
2. Perform this operation (the actual playback of the audio recording when the button is pressed).

<a name="002"></a>
##### Ability to stop audio recording playback
This use case should be tested on:
1. The app's response to an attempt to stop playing an audio recording.
2. Perform this operation (the actual playback of the audio recording when the button is pressed).

<a name="003"></a>
##### Ability to switch to the next or previous audio recording
This use case should be tested on:
1. The app's response to switching to the next audio recording in the selected direction.
2. Performing this operation (actually switching to the next audio recording in the selected direction).

<a name="004"></a>
##### Ability to upload all audio files to a playlist
This use case should be tested for:
1. Displaying audio files with the desired extension.
2. Upload all the selected audio files to the playlist.
3. Cancel the operation when the audio file selection window is closed.

<a name="005"></a>
##### Ability to delete an audio recording from a playlist
This use case should be tested on:
1. The app's response to an attempt to delete an audio recording from the playlist.
2. Perform this operation (delete the audio recording from the playlist).

<a name="006"></a>
##### Changing the playback volume
This use case should be tested on:
1. The app's response to an attempt to change the volume.
2. Performing this operation (actual change in the playback volume).

<a name="007"></a>
##### Ability to play the playlist again, when it ends
This use case should be tested on:
1. The app's response to the playback of the audio recording following the last one in the playlist, i.e. the first audio recording in the playlist.
2. Perform this operation (switch to the first audio recording in the playlist).

<a name="008"></a>
##### Playing audio recordings in different sequences
This use case should be tested for:
1. Changing the playback order when the button is pressed to sequential or arbitrary.
2. Performing this operation (changing the playback order).

#### Non-functional requirements:
- quick launch of the app;
- all user interface elements have a name that describes the action they perform.

<a name="6"></a>
### 6. Testing approaches
The conducted testing can be outstripped as:
- By the degree of automation: manual.
- According to the knowledge of the system: black box.
- By the degree of isolation of components: integration.

<a name="7"></a>
### 7. Presentation of results
The test results are presented in [table](https://github.com/steppbol/B-Player/blob/master/documentation/test-plan/TestResults(EN).md).

<a name="8"></a>
### 8. Conclusions
This test plan allows you to test the main functionality of the application. Successful completion of all tests does not guarantee full performance on all platforms and architectures, but it allows you to believe that this software works correctly.
