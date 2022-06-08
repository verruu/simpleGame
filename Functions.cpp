#include "Header-files/Functions.h"

const std::string gui::menu_title(const std::string title)
{
    std::stringstream ss;
    ss << "-=" << title << "=-" << "\n\n";
    return ss.str();
}

const std::string gui::menu_divider(const unsigned amount, const char symbol)
{
    std::stringstream ss;
    ss << std::string(amount, symbol) << "\n\n";
    return ss.str();
}

const std::string gui::menu_item(const unsigned index, const std::string text)
{
    std::stringstream ss;
    ss << "-" << " (" << index << ") " << text << "\n";
    return ss.str();
}

const std::string gui::alert(const std::string message)
{
    std::stringstream ss;
    ss << "[[ " << message << " ]]" << "\n\n";
    return ss.str();
}

const std::string gui::error(const std::string message)
{
    std::stringstream ss;
    ss << "!! " << message << " !!" << "\n\n";
    return ss.str();
}

const std::string gui::progressBar(const int valueMin, const int valueMax, const int lengthMax,
                                   const char symbolEmpty, const char symbolFull)
{
    std::stringstream ss;

    double percent = static_cast<double>(valueMin)/valueMax;
    int sFull = lengthMax * percent;
    int sEmpty = lengthMax - sFull;

    if (sFull < 0)
        sFull = 0;
    else if (sFull > lengthMax)
        sFull = lengthMax;

    if (sEmpty < 0)
        sEmpty = 0;
    else if (sEmpty > lengthMax)
        sEmpty = lengthMax;

//    ss << percent << " " << sFull << " " << sEmpty << "\n";
    ss << " |" << std::string(sFull, symbolFull) << std::string(sEmpty, symbolEmpty) << "| ";

    return ss.str();
}
