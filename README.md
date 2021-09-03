# Z80 Core for Arduino Mega

**This library only functions with the Arduino Mega or Mega 2560 due to memory constraints!**

This is a free, open source project which comprises light modification of Marat Fayzullin's brilliant Z80 emulator in C in order to make it compatible with the Arduino Mega (other Arduinos do not have the memory to run it). You can view his [download page for the original code here](https://fms.komkon.org/EMUL8/). This library is based off of [`Z80-081707.zip`](https://fms.komkon.org/EMUL8/Z80-081707.zip).

Reading over `Z80.h` is strongly encouraged to get a feel for the bitfields and core CPU structs, as well as the functions you must implement (see *Usage* below) and optional ones you can enable with by `#define`ing flags (such as running until `HALT` or running n cycles at a time as opposed to one opcode at a time, which is the default behavior).

*THIS IS FIRST AND FOREMOST MARAT FAYZULLIN'S CODE AND HARD WORK. ALL I'VE DONE IS MAKE MINOR COMPATIBILITY AND CONVENIENCE MODIFICATIONS. USAGE IS SUBJECT TO HIS LICENSE TERMS ALONE.*

The changes comprise:

* Renaming the `SP` field in the state struct to `SPtr` because `SP` is a reserved keyword on AVR systems
* Renaming the defined `word` type to `zword` since word with the Arduino type of the same name
* Define `LSB_FIRST` to get existing Z80 sources working correctly
* Define `RUNZ80` and `STEPZ80` flags in order to disable the `RunZ80` inclusion and instead include `StepZ80`
* Define an additional function `StepZ80` which allows one to execute one opcode at a time, a feature I found in older versions of the emulator and loved but that was apparently removed in newer versions

# Usage

In order to compile this library, you need to implement five functions in your main `.ino` file:

```C
// This is not mandatory in and of itself but is used in the below examples
// and defines 128 bytes of memory to be read and written to
byte ram[128];

// Memory write -- write the Value to memory location Addr
void WrZ80(register zword Addr, register byte Value) {
  ram[Addr] = Value;
}

// Memory read -- read the value at memory location Addr
byte RdZ80(register zword Addr) {
  return ram[Addr];
}

// IO -- output the Value on the given IO Port
// This is generally optional to have functional unless your code uses IO
void OutZ80(register zword Port, register byte Value) {}

// IO -- read a value from an IO Port (currently defaults to 0)
// This is generally optional to have functional unless your code uses IO
// The only requirement is that is must return a byte (0, in this case)
byte InZ80(register zword Port) {
  return 0;
}

// Advanced -- called when an emulator-specific opcode of
// ED FE is encountered. Generally can be left empty.
void PatchZ80(register Z80 *R) {}
```

*Without these functions implemented, you will recieve compilation errors.*

# Example

Below is a basic example program which runs a small program to count up by twos at `0x0010` and print the program counter and contents of `0x0010` as it goes.

```C
#define MEM_SIZE 512
#define STEP_DELAY 300

#include <Z80.h>

/*
 * Global declaration of RAM. This demo program counts
 * up by 2s at memory address 0x0010.
 */
byte ram[MEM_SIZE] = {
  // count by 2s at 0x10
  0x3E, 0x00,         // LD   A,$04
  0x32, 0x10, 0x00,   // LD   ($0010),A
  0x3A, 0x10, 0x00,   // LD   A,($0010)
  0x3C,               // INC   A
  0x3C,               // INC   A
  0x32, 0x10, 0x00,   // LD   ($0010),A
  0x18, 0xF6          // JR   $5
};

// Memory write -- write the Value to memory location Addr
void WrZ80(register zword Addr, register byte Value) {
  ram[Addr] = Value;
}

// Memory read -- read the value at memory location Addr
byte RdZ80(register zword Addr) {
  return ram[Addr];
}

// IO -- output the Value on the Port (currently does nothing)
void OutZ80(register zword Port, register byte Value) {}

// IO -- read a value from Port (currently defaults to 0)
byte InZ80(register zword Port) {
  return 0;
}

// Advanced -- called when an emulator-specific opcode of
// ED FE is encountered. Generally can be left empty.
void PatchZ80(register Z80 *R) {}

// create a CPU core object
Z80 cpu;

void setup() {
  Serial.begin(9600);

  // Reset the CPU to 0x00 and zero the regs/flags
  ResetZ80(&cpu);
}

void loop() {
  // print out current program counter
  // see Z80.h for the struct definition + fields
  Serial.print("PC: ");
  Serial.println(cpu.PC.W);

  // execute single opcode from memory at the current PC
  StepZ80(&cpu);

  // display the contents of memory where we're counting up (0x0010)
  Serial.print("Current value of 0x0010: ");
  Serial.println(RdZ80(0x0010));

  // delay before stepping again so you can watch it count up slowly
  delay(STEP_DELAY);
}
```
