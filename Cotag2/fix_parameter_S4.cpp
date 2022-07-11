/*
 * Copyright (c) 2015-2020 IMDEA Networks Institute
 * Author: Hany Assasa <hany.assasa@gmail.com>
 */
#include "parameter.h"
#include <ios>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
// using namespace ns3;
using namespace std;
int C2_set[1][3] = {
  {14,0,6},
};

int C1_set[24][3] = {
  {14,0,8},
  {14,0,7},
  {14,0,6},
  {14,0,5},
  {14,0,4},
  {14,0,3},
  {14,0,2},
  {14,0,1}, // 7
};
int
main (int argc, char *argv[])
{
  int now = 0;
  int seedwrite = seed;
  if (condition == 2)
  {
    for (int i =0 ; i< 21 ; i++)
    {
      if (C2_set[i][0]==EncodeMaxNum)
      {
        if (C2_set[i][1]==BM_enable)
        {
          if (C2_set[i][2]==UserNum)
         {
          now = i;
         }
        }
      }
    }
    now++;
    if (now<=0)
    {
      ofstream fout;
      fout.open("parameter.h" ,std::ios::trunc);
      fout  <<  "#define seed "  << seedwrite << "\n";
      fout  <<  "#define condition "  << 2 << "\n";
      fout  <<  "#define EncodeMaxNum "  << C2_set[now][0] << "\n";
      fout  <<  "#define BM_enable "  << C2_set[now][1] << "\n";
      fout  <<  "#define UserNum "  << C2_set[now][2] << "\n";
      fout.close();
    }
    else
    {
      now = 0;
      ofstream fout;
      fout.open("parameter.h" ,std::ios::trunc);
      fout  <<  "#define seed "  << seedwrite + 5 << "\n";
      fout  <<  "#define condition "  << 2 << "\n";
      fout  <<  "#define EncodeMaxNum "  << C2_set[now][0] << "\n";
      fout  <<  "#define BM_enable "  << C2_set[now][1] << "\n";
      fout  <<  "#define UserNum "  << C2_set[now][2] << "\n";
      fout.close();
    }
  }


  return 0;
}

