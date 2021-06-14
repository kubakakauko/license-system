#include "crypto/sealedbox.hpp"
#include "http/http.hpp"
#include "auth/hwid.hpp"
#include "auth/validation.hpp"

//Requirements for the scripts
#include <Windows.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <stdio.h>
#include "../Weapons.hpp"
#include <fcntl.h> 

#include <io.h>
#include <fcntl.h> 
#include <cstdio>
//Includes for Dialog
#include <shobjidl.h> 
#include <sstream>
#include <fstream>

#define FG_RED "\033[31m"
#define FG_PURPLE "\033[35m"
#define FG_GREEN "\033[32m"
#define FG_YELLOW "\033[33m"
#define FG_CYAN  "\033[1;36m"

int currentwep = 0;
int scope = 0;
int barrel = 0;
int randomizer = 0;
float playerfov = 90.0f;
float playersens = 1.0f;
bool enabled = false;
std::string username;
std::string configPath = "C:/Program Files (x86)/Steam/steamapps/common/Rust/cfg/client.cfg";

//Opens the file directory and sets configPath to user selection.
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
		COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr))
	{
		IFileOpenDialog* pFileOpen;
		// Create the FileOpenDialog object.
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

		if (SUCCEEDED(hr))
		{
			// Show the Open dialog box.
			hr = pFileOpen->Show(NULL);

			// Get the file name from the dialog box.
			if (SUCCEEDED(hr))
			{
				IShellItem* pItem;
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr))
				{
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					// Display the file name to the user.
					if (SUCCEEDED(hr))
					{
						MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
						std::wstring ws(pszFilePath);
						std::string strP(ws.begin(), ws.end());
						//Setting the string.
						configPath.assign(strP);

						CoTaskMemFree(pszFilePath);
					}
					pItem->Release();
				}
			}
			pFileOpen->Release();
		}
		CoUninitialize();
	}
	return 0;
}

std::string RemoveChars(const std::string& source, const std::string& chars) {
	std::string result = "";
	for (unsigned int i = 0; i < source.length(); i++) {
		bool foundany = false;
		for (unsigned int j = 0; j < chars.length() && !foundany; j++) {
			foundany = (source[i] == chars[j]);
		}
		if (!foundany) {
			result += source[i];
		}
	}
	return result;
}

void ReadSetting() {

	std::ifstream infline(configPath);
	std::string fovString;
	std::string sensString;

	if (infline.is_open()) {
		for (int i = 0; i < 71; i++)
		{
			std::getline(infline, fovString);
			//std::getline(infline, testing);
		}
		std::string const s = fovString;
		std::string::size_type const n = s.find('"');
		fovString = RemoveChars(s.substr(n), "\"");

		for (int i = 0; i < 27; i++) {
			std::getline(infline, sensString);
		}
		std::string const st = sensString;
		std::string::size_type const x = st.find('"');
		sensString = RemoveChars(st.substr(x), "\"");

		playerfov = std::stof(fovString);
		playersens = std::stof(sensString);
	}
	else {
		wWinMain(NULL, NULL, NULL, 0);
		ReadSetting();
	}
}

void DrawCLI()
{
	system("cls");
	system("color 3");
	_setmode(_fileno(stdout), 0x20000);
	wprintf(L"ANUB!NGUS#8780\n");
	_setmode(_fileno(stdout), _O_TEXT);


	std::cout << FG_GREEN << "Enable/Disable: INSERT" << std::endl;
	std::cout << FG_GREEN << "Reload setting: F5" << std::endl;
	std::cout << FG_CYAN << "Switch weapons: PGUP / PGDN / FN 2 - 8" << std::endl;
	std::cout << FG_CYAN << "Switch scope: LEFT ARROW / RIGHT ARROW" << std::endl;
	std::cout << FG_CYAN << "Switch barrel: DOWN ARROW / UP ARROW" << std::endl;
	std::cout << std::endl;


	std::cout << FG_YELLOW << "Current Weapon: ";
	switch (currentwep)
	{
	case 0:
		std::cout << "AK-47" << std::endl;
		break;
	case 1:
		std::cout << "Thompson" << std::endl;
		break;
	case 2:
		std::cout << "Custom SMG" << std::endl;
		break;
	case 3:
		std::cout << "LR-300" << std::endl;
		break;
	case 4:
		std::cout << "MP5A4" << std::endl;
		break;
	case 5:
		std::cout << "SAR" << std::endl;
		break;
	case 6:
		std::cout << "M249" << std::endl;
		break;
	case 7:
		std::cout << "TEST" << std::endl;
		break;
	}
	std::cout << FG_YELLOW << "Current Scope: ";
	switch (scope)
	{
	case 0:
		std::cout << "None" << std::endl;
		break;
	case 1:
		std::cout << "Holo" << std::endl;
		break;
	case 2:
		std::cout << "X8" << std::endl;
		break;
	case 3:
		std::cout << "X16" << std::endl;
		break;
	case 4:
		std::cout << "Simple Sights" << std::endl;
		break;

	default:
		std::cout << "NONE" << std::endl;
		break;
	}
	std::cout << FG_YELLOW << "Current Barrel: ";
	switch (barrel)
	{
	case 0:
		std::cout << "None" << std::endl;
		break;
	case 1:
		std::cout << "Suppressor" << std::endl;
		break;
	case 2:
		std::cout << "Muzzle brake" << std::endl;
		break;
	}
	std::cout << std::endl;

	std::cout << (enabled ? FG_GREEN "Enabled" : FG_RED "Enabled");
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "FOV: " << playerfov << std::endl;
	std::cout << "SENS: " << playersens << std::endl;

	std::cout << FG_CYAN << "Update Logs (v1.3): ";
	std::cout << std::endl;
	std::cout << FG_CYAN << "Added automatic setting reader";

}

float Randomize(float val, int perc)
{
	srand(time(NULL));
	float range = val * perc / 100;

	if (range <= 0.5) return val;
	if (range > 0.5) range = 1;

	int result = 1 + (rand() % (int)range);

	if ((1 + (rand() % 1) > 0)) return val + result;
	else return val + (result * -1);
}

void QuerySleep(int ms) // Sleep / Delay
{
	LONGLONG timerResolution;
	LONGLONG wantedTime;
	LONGLONG currentTime;

	QueryPerformanceFrequency((LARGE_INTEGER*)&timerResolution);
	timerResolution /= 1000;

	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
	wantedTime = currentTime / timerResolution + ms;
	currentTime = 0;
	while (currentTime < wantedTime)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
		currentTime /= timerResolution;
	}
}

void Smoothing(double delay, double control_time, float x, float y)
{
	int x_ = 0, y_ = 0, t_ = 0;
	for (int i = 1; i <= (int)control_time; ++i)
	{
		int xI = i * x / (int)control_time;
		int yI = i * y / (int)control_time;
		int tI = i * (int)control_time / (int)control_time;
		mouse_event(1, (int)xI - (int)x_, (int)yI - (int)y_, 0, 0);
		QuerySleep((int)tI - (int)t_);
		x_ = xI; y_ = yI; t_ = tI;
	}
	QuerySleep((int)delay - (int)control_time);
}

float getScope(float val)
{

	if (scope == 1)
		return val * 1.2;
	if (scope == 2)
		return val * 3.84;
	if (scope == 4)
		return val * 0.80;
	if (barrel == 1)
		return val * 0.80;
	if (barrel == 2)
		return val * 0.5;
	return val;
}

float tofovandsens(float sens, int fov, float val)
{
	float a = (0.5 * fov * val) / (sens * 90);
	return getScope(a);
}

std::int32_t main()
{
    sodium_init();

    ls::validation v("http://9b59cc5a3545.ngrok.io", "kYaIFZjOwgk8YPcH7Ffx9//MlMXaajt+moZYUvMYB3U=" );
     // 400: Bad Request
     // 401: Unauthorized
	std::cout << "Please enter your username: " << std::endl;
	std::cin >> username;

	std::cout << v.login(username) << std::endl;

	if( !v.login( username ) ) {
        return -1;
    }

    std::vector<ls::validation::subscription_type> subs;
    if( !v.get_subscriptions( subs ) ) {
        return -1;
    }

    std::string file;
    if( !v.get_product( std::get<1>( subs.front() ), file ) ) {
        return -1;
    }


	//At this point the program seems activated

    printf( "ok!\n" ); 
    getchar();

	//Reading setting of the client once
	ReadSetting();

	int count = 0;
	SetConsoleTitle(L"!ANUBINGUS! | ANUB!NGUS#8780");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);

	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL) { MoveWindow(hwnd, 0, 0, 420, 320, FALSE); }

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);


	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE));
	DrawCLI();

	while (true)
	{

		if (GetKeyState(VK_F9) & 0x8000)
		{
			if (currentwep != 7)
			{
				currentwep = 7;
				DrawCLI();
			}
		}
		if (GetKeyState(VK_F2) & 0x8000)
		{
			if (currentwep != 0)
			{
				currentwep = 0;
				DrawCLI();
			}
		}
		if (GetKeyState(VK_F3) & 0x8000)
		{
			if (currentwep != 1)
			{
				currentwep = 1;
				DrawCLI();
			}
		}
		if (GetKeyState(VK_F4) & 0x8000)
		{
			if (currentwep != 2)
			{
				currentwep = 2;
				DrawCLI();
			}
		}
		if (GetKeyState(VK_F5) & 0x8000)
		{
			if (currentwep != 3)
			{
				currentwep = 3;
				DrawCLI();
			}
		}
		if (GetKeyState(VK_F6) & 0x8000)
		{
			if (currentwep != 4)
			{
				currentwep = 4;
				DrawCLI();
			}
		}
		if (GetKeyState(VK_F7) & 0x8000)
		{
			if (currentwep != 5)
			{
				currentwep = 5;
				DrawCLI();
			}
		}
		if (GetKeyState(VK_F8) & 0x8000)
		{
			if (currentwep != 6)
			{
				currentwep = 6;
				DrawCLI();
			}
		}
		if (GetAsyncKeyState(VK_INSERT) == -32767)
		{
			enabled = !enabled;
			DrawCLI();
		}

		if (GetAsyncKeyState(VK_LEFT) == -32767)
		{
			if (scope != 0) { scope--; }
			else { scope = 4; }
			DrawCLI();
		}

		if (GetAsyncKeyState(VK_RIGHT) == -32767)
		{
			if (scope != 4) { scope++; }
			else { scope = 0; }
			DrawCLI();
		}

		if (GetAsyncKeyState(VK_UP) == -32767) {
			if (barrel != 2) { barrel++; }
			else { barrel = 0; }
			DrawCLI();
		}

		if (GetAsyncKeyState(VK_DOWN) == -32767) {
			if (barrel != 0) { barrel--; }
			else { barrel = 2; }
			DrawCLI();
		}

		if (GetAsyncKeyState(VK_NEXT) == -32767) {
			if (currentwep != 6) { currentwep++; }
			else { currentwep = 0; }
			DrawCLI();
		}

		if (GetAsyncKeyState(VK_PRIOR) == -32767) {
			if (currentwep != 0) { currentwep--; }
			else { currentwep = 6; }
			DrawCLI();
		}
		if (GetAsyncKeyState(VK_F5) & 0x8000) {
			ReadSetting();
		}



		if (enabled == true)
		{
			if (GetAsyncKeyState(VK_LBUTTON) && GetAsyncKeyState(VK_RBUTTON))
			{

				switch (currentwep)
				{
				case 0:
					if (count < Weapons::ak::pattern.size())
					{
						Smoothing(Weapons::ak::delay, Weapons::ak::controltime.at(count), Randomize(tofovandsens(playersens, playerfov, Weapons::ak::pattern.at(count).x), randomizer), Randomize(tofovandsens(playersens, playerfov, Weapons::ak::pattern.at(count).y), randomizer));
						count++;
					}
					break;
				case 1:
					if (count < Weapons::thompson::pattern.size())
					{
						Smoothing(Weapons::thompson::delay, Weapons::thompson::delay, Randomize(tofovandsens(playersens, playerfov, Weapons::thompson::pattern.at(count).x), randomizer), Randomize(tofovandsens(playersens, playerfov, Weapons::thompson::pattern.at(count).y), randomizer));
						count++;
					}
					break;
				case 7:
					if (count < Weapons::test::pattern.size())
					{
						Smoothing(Weapons::test::delay, Weapons::test::delay, Randomize(tofovandsens(playersens, playerfov, Weapons::test::pattern.at(count).x), randomizer), Randomize(tofovandsens(playersens, playerfov, Weapons::test::pattern.at(count).y), randomizer));
						count++;
					}
					break;
				case 2:
					if (count < Weapons::smg::pattern.size())
					{
						Smoothing(Weapons::smg::delay, Weapons::smg::delay, Randomize(tofovandsens(playersens, playerfov, Weapons::smg::pattern.at(count).x), randomizer), Randomize(tofovandsens(playersens, playerfov, Weapons::smg::pattern.at(count).y), randomizer));
						count++;
					}
					break;
				case 3:
					if (count < Weapons::lr::pattern.size())
					{
						Smoothing(Weapons::lr::delay, Weapons::lr::delay, Randomize(tofovandsens(playersens, playerfov, Weapons::lr::pattern.at(count).x), randomizer), Randomize(tofovandsens(playersens, playerfov, Weapons::lr::pattern.at(count).y), randomizer));
						count++;
					}
					break;
				case 4:
					if (count < Weapons::mp5::pattern.size())
					{
						Smoothing(Weapons::mp5::delay, Weapons::mp5::delay, Randomize(tofovandsens(playersens, playerfov, Weapons::mp5::pattern.at(count).x), randomizer), Randomize(tofovandsens(playersens, playerfov, Weapons::mp5::pattern.at(count).y), randomizer));
						count++;
					}
					break;
				case 5:
					if (count < Weapons::semi::pattern.size())
					{
						Smoothing(Weapons::semi::delay, Weapons::semi::delay, Randomize(tofovandsens(playersens, playerfov, Weapons::semi::pattern.at(count).x), randomizer), Randomize(tofovandsens(playersens, playerfov, Weapons::semi::pattern.at(count).y), randomizer));
					}
					break;
				case 6:
					Smoothing(Weapons::m249::delay, Weapons::m249::delay, Randomize(tofovandsens(playersens, playerfov, Weapons::m249::pattern.at(count).x), randomizer), Randomize(tofovandsens(playersens, playerfov, Weapons::m249::pattern.at(count).y), randomizer));
					break;
				default:
					break;
				}

			}
			else
				count = 0;
		}

	}

    return 0;
}
