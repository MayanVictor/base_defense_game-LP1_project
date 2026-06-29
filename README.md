# Base Defense

This project is a game where you must defend a base against enemies that will shoot at you and the base; your goal is to prevent the base from being destroyed until the wave ends.

## Controls

click with the mouse moves the player.
Aim with the mouse.
Shoot with the Key Q.

## Project Structure

C++ Developed Project Using Raylib

## Dependences

- MSYS2 UCRT64
- Raylib 5.5
- GCC 15+

## Compile

Compile the project with:

```bash
g++ src/the_invasion.cpp src/Player.cpp src/Enemy.cpp src/Base.cpp src/Bullet.cpp -o the_invasion.exe -Iinclude -I/ucrt64/include -L/ucrt64/lib -lraylib
```

Run the executable:

```bash
./the_invasion.exe
```

Or you can add the .vscode paste and then you can press F5 to compile and run the code.

