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

    void insert_column(int column_index, autostring column_name, int column_width = 100)
    {
        LVCOLUMN column;
        column.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
        column.cx = column_width;
        column.pszText = const_cast<autochar*>(column_name.c_str());
        column.iSubItem = column_index;
        ListView_InsertColumn(this->get_handle(), column_index, &column);
    }

    void add_column_values(int column_index, vector<autostring> values) 
    {
        LVITEM item;

        for (int i = 0; i < values.size(); ++i) {
            if (column_index == 0) {
                item.mask = LVIF_TEXT;
                item.iItem = i;
                item.iSubItem = column_index;
                item.pszText = const_cast<autochar*>(values[i].c_str());
                ListView_InsertItem(this->get_handle(), &item);
            }
            else
            {
                ListView_SetItemText(this->get_handle(), i, column_index, const_cast<autochar*>(values[i].c_str()));
            }
        }
    }

    void update_item(int index, autostring new_text, int column = 0) {
        ListView_SetItemText(this->get_handle(), index, column, (autochar*)new_text.c_str());
    }

    autostring get_item_by_index(int index, int column = 0)
    {
        autochar buffer[512] = { 0 };
        ListView_GetItemText(this->get_handle(), index, column, buffer, sizeof(buffer) / sizeof(buffer[0]));
        return autostring(buffer);
    }

    bool item_exists_at_index(int index) {
        int item_count = ListView_GetItemCount(this->get_handle());
        return (index >= 0 && index < item_count);
    }

    void delete_item_at_index(int index) {
        ListView_DeleteItem(this->get_handle(), index);
    }

    int item_count() {
        return ListView_GetItemCount(this->get_handle());
    }

    int item_count_in_column(int column_index)
    {
        int item_count = this->item_count();
        int column_item_count = 0;

        for (int i = 0; i < item_count; ++i) 
        {
            autostring item_text = this->get_item_by_index(i, column_index);

            if (item_text.length() > 0) 
            {
                ++column_item_count;
            }
        }

        return column_item_count;
    }

    void add_item(autostring text, int column = 0) {
        int item_count = this->item_count();

        if (column == 0) 
        {
            LVITEM lvItem;
            lvItem.mask = LVIF_TEXT;
            lvItem.iItem = item_count;
            lvItem.iSubItem = 0;
            lvItem.pszText = const_cast<autochar*>(text.c_str());

            ListView_InsertItem(this->get_handle(), &lvItem);
        }
        else
        {
            ListView_SetItemText(this->get_handle(), this->item_count_in_column(column), column, const_cast<autochar*>(text.c_str()));
        }
    }


    void clear_all_values() {
        ListView_DeleteAllItems(this->get_handle());
    }

    void clear_column(int column_index) {
        for (int i = 0; i < this->item_count(); ++i)
        {
            ListView_SetItemText(this->get_handle(), i, column_index, const_cast<autochar*>(_T("")));
        }
    }

    void add_click_handler(std::function<void(LPNMITEMACTIVATE)> on_click)
    {
        list_click_handlers.emplace(this->get_id(), on_click);
    }
};
