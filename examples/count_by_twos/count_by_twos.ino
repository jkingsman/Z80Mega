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

/*
 * Five mandatory functions! Compilation will fail if these are
 * not defined. You must implement them yourself.
 */

// Memory write -- write the Value to memory location Addr
void WrZ80(register zword Addr, register byte Value) {
  ram[Addr] = Value;
}

// Memory read -- read the value at memory location Addr
byte RdZ80(register zword Addr) {
  return ram[Addr];
}

// IO -- output the Value on the Port (currently does nothing)
// This is generally optional unless your code uses IO
// Can be left blank.
void OutZ80(register zword Port, register byte Value) {}

// IO -- read a value from Port (currently defaults to 0)
// This is generally optional unless your code uses IO
// Can be left empty as long as it returns a byte.
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
  Serial.println(RdZ80(0x010));

  // delay before stepping again so you can watch it count up slowly
  delay(STEP_DELAY);
}
