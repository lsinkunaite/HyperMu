#!/bin/bash

echo "==============================="
echo "Enter z-shift: "
echo -e "\n"
read zshift
echo "Enter phi-shift: "
echo -e "\n"
read phishift

echo "Current presets: z-shift = $zshift, phi-shift = $phishift"


cd ~/code/g4bl

echo "Current depository: ${pwd}" 

echo "Now, running the script"

g4bl recover.g4bl

echo "Script ran successfully!"
