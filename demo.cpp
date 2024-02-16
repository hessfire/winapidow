#include <Windows.h>
#include <iostream>
#include <string>
#include <format>

#include "winapidow/includes.h"
#include "winapidow/window.h"

#include "winapidow/controls/all_controls.h"

bool is_numeric(std::wstring str)
{
	std::wstring::const_iterator it = str.begin();
	while (it != str.end() && std::isdigit(*it)) ++it;
	return !str.empty() && it == str.end();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int w = 640, h = 380;

	window* wnd = new window(hInstance, L"demo_class", L"demo", w, h, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);

	progress_bar_control* progress_bar = new progress_bar_control{ 10, 10, 270, 20, 100, 10 };
	button_control* step_button = new button_control{ L"step", 10, 40, 140, 20 };
	button_control* reset_button = new button_control{ L"reset", 150, 40, 130, 20 };
	textbox_control* step_amount = new textbox_control{ L"10", 290, 10, 65, 20 };
	label_control* amount_hint = new label_control{ L"step amount", 290, 40, 70, 20 };
	button_control* dif_style_button = new button_control{ L"button with different style", 380, 15, 225, 40, WS_CHILD | WS_VISIBLE | BS_COMMANDLINK };
	horizontal_separator_control* separator1 = new horizontal_separator_control{ 10, 70, w - 40, 1 };
	vertical_separator_control* separator2 = new vertical_separator_control{ 370, 10, 1, 50 };

	listview_control* lw = new listview_control{ 10, 80, 270, 240 };
	textbox_control* item_to_add = new textbox_control{ L"something", 290, 80, 120, 20 };
	button_control* add_item_button = new button_control{ L"add item", 290, 110, 120, 20 };
	button_control* clear_list_button = new button_control{ L"clear list", 420, 80, 190, 20 };
	button_control* nothing_button = new button_control{ L"nothin", 420, 110, 190, 20 };
	horizontal_separator_control* separator3 = new horizontal_separator_control{ 290, 140, 320, 1 };

	groupbox_control* groupbox = new groupbox_control{ L"other things", 290, 150, 320, 170 };

	checkbox_control* checkbox1 = new checkbox_control(L"check 1", 300, 170, 60, 20);
	checkbox_control* checkbox2 = new checkbox_control(L"check 2", 370, 170, 60, 20);
	checkbox_control* checkbox3 = new checkbox_control(L"check 3", 440, 170, 60, 20);
	button_control* check_status_button = new button_control(L"check status", 510, 170, 90, 20);

	radiobutton_control* radio1 = new radiobutton_control(L"radio 1", 300, 200, 60, 20);
	radiobutton_control* radio2 = new radiobutton_control(L"radio 2", 370, 200, 60, 20);
	radiobutton_control* radio3 = new radiobutton_control(L"radio 3", 440, 200, 60, 20);
	button_control* check_status_button_radio = new button_control(L"check status", 510, 200, 90, 20);

	combobox_control* combobox1 = new combobox_control(300, 230, 200, 20);
	button_control* selected_item_button = new button_control(L"selected item", 510, 230, 90, 20);

	button_hidden_control* hidden_button_test = new button_hidden_control(L"this button has hidden text", 300, 260, 300, 20);
	label_control* info_label = new label_control(L"it cannot be seen by enumerating subwindows", 300, 290, 300, 20);

	wnd->add_control(progress_bar);
	wnd->add_control(step_button);
	wnd->add_control(reset_button);
	wnd->add_control(step_amount);
	wnd->add_control(amount_hint);
	wnd->add_control(dif_style_button);
	wnd->add_control(separator1);
	wnd->add_control(separator2);

	wnd->add_control(lw);
	wnd->add_control(item_to_add);
	wnd->add_control(add_item_button);
	wnd->add_control(clear_list_button);
	wnd->add_control(nothing_button);
	wnd->add_control(separator3);
	wnd->add_control(groupbox);

	wnd->add_control(checkbox1);
	wnd->add_control(checkbox2);
	wnd->add_control(checkbox3);
	wnd->add_control(check_status_button);

	wnd->add_control(radio1);
	wnd->add_control(radio2);
	wnd->add_control(radio3);
	wnd->add_control(check_status_button_radio);

	wnd->add_control(combobox1);
	wnd->add_control(selected_item_button);

	wnd->add_control(hidden_button_test);
	wnd->add_control(info_label);

	lw->insert_column(0, L"column", 140);

	combobox1->add_item(L"item1");
	combobox1->add_item(L"item2");
	combobox1->add_item(L"item3");

	hidden_button_test->add_click_handler([&]() {
		MessageBoxW(0, L"you still can click it! (though there is no animation)", 0, MB_ICONINFORMATION);
	});

	selected_item_button->add_click_handler([&]() {
		MessageBoxW(0, std::format(L"{}", combobox1->get_selected_text()).c_str(), 0, 0);
	});

	check_status_button_radio->add_click_handler([&]() {
		MessageBoxW(0, std::format(L"radio1 = {}, radio3 = {}, radio3 = {}", radio1->is_checked(), radio2->is_checked(), radio3->is_checked()).c_str(), 0, 0);
	});

	check_status_button->add_click_handler([&]() {
		MessageBoxW(0, std::format(L"check1 = {}, check2 = {}, check3 = {}", checkbox1->is_checked(), checkbox2->is_checked(), checkbox3->is_checked()).c_str(), 0, 0);
	});

	add_item_button->add_click_handler([&]() {
		lw->add_item(item_to_add->get_text());
	});

	clear_list_button->add_click_handler([&]() {
		lw->clear_all_values();
	});

	step_button->add_click_handler([&]() {
		std::wstring amount = step_amount->get_text();

		if (!is_numeric(amount))
		{
			MessageBoxW(0, L"given amount is not numeric", 0, MB_ICONERROR);
			return;
		}

		progress_bar->set_step(std::stoi(amount));
		progress_bar->step();
	});

	reset_button->add_click_handler([&]() {
		progress_bar->set_position(0);
	});

	wnd->show();

	wnd->start_message_loop();
}