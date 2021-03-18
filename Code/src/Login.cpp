#include "Login.h"
#include "validTags.h"
#include "config.h"

Login::Login()
{
}

boolean Login::validate(String currentId)
{
#ifdef groepsOntsmetting
  for (int i = 0; i < length; i++)
  {
    if (tags[i].compareTo(currentId) == 0)
    {
      return true;
    }
  }
  return false;
#endif

#ifdef duoOntsmetting
  for (int i = 0; i < bestemtteIDS.size(); i++)
  {
    int index = bestemtteIDS.at(i);
    if (tags[index].compareTo(currentId) == 0)
    {
      return true;
    }
  }
  return false;
#endif
}

boolean Login::login(String currentId)
{
  if (validate(currentId))
  {
    if (std::find(scannedIDS.begin(), scannedIDS.end(), currentId) == scannedIDS.end())
    {
      scannedIDS.push_back(currentId);
      return true;
    }
    else
    {
      return false;
    }
  }
  else
    return false;
}

int Login::getUserCount()
{
  return scannedIDS.size();
}

void Login::reset()
{
  scannedIDS.clear();
  bestemtteIDS.clear();
}

void Login::setId(String ids)
{
  bestemtteIDS.clear();
  bestemtteIDS.push_back(ids.charAt(0) - 48);
  bestemtteIDS.push_back(ids.charAt(1) - 48);
  Serial.print("id set: ");
  for (unsigned i = 0; i < bestemtteIDS.size(); i++)
  {
    Serial.println(bestemtteIDS.at(i));
  }
}