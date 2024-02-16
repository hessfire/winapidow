#pragma once
#include "..\includes.h"

#include "base_control.h"

class progress_bar_control : public base_control
{
public:
    autostring get_control_class_name() const override { return PROGRESS_CLASS; }

    progress_bar_control(int x, int y, int w, int h, int range = 100, int step = 10, DWORD style = WS_CHILD | WS_VISIBLE) : base_control(_T(""), x, y, w, h, style)
    {
        this->post_creation = [range, step](HWND control_handle) {
            SendMessage(control_handle, PBM_SETRANGE, 0, MAKELPARAM(0, range));
            SendMessage(control_handle, PBM_SETSTEP, (WPARAM)step, 0);
            };
    }

    void step() { SendMessage(this->get_handle(), PBM_STEPIT, 0, 0); }

    void set_position(int position) { SendMessage(this->get_handle(), PBM_SETPOS, position, 0); }

    int get_position() { return SendMessage(this->get_handle(), PBM_GETPOS, 0, 0); }

    void set_range(int min_range, int max_range) { SendMessage(this->get_handle(), PBM_SETRANGE, 0, MAKELPARAM(min_range, max_range)); }

    void set_step(int step) { SendMessage(this->get_handle(), PBM_SETSTEP, (WPARAM)step, 0); }

    int get_min_range() { return LOWORD(SendMessage(this->get_handle(), PBM_GETRANGE, true, 0)); }

    int get_max_range() { return HIWORD(SendMessage(this->get_handle(), PBM_GETRANGE, true, 0)); }
};