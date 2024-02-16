#pragma once
#include "..\includes.h"

class base_control
{
private:
    int m_iPos_x, m_iPos_y, m_iWidth, m_iHeight, m_iID;
    autostring m_szText;
    DWORD m_dwStyle;
    DWORD m_dwExStyle;
    HWND m_hWnd;
    HWND m_hWndCustomParent;
public:
    virtual autostring get_control_class_name() const { return _T("baseclass"); }

    base_control(autostring text, int x, int y, int w, int h, DWORD style = WS_CHILD | WS_VISIBLE, DWORD ex_style = 0, HWND custom_parent = nullptr)
    {
        m_szText = text;
        m_iPos_x = x;
        m_iPos_y = y;
        m_iWidth = w;
        m_iHeight = h;

        ids_base++;

        m_iID = ids_base;
        m_dwStyle = style;
        m_dwExStyle = ex_style;
        m_hWndCustomParent = custom_parent;
    }

    virtual ~base_control() {};

    int get_pox_x() { return m_iPos_x; };
    int get_pox_y() { return m_iPos_y; };
    int get_width() { return m_iWidth; };
    int get_height() { return m_iHeight; };
    int get_id() { return m_iID; };
    int get_style() { return m_dwStyle; };
    int get_ex_style() { return m_dwExStyle; };
    autostring get_text() { return m_szText; };
    HWND get_handle() { return m_hWnd; }
    HWND get_custom_parent_handle() { return m_hWndCustomParent; }
    void set_handle(HWND handle) { m_hWnd = handle; }
    void enable() { EnableWindow(m_hWnd, true); }
    void disable() { EnableWindow(m_hWnd, false); }
    void set_font(HFONT font) { SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, true); }

    std::function<void(HWND)> post_creation;
    //void (*post_creation)(HWND control_handle);
};