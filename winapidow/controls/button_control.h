#pragma once
#include "..\includes.h"

#include "base_control.h"

class button_control : public base_control
{
public:
    autostring get_control_class_name() const override { return WC_BUTTON; }

    button_control(autostring button_text, int x, int y, int w, int h, DWORD style = WS_CHILD | WS_VISIBLE | BS_PUSHLIKE) : base_control(button_text, x, y, w, h, style)
    {

    }

    void add_click_handler(std::function<void()> on_click)
    {
        button_handlers.emplace(this->get_id(), on_click);
    }
};