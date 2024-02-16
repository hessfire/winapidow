#pragma once
#include "includes.h"

class base_control;

std::unordered_map<int /*id*/, std::function<void()> /*on_click*/> button_handlers = {};
std::unordered_map<int /*id*/, std::function<void(LPNMITEMACTIVATE)> /*on_click*/> list_click_handlers = {};
std::unordered_map<int /*id*/, std::function<void()> /*on_check*/> checkbox_handlers = {};
std::unordered_map<int /*index*/, DWORD /*bg_color*/> list_items_colors = {};
std::unordered_map<int /*id*/, base_control* /*button*/> hidden_controls = {};
int ids_base = 1000;

#ifdef _UNICODE
typedef wchar_t autochar;
typedef std::wstring autostring;
#else
typedef char autochar;
typedef std::string autostring;
#endif