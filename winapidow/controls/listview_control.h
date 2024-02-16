#pragma once
#include "..\includes.h"

#include "base_control.h"

class listview_control : public base_control
{
public:
    autostring get_control_class_name() const override { return WC_LISTVIEW; }

    listview_control(int x, int y, int w = 50, int h = 20, DWORD style = WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SINGLESEL) : base_control(_T(""), x, y, w, h, style)
    {
        this->post_creation = [](HWND control_handle) {
            ListView_SetExtendedListViewStyle(control_handle, LVS_EX_FULLROWSELECT);
            };
    }

    void insert_column(int columnIndex, LPCWSTR columnName, int columnWidth = 100) {
        LVCOLUMN lvColumn;
        lvColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
        lvColumn.cx = columnWidth;
        lvColumn.pszText = const_cast<LPWSTR>(columnName);
        lvColumn.iSubItem = columnIndex;
        ListView_InsertColumn(this->get_handle(), columnIndex, &lvColumn);
    }

    void add_column_values(int columnIndex, vector<LPCWSTR> values) {
        LVITEM lvItem;

        for (int i = 0; i < values.size(); ++i) {
            lvItem.mask = LVIF_TEXT;
            lvItem.iItem = i;
            lvItem.iSubItem = columnIndex;
            lvItem.pszText = (wchar_t*)(values[i]);
            ListView_InsertItem(this->get_handle(), &lvItem);
        }
    }

    void update_item(int index, autostring new_text, int column = 0) {
        ListView_SetItemText(this->get_handle(), index, column, (wchar_t*)new_text.c_str());
    }

    autostring get_item_by_index(int index, int column = 0)
    {
        wchar_t buffer[512] = { 0 };
        ListView_GetItemText(this->get_handle(), index, column, buffer, sizeof(buffer) / sizeof(buffer[0]));
        return autostring(buffer);
    }

    bool item_exists_at_index(int index) {
        int itemCount = ListView_GetItemCount(this->get_handle());
        return (index >= 0 && index < itemCount);
    }

    void delete_item_at_index(int index) {
        ListView_DeleteItem(this->get_handle(), index);
    }

    int item_count()
    {
        return ListView_GetItemCount(this->get_handle());
    }

    void add_item(autostring text, int column = 0) {
        LVITEM lvItem;
        lvItem.mask = LVIF_TEXT;
        lvItem.iItem = ListView_GetItemCount(this->get_handle());
        lvItem.iSubItem = column;
        lvItem.pszText = (wchar_t*)text.c_str();

        ListView_InsertItem(this->get_handle(), &lvItem);
    }

    void clear_all_values() {
        ListView_DeleteAllItems(this->get_handle());
    }

    void add_click_handler(std::function<void(LPNMITEMACTIVATE)> on_click)
    {
        list_click_handlers.emplace(this->get_id(), on_click);
    }
};