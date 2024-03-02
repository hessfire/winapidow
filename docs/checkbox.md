# checkbox control

## apis

```cpp
void add_click_handler(std::function<void()> on_click);
bool is_checked();
void check();
void uncheck();
void toggle(); //uncheck if checked, check if unchecked
```
***

## constructor

```cpp
checkbox_control(autostring text = _T(""), int x = 0, int y = 0, int w = 0, int h = 0, DWORD style = WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX)
```
***

## creating this control

```cpp
checkbox_control* test_checkbox = new checkbox_control(L"check", 10, 10, 60, 20, /*x, y, w, h*/);
```