# Sparrowhawk tutorial

This repository contains a simple example on how to use the Sparowhawk text-to-speech normalizer in your own C++ program.

The engine itself is available in the following repository:

https://github.com/google/sparrowhawk

## Note

This example only explains how to set up and compile the C++ program using a sample language. It does not contain any information on how to create the necessary files for using it with a different language.

The program shown here is not strictly neccessary to use Sparrohawk. It merely explains the install procedure and shows how you can use it in a C++ program. To play around in Sparrowhawk, you can use the `normalizer_main` program included in Sparrowhawk's repository. Read this page for more details on Sparrowhawk:

https://github.com/google/sparrowhawk/tree/master/documentation

# Installation

While the instruction for installation is available on other sources, I would like to provide a few hints for people who are just starting out and stuck on some steps. It is recommended to install everything in a safe environemnt, like virtualenv or conda, because some of the libraries can cause issues if installed globally (eg. OpenFST may cause problems with Kaldi if installed globally).

For this document, I will be using conda, but feel free to use anything else (or install globally). You can change `$CONDA_PREFIX` in the description below to whatever meets your needs. To install conda, look for a script online (eg. https://conda.io/miniconda.html) and then do the following steps to create a suitable environment:

  1. Create tan environemnt which we will call sparrowhawk:
```
conda create --name=sparrowhawk
```
  2. Use this to activate the environment anytime you want to use this program:
```
source activate sparrowhawk
```
    * you can leave the environment using this command :
```
source deactivate
```
  3. We will store all the files in the main env directory:
```
cd $CONDA_PREFIX
```
  4. Before we can do that, we should set some environment variables:
```
mkdir -p etc/conda/activate.d
printf '#!/bin/bash\n\nexport CPPFLAGS=-I$CONDA_PREFIX/include\nexport LDFLAGS=-L$CONDA_PREFIX/lib\nexport LD_LIBRARY_PATH=$CONDA_PREFIX/lib\n' > etc/conda/activate.d/env.sh
chmod +x etc/conda/activate.d/env.sh
source deactivate
source activate sparrowhawk
```

Now you should be all set to perform the steps below.

## 1. Get OpenFST and Thrax

This engine relies heavily on OpenFST and the Thrax grammar compiler. These are pretty standard tools and used in many different projects. They are used to represent the rules of the language in a consistent and usable fashion. It's highly recommended to go through some examples on the OpenFST website (they're pretty fun!).

  1. download a fresh version of OpenFST, save and unpack:
```
wget http://www.openfst.org/twiki/pub/FST/FstDownload/openfst-1.6.3.tar.gz
tar xvf openfst-1.6.3.tar.gz
cd openfst-1.6.3
```
  2. inside do configure, but add the prefix and some the extra modules (do `./configure --help` to see a list and install more if you want - it doesn't hurt anything):
```
./configure --prefix=$CONDA_PREFIX --enable-far --enable-linear-fsts --enable-pdt --enable-mpdt --enable-grm
```
  3. do `make` and `make install` (no sudo neccessary in this case) -- hint, do `make -j8` to parallelize compiling and speed things up
  4. download and unpack Thrax similarly to how you did OpenFST:
```
wget http://www.openfst.org/twiki/pub/GRM/ThraxDownload/thrax-1.2.3.tar.gz
tar xvf thrax-1.2.3.tar.gz
cd thrax-1.2.3
```
  6. do configure, just like before:
```
./configure --prefix=$CONDA_PREFIX
```
  7. do `make` and `make install` 
     
Once you have OpenFST and Thrax installed, you will find some useful programs and libraries in the chosen directory. Again, look for some tutorials on OpenFST and Thrax to learn what they do.

## 2. Install RE2

This is a pretty standard and not too big library for regular expressions. According to their instructions, you should be able to do the following:

  1. `cd $CONDA_PREFIX`
  2. `git clone https://github.com/google/re2`
  3. Edit the Makefile and change the `prefix` variable to this:
     `prefix=$(CONDA_PREFIX)`
  3. `cd re2`
  4. `make`
  5. `make test`
  6. `make install`
  7. `make testinstall`

## 3. Install protobuf

This is a pretty involved library that provides a communication layer (a protocol buffer) for different modules within Sparrowhawk Anyway, it's also pretty standard and you can use the instructions (from https://github.com/google/protobuf/blob/master/src/README.md) to install it:

  1. `cd $CONDA_PREFIX`
  2. `git clone https://github.com/google/protobuf`
  3. `cd protobuf`
  4. `autogen.sh`
    - Sometimes the commands below will complain about the wrong version of automake. Simply run `autoreconf` to fix this.
  5. `./configure --prefix=$CONDA_PREFIX`
  5. `make`
  6. `make check`
  7. `make install`
  
If you get errors on the `make check` step, you can either skip it, or you can go into `src/Makefile` and remove the `-Werror` switch and try again. Some warnings are not that harmful, and the check should go fine, even with them in place.

## 4. Install Sparrowhawk

This is the actual project you need. Make sure you havemake -j your OpenFST paths set in CPPFLAGS and LDFLAGS and you can run the simple, standard steps:

  1. `cd $CONDA_PREFIX`
  2. `git clone https://github.com/google/sparrowhawk`
  3. `cd sparrowhawk`
     - you may also need to do `autoreconf` here
  4. `./configure --prefix=$CONDA_PREFIX`
  5. `make`
  6. `make install` 
  
For some reason, not all include files are copied from Sparrowhawk, so it is recommended to copy them manually in order to allow this project to compile correctly:
` cp src/include/sparrowhawk/* $CONDA_PREFIX/include/sparrowhawk`
  
# Compiling this project

This project was created using CLion and it uses CMake to compile the single CPP file included. If you want to use it within CLion, make sure to set the paths in CMakeLists.txt accordingly. Also, set the LD_LIBRARY_PATH to the proper lib directory with the Conda environment. Otherwise, simply run:

  1. `git clone https://github.com/danijel3/SparrowhawkTest`
  2. `cd SparrowhawkTest`
  3. `cmake .`
  4. `make`
  5. `cd bin`
  6. `./SparrowhawkTest`
 
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
