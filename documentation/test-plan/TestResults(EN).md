Script|Action|Expected result|Actual result| Rating|
|:---|:---|:---|:---|:---|
|001-1: Playing an audio recording that is not selected| Click on the "Play" button| The first audio recording in the playlist has started playing|The first audio recording in the playlist has started playing|Passed|
|001-2: Plays the audio recording that is selected|Select an audio recording and click on the "Play" button|The selected audio recording has started playing|The selected audio recording has started playing|Passed|
|002-1: Stop playing audio| Click on the Pause button when playing an audio record| Stop playback of the current audio|Stop playing the current audio recording|Passed|
|003-1: Switch to the next audio recording| Click on the "Next" button |Switch to the next audio recording in the playlist|Switch to the next audio recording in the playlist|Passed|
003-2: Switches to the next audio recording, with one audio recording in the playlist| Click on the "Next" button |There is no reaction|The app started playing the audio recording first|Failed|
|003-3: Switch to the previous audio recording|Click on the "Previous" button |Switch to the previous audio recording in the playlist|Switch to the previous audio recording in the playlist|Passed|
|004-1: Uploading all audio files to the playlist| Click on the " Add " button, select audio files. Click " OK " and check that all audio files are added to the playlist|All files were added to the playlist|All files were added to the playlist|Passed|
|004-2: Cancels uploading of all audio files to the playlist| Click on the " Add " button, select audio files, close the File Explorer window|The app does not react to this in any way|The application did not react in any way, but the management interface was displayed|Failed|
|005-1: Deleting an audio recording from a playlist| Select an audio recording, click"Remove" |The app will delete the selected audio recording|The app deleted the selected audio recording|Passed|
|005-2: Deletes the currently playing audio from the playlist| Press the "Remove" key|The app will stop playing the audio recording and delete it from the playlist|The app stopped playing the audio recording and removed it from the playlist|Passed|
|006-1: Changing the playback volume|Click on the "Volume" button, move the slider to change the volume|The app will change the volume of audio recordings|The app changed the volume|Passed|
|007-1: Play the playlist again when it ends|Switch to the last audio recording in the playlist and click "Next"| The app will play the first audio recording in the playlist|The app has started playing the first audio recording|Passed|
|008-1: Playing audio recordings in any sequence|Click on the "Random" button, the icon will change to two "arrows", click on the "Next" key|The app will start playing any audio recording in the playlist|The app played an audio recording with an arbitrary number, but sometimes plays it back with its own number|Failed|
|008-2: Playing audio recordings sequentially|Click on the "Random" button, the icon will change to "AB", click on the "Next" key|The app will start playing the next audio recording in the playlist|The app has started playing the next audio recording in the playlist|Passed|
|009: Quick launch of the app|Launch B-Player.exe. Make sure that the application runs for no more than 4 seconds |The application should run for no more than 4 seconds.|The application starts in 4 seconds, but when the system is loaded, it starts in 6|Failed|
|010: All user interface elements have a name that describes the action they perform|Launch the application and check on the main window captions for all buttons|There must be captions for all buttons|There are captions for all buttons|Passed|


## Comments
* After deleting an audio recording that is being played, its name remains in the name of the currently playing audio recording.;
* When the window is resized, the cursor continues to be displayed as if stretched.
