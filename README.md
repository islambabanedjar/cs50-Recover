# Recover – JPEG Image Recovery

## Overview
Recover is a command-line program written in C that recovers JPEG images from a forensic memory card image.

This project was developed as part of Harvard's CS50 Introduction to Computer Science course.

## How It Works
- Reads the input file in blocks of 512 bytes.
- Checks each block for the JPEG signature.
- Creates a new JPEG file whenever a JPEG header is detected.
- Writes the corresponding data blocks into the recovered image.

## JPEG Signature
The program identifies JPEG files using the following byte pattern:

- First byte: `0xFF`
- Second byte: `0xD8`
- Third byte: `0xFF`
- Fourth byte: `(byte & 0xF0) == 0xE0`

## Requirements
- GCC compiler
- Linux or another environment with a C compiler

## Compilation

```bash
gcc recover.c -o recover
## Usage

./recover card.raw

## Technologies
- C
- Standard I/O
- Binary file handling
- JPEG signatures

## Limitations
This implementation is designed for the CS50 forensic recovery exercise. It assumes 512-byte blocks and is not a general-purpose tool for recovering files from every storage device.

## Acknowledgment
Harvard University – CS50 Introduction to Computer Science.
