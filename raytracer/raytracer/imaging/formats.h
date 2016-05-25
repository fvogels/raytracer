#ifndef FORMATS_H
#define FORMATS_H

#include "bitmap.h"
#include <string>

Bitmap load_bitmap(const std::string& path);
void save_bitmap(const std::string& path, const Bitmap& bitmap);

#endif
