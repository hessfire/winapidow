#pragma once
#include "..\includes.h"

#include "base_control.h"

class textbox_control : public base_control
{
public:
    autostring get_control_class_name() const override { return WC_EDIT; }

    textbox_control(autostring default_text = _T(""), int x = 0, int y = 0, int w = 50, int h = 20, DWORD style = WS_CHILD | WS_VISIBLE | WS_BORDER, DWORD ex_style = WS_EX_CLIENTEDGE) : base_control(default_text, x, y, w, h, style, ex_style)
    {

    }

    void set_text(autostring text)
    {
        SetWindowText(this->get_handle(), (autochar*)(text.c_str()));
    }

    autostring get_text()
    {
        int length = GetWindowTextLength(this->get_handle());
        autochar* buffer = new autochar[length + 1];

        GetWindowText(this->get_handle(), buffer, length + 1);
        autostring return_value(buffer);
        delete[] buffer;
        return return_value;
        //created separate value to clean the buffer and return its stack-stored value, otherwise it will result in memory leak (if you juse use return autostring(buffer) without deleting da buffer)
    }
};