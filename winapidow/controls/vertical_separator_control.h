#pragma once
#include "..\includes.h"

#include "base_control.h"

class vertical_separator_control : public base_control
{
public:
    autostring get_control_class_name() const override { return WC_STATIC; }

    vertical_separator_control(int x, int y, int w, int h, DWORD style = WS_CHILD | WS_VISIBLE | SS_ETCHEDVERT) : base_control(_T(""), x, y, w, h, style)
    {

    }
};