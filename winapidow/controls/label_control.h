#pragma once
#include "..\includes.h"

#include "base_control.h"

class label_control : public base_control
{
public:
    autostring get_control_class_name() const override { return WC_STATIC; }

    label_control(autostring label_text, int x, int y, int w = 50, int h = 20, DWORD style = WS_CHILD | WS_VISIBLE) : base_control(label_text, x, y, w, h, style)
    {

    }

    void set_text(autostring text)
    {
        SetWindowText(this->get_handle(), (autochar*)(text.c_str()));
        InvalidateRect(this->get_handle(), 0, TRUE);
    }
};