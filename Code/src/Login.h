#ifndef __LOGIN_H__
#define __LOGIN_H__

#include <Arduino.h>

class Login
{
private:
public:
    Login();
    boolean validate(String currentId);
};
#endif
