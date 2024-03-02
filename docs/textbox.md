# textbox control

## apis

```cpp
void set_text(autostring text);
autostring get_text();
```
***

## constructor

```cpp
textbox_control(autostring default_text = _T(""), int x = 0, int y = 0, int w = 50, int h = 20, DWORD style = WS_CHILD | WS_VISIBLE | WS_BORDER, DWORD ex_style = WS_EX_CLIENTEDGE)
```
***

## creating this control

```cpp
textbox_control* test_textbox = new textbox_control{ L"default text goes here", 10, 10, 60, 20, /*x, y, w, h*/ };
```