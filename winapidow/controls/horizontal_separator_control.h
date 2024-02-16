#pragma once
#include "..\includes.h"

#include "base_control.h"

class horizontal_separator_control : public base_control
{
public:
    autostring get_control_class_name() const override { return WC_STATIC; }

    horizontal_separator_control(int x, int y, int w, int h, DWORD style = WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ) : base_control(_T(""), x, y, w, h, style)
    {

    }
};