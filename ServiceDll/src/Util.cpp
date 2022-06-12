#include "Util.h"
#include <string>
int ReadJSON(char *buff, InputJSON &in) {
	int i = 0;
	char ch = buff[i];
	int state = 0;
	int start = 0;
	int stop = -1;
	std::string key;
	std::string value;
	bool flag = true;
	while (flag)
	{
		ch = buff[i];
		switch (state) {
		case 0:
			if (ch == '{') {
				state = 1;
			}
			else {
				state = -1;
				flag = false;
			}
			break;
		case 1:
			if (ch == '\"') {
				state = 2;
			}
			else {
				state = -2;
				flag = false;
			}
			break;
		case 2:
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
				start = i;
			}
			else {
				state = -3;
				flag = false;
			}
			break;
		case 3:
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
				break;
			}
			else {
				state = -4;
				flag = false;
			}
			break;
		case 4:
			if (ch == '\"') {
				stop = i;
				int len = stop - start;
				string 
			}
			else {
				state = -5;
				flag = false;
			}
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		

		default:
			break;
		}
		i++;
	}
/*

	while (ch) {

		switch (state)
		{
		case 0:
			if (ch == ' ') {
				i++;
			}
			else if (ch == '-') {
				state = 4;
				i++;
			}
			else {
				state = 1;
			}
			break;
		case 1:
			if (ch >= 48 && ch <= 57) {
				X *= 10;
				X += ch - 48;
				i++;
			}
			else if (ch == ' ') {

				state = 2;
			}
			else {
				return;
			}

			break;
		case 2:
			if (ch == ' ') {
				i++;
			}
			else if (ch >= 48 && ch <= 57) {
				state = 3;
			}
			else if (ch == '-') {
				state = 5;
				i++;
			}
			else {
				return;
			}
			break;
		case 3:
			if (ch >= 48 && ch <= 57) {
				Y *= 10;
				Y += ch - 48;
				i++;
			}
			else {
				state = 6;
			}
			break;
		case 4:
			if (ch >= 48 && ch <= 57) {
				X *= 10;
				X += ch - 48;
				i++;
			}
			else {
				X *= -1;
				state = 2;
			}
			break;
		case 5:
			if (ch <= 57 && ch >= 48) {
				Y *= 10;
				Y -= ch - 48;
				i++;
			}
			else {

				state = 6;
			}
			break;
		case 6:
			while (true) {
				ch = buff[i++];
				if (ch != ' ') {
					msg = ch;
					return;
				}
			}
			break;
		default:
			break;
		}
		ch = buff[i];
	}*/
}