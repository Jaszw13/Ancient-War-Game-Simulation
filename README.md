
# COMP2011 Fall 2024 PA1: Ancient War Game Simulation
A text-based ancient war game simulation, featuring warrior movement, close-range combat, and long-range shooting mechanics on a 2D grid.

## 📁 Project Structure
```
pa1_skeleton/
├── pa1.cpp               # Core logic (input handling, action simulation, output)
├── testcase/             # Test case files (inputX.txt for different scenarios)
└── .gitignore            # Git ignore rules for C++ assignments (e.g., executables)
```

## 🎯 Core Features
- **Warrior Management**: Track warrior attributes (HP/FP/SP) and positions on a 2D grid (max 20×30).
- **Action Simulation**:
  - **Move**: 4-directional movement (east/south/west/north) with boundary/collision checks.
  - **Fight**: Close-range combat (4 directions) with HP reduction and position takeover (if target is eliminated).
  - **Shoot**: Long-range attack (8 directions) with HP reduction (no position takeover).
- **Input/Output**: Read structured input (warrior attrs, map, actions) and print real-time game state (map + warrior stats).
- **Validation**: Check for invalid actions (out-of-bounds, empty targets, invalid directions).

## 🛠️ How to Compile & Run
### Compile (in `pa1_skeleton/` directory):
```bash
g++ pa1.cpp -o pa1 -Wall  # -Wall enables all warning messages (recommended)
```
### Run with test cases:
#### Option 1: Output to terminal
```bash
./pa1 < testcase/input1.txt
```
#### Option 2: Save output to a file (for comparison)
```bash
./pa1 < testcase/input1.txt > output1.txt
```

## 📚 PA Requirements
- **Header Restriction**: Only `iostream` and `cstring` headers are allowed (no extra libraries).
- **Technical Constraints**:
  - Maximum map size: 20 rows × 30 columns.
  - Maximum warriors: 26 (labeled A-Z, one per letter).
  - No generative AI (e.g., ChatGPT) usage — all code must be original.
- **Action Rules**:
  - Movement fails if path is blocked (other warrior) or out of map bounds.
  - Fight/shoot fails if target cell is empty or out of bounds.

## 🧪 Test Cases
The `testcase/` directory includes typical test scenarios to verify:
1. Basic warrior initialization and map loading.
2. Valid/invalid movement (boundary/collision checks).
3. Fight action (HP reduction + position takeover for eliminated targets).
4. Shoot action (8-directional attack with HP reduction only).
5. Edge cases (e.g., warrior elimination, consecutive actions).

## 📌 Author
- **Your Name** Jaszw13
- Course: COMP2011 (HKUST Fall 2024)
- Assignment: PA1 Ancient War Game Simulation
```的功能和要求，包含编译运行指令、核心规则和测试用例说明。
