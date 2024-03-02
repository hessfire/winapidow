# progressbar control

## apis

```cpp
void step();
void set_position(int position);
int get_position();
void set_range(int min_range, int max_range);
void set_step(int step);
int get_min_range();
int get_max_range();
```
***

## constructor

```cpp
progress_bar_control(int x, int y, int w, int h, int range = 100, int step = 10, DWORD style = WS_CHILD | WS_VISIBLE)
```
***

## creating this control

```cpp
progress_bar_control* test_progressbar = new progress_bar_control{ 10, 10, 270, 20, 100, 10 /*x, y, w, h, range, step*/ };
```