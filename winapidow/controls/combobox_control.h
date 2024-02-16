#pragma once
#include "..\includes.h"

#include "base_control.h"

class combobox_control : public base_control
{
public:
    autostring get_control_class_name() const override { return WC_COMBOBOX; }

    combobox_control(int x, int y, int w, int h, DWORD style = WS_CHILD | WS_VISIBLE | CBS_DROPDOWN) : base_control(_T(""), x, y, w, h, style)
    {

    }

    void add_item(autostring item) { SendMessage(this->get_handle(), CB_ADDSTRING, 0, (LPARAM)item.c_str()); }

    void clear() { SendMessage(this->get_handle(), CB_RESETCONTENT, 0, 0); }

    int get_selected_index() { return SendMessage(this->get_handle(), CB_GETCURSEL, 0, 0); }

    void set_selected_index(int index) { SendMessage(this->get_handle(), CB_SETCURSEL, index, 0); }

    autostring get_selected_text()
    {
        int index = get_selected_index();
        autostring text;
        if (index != CB_ERR)
        {
            int length = SendMessage(this->get_handle(), CB_GETLBTEXTLEN, index, 0);
            if (length != CB_ERR)
            {
                text.resize(length + 1);
                SendMessage(this->get_handle(), CB_GETLBTEXT, index, (LPARAM)text.data());
            }
        }
        return text;
    }
};