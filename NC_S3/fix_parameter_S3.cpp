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
int C2_set[20][3] = {
  {14,7,8},
  {14,11,8},
  {14,15,8},
  {14,19,8},
  {14,23,8},
  {1,7,8},
  {1,11,8},
  {1,15,8},
  {1,19,8},
  {1,23,8},
  {14,7,4},
  {14,11,4},
  {14,15,4},
  {14,19,4},
  {14,23,4},
  {1,7,4},
  {1,11,4},
  {1,15,4},
  {1,19,4},
  {1,23,4}
};

// int C2_set[82][3] = {
//   {14,8,8},
//   {1,8,8}

// };

int C1_set[24][3] = {
  {14,1,8},
  {14,1,7},
  {14,1,6},
  {14,1,5},
  {14,1,4},
  {14,1,3},
  {14,1,2},
  {14,1,1}, // 7
  {1,1,8},
  {1,1,7},
  {1,1,6},
  {1,1,5},
  {1,1,4},
  {1,1,3},
  {1,1,2}, 
  {1,1,1}, //15
  {1,0,8},
  {1,0,7},
  {1,0,6},
  {1,0,5},
  {1,0,4},
  {1,0,3},
  {1,0,2}, 
  {1,0,1}
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
    if (now<=19)
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
    else if (now == 20)
    {
      now = 0;
      ofstream fout;
      fout.open("parameter.h" ,std::ios::trunc);
      fout  <<  "#define seed "  << seedwrite+5 << "\n";
      fout  <<  "#define condition "  << 2 << "\n";
      fout  <<  "#define EncodeMaxNum "  << C2_set[now][0] << "\n";
      fout  <<  "#define BM_enable "  << C2_set[now][1] << "\n";
      fout  <<  "#define UserNum "  << C2_set[now][2] << "\n";
      fout.close();
    }
  }


  return 0;
}

