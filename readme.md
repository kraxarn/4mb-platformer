# Tixel

A **ti**ny pi**xel** platformer made for the [4MB Jam](https://itch.io/jam/4mb).

## Compiling

Binaries are provided for Linux, macOS and Windows (all x86_64), if you want to compile it yourself
for some reason, it's pretty easy:

```shell
git clone --recursive https://github.com/kraxarn/4mb-platformer.git
cd 4mb-platformer
cmake -DCMAKE_BUILD_TYPE=Release .
cmake --build .
./4mb_platformer
```
