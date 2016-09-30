# Sparrowhawk tutorial

This repository contains a simple example on how to use the Sparowhawk text-to-speech normalizer in your own C++ program.

The engine itself is available in the following repository:

https://github.com/google/sparrowhawk

## Note

This example only explains how to set up and compile the C++ program using a sample language. It does not contain any information on how to create the necessary files for using it with a different language.

# Installation

While the instruction for installation is available on other sources, I would like to provide a few hints for people who are just starting out and stuck on some steps.

## 1. Get OpenFST and Thrax

This engine relies heavily on OpenFST and the Thrax grammar compiler. These are pretty standard tools and used in many different projects. They are used to represent the rules of the language in a consistent and usable fashion. It's highly recommended to go through some examples on the OpenFST website (they're pretty fun!).

My personal advice is to not install OpenFST system-wide, since some projects (e.g. Kaldi) don't like that and you can always install it in a local dir and use it from there.

  1. download a fresh version of OpenFST (I used 1.5.4), save and unpack it somewhere convenient  
  2. inside do configure, but add the prefix and some the extra modules (do `./configure --help` to see a list and install more if you want - it doesn't hurt anything):
    `./configure --prefix=/your/apps/dir/openfst --enable-far --enable-linear-fsts`
  3. set up CPPFLAGS and LDFLAGS, since you are using OpenFST in a non-standard and non-global directory:
    `export CPPFLAGS=-I/your/apps/dir/openfst/include
    export LDFLAGS=-I/your/apps/dir/openfst/lib`
  4. do `make` and `make install` (no sudo neccessary in this case) -- hint, do `make -j8` to parallelize compiling and speed things up
  5. download and unpack Thrax (my version was 1.2-2) similarly to how you did OpenFST
  6. do configure, just like before (set the prefix to the same openfst directory, to make things simpler):
    `./configure --prefix=/your/apps/dir/openfst`
    If you set up the flags correctly and installed all the necessary extensions, the configure shouldn't complain about not being able to find some files.  
    
Once you have OpenFST and Thrax installed, you will find some useful programs and libraries in the chosen directory. Again, look for some tutorials on OpenFST and Thrax to learn what they do.

## 2. Install RE2

This is a pretty standard and not too big library for regular expressions. According to their instructions, you should be able to do the following:

  1. `cd /your/apps/dir`
  2. `git clone https://github.com/google/re2`
  3. `cd re2`
  4. `make`
  5. `make test`
  6. `make install`
  7. `make testinstall`
  
If you get an error with `unknown array size in delete`, simply add `[0]` next to `std::atomic<State*> next_`, as per the issue here:

https://github.com/google/re2/issues/102

## 3. Install protobuf

This is a pretty involved library that provides an interface to the engine and allows it to be used in various environments (I think). Anyway, it's also pretty standard and you can use the instructions (from https://github.com/google/protobuf/blob/master/src/README.md) to install it:

  1. `cd /your/apps/dir`
  2. `git clone https://github.com/google/protobuf`
  3. `cd protobuf`
  4. `autogen.sh`
  5. `make`
  6. `make check`
  7. `sudo make install`
  8. `sudo ldconfig`
  
If you get errors on the `make check` step, you can either skip it, or you can go into `src/Makefile` and remove the `-Werror` switch and try again. Some warnings are not that harmful, and the check should go fine, even with them in place.

## 4. Install Sparrowhawk

This is the actual project you need. Make sure you have your OpenFST paths set in CPPFLAGS and LDFLAGS and you can run the simple, standard steps:

  1. `./configure`
  2. `make`
  3. `make install`

Note that Sparrowhawk installs itself in `/usr/local` so it will likely not be globally visible.
  
  
# Compiling this project

This project was created using CLion and it uses CMake to compile the single CPP file included. If you are goind to use CLion yourself, make sure you edit the CMakeLists.txt file and change the include and link directories to your locations of OpenFST and Thrax. After that, you should be able to simply do Build All. To run the program, you will also need to modify the LD_LIBRARY_PATH in the Edit Configurations, accordingly.

If you want to compile it yourself, simply make sure to link all the requisite dynamic libraries:

  * sparrowhawk
  * dl
  * re2
  * protobuf
  * pthread
  * thrax
  * fst
  * fstfar
  
Likewise, if you are running it from the terminal, make sure you have the right libraries visible (e.g. using LD_LIBRARY_PATH), and that includes both OpenFST and Sparrowhawk, which generally ends up in /usr/local/lib
 
# About executing this project

This simple example creates the Normalizer class and sets up the Afrikaans language grammars provided by Google. It then provides a short string to the normalize method and prints out both the input and the output:

```
[DEBUG:normalizer.cc:146] Verbalizing: [	"123(r
123]
[DEBUG:normalizer.cc:179] Verbalize output: Words
I have honderd drie en twintig apples sil
INPUT: I have 123 apples.

OUTPUT: I have honderd drie en twintig apples sil
```