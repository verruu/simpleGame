#pragma once

#include <sstream>
#include <string>

namespace gui
{
    const std::string menu_title(const std::string title);
    const std::string menu_divider(const unsigned amount = 40, const char symbol = '-');
    const std::string menu_item(const unsigned index, const std::string text);
    const std::string progressBar(const int valueMin, const int valueMax, const int lengthMax,
                                  const char symbolEmpty, const char symbolFull);
    const std::string alert(const std::string message);
    const std::string error(const std::string message);
}
