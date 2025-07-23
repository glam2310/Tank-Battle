# TankBattle – C++ Console Game

TankBattle is an object-oriented tank combat game written in C++ as part of an academic course project.  
The game features tanks, mines, walls, and dynamic gameplay across multiple screens, with optional computer players, recording functionality, and automated result validation.

## Features

- Multiple tanks per player
- Multiple levels (game progresses through several `.screen` files)
- Human vs Human, Human vs Computer, and Computer vs Computer modes
- Smart computer player logic
- Save & Load functionality for gameplay using `.steps` and `.result` files
- Silent mode: run the game and validate results automatically
- Step-by-step screen loading in lexicographical order
- Full control system per tank track and shooting mechanism
- Score tracking per screen and across the session

## Technologies

- **C++ using Object-Oriented Programming (OOP)**: class hierarchy, inheritance, encapsulation
- Console I/O: `gotoxy`, `_kbhit`, `_getch`, `Sleep`
- Custom file parsing and structured I/O (`.screen`, `.steps`, `.result`)
- Console-based UI running on Windows (80x25 screen size)

## Project Structure
```
TankBattle/
├── src/ # All C++ source files and class implementations
├── screens/ # Game maps in .screen format
├── steps/ # Saved gameplay input (used in -load mode)
├── results/ # Expected output files for validation (used in -silent mode)
├── files_format.txt # Explanation of .steps and .result file formats
├── README.md # Project description and instructions
```

## Files Format

A detailed explanation of the `.steps` and `.result` formats can be found in `files_format.txt`.

## Author

Stav Glam  
MTA – C++ Course 2025  
This project was submitted as part of a multi-stage programming assignment.