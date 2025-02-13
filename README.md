# Calamity Engine

A PSP Game Engine, based on SDL2.

# Build instructions

First, you will need to setup the [PSPDEV Tools](https://pspdev.github.io/installation.html).

```
git clone https://git.gay/slashed/calamity-engine/
cd calamity-engine

mkdir build && cd build
psp-cmake ..
make

# Run with PPSSPP
flatpak run org.ppsspp.PPSSPP "PATH TO BUILD FOLDER"
```