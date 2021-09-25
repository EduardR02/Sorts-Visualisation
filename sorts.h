#pragma once

#include <utility>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "bar.h"
#include "my_enum.h"

class Sorts {
        std::vector<std::unique_ptr<Rectangle>>& arr;
        int sleep_ms, updates_per_draw, comparisons, swaps, sleep_time_sorted, ext_swaps, ext_comparisons;
        void bubble_sort();
        void selection_sort();
        void insertion_sort();
        void bogo_sort();
        void mergesort(int left, int right);
        void quicksort_hoare(int left, int right);
        void cocktail_sort();
        void gnome_sort();
        void stooge_sort(int left, int right);
        void shell_sort();
        void pancake_sort();
        bool check_sorted(bool for_bogo=false);
        void shuffle(bool for_bogo=false);
        void flip_arr(size_t right);
        size_t find_max(size_t elements);
        void set_sleep_time_sorted();
        int set_updates_per_draw_for_sorted();
        void merge(int left1, int mid, int right2);
        int partition(int left, int right);
        void increment_counters(bool comparison, bool swap, bool shuffling_or_sorting);
        void wait_and_highlight(bool comparison, bool swap, int index1, int index2, bool sort_check);
        void reset_counters();
        void dehighlight_all();
        template<typename T>
        void swap_back_to_mainarr(T& old, T& to_swap_back) {
            to_swap_back->set_posx(old->get_posx());
            old = std::move(to_swap_back);
        }
        template<typename T>
        void my_swap(T& x, T& y) {
            double temp = x->get_posx();
            x->set_posx(y->get_posx());
            y->set_posx(temp);
            std::swap(x, y); 
        }
    public:
        bool waiting, sorted, window_closed;
        Sorts(std::vector<std::unique_ptr<Rectangle>>& passed_arr, int, int);
        void do_sort(const SortNames& sort_name);
        int get_comparisons() const {
            return ext_comparisons;
        };
        int get_swaps() const {
            return ext_swaps;
        };
};