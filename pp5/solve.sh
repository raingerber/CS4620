#!/bin/sh
echo "--test--"
./solution/dcc < untitled > solved.asm
cat defs.asm >> solved.asm
spim -file solved.asm
echo "--test--"






