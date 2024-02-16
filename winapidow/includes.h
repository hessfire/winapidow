#pragma once

#include <unordered_map>
#include <Windows.h>
#include <CommCtrl.h>
#include <tlhelp32.h>
#include <winternl.h>
#include <functional>
#include <algorithm> 
#include <iostream>
#include <typeinfo>
#include <psapi.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <random>
#include <format>
#include <mutex> 
#include <ctime>

#include "globals.h"
#include "window.h"

using std::vector;

#pragma comment(lib, "Comctl32.lib")

#pragma comment(linker,"/manifestdependency:\"type='win32' "\
               "name='Microsoft.Windows.Common-Controls' "\
               "version='6.0.0.0' "\
               "processorArchitecture='*' "\
               "publicKeyToken='6595b64144ccf1df' "\
               "language='*' "\
               "\"")