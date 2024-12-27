# Hangman Game README

## Overview
This is a console-based **Hangman Game** implemented in C++ that allows players to guess a word by suggesting letters within a limited number of lives. The game supports different difficulty levels and maintains a leaderboard to track player scores.

## Features
1. **Difficulty Levels**: 
   - Easy, Medium, and Hard levels with predefined word lists.
2. **Word Selection**:
   - Words are randomly selected based on the chosen difficulty.
3. **File Handling**:
   - Reads word lists from text files (`easy.txt`, `medium.txt`, `hard.txt`).
   - Saves and retrieves leaderboard data from `leaderboard.txt`.
4. **Leaderboard**:
   - Tracks player names and scores, sorted by score in descending order.
5. **Interactive Gameplay**:
   - Displays the Hangman drawing as the game progresses.
   - Tracks guessed letters and remaining lives.

## Requirements
- A C++ compiler that supports C++11 or later.
- Standard libraries including `<iostream>`, `<fstream>`, `<vector>`, and others.

## Setup Instructions
1. **Clone the Repository**:
   - Clone or download the repository containing the source code and predefined word files.
2. **Prepare Word Files**:
   - Ensure `easy.txt`, `medium.txt`, and `hard.txt` exist in the working directory. If not, they will be initialized automatically with predefined words.
3. **Compile the Code**:
   - Use any C++ compiler (e.g., g++, Visual Studio) to compile `main.cpp`.
   - Example:
     ```bash
     g++ -o hangman main.cpp
     ```
4. **Run the Game**:
   - Execute the compiled binary:
     ```bash
     ./hangman
     ```

## How to Play
1. **Start the Game**:
   - Enter your name and select a difficulty level.
2. **Gameplay**:
   - Guess letters to uncover the hidden word.
   - Each incorrect guess reduces the number of lives and adds to the Hangman drawing.
   - The game ends when:
     - You correctly guess the word.
     - You run out of lives.
3. **Leaderboard**:
   - After the game, your score is saved to the leaderboard.

## File Structure
- **Source Code**:
  - `main.cpp`: The main source file containing the game logic.
- **Word Files**:
  - `easy.txt`, `medium.txt`, `hard.txt`: Contain word lists for different difficulty levels.
- **Leaderboard**:
  - `leaderboard.txt`: Stores player names and scores.

## Sample Output
```
Enter your name: Dar
Select difficulty (easy, medium, hard): easy

  +---+
      |
      |
      |
     ===
Current word: _ _ _
Lives remaining: 6
Guessed letters: 
Enter your guess: o

Congratulations, Dar! You guessed the word: fox

Leaderboard:
-------------------
Name           Score
-------------------
Dar           60
-------------------
```



