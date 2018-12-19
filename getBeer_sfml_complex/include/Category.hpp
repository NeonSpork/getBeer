#ifndef CATEGORY_HPP
#define CATEGORY_HPP

namespace Category
{
  enum Type
  {
    None = 0,
    Thumbnail = 1 << 0,
    Background = 1 << 1,
    DispensorButton = 1 << 2,
    SecretIndicator = 1 << 3,
    MenuChanger = 1 << 4,
    MenuExit = 1 << 5,
  };
}

#endif // CATEGORY_HPP