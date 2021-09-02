# Arduino Mega Z80 Core

This is a free, open source project which comprises light modification of Marat Fayzullin's brilliant Z80 emulator in C in order to make it compatible with the Arduino Mega (other Arduinos do not have the memory to run it). You can view his [download page for the original code here](https://fms.komkon.org/EMUL8/). This library is based off of [`Z80-081707.zip`](https://fms.komkon.org/EMUL8/Z80-081707.zip).

*THIS IS FIRST AND FOREMOST MARAT FAYZULLIN'S CODE AND HARD WORK. ALL I'VE DONE IS MAKE MINOR COMPATIBILITY AND CONVENIENCE MODIFICATIONS. USAGE IS SUBJECT TO HIS LICENSE TERMS ALONE.*

The changes comprise:

* Renaming the `SP` field in the state struct to `SPtr` because `SP` is a reserved keyword on AVR systems
* Renaming the defined `word` type to `zword` since word with the Arduino type of the same name
* Define `LSB_FIRST` to get existing Z80 sources working correctly
* Define `RUNZ80` and `STEPZ80` flags in order to disable the `RunZ80` inclusion and instead include `StepZ80`
* Define an additional function `StepZ80` which allows one to execute one opcode at a time, a feature I found in older versions of the emulator and loved but that was apparently removed in newer versions

# Licensing

As this is a collection of minor changes to Mr. Fayzullin's original work, it is released under [identical terms as his Z80 code](https://fms.komkon.org/EMUL8/):

* You can use these resources for any non-profit purposes, as long as you make a proper reference to [Mr. Fayzullin].
* You cannot use any of these resources to gain profit. This includes using them in commercial projects, putting them onto companion CDs, etc. If you want to use my work in a commercial project, please, contact [Mr. Fayzullin] to negotiate the terms.
* You cannot distribute these resources yourself, through your own WWW or FTP sites, even if they are non-profit. It is ok to have them as part of your non-profit software though.
* If you use my code for your own project, please, let [Mr. Fayzullin] know about it.
* The above license terms are incompatible with GPL. Thus, you should avoid making the source code from this page and any derived code part of a GPLed project.
