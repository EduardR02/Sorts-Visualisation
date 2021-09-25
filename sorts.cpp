#include "sorts.h"

Sorts::Sorts(std::vector<std::unique_ptr<Rectangle>>& passed_arr, int sleep_ms, int updates_per_draw) : arr(passed_arr) {
    this->sleep_ms = sleep_ms;
    this->updates_per_draw = updates_per_draw;
    reset_counters();
    this->waiting = true;
    this->window_closed = false;
    set_sleep_time_sorted();
}

void Sorts::bubble_sort() {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        for (size_t j = 0; j < arr.size() - i - 1; j++) {
            wait_and_highlight(true, false, j, j + 1, false);
            if (arr[j]->get_sort_id() > arr[j + 1]->get_sort_id()) {
                my_swap(arr[j], arr[j + 1]);
                wait_and_highlight(false, true, j, j + 1, false);
            }
        }
    }
}

void Sorts::selection_sort() {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        int minIndex = i;
        for (size_t j = i + 1; j < arr.size(); j++) {
            wait_and_highlight(true, false, minIndex, j, false);
            if (arr[minIndex]->get_sort_id() > arr[j]->get_sort_id()) {
                minIndex = j;
            }
        }
        my_swap(arr[i], arr[minIndex]);
        wait_and_highlight(false, true, i, minIndex, false);
    }
}

void Sorts::insertion_sort() {
    for (size_t i = 1; i < arr.size(); i++) {
        int j = i;
        wait_and_highlight(true, false, j, j - 1, false);
        while (j > 0 && arr[j - 1]->get_sort_id() > arr[j]->get_sort_id()) {
            my_swap(arr[j - 1], arr[j]);
            wait_and_highlight(true, true, j, j - 1, false);
            j--;
        }
    }
}

void Sorts::cocktail_sort() {
    int left = 0;
    int right = arr.size() - 1;
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int i = left; i < right; i++) {
            wait_and_highlight(true, false, i, i + 1, false);
            if (arr[i]->get_sort_id() > arr[i + 1]->get_sort_id()) {
                swapped = true;
                my_swap(arr[i], arr[i + 1]);
                wait_and_highlight(false, true, i, i + 1, false);
            }
        }
        if (!swapped) {
            break;
        }
        swapped = false;
        right--;
        for (int i = right-1; i >= left; i--) {
            wait_and_highlight(true, false, i, i + 1, false);
            if (arr[i]->get_sort_id() > arr[i + 1]->get_sort_id()) {
                swapped = true;
                my_swap(arr[i], arr[i + 1]);
                wait_and_highlight(false, true, i, i + 1, false);
            }
        }
        left++;
    }
}

void Sorts::shell_sort() {
    for (size_t gap = arr.size() / 2; gap > 0; gap = gap / 2) {
        for (size_t i = gap; i < arr.size(); i++) {
            std::unique_ptr<Rectangle> temp = std::make_unique<Rectangle>(*arr[i]);
            size_t j = i;
            for (j = i; j >= gap && arr[j - gap]->get_sort_id() > temp->get_sort_id(); j -= gap) {
                my_swap(arr[j], arr[j - gap]);
                wait_and_highlight(true, true, j, j - gap, false);
            }
            swap_back_to_mainarr(arr[j], temp);
            wait_and_highlight(false, true, j, i, false);
        }
    }
}

void Sorts::gnome_sort() {
    size_t index = 0;
    while (index < arr.size()) {
        if (index == 0) index++;
        wait_and_highlight(true, false, index, index - 1, false);
        if (arr[index]->get_sort_id() >= arr[index - 1]->get_sort_id()) index++;
        else {
            my_swap(arr[index], arr[index - 1]);
            wait_and_highlight(false, true, index, index - 1, false);
            index--;
        }
    }
}

void Sorts::stooge_sort(int left, int right) {
    wait_and_highlight(true, false, left, right, false);
    if (arr[left]->get_sort_id() > arr[right]->get_sort_id()) {
        my_swap(arr[left], arr[right]);
        wait_and_highlight(false, true, left, right, false);
    }
    wait_and_highlight(true, false, left, right, false);
    if ((right - left + 1) > 2) {
        int div = std::floor((right - left + 1) / 3);
        stooge_sort(left, right - div);
        stooge_sort(left + div, right);
        stooge_sort(left, right - div);
    }
}

void Sorts::bogo_sort() {
    std::srand(std::time(NULL));
    while(!check_sorted(true)) {
        shuffle(true);
    }
}

void Sorts::pancake_sort() {
    for (size_t i = arr.size(); i > 1; i--) {
        size_t max_elem_idx = find_max(i);
        if (max_elem_idx != i - 1) {
            flip_arr(max_elem_idx);
            flip_arr(i - 1);
        }
    }
}

size_t Sorts::find_max(size_t elements) {
    size_t max_idx = 0;
    for (size_t i = 1; i < elements; i++) {
        wait_and_highlight(true, false, i, max_idx, false);
        if (arr[i]->get_sort_id() > arr[max_idx]->get_sort_id()) {
            max_idx = i;
        }
    }
    return max_idx;
}

void Sorts::flip_arr(size_t right) {
    size_t left = 0;
    while (left < right) {
        my_swap(arr[left], arr[right]);
        wait_and_highlight(false, true, left, right, false);
        right--;
        left++;
    }
}

void Sorts::merge(int left, int mid, int right) {
    int i = left, j = mid + 1, x = 0;
    /* Because it is necessary to display the process of "overwriting" of the new array with the
    temporary array in the merge process, just one object would not be enough, 
    as some objects need to be in two spots at the same time.
    If that process would not need to be shown / drawn, you could of course just std::move twice.*/
    std::unique_ptr<Rectangle>* temp_arr = new std::unique_ptr<Rectangle>[right - left + 1];
    while (i <= mid && j <= right) {
        wait_and_highlight(true, true, i, j, false);
        temp_arr[x++] = (arr[i]->get_sort_id() < arr[j]->get_sort_id()) ? 
                         std::make_unique<Rectangle>(*arr[i++]) : std::make_unique<Rectangle>(*arr[j++]);
    }
    while (i <= mid) {
        temp_arr[x] = std::make_unique<Rectangle>(*arr[i]);
        wait_and_highlight(false, true, i, -1, false);
        x++;
        i++;
    }
    while (j <= right) {
        temp_arr[x] = std::make_unique<Rectangle>(*arr[j]);
        wait_and_highlight(false, true, j, -1, false);
        x++;
        j++;
    }
    x = 0;
    while (x < right - left + 1) {
        swap_back_to_mainarr(arr[left + x], temp_arr[x]);
        wait_and_highlight(false, true, left + x, -1, false);
        x++;
    }
    delete[] temp_arr;
}

void Sorts::mergesort(int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergesort(left, mid);
    mergesort(mid + 1, right);
    merge(left, mid, right);
}

int Sorts::partition(int left, int right) {
    int pivot = arr[std::rand() % (right - left + 1) + left]->get_sort_id();
    int i = left - 1, j = right + 1;
    while (1) {
        while(arr[++i]->get_sort_id() < pivot) {
            wait_and_highlight(true, false, i, -1, false);
        }
        while(arr[--j]->get_sort_id() > pivot) {
            wait_and_highlight(true, false, j, -1, false);
        }
        if (i >= j) return j;
        my_swap(arr[i], arr[j]);
        wait_and_highlight(false, true, i, j, false);
    }
}


void Sorts::quicksort_hoare(int left, int right) {
    if (left >= right) return;
    int partition_index = partition(left, right);
    quicksort_hoare(left, partition_index);
    quicksort_hoare(partition_index + 1, right);
}

void Sorts::shuffle(bool for_bogo /*=false*/) {
    sorted = false;
    // bogosort might get stuck if seed is constantly reset.
    if (!for_bogo) {
        std::srand(std::time(NULL));
    }
    size_t vec_size = arr.size();
    for (size_t i = 0; i < vec_size - 1; i++) {
        int index = std::rand() % (vec_size - i) + i;
        my_swap(arr[i], arr[index]);
        wait_and_highlight(false, true, i, index, !for_bogo);
    }
}

bool Sorts::check_sorted(bool for_bogo /*=false*/) {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        wait_and_highlight(true, false, i, i + 1, !for_bogo);
        if (arr[i]->get_sort_id() > arr[i + 1]->get_sort_id()) {
            if (!for_bogo) {
                dehighlight_all();
            }
            return false;
        }
    }
    dehighlight_all();
    return true;
}

void Sorts::wait_and_highlight(bool comparison, bool swap, int index1, int index2, bool shuffling_or_sorting) {
    /* 
    the distinction of comparison and swap coupled with shuffling_or_sorting is made,
    as when shuffling, items should be dehilighted normally, but not when checking for sorted.
    as shuffle only swaps, and check_sorted only compares.
    */
    if (window_closed) {
        std::terminate();
    }
    if (shuffling_or_sorting && comparison) {
        arr[index1]->highlight_sorted();
        if (index2 != -1) arr[index2]->highlight_sorted();
    }
    if ((comparisons + swaps) % updates_per_draw == 0) {
        if (!shuffling_or_sorting || swap) {
            arr[index1]->highlight();
            if (index2 != -1) arr[index2]->highlight();
        }
        waiting = true;
        if (!shuffling_or_sorting) {
            sf::sleep(sf::milliseconds(sleep_ms));
        }
        else {
            if (sleep_time_sorted < 1000) {
                sf::sleep(sf::milliseconds(1));
            }
            else {
                sf::sleep(sf::microseconds(sleep_time_sorted));
            }
        }
        waiting = false;
        if (!shuffling_or_sorting || swap) {
            arr[index1]->un_highlight();
            if (index2 != -1) arr[index2]->un_highlight();
        }
    }
    increment_counters(comparison, swap, shuffling_or_sorting);
    
}

void Sorts::increment_counters(bool comparison, bool swap, bool sort_check) {
    if (comparison) {
        comparisons += 1;
        if (!sort_check) ext_comparisons += 1;
    }
    if (swap) {
        swaps += 1;
        if (!sort_check) ext_swaps += 1;
    }
}

void Sorts::dehighlight_all() {
    for (size_t i = 0; i < arr.size(); i++) {
        arr[i]->un_highlight();
    }
}

void Sorts::reset_counters() {
    swaps = 0;
    waiting = false;
    comparisons = 0;
    ext_comparisons = 0;
    ext_swaps = 0;
}

inline void Sorts::set_sleep_time_sorted() {
    sleep_time_sorted = std::round((double)(500 * updates_per_draw) / ((double)arr.size() / 1000));
}

int Sorts::set_updates_per_draw_for_sorted() {
    int temp_update = updates_per_draw;
    updates_per_draw = 1;
    set_sleep_time_sorted();
    if (sleep_time_sorted < 1000) {
        updates_per_draw = temp_update;
        set_sleep_time_sorted();
    }
    return temp_update;
}

void Sorts::do_sort(const SortNames& sort_name) {
    set_sleep_time_sorted();
    reset_counters();
    shuffle();
    switch (sort_name) {
        case SortNames::bubble_sort:
            bubble_sort();
            break;
        case SortNames::selection_sort:
            selection_sort();
            break;
        case SortNames::merge_sort:
            mergesort(0, arr.size() - 1);
            break;
        case SortNames::quick_sort:
            quicksort_hoare(0, arr.size() - 1);
            break;
        case SortNames::insertion_sort:
            insertion_sort();
            break;
        case SortNames::bogo_sort:
            bogo_sort();
            break;
        case SortNames::cocktail_sort:
            cocktail_sort();
            break;
        case SortNames::gnome_sort:
            gnome_sort();
            break;
        case SortNames::stooge_sort:
            stooge_sort(0, arr.size() - 1);
            break;
        case SortNames::shell_sort:
            shell_sort();
            break;
        case SortNames::pancake_sort:
            pancake_sort();
            break;
    }
    /*
    sleeping less than 1ms does not work on my machine (windows)
    */
    int temp_update = set_updates_per_draw_for_sorted();
    bool temp_sorted = check_sorted();
    reset_counters();
    updates_per_draw = temp_update;
    sorted = temp_sorted;
}
