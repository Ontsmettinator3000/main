#ifndef __LOGIN_H__
#define __LOGIN_H__

#include <Arduino.h>
#include <vector>
#include <algorithm>

class Login
{
private:
    std::vector<String> scannedIDS;

public:
    Login();
    boolean validate(String currentId);
    boolean login(String currentId);
    int getUserCount();
    void reset();
};
#endif
