# FT_LS

Ft_ls is a team project for School 21/42

Description: this is an analogue of the basic ls function. Implemented the following flags: -R, -l, -a, -C, -r, -t, -1; and correct output to a file.

Algorithm: In program used two structures: the first stores input data from the console and folders to bypass in the case of the -R flag. Sorting is implemented by the merge method. The second structure is used when opening a folder. A linked list of structures2 is created containing detailed information about the files depending on the flags. Further, the data from structure 2 are sent to the output. To speed up the program, all data from one folder is displayed in one write.

