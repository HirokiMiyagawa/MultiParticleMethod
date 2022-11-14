/**
 * @file ExportToCsv.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-12-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef EXPORTTOCSV_hpp
#define EXPORTTOCSV_hpp

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;

/**
 * @brief
 *
 */
class ExportToCsv {
   public:
    std::string ConvertFlagToPositionText(int const&, std::string const&);
    ExportToCsv();
    ~ExportToCsv();
};

std::string ExportToCsv::ConvertFlagToPositionText(int const& position_flag,
                                                   std::string const& shape) {
    std::map<int, string> reFlag;
    if (shape == "cuboid") {
        reFlag = {{0b00000000, "None"},
                  {0b00010000, "RightSideCenter"},
                  {0b00010001, "RightSideRight"},
                  {0b00010010, "RightSideLeft"},
                  {0b00010100, "RightSideBottom"},
                  {0b00011000, "RightSideTop"},
                  {0b00010101, "RightSideRightBottom"},
                  {0b00011001, "RightSideRightTop"},
                  {0b00010110, "RightSideLeftBottom"},
                  {0b00011010, "RightSideLeftTop"},

                  {0b00100000, "BackCenter"},
                  {0b00100001, "BackRight"},
                  {0b00100010, "BackLeft"},
                  {0b00100100, "BackBottom"},
                  {0b00101000, "BackTop"},
                  {0b00100101, "BackRightBottom"},
                  {0b00101001, "BackRightTop"},
                  {0b00100110, "BackLeftBottom"},
                  {0b00101010, "BackLeftTop"},

                  {0b01000000, "CeilingCenter"},
                  {0b01000001, "CeilingRight"},
                  {0b01000010, "CeilingLeft"},
                  {0b01000100, "CeilingBottom"},
                  {0b01001000, "CeilingTop"},
                  {0b01000101, "CeilingRightBottom"},
                  {0b01001001, "CeilingRightTop"},
                  {0b01000110, "CeilingLeftBottom"},
                  {0b01001010, "CeilingLeftTop"}};

        return reFlag[position_flag];
    }

    reFlag = {{0x00, "Center"},  {0x01, "Left"},        {0x02, "Right"},
              {0x03, "Bottom"},  {0x04, "Top"},         {0x05, "LeftBottom"},
              {0x06, "LeftTop"}, {0x07, "RightBottom"}, {0x08, "RightTop"}};

    return reFlag[position_flag];
}

#endif
