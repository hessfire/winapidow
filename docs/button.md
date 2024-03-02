# button control

## apis

```cpp
void add_click_handler(std::function<void()> on_click);
```
***

## constructor

```cpp
button_control(autostring button_text, int x, int y, int w, int h, DWORD style = WS_CHILD | WS_VISIBLE | BS_PUSHLIKE)
```
***

## creating this control

```cpp
button_control* test_button = new button_control{ L"click me", 10 /*x*/, 40 /*y*/, 140 /*w*/, 20 /*h*/ };
```

## available styles

>https://learn.microsoft.com/en-us/windows/win32/controls/button-styles