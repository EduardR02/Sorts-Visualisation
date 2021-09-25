#pragma once

#include <string>
#include <vector>

/* array sizes that fit together well, meaning execute in similar time.
might need to be changed with differing inputs from random shuffling.*/
enum Complexity {
    n_squared = 100, n_logn = 1024, bogo_cmplx = 6, stooge_cmplx = 30, shell_cmplx = n_squared * 4
};

/* enum order should match string array order, otherwise text label will display incorrectly*/
enum SortNames {
    bubble_sort = 0, selection_sort, quick_sort, merge_sort, insertion_sort, bogo_sort, cocktail_sort, gnome_sort,
    stooge_sort, shell_sort, pancake_sort
};

const std::vector<std::string> SortNamesArr = {"Bubble Sort", "Selection Sort", "Quick Sort", "Merge Sort",
"Insertion Sort", "Bogo Sort", "Cocktail Shaker Sort", "Gnome Sort", "Stooge Sort", "Shell Sort", "Pancake Sort"};