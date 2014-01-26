IHM_OFELI
=========

This program has been created to modify the data files used with OFELI. Those files are written in XML and have the extension ".dat".
The only requirement to use it is to install Qt (follow this link for more information <a href="http://qt-project.org/doc/qt-4.8/installation.html">Installation Qt</a>

To build the program from sources you can use the script "compil", or you can follow this procedure :
	- launch the command "qmake -o Makefile IHM_OFELI.pro" to generate the makefile
	- then use "make" to build the program, this will create an executable named IHM_OFELI
To launch the program, just use "./IHM_OFELI".

With this program you can create a new data file for OFELI or modify an existing file.
The creation of a new file can be performed by using the default file provided with the program as a base. Once this file is opened, you can modify it as you wish.
For the modification, this program allows you to perform all the operations you should need (add/delete tag, add/delete comment, modification of a tag, modification of attributes).

