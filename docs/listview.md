# progressbar control

listview is kinda broken, i'll fix it later

you can't really use multiple columns with default control apis as of now

## apis

```cpp
void insert_column(int column_index, autostring column_name, int column_width = 100);
void add_column_values(int column_index, vector<autostring> values);
void update_item(int index, autostring new_text, int column = 0);
autostring get_item_by_index(int index, int column = 0);
bool item_exists_at_index(int index);
void delete_item_at_index(int index);
int item_count();
void add_item(autostring text, int column = 0);
void clear_all_values();
void add_click_handler(std::function<void(LPNMITEMACTIVATE)> on_click);
```
***

## constructor

```cpp
listview_control(int x, int y, int w = 50, int h = 20, DWORD style = WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SINGLESEL)
```
***

## creating this control

```cpp
listview_control* test_listview = new listview_control{ 10, 80, 270, 240 /*x, y, w, h*/ };
```