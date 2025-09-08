<img align="left" width="100" height="100" alt="Profil2_sym_100" src="https://github.com/user-attachments/assets/eb732e26-5008-46cd-989b-152fb5f8683b" />

# GodotSampleGDExtension
Sample Godot Project with C++ dll (GDExtension) with Visual Studio debugging.

## Content
This sample project follows the sample page from Godot Engine documentation here:
https://docs.godotengine.org/en/4.4/tutorials/scripting/gdextension/gdextension_cpp_example.html

- godot folder contains the godot project
- code folder contains the C++ code.

## Open in Visual Studio
To open it in Visual Studio, chose "Open a Local Folder" and the code folder
After opening, CMAKE should generate the proper build scripts (you can see it in Output)

## Build and debug
When building, it first retrieves and compiles godot-cpp versioin 4.4 (to change this, edit CMakLists.txt)
The compiled dll is then copied to godot/bin where GodotSampleProject.gdextension tells Godot about it

Build the x64-Debug version of the dll to debug, and select Debug debug target to launch and debug the godot project directly.
Select Edit debug target to launch the godot editor. To debug while the editor is launched you will need to attach manually to the running project.

Building the x64-Release version of the dll to export the godot project (then you should uncheck debug in godot export)

## Rename project
To rename the project
- close VS
- delete .vs folder in code
- delete out folder in code
- delete bin folder in godot
- rename top folder name
- open code folder in VS
- get a well-deserved toast

  
  



