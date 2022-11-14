#ifndef __INCLUDED_CSV_HPP__
#define __INCLUDED_CSV_HPP__

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Params.hpp"

using namespace std;

/**
 ///////////////////////////////////////////////////////////////////////////////
 * @brief csvファイルから、パラメーターを読み込んでシミュレーションを行う場合
 * @details 	引数付きコンストラクタ
 * @note		main関数からしか呼び出されない
 * 読み込むcsvファイルの2列目の最終行に'FALSE'と入力すること
 ///////////////////////////////////////////////////////////////////////////////
*/
class Csv {
   public:
    string csv_file;

   public:
    Csv(string);
    bool getCsv(vector<vector<string>>&, const char delim = ',');
    void myparamRead(Params&, vector<vector<string>>& data);
};

Csv::Csv(string csv_file) { this->csv_file = csv_file; }

bool Csv::getCsv(vector<vector<string>>& data, const char delim) {
    ifstream ifs(csv_file);
    if (!ifs.is_open()) {
        return false;
    }

    string buf;
    while (getline(ifs, buf)) {
        vector<string> rec;
        istringstream iss(buf);
        string field;
        while (getline(iss, field, delim)) {
            rec.push_back(field);
        }

        if (rec.size() != 0) {
            data.push_back(rec);
        }
    }

    return true;
}

/**
 * @brief	各行数ごとに値を格納する
 * @note	以下に各行数での読み込む値を示す
 * 0：iNum
 * 1：jNum
 * 2：m_sheet_skip
 * 3：Lref
 * 4：Vref
 * 5：Pref
 * 6：m_tmax
 * 7：m_kx
 * 8：m_ky
 * 9：m_kz
 * 10：m_dt
 * 11：m_E
 * 12：h0
 * 13：m_rh_0
 * 14：m_mu
 * 15：Cv
 */
void Csv::myparamRead(Params& myparamread, vector<vector<string>>& data) {
    for (unsigned int row = 0; row < data.size(); row++) {
        vector<string> rec = data[row];
        for (unsigned int col = 0; col < rec.size(); col++) {
            if (col < rec.size() - 1) {
                cout << rec[col];
                cout << "=";
            } else {
                switch (row) {
                    case 0:
                        myparamread.m_iNum = atoi(rec[col].c_str());
                        cout << myparamread.m_iNum;
                        break;

                    case 1:
                        myparamread.m_jNum = atoi(rec[col].c_str());
                        cout << myparamread.m_jNum;
                        break;

                    case 2:
                        myparamread.m_sheet_skip = atof(rec[col].c_str());
                        cout << myparamread.m_sheet_skip;
                        break;

                    case 3:
                        myparamread.Lref = atof(rec[col].c_str());
                        cout << myparamread.Lref;
                        break;

                    case 4:
                        myparamread.Vref = atof(rec[col].c_str());
                        cout << myparamread.Vref;
                        break;

                    case 5:
                        myparamread.Pref = atof(rec[col].c_str());
                        cout << myparamread.Pref;
                        break;

                    case 6:
                        myparamread.m_tmax = atof(rec[col].c_str());
                        cout << myparamread.m_tmax;
                        break;

                    case 7:
                        myparamread.m_kx = atof(rec[col].c_str());
                        cout << myparamread.m_kx;
                        break;

                    case 8:
                        myparamread.m_ky = atof(rec[col].c_str());
                        cout << myparamread.m_ky;
                        break;

                    case 9:
                        myparamread.m_kz = atof(rec[col].c_str());
                        cout << myparamread.m_kz;
                        break;

                    case 10:
                        myparamread.m_dt = atof(rec[col].c_str());
                        cout << myparamread.m_dt;
                        break;

                    case 11:
                        myparamread.m_E = atof(rec[col].c_str());
                        cout << myparamread.m_E;
                        break;

                    case 12:
                        myparamread.h0 = atof(rec[col].c_str());
                        cout << myparamread.h0;
                        break;

                    case 13:
                        myparamread.m_rho = atof(rec[col].c_str());
                        cout << myparamread.m_rho;
                        break;

                    case 14:
                        myparamread.m_nu = atof(rec[col].c_str());
                        cout << myparamread.m_nu;
                        break;

                    case 15:
                        myparamread.Cv = atof(rec[col].c_str());
                        cout << myparamread.Cv;
                        break;
                }
            }
        }
        cout << endl;
    }
}

#endif
