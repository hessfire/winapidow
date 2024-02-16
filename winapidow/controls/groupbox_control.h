#pragma once
#include "..\includes.h"

#include "base_control.h"

class groupbox_control : public base_control
{
public:
    autostring get_control_class_name() const override { return WC_BUTTON; }

    groupbox_control(autostring text = _T(""), int x = 0, int y = 0, int w = 0, int h = 0, DWORD style = WS_CHILD | WS_VISIBLE | BS_GROUPBOX) : base_control(text, x, y, w, h, style)
    {

    }
};