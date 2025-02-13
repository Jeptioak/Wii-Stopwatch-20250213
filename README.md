# Wii-Stopwatch
As the name says... it's a stopwatch for the Wii. It's written in C and uses DevKitPPC for its dev environement.

The Stopwatch is written in C, and uses the DevKitPPC (PPC standing for PowerPC) environement. I'll also be using their library that you can find here: https://github.com/devkitPro/libogc

To edit, it is highly recommended you modify the `template-to-edit-utf8.c` file to avoid encoding errors.

## Get started
1. Install/Set-up [devkitPro](https://devkitpro.org/wiki/devkitPro_pacman#Customising_Existing_Pacman_Install).
2. Clone this repository.

### Compiling
3. Open a terminal and enter`cd <"Wii-Stopwatch-Main" folder>` to use the root of the repositoy.
4. Enter `iconv -f UTF-8 -t CP437 ./template-to-edit-utf8.c > ./source/template.c && make` to compile the project.
