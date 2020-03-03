# Are you an Adult

This program asks for your age, then tells you if you're an adult or a minor.

```
00 ARE YOU AN ADULT ;; Comment describing program.
02 00 MSG           ;; Name Bank 00 "MSG"
02 01 ADULT         ;; Name Bank 01 "ADULT"
02 02 AGE           ;; Name Bank 02 "AGE"
14 00 HOW OLD ARE YOU ;; Store "HOW OLD ARE YOU" in Bank 01 00 MSG
12 01 18            ;; Store 18 (age of adulthood) in Bank 01  
03 00 00            ;; Display the message "HOW OLD ARE YOU"
04 01 02            ;; Store the button input in Bank 02 (your age)
25 02 01            ;; If Bank 02 (your age) is less than Bank 01 (age of adulthood)
20 01               ;; ...Jump to label 01.
20 00               ;; ...Otherwise jump to label 00.
01 00 IS ADULT      ;; Label 00 (for adults)
14 00 YOU ARE ADULT ;; Store "YOU ARE ADULT" in Bank 00
20 02               ;; Jump to label 02 (end).
01 01 IS MINOR      ;; Label 01 (for minors)
14 00 YOU ARE MINOR ;; Store "YOU ARE MINOR" in Bank 00
01 02 END           ;; Label 02 (end)
03 00 00            ;; Display the message in Bank 00 ("YOU ARE ADULT" or "YOU ARE MINOR")
```

The interpreter would replace the above with mnemonics as the user typed:

```
!!! ARE YOU AN ADULT    ;; Comment describing program.
    @00 MSG             ;; Name Bank 00 "MSG"
    @01 ADULT           ;; Name Bank 01 "ADULT"
    @02 AGE             ;; Name Bank 02 "AGE"
STR MSG HOW OLD ARE YOU ;; Store "HOW OLD ARE YOU" in Bank 00
INT ADULT 18            ;; Store 18 (age of adulthood) in Bank 01  
 << OUT MSG             ;; Display the message "HOW OLD ARE YOU"
 >>  IN AGE             ;; Store the button input in Bank 02 (your age)
IF< AGE ADULT           ;; If Bank 02 (your age) is less than Bank 01 (age of adulthood)
 -> IS ADULT            ;; ...Jump to label 01.
 -> IS MINOR            ;; ...Otherwise jump to label 00.
### :00 IS ADULT        ;; Label 00 (for adults)
STR MSG YOU ARE ADULT   ;; Store "YOU ARE ADULT" in Bank 00
 -> END                 ;; Jump to label 02 (end).
### :01 IS MINOR        ;; Label 01 (for minors)
STR MSG YOU ARE MINOR   ;; Store "YOU ARE MINOR" in Bank 00
### :02 END             ;; Label 02 (end)
 << OUT MSG             ;; Display the message in Bank 00 ("YOU ARE ADULT" or "YOU ARE MINOR")
```