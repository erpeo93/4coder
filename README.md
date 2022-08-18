Welcome to the 4coder code base.

This codebase was authored by Allen Webster from 2014-2022, with help from a number of contributors:
+ Casey Muratori
+ "insofaras" Alex Baines
+ Yuval Dolev
+ Ryan Fleury

Also thanks to all those who supported the project, financially and/or through all your detailed feedback.

As of May 31st 2022, I am freezing this codebase and open sourcing it.

I *DO NOT* recommend learning from this codebase, especially not with an uncritical eye. It may be a useful reference for certain algorithms and architectural ideas, and it certainly contains some cautionary tales. But if you are a beginner, I encourage you to aim for more than emulating the style and structure of this codebase.

I will not be taking pull requests, or any other form of contribution in this repository. Since I am no longer maintaining this codebase, it is my intention that users who rely on 4coder will have the option to fork the codebase, fix their issues, or carry what I started in new directions according to their own vision if they would like.

The license I chose for this codebase is the very permissive MIT license. For the sake of clarity in the community of 4coder users, I ask that new forks of this codebase be given unique names.

In this readme you will find:
 1. License (MIT)
 2. Build Instructions
 3. Notes on Major Issues


# License

Copyright (c) 2022 Allen Webster

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


# Build Instructions

(0.) On MacOS: 


(Taken from https://peter-slattery.github.io/4coder-for-mac/)

0.0. brew install coreutils

The 4coder-non-source repo has prebuild libraries for freetype. Those libraries are built for Macs running on Intel chips.

I figured out how to do this by following nakst’s excellent tutorial here. It turns out, much of that isn’t necessary for our purposes however. I will detail the steps I took here.
0.1. Run the following to get the freetype source code:

curl https://mirrors.up.pt/pub/nongnu/freetype/freetype-2.9.tar.gz > freetype-2.9.tar.gz
gunzip freetype-2.9.tar.gz
tar -xf freetype-2.9.tar

0.2. cd into the freetype-2.9 folder

0.3. Run this configure command:
./configure --without-zlib --without-bzip2 \
--without-png --without-harfbuzz \
CFLAGS="-g -ffreestanding -Wno-unused-function"

0.4. Run the make command: make ANSIFLAGS="" > /dev/null

0.5. Copy freetype-2.9/objs/.libs/libfreetype.a to 4ed/4coder-non-source/foreign/x64/libfreetype-mac.a (Remember to rename the original if you want to compile for x64 at some point in the future)



1. Create an empty folder named "4ed" to contain the codebase.
2. Clone the repository
3. Rename the folder containing the repository to "code"
4. At the same level as the "code" folder, clone the "4coder-non-source" repository
5. At the same level as the "code" folder, create an empty folder and name it "build"
6. A. On windows setup the visual studio command line magic sauce so that "cl" works
   B. On linux setup g++
   C. On mac setup clang
7. Navigate to the "4ed/code" folder.
8. A. On windows run "bin\build.bat"
   B. On linux run "bin\build-linux.sh"
   C. On MacOS run "bin\build-mac.sh"
(9.) On Windows, Make sure you copy the "fonts" folder from the "4coder-non-source" repo into the executable folder  


# Notes on Major Issues

1. The build system and organization of files is extremely complicated. There is a 4ed_build.cpp that defines how builds run, and the build scripts have to build and run this C++ file. The file is pretty chaotic since it cannot rely on the codebase's usual helpers. On top of that there is a totally separate build system for the custom layer which is also a big gigantic mess of its own. It involves several stages of compilation, and a number of metaprograms.

2. The documentation system is over complicated & the documentation is incomplete. There is very little documentation for the internals or the complicated layers of helpers.

3. The lexer generator is way too complicated, and the built-in support for language features is not fully developed. The background threaded parsing is not very carefully organized and is not very flexible, so it's hard to add new languages at any level of the system.

4. There are a few layers of overcomplicated configuration parsers.

5. Mac support has not been maintained for several versions.

6. The codebase has a very weak base layer with key features that were added very late, so lots of code was written in the absence of useful features to bind things together. To make matters worse the base layer is split by the distinction of custom layer & core layer, leading to some double definitions and some incosistencies.



