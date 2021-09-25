#include "gui.h"

int main() {
    GUI my_gui(20, 1, 10, 50, 100, 1, 2);
    my_gui.do_single_sort(bubble_sort, n_squared);
    my_gui.do_all_sorts();
    return 0;
}