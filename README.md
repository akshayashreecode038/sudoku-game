# 🧩 Sudoku Game – DSA Mini Project

A Sudoku game developed as a Data Structures and Algorithms (DSA) mini project. This project demonstrates the practical implementation of fundamental DSA concepts through an interactive 9×9 Sudoku puzzle.

The project includes a **C-based console application** and an **HTML, CSS, and JavaScript-based interactive version**, allowing users to experience Sudoku through both terminal-based and browser-based interfaces.

## ✨ Features

### 🎮 Gameplay
- Interactive 9×9 Sudoku board.
- Three difficulty levels: Easy, Medium, and Hard (browser version).
- Number placement with real-time validation.
- Prevention of modifications to original puzzle numbers.
- Automatic detection of completed puzzles.
- New puzzle generation in the browser version.

### 💡 Game Assistance
- Hint functionality to help solve difficult cells.
- Undo functionality to reverse previous moves.
- Automatic Sudoku solver.
- Error detection for invalid number placements.
- Timer and mistake counter in the browser version.

### 🧠 DSA Implementation
The project demonstrates the following Data Structures and Algorithms concepts:

| DSA Concept | Application |
|---|---|
| 2D Arrays | Representing and managing the 9×9 Sudoku grid |
| Recursion | Solving Sudoku by repeatedly processing empty cells |
| Backtracking | Trying possible numbers and reversing invalid choices |
| Stack | Maintaining previous moves for the Undo feature |
| Searching | Finding empty cells in the Sudoku grid |
| Functions | Dividing the program into reusable modules |

## 🛠️ Technologies Used

- **C Programming** – Core game logic and DSA implementation.
- **HTML** – Structure of the browser-based game.
- **CSS** – Styling and responsive user interface.
- **JavaScript** – Interactive gameplay and puzzle generation.

## 📂 Project Structure

```text
sudoku-game/
│
├── sudoku.c       # C implementation of the Sudoku game
├── sudoku.html    # Browser-based interactive Sudoku game
└── README.md      # Project documentation
```

## ⚙️ Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/akshayashreecode038/sudoku-game.git
```

### 2. Navigate to the Project Directory

```bash
cd sudoku-game
```

### 3. Run the C Version

Make sure GCC or another C compiler is installed.

**Compile:**

```bash
gcc sudoku.c -o sudoku
```

**Run on Windows:**

```bash
sudoku.exe
```

**Run on Linux/macOS:**

```bash
./sudoku
```

### 4. Run the Browser Version

1. Open the project folder.
2. Locate `sudoku.html`.
3. Open the file in any modern web browser.
4. Start playing!

No additional dependencies or installations are required for the browser version.

## 🎯 Sudoku Rules

- Each row must contain numbers 1–9 without repetition.
- Each column must contain numbers 1–9 without repetition.
- Each 3×3 sub-grid must contain numbers 1–9 without repetition.
- Original pre-filled numbers cannot be modified.
- Complete the grid correctly to win the game.

## 📚 Learning Outcomes

Through this project, we explored how fundamental DSA concepts can be applied to solve real-world computational problems.

Key learning outcomes include:

- Understanding the practical application of 2D arrays.
- Implementing recursive algorithms.
- Understanding backtracking through trial-and-error problem solving.
- Using stacks to maintain and reverse game operations.
- Applying searching and validation techniques.
- Developing interactive applications using programming fundamentals.

## 🚀 Future Enhancements

- Additional Sudoku difficulty levels.
- Player score tracking and leaderboard.
- Save and resume game functionality.
- More advanced puzzle-solving techniques.
- Improved user interface and gameplay experience.

## 👩‍💻 Project Information

**Project Type:** Data Structures and Algorithms Mini Project

**Primary Language:** C

**Additional Technologies:** HTML, CSS, JavaScript

---

⭐ If you find this project interesting, feel free to explore the repository!
