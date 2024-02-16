#pragma once
#include "includes.h"
#include "controls/base_control.h"

class window
{
private:
    WNDCLASSEX m_wndClass;
    HINSTANCE m_hInstance;
    HWND main_window = nullptr;

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);

            if (button_handlers.find(wmId) != button_handlers.end() && button_handlers[wmId] != nullptr) {
                button_handlers[wmId]();
            }

            //if (IsDlgButtonChecked(hWnd, wmId))
            //    CheckDlgButton(hWnd, wmId, BST_CHECKED);

            if (checkbox_handlers.find(wmId) != checkbox_handlers.end() && checkbox_handlers[wmId] != nullptr) {
                checkbox_handlers[wmId]();
            }

            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        case WM_CTLCOLORSTATIC:
        {
            // HDC hdcStatic = (HDC)wParam;
             //SetBkMode(hdcStatic, TRANSPARENT);
            return (LRESULT)GetStockObject(COLOR_WINDOW + 1);
        }
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_DRAWITEM:
        {
            LPDRAWITEMSTRUCT lpDrawItem = (LPDRAWITEMSTRUCT)lParam;
            RECT rcItem = lpDrawItem->rcItem;
            HWND hwndItem = (HWND)lpDrawItem->hwndItem;

            int controlId = GetDlgCtrlID(hwndItem);

            if (hidden_controls.find(controlId) != hidden_controls.end()) {
                bool is_multiline = hidden_controls[controlId]->get_style() & BS_MULTILINE;
                FillRect(lpDrawItem->hDC, &rcItem, (HBRUSH)(COLOR_BTNFACE + 1));

                SetTextColor(lpDrawItem->hDC, RGB(0, 0, 0));
                SetBkMode(lpDrawItem->hDC, TRANSPARENT);

                autostring button_text = hidden_controls[controlId]->get_text();

                DrawText(lpDrawItem->hDC, button_text.c_str(), button_text.length(), &rcItem, DT_CENTER | DT_VCENTER | (is_multiline ? 0 : DT_SINGLELINE));
            }

            break;
        }
        case WM_NOTIFY:
        {
            LPNMHDR pnmh = (LPNMHDR)lParam;

            if (list_click_handlers.find(pnmh->idFrom) != list_click_handlers.end() && (pnmh->code == NM_CLICK) && list_click_handlers[pnmh->idFrom] != nullptr) {
                list_click_handlers[pnmh->idFrom]((LPNMITEMACTIVATE)lParam);
            }

            if (pnmh->code == NM_CUSTOMDRAW) {
                LPNMLVCUSTOMDRAW custom_draw = (LPNMLVCUSTOMDRAW)lParam;

                switch (custom_draw->nmcd.dwDrawStage) {
                case CDDS_PREPAINT:
                    return CDRF_NOTIFYITEMDRAW;
                    break;
                case CDDS_ITEMPREPAINT:
                    if (list_items_colors.find(((int)custom_draw->nmcd.dwItemSpec)) != list_items_colors.end() && list_items_colors[((int)custom_draw->nmcd.dwItemSpec)] != 0) {
                        custom_draw->clrTextBk = list_items_colors[((int)custom_draw->nmcd.dwItemSpec)];
                    }
                    return CDRF_NEWFONT;
                    break;

                case CDDS_SUBITEM | CDDS_ITEMPREPAINT:
                    return CDRF_NEWFONT;
                    break;
                }

                return true;
            }
        }
        break;
        default:
            return DefWindowProcW(hWnd, message, wParam, lParam);
        }
        return 0;
    }

public:
    window(HINSTANCE hInstance, autostring class_name, autostring window_title, int w, int h, DWORD style = WS_OVERLAPPEDWINDOW, HWND parent = nullptr, HBRUSH background = (HBRUSH)(COLOR_WINDOW + 1), HICON icon = LoadIcon(0, IDI_APPLICATION))
    {
        m_hInstance = hInstance;
        m_wndClass.cbSize = sizeof(WNDCLASSEX);
        m_wndClass.style = CS_HREDRAW | CS_VREDRAW;
        m_wndClass.lpfnWndProc = &window::WndProc;
        m_wndClass.cbClsExtra = 0;
        m_wndClass.cbWndExtra = 0;
        m_wndClass.hInstance = hInstance;
        m_wndClass.hIcon = icon;
        m_wndClass.hCursor = LoadCursor(0, IDC_ARROW);
        m_wndClass.hbrBackground = background;
        m_wndClass.lpszMenuName = 0;
        m_wndClass.lpszClassName = class_name.c_str();
        m_wndClass.hIconSm = icon;

        if (!RegisterClassEx(&m_wndClass)) return;

        main_window = CreateWindowExW(
            WS_EX_CLIENTEDGE,
            class_name.c_str(),
            window_title.c_str(),
            style,
            CW_USEDEFAULT, CW_USEDEFAULT, w, h,
            parent, 0, hInstance, 0);

        if (main_window == 0) return;
    }

    int start_message_loop(std::function<void()> inloop = nullptr)
    {
        MSG msg;
        while (GetMessage(&msg, 0, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (inloop != nullptr) inloop();
        }

        return (int)msg.wParam;
    }

    HWND add_control(base_control* control_obj)
    {
        //autostring text = control_obj->get_text();
        //if (strstr(typeid(control_obj).name(), "button_hidden_class") != 0)
        //    text = _T("");

        HWND control_handle = CreateWindowExW(
            0,
            control_obj->get_control_class_name().c_str(),
            control_obj->get_text().c_str(),
            control_obj->get_style(),
            control_obj->get_pox_x(), control_obj->get_pox_y(), control_obj->get_width(), control_obj->get_height(),
            (control_obj->get_custom_parent_handle() == nullptr) ? main_window : control_obj->get_custom_parent_handle(),
            (HMENU)control_obj->get_id(),
            m_hInstance,
            0);

        control_obj->set_handle(control_handle);

        HFONT font = CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Segoe UI"));
        SendMessage(control_handle, WM_SETFONT, (WPARAM)font, true);

        if (control_obj->post_creation != nullptr) control_obj->post_creation(control_handle);

        return control_handle;
    }

    void show()
    {
        ShowWindow(main_window, true);
        UpdateWindow(main_window);
    }

    void hide()
    {
        ShowWindow(main_window, false);
        UpdateWindow(main_window);
    }

    HWND get_handle() { return main_window; }
};