# 2dSimpleGameLibrary

A Simple 2d Game Library with some prebuilt systems to help you make simple 2d games, it use SDL for window creating and rendering (i perfectly know it is a bad practice but i wanted a simple portfolio thing to show, in a more sophisticated scenario i would have end up abstracting vulkan/directx/opengl graphic apis.

### Features

- Game Objects PreBuilt System.
- Rendering PreBuilt System (separeted from main game loop).
- Debug Mode with ImGui.
- Texture System.
- Collider System (with pyshics).
- More...

### Setup 

In order to make everything works you need to go in project solution property and add this settings.
- Download the directory files and copy it into your project folder as you see them.
- Go to **General/C++ Standard** and set to c++20
- Go to **Linker/General/AdditionalLibraryDirectories** and add the following property **$(ProjectDir)SDLGameLib\Vendors\Binaries**
- Go to **Linker/Input/AdditionalLibraries** and add the following properties **SDL2.lib;SDL2main.lib;SDL2_image.lib;**

### How It Works
Once you downloaded it and setup, you should have something like this.
![immagine](https://user-images.githubusercontent.com/85369525/207132906-8f2d8c28-3cea-42fe-805b-11840979baeb.png)
