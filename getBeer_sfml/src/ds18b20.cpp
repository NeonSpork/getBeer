#include "../include/ds18b20.h"

Ds18b20::Ds18b20()
{
  try
  {
    int status = init();
    if (status == 1)
    {
      throw NoInit{};
    }
  }
  catch (NoInit)
  {
    std::cout << "DS18B20 could not be initialized.\n";
  }
}

Ds18b20::~Ds18b20()
{
}

int Ds18b20::init()
{
  try
  {
    dir = opendir ("/sys/bus/w1/devices");
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
    return 0;
  }
  catch(NoDir)
  {
    std::cout << "Couldn't open the w1 devices directory\n";
    return 1;
  }
}

float Ds18b20::getTemp()
{
  try
  {
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
     // printf("Device: %s  - ", dev); 
     printf("Temp: %.3f C  \n", tempC / 1000);
     // printf("%.3f F\n\n", (tempC / 1000) * 9 / 5 + 32);
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