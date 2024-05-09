# Tixel

A **ti**ny pi**xel** platformer made for the [4MB Jam](https://itch.io/jam/4mb).

## Changes from jam version

The original jam version can be browsed using the [v1.0 tag](https://github.com/kraxarn/4mb-platformer/tree/v1.0).

Changed, or planned changes, from the original jam version, in no particular order:

* [ ] Move "engine" related code to chirp
* [ ] Support any resolution / aspect ratio
* [ ] Support any framerate
* [ ] Android port
* [ ] Web port
* [ ] Options (controls, sound, resolution)
* [ ] Ability to restart level
* [ ] Improve macOS support (proper app bundle)
* [ ] Improve Windows support (hide console)
* [ ] Move resources out from executable

## Compiling

Binaries are provided for Linux, macOS and Windows (all x86_64), if you want to compile it yourself
for some reason, it's pretty easy:

```shell
git clone https://github.com/kraxarn/4mb-platformer.git
cd 4mb-platformer
cmake -DCMAKE_BUILD_TYPE=Release .
cmake --build .
./4mb_platformer
```
It's important to compile in Release or MinSizeRel mode to not enable debug mode.
