#include "Login.h"
#include "validTags.h"

Login::Login()
{
}

boolean Login::validate(String currentId)
{
  for (int i = 0; i < length; i++)
  {
    if (tags[i].compareTo(currentId) == 0)
    {
      return true;
    }
  }
  return false;
}