# combobox control

## apis

```cpp
void add_item(autostring item);
void clear();
int get_selected_index();
void set_selected_index(int index);
autostring get_selected_text();
```
***

## constructor

```cpp
combobox_control(int x, int y, int w, int h, DWORD style = WS_CHILD | WS_VISIBLE | CBS_DROPDOWN)
```
***

## creating this control

```cpp
combobox_control* test_combobox = new combobox_control(10, 10, 200, 20, /*x, y, w, h*/);
```