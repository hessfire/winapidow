#pragma once
#include "..\includes.h"

#include "base_control.h"

class checkbox_control : public base_control
{
public:
    autostring get_control_class_name() const override { return WC_BUTTON; }

    checkbox_control(autostring text = _T(""), int x = 0, int y = 0, int w = 0, int h = 0, DWORD style = WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX) : base_control(text, x, y, w, h, style)
    {

    }

    void check() { SendMessage(this->get_handle(), BM_SETCHECK, BST_CHECKED, 0); }

    void uncheck() { SendMessage(this->get_handle(), BM_SETCHECK, BST_UNCHECKED, 0); }

    void toggle() { SendMessage(this->get_handle(), BM_CLICK, 0, 0); }

    bool is_checked() { return SendMessage(this->get_handle(), BM_GETCHECK, 0, 0) == BST_CHECKED; }

    void add_click_handler(std::function<void()> on_check)
    {
        checkbox_handlers.emplace(this->get_id(), on_check);
    }
};