#ifndef LOGIN_H
#define LOGIN_H


#include <Arduino.h>
class Login
{
private:
    String tags[2];
    int length;
public:
    Login();
    boolean validate(String currentId);
};
#endif
