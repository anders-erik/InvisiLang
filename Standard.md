

# InvisiLang


## Overview
- file extensions for scripts is : '.invisi'
- hex values below represent the actual binary/hex data as stored in script file (e.g. E2 = 0xE2 = 0b11100010)
- each script consists of a 'beginning' and an 'end' symbol. The script content to be executed is located between these two symbols and is organized as follows:
    - **Invisibits** (inx0, inx1) is a group of three real bytes to indicate an invisi-0 or invisi-1. 
    - **Invisibytes** (INx00-INxFF) make up all data in InvisiLang. Each Invisibyte consist of 8 consecutive invisibits (i.e. 24 real bytes for each Invisibyte).
    - **Invisicommands** (inC) are made up of two consecutive bytes and is the enabling the programmer to control the behavior of an InvisiLang program. The two Invisibytes making up a command are
        - Invisido (Actions), and
        - Invisival (Values)
    


## Script File Encoding

### Beginning of Script

```
E2 8F BF
```
- Start script: bytes 0-2 an eye icon <br>
- [⏿] (U+23FF)



### End Script

```
0A
```
- End Script - 1 byte new line
- [] (U+000A)

### Invisi-0
```
E2 80 8B
```
- invisi-0 : represents 'zero' in InvisiLang
- [​] (U+200B)

### Invisi-1
```
E2 80 8C
```
- invisi-1 : represents 'one' in InvisiLang
- [​] (U+200C)





<br>
<br>






## InvisiScript Commands

- Actions determine what InvisiScripts will do.
- Each command is represented by an action and and a value, both are one Invisibyte in length.
- Below is a list of all valid InvisiLang Command-Actions



### Invisido / Actions

---

***Print***
Invisibyte | Action name | Notes <br>
--- | --- | ---
00  |  print | Print ASCII* value of value at var-0 <br>
01  |  print | Print ASCII* value of value at var-1 <br>
02  |  print | Print ASCII* value of value at var-2 <br>
03  |  print | Print ASCII* value of value at var-3 <br>
05  |  print | Print ASCII value of provided Invisival to stdout <br>
<s>06  |  <s>read | <s>Read one byte from stdin <br>
 | | 

*Note: print mode chan be changed by setting the value of command value: 0=ASCII, 1=integer, 2=hex. Any other value is equivalent to 0. 

<br>



--- 

***Variables***
Invisibyte | Action name | Notes <br>
--- | --- | ---
10  |  var-0 | Store provided value in variable slot 0 <br>
11  |  var-1 | Store provided value in variable slot 1 <br>
12  |  var-2 | Store provided value in variable slot 2 <br>
13  |  var-3 | Store provided value in variable slot 3 <br>
 | | 

<br>


--- 

***Move***
Invisibyte | Action name | Notes <br>
--- | --- | ---
20  |  move-0 | Move value in var-0 to variable location specified by command value (e.g. INx1 -> var-1) <br>
21  |  move-1 | Move value in var-1 to variable location specified by command value (e.g. INx1 -> var-2) <br>
22  |  move-2 | Move value in var-2 to variable location specified by command value (e.g. INx1 -> var-3) <br>
23  |  move-3 | Move value in var-3 to variable location specified by command value (e.g. INx1 -> var-0) <br>
 | | 

<br>


--- 

***Math***
Invisibyte | Action name | Notes <br>
--- | --- | ---
30  |  add | add provided value to var-0 <br>
31  |  add-r | add var-1 to var-0 <br>
32  |  subtract | subtract provided value from var-0 <br>
33  |  subtract-r | subtract var-1from var-0 <br>
34  |  multiply | multiply var-0 by provided value <br>
35  |  multiply-r | multiply var-0 by var-1 <br>
36  |  divide | divide var-0 by provided invisival, rounded to nearest int <br>
37  |  divide-r | divide var-0 by var-1, rounded to nearest int <br>
38  |  percent | [ var-0 = 100 * (var-0 / Invisival)], rounded to nearest int <br>
39  |  percent-r | [ var-0 = 100 * (var-0 / var-1)], rounded to nearest int <br>
 | | 

<br>






<br>


### Invisival / Values

- Invisibytes are represented by 8 Invisibits, just like bits that make up a byte on a regular computer, with the leftmost Invisibit being the most significant.

```
inx00000000 = INx0      ~ 0
Real bits: E2808B E2808B E2808B E2808B E2808B E2808B E2808B E2808B

inx00000001 = INx1      ~ 1
Real bits: E2808B E2808B E2808B E2808B E2808B E2808B E2808B E2808C

inx10000000 = INx128    ~ 128
Real bits: E2808C E2808B E2808B E2808B E2808B E2808B E2808B E2808B

inx10001000 = INx136    ~ 136
Real bits: E2808C E2808B E2808B E2808B E2808C E2808B E2808B E2808B

inx11111111 = INx255    ~ 255
Real bits: E2808C E2808C E2808C E2808C E2808C E2808C E2808C E2808C
```
