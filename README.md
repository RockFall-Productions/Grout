# Grout Engine

<p align="center">
  <a href="https://github.com/RockFall-Productions/Grout">
    <img src="grout_logo.svg" width="400" alt="Grout Engine Logo">
  </a>
</p>

## What is it supposed to be?

**[Grout](https://github.com/RockFall-Productions/Grout) is an 2D/3D cross-plataform graphics engine, designed for easily generating visual simulations in an unified interface.** Grout can also be a powerful tool for designing games or any kind of visual ambience. With Grout the user can architect smart simulations and have visual and good-looking output, leading to unique insights without spending a lot of time worrying about rebuilding the entire graphical environment.

## What it really is?

In it's current state, Grout is a 2D/3D static library wraping openGL and prepared to deal with other graphics APIs, though not yet implemented. It is built with an custom Events System and Core/App Logging, 2D texture and 3D models uploading and a custom app-oriented graphic interface (ImGUI).
(Grout is, at this point, only tested and developed for Windows systems)

## How to use it?

(For Windows)
Grout is built using premake5, making it easy to use alongside Visual Studio. After downloading, run the "GenerateProjects.bat" file, or in the cmd:
```call vendor\bin\premake\premake5.exe vs2019```
