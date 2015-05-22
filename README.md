# cs3-webserver

Source Code Layout

The static server class contains methods to read in nGinx Config files and call the appropriate handler.
There are four request handlers: hello world, echo, request, and 404 error.  All request handlers are
subclasses of the static request handler.

How to Build

In order to build the code, simply clone to a directory and type make.  This will compile all necessary
executable files.

Testing

There are test files for several handler classes to give an idea of how to test the code.  More tests
can be added to these files in order to test new classes.  These test will be compiled when typing
make all.

Running

In order to run the code, type ./webserver [Config File].  Look at the example Config file for an
example of an appropriate nGinx config file.
