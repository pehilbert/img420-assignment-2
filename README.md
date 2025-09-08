# GodotSampleGDExtension
Sample Godot Project with C++ dll (GDExtension) with Visual Studio debugging.

This sample project follows the sample page from Godot Engine documentation here:
https://docs.godotengine.org/en/4.4/tutorials/scripting/gdextension/gdextension_cpp_example.html

- godot folder contains the godot project
- code folder contains the C++ code.
To open it in Visual Studio, chose "Open a Local Folder" and the code folder
After opening, CMAKE should generate the proper build scripts (you can see it in Output)
When building, it first retrieves and compiles godot-cpp versioin 4.4 (to change this, edit CMakLists.txt)
The compiled dll is then copied to godot/bin where GodotSampleProject.gdextension tells Godot about it

Build the x64-Debug version of the dll to debug, and select Debug to launch and debug the godot project directly.
Select Edit to launch the godot editor. To debug while the editor is launched you will need to attach manually to the running project.

Building the x64-Release version of the dll to export the godot project (then you should uncheck debug in godot export)





