# winapidows
>a small oop-oriented framework for creating a window using winapi under the hood 

## creating a window

you need to include controls you want to use from `winapidow/controls/`, or use `winapidow/controls/all_controls.h` to include every control

```cpp
window* wnd = new window(hInstance /*from WinMain*/ , L"demo_class" /*class name*/, L"demo" /*title name*/, 640 /*width*/, 480 /*height*/, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX /*style, defaults to WS_OVERLAPPEDWINDOW*/, nullptr /*parent window*/, (HBRUSH)(COLOR_WINDOW + 1) /*background color*/, LoadIcon(0, IDI_APPLICATION) /*icon*/);
```
***

## creating a control (button)

```cpp
button_control* test_button = new button_control{ L"click me", 10 /*x*/, 40 /*y*/, 140 /*w*/, 20 /*h*/ };
```

### you can get list of all controls by opening `winapidow/controls/` folder
and see usage of every control in demo file (demo.cpp)

***

## adding control to the window + adding click handler

```cpp
wnd->add_control(test_button);

test_button->add_click_handler([&]() {
    //your code goes here, you can capture context with & in this lambda since it uses std::function instead of function pointer under the hood
});
```
***

## about modifying controls
```cpp
//you need to add control (wnd->add_control) before you can modify a control 
combobox->add_item(L"test item");
//this won't work if you try to call add_item before calling add_control, because control handle is not created yet
```

## starting message loop

```cpp
wnd->show();
wnd->start_message_loop();
// you can also add lamda in start_message_loop to run your code in message loop

//example: 
wnd->start_message_loop([&]() {
    //this code will be executed in message loop, though i recommend you to create a separate thread for your own code
    //it is only used for running your own code and not overriding message handler 
});
```
***

## creating your own control

1. go to `winapidow/controls` and create a new file for your control
2. include `base_control.h` from current folder so you can inherit from it 
3. create a new class, make it inherit from "base_class"
4. include your control file in `winapidow/controls/all_controls.h`

example:

```cpp
#pragma once
#include "..\includes.h"

#include "base_control.h"

class custom_control : public base_control
{
public:
    //override get_control_class_name so your window can know class name when calling CreateWindow
    autostring get_control_class_name() const override { return WC_STATIC; }

    //constructor
    custom_control(autostring text = _T("") /*text on control*/, int x = 0, int y = 0, int w = 0, int h = 0, DWORD style = WS_CHILD | WS_VISIBLE /*customize style*/) : base_control(text /*remove text constructor and set this field to "" by default if you don't need any text on control*/, x, y, w, h, style)
    {

    }
};
```
***
