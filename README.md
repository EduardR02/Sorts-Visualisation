# Sorts-Visualisation

# Description
This is a project I made using SFML and C++ to learn C++. To try this out yourself you just need a C++ compiler
with C++14 and properly working threads, otherwise you will need to statically link,
which was the case for me (already done in the makefile).
I implemented it so it is very easy to add new sorting algorithms, so if you are curious how some funny sorting
algorithm looks, you could try it out yourself. You will also need to install SFML, I used this tutorial:
https://www.youtube.com/watch?v=ttYspMwzV8w

Rectangle width, height, sleeping time, and how many updates per single draw you want can all be controlled through the GUI constructor in main,
and other variables like array length for each algorithm can be found in the enum header file.
Keyboard controls of sim speed etc. can also be easily implemented with SFML in the handle_events function.


# Visualization
I have grouped the algorithms I implemented into three gifs in this showcase.
In the code these can run in the same window, with different array lengths and any order,
this is just so compression does not destroy the visuals too much.
First are Mergesort and Quicksort, as these are O(nlogn) on average, you can basically have as many elements as you want:

![alt text][gif2]

Next are algorithms that run in O(n^2) time, like Bubblesort and Insertion sort:

![alt text][gif1]

And last we have the funny ones, Stooge Sort and Bogosort. For those that don't know, Bogosort just randomly shuffles and hopes
that the elements will magically sort themselves. They do - just after a VERY long time ( O((n+1)!) ). And it is also a bad idea to increase
the elements in Stooge Sort, it will just check itself over and over again, even though it is already sorted. Can't hurt to double-check though.

![alt text][gif3]




[gif1]: https://github.com/EduardR02/Sorts-Visualisation/blob/main/gifs/all_n_squared_Trim.gif
[gif2]: https://github.com/EduardR02/Sorts-Visualisation/blob/main/gifs/merge_and_quicksort_Trim.gif
[gif3]: https://github.com/EduardR02/Sorts-Visualisation/blob/main/gifs/stooge_and_bogo_Trim.gif
