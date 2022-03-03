# Godot Advanced Controls

This'll give your project access to motion controls and trackpads.

There's a little demo project included to show how it's meant to be used.

I have *no* idea how SCons works, and barely got it to compile for Linux.
By the magic of open source technology, you're on your friggin' own if you
run Windows or Mac.

I'll happily accept any working alterations to the SCons file~!

Language: [GDNative C++](https://docs.godotengine.org/en/latest/tutorials/scripting/gdnative/index.html)

Renderer: GLES 3

Dependencies:
 * `clang`, `gcc`, or any decent C++ compiler that's C++14 compatible.

## Compiling

You can use SCons to compile the library:

```
scons platform=PLATFORM
```

Where PLATFORM is: `windows`, `linux`, or `osx`.

This creates the file `libadvancedcontrols` in the respective
subfolders in the `project/gdnative` directory.

