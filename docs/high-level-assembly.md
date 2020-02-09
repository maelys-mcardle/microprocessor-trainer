# High Level Assembly

**High Level Assembly** is a language designed for the microprocessor trainer, to make coding a little easier. It is designed for a system that has at a minimum a 2-line display of 20 character length, with a 4 x 4 button matrix for input. In this input system, typing numbers is easy, but letters is more arduous.

It uses the concept of a **Bank** to store a value. These values have a type, which can either be boolean, integer, floating point, or string. Banks are numbered. The numbers don't have to follow one another, or be sequential. There can be gaps. Banks can also be given names.

## Reference

### Instruction Set

```
BASIC I/O

CODE  MNEMONIC  ARGUMENTS       DESCRIPTION
---  ---------  --------------  -----------
00   ###        LABEL   LITERAL Assign a name to a LABEL. If no LITERAL is specified, LABEL acts as a comment.
01   :::        BANK    LITERAL Assign a name to a BANK. This is then substituted by the interpreter like the mnemonics.
02   OUT        DEVICE  BANK    Ouput to LCD / Printer / etc, as defined by DEVICE.
                                Each invocation of OUT is on its own new line.
03   IN         DEVICE  BANK    Input from Buttons / etc, as defined by DEVICE.
                                The value is stored in the BANK after the ENTER key is pressed.
04   MOV        BANK1   BANK2   Copy BANK2 contents to BANK1. If BANK2 is not specified, clears BANK1.
```

```
TYPES

CODE  MNEMONIC  ARGUMENTS       DESCRIPTION
---  ---------  --------------  -----------
10   VAR        BANK LITERAL    Stores LITERAL in BANK. Type is inferred. If LITERAL is unspecified, clears BANK.
11   BLN        BANK LITERAL    Stores LITERAL into BANK as boolean. If LITERAL is unspecified, converts BANK into a boolean.
12   INT        BANK LITERAL    Stores LITERAL into BANK as integer. If LITERAL is unspecified, converts BANK into a integer.
13   FLT        BANK LITERAL    Stores LITERAL into BANK as float. If LITERAL is unspecified, converts BANK into a float.
14   STR        BANK LITERAL    Stores LITERAL into BANK as string. If LITERAL is unspecified, converts BANK into a string.
```

```
BRANCHING

CODE  MNEMONIC  ARGUMENTS       DESCRIPTION
---  ---------  --------------  -----------
20   ->         LABEL           Jumps to a LABEL.
21   IF=        BANK1   BANK2   If BANK1 is equal to BANK2, run the next instruction (often a JMP), otherwise go to the instruction after.
22   IF!        BANK1   BANK2   If BANK1 is not equal to BANK2, run the next instruction (often a JMP), otherwise go to the instruction after.
23   IF>        BANK1   BANK2   If BANK1 is greater than BANK2, run the next instruction (often a JMP), otherwise go to the instruction after
24   IF<        BANK1   BANK2   If BANK1 is less than BANK2, run the next instruction (often a JMP), otherwise go to the instruction after
```

```
MATH 

CODE  MNEMONIC  ARGUMENTS       DESCRIPTION
---  ---------  --------------  -----------
30   ADD        BANK1   BANK2   Add BANK2 to BANK1.
31   SUB        BANK1   BANK2   Subtract BANK2 from BANK1.
32   MUL        BANK1   BANK2   Multiply BANK2 with BANK1. Store in BANK1.
33   DIV        BANK1   BANK2   Divide BANK1 by BANK2, store result in BANK1.
34   POW        BANK1   BANK2   BANK1 to the power of BANK2, stored in BANK1.
```

```
LOGICAL 

CODE  MNEMONIC  ARGUMENTS       DESCRIPTION
---  ---------  --------------  -----------
40   NOT        BANK            Logical NOT. Inverts the value of BANK.
41   AND        BANK1   BANK2   Logical AND. Result stored in BANK1.
42   OR         BANK1   BANK2   Logical OR. Result stored in BANK1.
43   XOR        BANK1   BANK2   Logical XOR. Result stored in BANK1.
```

### Literals

`LITERAL` can be boolean, integer, floating point, or string.

If literals are inferred, it's according to the following rules:
* If 0-9 is entered, its stored as an INTEGER.
* If 0-9 with a . is entered, its stored as a FLOAT.
* If any other characters are entered, its stored as a STRING.

### Labels

Labels can be any literal value.

As it's easier in this device to enter integers, it's most commonly integers.

### Boolean Values

```
VALUE   MEANING
------  -------
0       False
1       True
```

### Devices

```
DEVICE  MNEMONIC  DESCRIPTION 
------  --------  -----------
00      LCD       LCD Display
01      BTN       Buttons
02      PRT       Thermal Printer
```

## Sample Code

### Add Two Numbers

Here's a basic program that adds two numbers, as entered by the user:

```
10 00 ENTER NUMBER ;; Store string "ENTER NUMBER" in Bank 00
02 00 00           ;; Output the contents of Bank 00 to the LCD ("ENTER NUMBER")
03 01 01           ;; Store the button presses to Bank 01
02 00 00           ;; Output the contents of Bank 00 to the LCD ("ENTER NUMBER")
03 01 02           ;; Store the button presses to Bank 02
30 01 02           ;; Add Bank 02 to Bank 01
02 00 01           ;; Output the contents of Bank 01 (the sum of the addition)
```

The interpreter would replace the above with mnemonics as the user typed:

```
VAR BANK-00 ENTER NUMBER  ;; Store string "ENTER NUMBER" in Bank 00
OUT LCD BANK-00           ;; Output the contents of Bank 00 to the LCD ("ENTER NUMBER")
 IN BTN BANK-01           ;; Store the button presses to Bank 01
OUT LCD BANK-00           ;; Output the contents of Bank 00 to the LCD ("ENTER NUMBER")
 IN BTN BANK-02           ;; Store the button presses to Bank 02
ADD BANK-01 BANK-02       ;; Add Bank 02 to Bank 01
OUT LCD BANK-01           ;; Output the contents of Bank 01 (the sum of the addition)
```

### Add Two Numbers (with named banks)

Banks can also be given names, for readability:

```
00 ADD TWO NUMBERS  ;; Comment describing program
01 00 MSG           ;; Name Bank 00 "MSG"
01 01 A             ;; Name Bank 01 "A"
01 02 B             ;; Name Bank 02 "B"
10 00 ENTER NUMBER  ;; Store string "ENTER NUMBER" in MSG
02 00 00            ;; Output the contents of MSG to the LCD ("ENTER NUMBER")
03 01 01            ;; Store the button presses to A
02 00 00            ;; Output the contents of Bank 00 to the LCD ("ENTER NUMBER")
03 01 02            ;; Store the button presses to B
30 01 02            ;; Add B to A
02 00 01            ;; Output the contents of A (the sum of the addition)
```

The interpreter would replace the above with mnemonics as the user typed:

```
### ADD TWO NUMBERS    ;; Comment describing program
::: BANK-00 MSG        ;; Name Bank 00 "MSG"
::: BANK-01 A          ;; Name Bank 01 "A"
::: BANK-02 B          ;; Name Bank 02 "B"
VAR MSG ENTER NUMBER   ;; Store string "ENTER NUMBER" in MSG
OUT LCD MSG            ;; Output the contents of Bank 00 to the LCD ("ENTER NUMBER")
 IN BTN A              ;; Store the button presses to Bank 01
OUT LCD MSG            ;; Output the contents of Bank 00 to the LCD ("ENTER NUMBER")
 IN BTN B              ;; Store the button presses to Bank 02
ADD A B                ;; Add Bank 02 to Bank 01
OUT LCD A              ;; Output the contents of Bank 01 (the sum of the addition)
```

### Are you an Adult

This program asks for your age, then tells you if you're an adult or a minor.

```
00 ARE YOU AN ADULT ;; Label describing program.
01 00 MSG           ;; Name Bank 00 "MSG"
01 01 ADULT         ;; Name Bank 01 "ADULT"
01 02 AGE           ;; Name Bank 02 "AGE"
14 00 HOW OLD ARE YOU ;; Store "HOW OLD ARE YOU" in Bank 01 00 MSG
12 01 18            ;; Store 18 (age of adulthood) in Bank 01  
02 00 00            ;; Display the message "HOW OLD ARE YOU"
03 01 02            ;; Store the button input in Bank 02 (your age)
24 02 01            ;; If Bank 02 (your age) is less than Bank 01 (age of adulthood)
20 01               ;; ...Jump to label 01.
20 00               ;; ...Otherwise jump to label 00.
00 00 IS ADULT      ;; Label 00 (for adults)
14 00 YOU ARE ADULT ;; Store "YOU ARE ADULT" in Bank 00
20 02               ;; Jump to label 02 (end).
00 01 IS MINOR      ;; Label 01 (for minors)
14 00 YOU ARE MINOR ;; Store "YOU ARE MINOR" in Bank 00
00 02 END           ;; Label 02 (end)
02 00 00            ;; Display the message in Bank 00 ("YOU ARE ADULT" or "YOU ARE MINOR")
```

The interpreter would replace the above with mnemonics as the user typed:

```
### ARE YOU AN ADULT  ;; Label describing program.
::: 00 MSG            ;; Name Bank 00 "MSG"
::: 01 ADULT          ;; Name Bank 01 "ADULT"
::: 02 AGE            ;; Name Bank 02 "AGE"
STR MSG HOW OLD ARE YOU ;; Store "HOW OLD ARE YOU" in Bank 00
INT ADULT 18          ;; Store 18 (age of adulthood) in Bank 01  
OUT LCD MSG           ;; Display the message "HOW OLD ARE YOU"
 IN BTN AGE           ;; Store the button input in Bank 02 (your age)
IF< AGE ADULT         ;; If Bank 02 (your age) is less than Bank 01 (age of adulthood)
 -> IS ADULT          ;; ...Jump to label 01.
 -> IS MINOR          ;; ...Otherwise jump to label 00.
### 00 IS ADULT       ;; Label 00 (for adults)
STR MSG YOU ARE ADULT ;; Store "YOU ARE ADULT" in Bank 00
 -> END               ;; Jump to label 02 (end).
### 01 IS MINOR       ;; Label 01 (for minors)
STR MSG YOU ARE MINOR ;; Store "YOU ARE MINOR" in Bank 00
### 02 END            ;; Label 02 (end)
OUT LCD MSG           ;; Display the message in Bank 00 ("YOU ARE ADULT" or "YOU ARE MINOR")
```

### Fibonacci Sequence

The following calculates the Fibonacci Sequence up to a user-defined number.

```
03 01 00  ;; User enters MAX. Stored in Bank 00.
12 01 01  ;; CURRENT NUMBER (Bank 01) is set to 1.
12 02 01  ;; LAST NUMBER (Bank 02) is set to 1.
00 00     ;; Start of loop
04 03 01  ;; SUM = CURRENT NUMBER
30 03 02  ;; SUM = SUM + LAST NUMBER
02 00 03  ;; Output value of SUM
23 03 00  ;; If SUM > MAX
20 01     ;; ...go to end.
04 02 01  ;; CURRENT NUMBER becomes LAST NUMBER
04 03 02  ;; SUM becomes CURRENT NUMBER
20 00     ;; Start loop over.
00 01     ;; End
```

The interpreter would replace the above with mnemonics as the user typed:

```
 IN BTN 00 ;; User enters MAX. Stored in Bank 00.
INT 01 01  ;; CURRENT NUMBER (Bank 01) is set to 1.
INT 02 01  ;; LAST NUMBER (Bank 02) is set to 1.
### 00     ;; Start of loop
MOV 03 01  ;; SUM = CURRENT NUMBER
ADD 03 02  ;; SUM = SUM + LAST NUMBER
OUT LCD 03 ;; Output value of SUM
IF> 03 00  ;; If SUM > MAX
 -> 01     ;; ...go to end.
MOV 02 01  ;; CURRENT NUMBER becomes LAST NUMBER
MOV 03 02  ;; SUM becomes CURRENT NUMBER
 -> 00     ;; Start loop over.
### 01     ;; End
```