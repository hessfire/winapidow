#pragma once
#include "..\includes.h"

#include "base_control.h"

class button_hidden_control : public base_control
{
public:
    autostring get_control_class_name() const override { return WC_BUTTON; }

    button_hidden_control(autostring button_text, int x, int y, int w, int h, DWORD style = WS_CHILD | WS_VISIBLE | BS_PUSHLIKE | BS_OWNERDRAW, HWND custom_parent = nullptr) : base_control(button_text, x, y, w, h, style, 0, custom_parent)
    {
        hidden_controls.emplace(this->get_id(), this);
        this->post_creation = [](HWND control_handle) {
            SetWindowText(control_handle, _T(""));
            };
    }

    void add_click_handler(std::function<void()> on_click)
    {
        button_handlers.emplace(this->get_id(), on_click);
    }
};