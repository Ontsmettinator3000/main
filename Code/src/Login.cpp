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

boolean Login::login(String currentId)
{
  if (validate(currentId))
  {
    if (std::find(scannedIDS.begin(), scannedIDS.end(), currentId) != scannedIDS.end())
    {
      scannedIDS.push_back(currentId);
      return true;
    }
    else
    {
      return false;
    }
  };
}

int Login::getUserCount()
{
  return scannedIDS.size();
}