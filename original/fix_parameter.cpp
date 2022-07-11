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
  {1,0,8}
};

int C1_set[1][3] = {
  {1,0,8}
};
int
main (int argc, char *argv[])
{
  int now = 0;
  int seedwrite =seed;
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
    if (now<=20)
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
    else if (now == 21)
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

  if (condition == 1)
  {
    for (int i = 0 ; i< 24 ; i++)
    {
      if (C1_set[i][0]==EncodeMaxNum)
      {
        if (C1_set[i][1]==BM_enable)
        {
          if (C1_set[i][2]==UserNum)
         {
          now = i;
         }
        }
      }
    }
    now++;
    std::cout << now<<"\n";
    if (now<=0)
    {
      ofstream fout;
      fout.open("parameter.h" ,std::ios::trunc);
      fout  <<  "#define seed "  << seedwrite << "\n";
      fout  <<  "#define condition "  << 1 << "\n";
      fout  <<  "#define EncodeMaxNum "  << C1_set[now][0] << "\n";
      fout  <<  "#define BM_enable "  << C1_set[now][1] << "\n";
      fout  <<  "#define UserNum "  << C1_set[now][2] << "\n";
      fout.close();
    }
    else if (now == 1)
    {
      now = 0;
      ofstream fout;
      fout.open("parameter.h" ,std::ios::trunc);
      fout  <<  "#define seed "  << seedwrite+5 << "\n";
      fout  <<  "#define condition "  << 1 << "\n";
      fout  <<  "#define EncodeMaxNum "  << C1_set[now][0] << "\n";
      fout  <<  "#define BM_enable "  << C1_set[now][1] << "\n";
      fout  <<  "#define UserNum "  << C1_set[now][2] << "\n";
      fout.close();
    }
  }


  return 0;
}

