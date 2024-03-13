=============================================|
# Assignment 2 (Pratik and Ishaan Karnani)   |
=============================================|


-----------------------------------------------------------------------------------------------------

## Command-Line File Manipulation Program

--> This is a command-line program written in C that allows users to perform various file manipulation:-
such as 

1. Creating files or directories
2. appending text or numbers to files 
3. renaming files or directories
4. outputting the first 50 bytes of a file to standard output
5. deleting files or directories.

----------------------------------------------------------------------------------------------------

### Usage

To use this program, compile the provided source code using a C compiler :-

	gcc -o my_fm my_fm.c

Once compiled, you can run the program with the following command :-

	./my_fm [options] [arguments]


-------------------------------------------------------------------------------------------------------

#### Options

The program supports the following options:

    -c: Create a file or directory.
    -a: Append text or a sequence of odd numbers to a file.
    -r: Rename a file or directory.
    -x: Delete a file or directory.
    -p: Output the first 50 bytes of a file to standard output.

------------------------------------------------------------------------------------------------------

##### Arguments

The arguments required for each option are as follows:

	1. For -c option: Specify the path of the file or directory to be created.
	    a. Use -f followed by the path name to create a file.
	    b. Use -d followed by the path name to create the directory.
	2. For -a option:
	    a. Use -t followed by the text to be appended to a file.
	    b. Use -n followed by the number to specify the length of the sequence of odd numbers to be appended to a file. (It is for binary files)
	3. For -r option: Specify the old path and the new path for renaming a file or directory.
	4. For -x option: Specify the path of the file or directory to be deleted.
	5. For -p option: Specify the path of the file to output its first 50 bytes to standard output.

---------------------------------------------------------------------------------------------------

###### Example Usages

  Create a file or directory:

	./my_fm -c -f example.txt
	./my_fm -c -f a.out
	./my_fm -c -d example

Append text or number to a file:

	./my_fm -a example.txt -t "This is some text."
	./my_fm -a a.out -n 50

Rename a file or a directory:

	./my_fm -r old_name.txt new_name.txt
	./my_fm -r old_name new_name

Output the first 50 bytes of a file:

	./my_fm -p example.txt
	./my_fm -p a.out

Delete a file or directory:

	./my_fm -x directory_to_delete
	./my_fm -x file_to_delete


------------------------------------------------------------------------------------------------------