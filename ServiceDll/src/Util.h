#pragma once

struct InputJSON {

};
/**
* return type indicates error code
* 0 for no errors
* ... and so on
* */
int ReadJSON(char *buff, struct InputJSON& input);
