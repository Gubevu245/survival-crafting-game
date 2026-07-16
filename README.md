# C++ Survival Game

A fun survival game made in C++. You play on a grid and explore the wild. You need to collect items and build tools to stay alive before you run out of turns. The game keeps track of your items and has clear rules for winning or losing.

## Game Features
* **Building Items:** Collect Sticks and Flints to make an Axe. Use more items to build a Firekit to win!
* **Item Bag:** The game easily tracks exactly what you have collected and built.
* **Turns and Time:** Every time you move or do something, it costs a turn. You must win before your turns run out.
* **Changing the Map:** Once you build an Axe, you can chop down trees to clear your path and get logs.
* **Smooth Screen:** The game screen updates smoothly without flashing or glitching when you move.
* **Clean Code:** The game uses memory well and cleans up after itself when you close it.

## Built With
* **Language:** C++
* **Program Used:** Code::Blocks

## How to Play
1. Open the `.cbp` file in Code::Blocks or run it from your command line.
2. The game needs some numbers to start up (like how big the map is and how many turns you get):
   `[GameName] <Rows> <Cols> <BushChance> <Trees> <Flints> <Turns>`
   *(Example: `BushGame 15 15 10 8 4 50` creates a 15x15 map with 8 trees, 4 flints, and gives you 50 turns)*
3. **Controls:**
   * `W / A / S / D` - Move Up, Left, Down, Right
   * `Q / E / Z / C` - Move Diagonally (Corners)
   * `1` - Open the Crafting Menu to build tools
   * `X` - Quit the game
4. **Map Symbols:**
   * `P` - You (The Player)
   * `#` - Bushes (Walk here to get Sticks)
   * `O` - Flint
   * `T` - Trees (You need an Axe to chop these and get Logs)

## Setup Instructions
To play this on your own computer, download the files and run this in your terminal:
```bash
git clone [https://github.com/Gubevu245/cpp-survival-crafting-game.git](https://github.com/Gubevu245/cpp-survival-crafting-game.git)
g++ main.cpp RecipeSpace.cpp -o BushGame
./BushGame 15 15 10 8 4 50
