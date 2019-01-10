#include "../include/ds18b20.h"

Ds18b20::Ds18b20()
{
  init();
}

Ds18b20::~Ds18b20()
{
}

void Ds18b20::init()
{
  try
  {
    dir = opendir (path);
    if (dir == NULL)
    {
      throw NoDir{};
    }
    if (dir != NULL)
    {
      while ((dirent = readdir (dir)))
      // 1-wire devices are links beginning with 28-
      if (dirent->d_type == DT_LNK && strstr(dirent->d_name, "28-") != NULL)
      { 
        strcpy(dev, dirent->d_name);
        printf("\nDevice: %s\n", dev);
      }
      (void) closedir (dir);
    }
  }
  catch(NoDir)
  {
    std::cout << "Couldn't open the w1 devices directory\n";
  }
}

float Ds18b20::getTemp()
{
  try
  {
    sprintf(devPath, "%s/%s/w1_slave", path, dev);
    int fd = open(devPath, O_RDONLY);
    if(fd == -1)
    {
      throw NoRead{};   
    }
    float tempC;
    while((numRead = read(fd, buf, 256)) > 0) 
    {
     strncpy(tmpData, strstr(buf, "t=") + 2, 5); 
     tempC = strtof(tmpData, NULL);
     printf("Temp: %.3f C  \n", tempC / 1000);
    }
    close(fd);
    return tempC / 1000;
  }
  catch(NoRead)
  {
    std::cout << "No temp to read.\n";
    return 0;
  }
}