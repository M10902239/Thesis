/*
 * Copyright (c) 2015-2020 IMDEA Networks Institute
 * Author: Hany Assasa <hany.assasa@gmail.com>
 */
#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"
#include "ns3/wifi-module.h"
#include "ns3/point-to-point-module.h"
#include "common-functions.h"
#include "../parameter.h"
// #include "/home/wise/MengHua/0414Auto/NC/parameter.h"
#include "ns3/timestamp-tag.h"
// #include "ns3/flow-monitor-module.h"
// #include "ns3/spectrum-module.h"
// #include "ns3/beamforming-trace-helper.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <ios>
#define PI 3.14159
// #define UserNum 6

/**
 * Simulation Objective:
 * Compare the performance of the channel access schemes in IEEE 802.11ad/ay standards.
 * Basically, the simulation compares the achievable throughput between CSMA/CA and SP allocations.
 * Thw two devices support DMG/EDMG SC and OFDM PHY layers.
 *
 * Network Topology:
 * The scenario consists of signle DMG STA and single PCP/AP.
 *
 *          DMG PCP/AP (0,0)                       DMG STA (+1,0)
 *
 * Simulation Description:
 * In the case of CSMA/CA access period, the whole DTI access period is allocated as CBAP. Whereas in the
 * of SP allocation, once the DMG STA has assoicated successfully with the PCP/AP. The PCP/AP allocates the
 * whole DTI as SP allocation.
 *
 * Running Simulation:
 * To evaluate CSMA/CA channel access scheme using the IEEE 802.11ad standard:
 * ./waf --run "compare_access_schemes --scheme=1 --simulationTime=10 --pcap=true"
 *
 * To evaluate Service Period (SP) channel access scheme:
 * ./waf --run "compare_access_schemes --scheme=0 --simulationTime=10 --pcap=true"
 *
 * Simulation Output:
 * The simulation generates the following traces:
 * 1. PCAP traces for each station.
 * 2. The achieved throughput during a window of 100 ms.
 */

NS_LOG_COMPONENT_DEFINE ("CompareAccessSchemes");

using namespace ns3;
using namespace std;

/**  Application Variables **/
// uint64_t totalRx = 0;
// double throughput = 0;
// uint64_t totalRx2 = 0;
// double throughput2 = 0;
// uint8_t beamformedLinks = 0;  
// uint8_t beamformedLinks2 = 0;  
// Ptr<PacketSink> packetSink;
// Ptr<PacketSink> packetSink2;
// Time totalDelay;
// uint64_t pktNum;


string condition_file = "S3"; // S1 S2
string method = EncodeMaxNum == 1  ? "PD_15ms":"NC_15ms"; 
//string seed = "seed15";

int forflie_UserNum = UserNum;
int seedwrite = seed;
string file_des = "./2_rawdata/"+ std::to_string(UserNum) +"/seed"+ std::to_string(seedwrite) + "/"+ condition_file +"/" + method + "/" + std::to_string(BM_enable) + "/";

char D_start = 'F'+(UserNum-1);
string D_start_S (1,D_start) ;
char D_end = 'F'+2*(UserNum-1);
string D_end_S (1,D_end) ;


uint64_t totalRx[UserNum] = {0};
double throughput[UserNum] = {0};
uint8_t beamformedLinks[UserNum] = {0};  
Ptr<PacketSink> packetSink[UserNum];

Time totalDelay[UserNum];
uint64_t pktNum[UserNum];
double thr_temp=0.0;

Ptr<Node> ServerNode;
Ptr<Node> GwNode1; //for encode node
Ptr<Node> GwNode;
Ptr<Node> UserNode[UserNum];

Ptr<Node> apWifiNode;
Ptr<Node> ap2WifiNode;
Ptr<Node> staWifiNode[2*UserNum];


Ptr<WifiNetDevice> apWifiNetDevice;
Ptr<WifiNetDevice> ap2WifiNetDevice;
Ptr<WifiNetDevice> staWifiNetDevice[2*UserNum];


Ptr<DmgApWifiMac> apWifiMac;
Ptr<DmgApWifiMac> ap2WifiMac;
Ptr<DmgStaWifiMac> staWifiMac[2*UserNum];

ApplicationContainer sinkApp[UserNum];
ApplicationContainer srcApp[UserNum];

uint32_t port = 9999;
double simulationTime = condition == 1 ? 10.0 : 4.0;                  /* Simulation time in seconds. */
uint32_t payloadSize = 1400;                  /* Application payload size in bytes. */
string dataRate = "300Mbps";   


/* Access Period Parameters */
uint32_t allocationType = CBAP_ALLOCATION;      /* The type of channel access scheme during DTI (CBAP is the default). */


void
CalculateThroughput (int seq)
{
  double thr = CalculateSingleStreamThroughput (packetSink[seq], totalRx[seq], throughput[seq]);
  if (seq == 0)
  {
    std::cout << std::left << std::setw (10) << Simulator::Now ().GetSeconds ()
              << std::left << std::setw (12) << thr;
    thr_temp += thr;
    ofstream fout;
    fout.open( file_des+"2_overall.csv" ,ios::app);
    fout << Simulator::Now ().GetSeconds () <<  ","  << thr;
    fout.close();
  }
  else if (seq == UserNum-1) // the last user
  {
    std::cout <<std::left << std::setw (12) << thr;
    thr_temp += thr;
    std::cout <<std::left << std::setw (12) << thr_temp; // total thr of users
    ofstream fout;
    fout.open( file_des+"2_overall.csv" ,ios::app);
    fout << "," << thr << "," << thr_temp;
    fout.close();

    thr_temp = 0.0;
  }
  else
  {
    std::cout <<std::left << std::setw (12) << thr;
    thr_temp += thr;

    ofstream fout;
    fout.open( file_des+"2_overall.csv" ,ios::app);
    fout  <<  ","  << thr ;
    fout.close();

  }
  
  Simulator::Schedule (MilliSeconds (100), &CalculateThroughput, seq);
}

static void SetVelocity (Ptr<Node> node, Vector vel)
{
  Ptr<ConstantVelocityMobilityModel> mobility = node->GetObject<ConstantVelocityMobilityModel> ();
  mobility->SetVelocity (vel);
}

void
SectortSweep (Ptr<DmgWifiMac> staWifiMac, Ptr<DmgWifiMac> apwifiMac)
{
  Simulator::ScheduleNow (&DmgWifiMac::Perform_TXSS_TXOP, staWifiMac, apwifiMac->GetAddress ());
  // Simulator::Schedule (MilliSeconds (100),&SectortSweep,wifistaMac,wifiapMac);
}

void
CalculateSnr (Ptr<DmgStaWifiMac> staWifiMac, Ptr<DmgWifiMac> apwifiMac)
{
  float staSNR = staWifiMac->GetSnrTable ();
  if (staSNR > -50)
  {
    std::cout<< std::left << std::setw (10) << staSNR;
    ofstream fout;
    fout.open( file_des+"2_overall.csv" ,ios::app);
    fout  <<  ","  << staSNR ;
    fout.close();
  }
  if (staSNR < 8 && staSNR > -50)  // less than threshold enable sectorSweep
  {
    Simulator::ScheduleNow (&SectortSweep,staWifiMac,apwifiMac);
  }

  Simulator::Schedule (MilliSeconds (100), &CalculateSnr,staWifiMac,apwifiMac);

}

void
CalcNodeDistance(Ptr<Node> node1, Ptr<Node> node2)
{
  Ptr<MobilityModel> model1 = node1->GetObject<MobilityModel>();
  Ptr<MobilityModel> model2 = node2->GetObject<MobilityModel>();
  double distance = model1->GetDistanceFrom (model2);
  double angle = acos(5/distance)*180/PI;
  std::cout << std::left << std::setw (12)  << angle;
    ofstream fout;
    fout.open( file_des+"2_overall.csv" ,ios::app);
    fout  <<  ","  << angle ;
    fout.close();
  Simulator::Schedule (MilliSeconds (100), &CalcNodeDistance, node1 ,node2);
}

void
StationAssoicated (Ptr<DmgStaWifiMac> staWifiMac, Mac48Address address, uint16_t aid)
{
  std::cout << "DMG STA " << staWifiMac->GetAddress () << " associated with DMG AP " << address << std::endl;
  std::cout << "Association ID (AID) = " << aid << std::endl;
  if (allocationType == SERVICE_PERIOD_ALLOCATION)
    {
      std::cout << "Allocate DTI as Service Period" << std::endl;
      apWifiMac->AllocateDTIAsServicePeriod (1, staWifiMac->GetAssociationID (), AID_AP);
    }
}

void
StationAssoicated2 (Ptr<DmgStaWifiMac> staWifiMac, Mac48Address address, uint16_t aid)
{
  std::cout << "DMG STA " << staWifiMac->GetAddress () << " associated with DMG AP " << address << std::endl;
  std::cout << "Association ID (AID) = " << aid << std::endl;
  if (allocationType == SERVICE_PERIOD_ALLOCATION)
    {
      std::cout << "Allocate DTI as Service Period" << std::endl;
      ap2WifiMac->AllocateDTIAsServicePeriod (1, staWifiMac->GetAssociationID (), AID_AP);
    }
}

void
SLSCompleted (Ptr<DmgWifiMac> wifiMac, SlsCompletionAttrbitutes attributes)
{
  if (attributes.accessPeriod == CHANNEL_ACCESS_BHI)
    {
      if (wifiMac == apWifiMac)
        {
          // std::cout << "[1] AP1 completed SLS phase with DMG STA1 ";
          // << apWifiMac->GetAddress () <<" completed SLS phase with DMG STA1 " << attributes.peerStation ;
        }
      else
        {
          // std::cout << "[1] STA1 completed SLS phase with DMG AP1 ";
          // << wifiMac->GetAddress ()<< " completed SLS phase with DMG AP1 " << attributes.peerStation 
        }
      // std::cout << "Best Tx Antenna Configuration: AntennaID=" << uint16_t (attributes.antennaID)
      // std::cout << ", SectorID=" << uint16_t (attributes.sectorID) << std::endl;
    }
  else if (attributes.accessPeriod == CHANNEL_ACCESS_DTI)
    {
      // beamformedLinks[0]++;
      // std::cout << "[1] STA1 completed SLS phase with DMG STA1 " << ", SectorID=" << uint16_t (attributes.sectorID)<< std::endl;
      // std::cout << "The best antenna configuration is AntennaID=" << uint16_t (attributes.antennaID)
                
      // if (beamformedLinks[0] == 2)
        // {
          // apWifiMac->PrintSnrTable ();
          // wifiMac->PrintSnrTable ();
        // }
    }
}

// void
// SLSCompleted2 (Ptr<DmgWifiMac> wifiMac, SlsCompletionAttrbitutes attributes)
// {
//   if (attributes.accessPeriod == CHANNEL_ACCESS_BHI)
//     {
//       if (wifiMac == ap2WifiMac)
//         {
//           // std::cout << "[2] AP2 completed SLS phase with DMG STA2 ";
//         }
//       else
//         {
//           // std::cout << "[2] STA2 completed SLS phase with DMG AP2 ";
//         }
//        // << "Best Tx Antenna Configuration: AntennaID=" << uint16_t (attributes.antennaID)
//        // std::cout << ", SectorID=" << uint16_t (attributes.sectorID) << std::endl;
//     }
//   else if (attributes.accessPeriod == CHANNEL_ACCESS_DTI)
//     {
//       beamformedLinks[1]++;
//       // std::cout << "[2] STA2 completed SLS phase with DMG STA2 " << ", SectorID=" << uint16_t (attributes.sectorID)<< std::endl;
//       if (beamformedLinks[1] == 2)
//         {
//           // ap2WifiMac->PrintSnrTable ();
//           // wifiMac->PrintSnrTable ();
//         }
//     }
// }
int k=2;

void
GetDelay (int value)
{
  // Time totalDelay1 = packetSink->GetAverageDelay();
  long diffdelay = CalculateSingleStreamDelay (packetSink[value], totalDelay[value], pktNum[value]);

  std::cout << std::left << std::setw (10)  << diffdelay;
  ofstream fout;
  fout.open( file_des+"2_overall.csv" ,ios::app);
  fout  <<  ","  << diffdelay ;
  if (value == UserNum-1)
  {
    std::cout << std::endl;
    fout  <<  ",=AVERAGE("<<D_start_S<<k<<":" << D_end_S<<k<<"),";
    fout  << "\n";
    k++;
  }
  fout.close();
  Simulator::Schedule (MilliSeconds (100),&GetDelay,value);
}


void
InstallApplications (Ptr<Node> apNode, Ptr<Node> staNode, Ipv4Address address, uint32_t i)
{
  /* Install Rx */
  PacketSinkHelper sinkHelper ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), port));
  sinkApp[i] = sinkHelper.Install (staNode);
  packetSink[i] = StaticCast<PacketSink> (sinkApp[i].Get (0));
  sinkApp[i].Start (Seconds (0.0));
  sinkApp[i].Stop (Seconds (simulationTime));

  /* Install Tx*/
  OnOffHelper src ("ns3::TcpSocketFactory", InetSocketAddress (address, port));
  src.SetAttribute ("MaxPackets", UintegerValue (0));
  src.SetAttribute ("PacketSize", UintegerValue (payloadSize));
  src.SetAttribute ("OnTime", StringValue ("ns3::ConstantRandomVariable[Constant=1e6]"));
  src.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=0]"));
  src.SetAttribute ("DataRate", DataRateValue (DataRate (dataRate)));
  src.SetAttribute ("EnableTimestamp", BooleanValue(true));  //need this to calculate delay
  srcApp[i] = src.Install (apNode);
  srcApp[i].Start (Seconds (1.4));
  srcApp[i].Stop (Seconds (simulationTime));


 }



int
main (int argc, char *argv[])
{
  // uint32_t payloadSize = 1400;                  /* Application payload size in bytes. */
  // uint32_t payloadSize2 = 1000; 
  // string dataRate = "150Mbps";                  /* Application data rate. */
  // string dataRate2 = "150Mbps";
  // string phyMode = "DMG_MCS12";                 /* Type of the Physical Layer. */
  // double simulationTime = 5.0;                   /* Simulation time in seconds. */
  string msduAggSize = "max";                   /* The maximum aggregation size for A-MSDU in Bytes. */
  string mpduAggSize = "max";                   /* The maximum aggregation size for A-MPDU in Bytes. */
  bool enableRts = false;                       /* Flag to indicate if RTS/CTS handskahre is enabled or disabled. */
  uint32_t rtsThreshold = 0;                    /* RTS/CTS handshare threshold. */
  string queueSize = "4000p";                   /* Wifi MAC Queue Size. */
  string phyMode = "EDMG_OFDM_MCS8";                 /* Type of the Physical Layer. */
  string standard = "ay";                       /* The WiGig standard being utilized (ad/ay). */
  bool verbose = false;                         /* Print Logging Information. */
  bool pcapTracing = false;                     /* PCAP Tracing is enabled. */
  float timeoffset = 0.5;
  bool mac_retx_enable = true; 
  int BM_time = 0;
  uint32_t snapshotLength = std::numeric_limits<uint32_t>::max (); /* The maximum PCAP Snapshot Length. */

  BM_time = BM_enable;
// if (BM_enable)
// {
//   // BM_time = UserNum < 6 ? 2+(UserNum-1)*3 : 15;
//   if (UserNum == 1)
//   {
//     BM_time = 3;
//   }
//   else
//   {
//     BM_time = UserNum < 6 ? 2+(UserNum-1)*3 : 15;
//     // BM_time = 2+(UserNum-1)*3;
//   }
// }
// else
// {
//   BM_time = 500 ;
// }

  ofstream fout;
  // fout.open( "0_AP1_lable.txt" ,std::ios::trunc);
  // fout.close();
  // fout.open( "0_AP2_lable.txt" ,std::ios::trunc);
  // fout.close();
  // fout.open( "0_decodeLabel.txt" ,std::ios::trunc);
  // fout.close();
  // fout.open( "1_RTT.txt" ,std::ios::trunc);
  // fout.close();
  // fout.open( "1_seq.txt" ,std::ios::trunc);
  // fout.close();
  // fout.open( "0_Decode_lable.txt" ,std::ios::trunc);
  // fout.close();
  fout.open( "0_packet_latency.txt" ,std::ios::trunc);
  fout.close();
  fout.open( file_des+"2_overall.csv" ,std::ios::trunc);
  fout.close();

  std::cout << "BM_time = " << BM_time << "\n";

  Config::SetDefault ("ns3::TcpL4Protocol::SocketType", StringValue ("ns3::TcpCubic"));
  // Config::SetDefault ("ns3::TcpL4Protocol::SocketType", StringValue ("ns3::TcpBic"));
  Config::SetDefault ("ns3::TcpSocket::SegmentSize", UintegerValue (payloadSize));
  Config::SetDefault ("ns3::TcpSocket::DelAckCount", UintegerValue (1));
  Config::SetDefault ("ns3::TcpSocket::SndBufSize", UintegerValue (0.45 * 1024 * 1024));//Mbytes
  Config::SetDefault ("ns3::TcpSocket::RcvBufSize", UintegerValue (0.45 * 1024 * 1024));
  Config::SetDefault("ns3::Ipv4GlobalRouting::RandomEcmpRouting",  BooleanValue(true));

  Config::SetDefault ("ns3::WifiMacQueue::MaxDelay", TimeValue (MilliSeconds (BM_time)));

  if (mac_retx_enable)
  {
    Config::SetDefault("ns3::WifiRemoteStationManager::MaxSlrc",  UintegerValue (4));
    Config::SetDefault("ns3::WifiRemoteStationManager::RtsCtsThreshold",  UintegerValue (65536));
  }
  else
  {
    Config::SetDefault("ns3::WifiRemoteStationManager::MaxSlrc",  UintegerValue (0));
    Config::SetDefault("ns3::WifiRemoteStationManager::RtsCtsThreshold",  UintegerValue (1400));
  }

  //  Command line argument parser setup. 
  CommandLine cmd;
  cmd.AddValue ("payloadSize", "Application payload size in bytes", payloadSize);
  cmd.AddValue ("dataRate", "Application data rate", dataRate);
  cmd.AddValue ("msduAggSize", "The maximum aggregation size for A-MSDU in Bytes", msduAggSize);
  cmd.AddValue ("mpduAggSize", "The maximum aggregation size for A-MPDU in Bytes", mpduAggSize);
  cmd.AddValue ("scheme", "The access scheme used for channel access (0: SP allocation, 1: CBAP allocation)", allocationType);
  cmd.AddValue ("enableRts", "Enable or disable RTS/CTS handshake", enableRts);
  cmd.AddValue ("rtsThreshold", "The RTS/CTS threshold value", rtsThreshold);
  cmd.AddValue ("queueSize", "The maximum size of the Wifi MAC Queue", queueSize);
  cmd.AddValue ("phyMode", "The WiGig PHY Mode", phyMode);
  cmd.AddValue ("standard", "The WiGig standard being utilized (ad/ay)", standard);
  cmd.AddValue ("verbose", "Turn on all WifiNetDevice log components", verbose);
  cmd.AddValue ("simulationTime", "Simulation time in seconds", simulationTime);
  cmd.AddValue ("pcap", "Enable PCAP Tracing", pcapTracing);
  cmd.AddValue ("snapshotLength", "The maximum PCAP snapshot length", snapshotLength);
  cmd.Parse (argc, argv);

  /* Validate WiGig standard value */
  WifiPhyStandard wifiStandard = WIFI_PHY_STANDARD_80211ad;
  if (standard == "ad")
    {
      wifiStandard = WIFI_PHY_STANDARD_80211ad;
    }
  else if (standard == "ay")
    {
      wifiStandard = WIFI_PHY_STANDARD_80211ay;
    }
  else
    {
      NS_FATAL_ERROR ("Wrong WiGig standard");
    }
  /* Validate A-MSDU and A-MPDU values */
  ValidateFrameAggregationAttributes (msduAggSize, mpduAggSize, wifiStandard);
  /* Configure RTS/CTS and Fragmentation */
  ConfigureRtsCtsAndFragmenatation (enableRts, rtsThreshold);
  /* Wifi MAC Queue Parameters */
  ChangeQueueSize (queueSize);

  /**** WifiHelper is a meta-helper: it helps creates helpers ****/
  DmgWifiHelper wifi;
  wifi.SetStandard (wifiStandard);

  /* Turn on logging */
  if (verbose)
    {
      wifi.EnableLogComponents ();
      LogComponentEnable ("CompareAccessSchemes", LOG_LEVEL_ALL);
    }

  /**** Set up Channel ****/
  DmgWifiChannelHelper wifiChannel ;
  /* Simple propagation delay model */
  wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
  // /* Friis model with standard-specific wavelength */
  wifiChannel.AddPropagationLoss ("ns3::FriisPropagationLossModel", "Frequency", DoubleValue (60.48e9));
  // wifiChannel.AddPropagationLoss ("ns3::FriisPropagationLossModel", "Frequency", DoubleValue (5e9));
  DmgWifiChannelHelper wifiChannel2 ;
  /* Simple propagation delay model */
  wifiChannel2.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
  // /* Friis model with standard-specific wavelength */
  wifiChannel2.AddPropagationLoss ("ns3::FriisPropagationLossModel", "Frequency", DoubleValue (60.48e9));
  // wifiChannel.AddPropagationLoss ("ns3::FriisPropagationLossModel", "Frequency", DoubleValue (5e9));

  /**** Setup physical layer ****/
  DmgWifiPhyHelper wifiPhy = DmgWifiPhyHelper::Default ();
  DmgWifiPhyHelper wifiPhy2 = DmgWifiPhyHelper::Default ();


  /* Nodes will be added to the channel we set up earlier */
  wifiPhy.SetChannel (wifiChannel.Create ());
  /* All nodes transmit at 10 dBm == 10 mW, no adaptation */
  wifiPhy.Set ("TxPowerStart", DoubleValue (10.0));
  wifiPhy.Set ("TxPowerEnd", DoubleValue (10.0));
  wifiPhy.Set ("TxPowerLevels", UintegerValue (1));
  /* Set operating channel */
  wifiPhy.Set ("ChannelNumber", UintegerValue (2));
  /* Add support for the OFDM PHY */
  wifiPhy.Set ("SupportOfdmPhy", BooleanValue (true));

  wifiPhy2.SetChannel (wifiChannel2.Create ());
  /* All nodes transmit at 10 dBm == 10 mW, no adaptation */
  wifiPhy2.Set ("TxPowerStart", DoubleValue (10.0));
  wifiPhy2.Set ("TxPowerEnd", DoubleValue (10.0));
  wifiPhy2.Set ("TxPowerLevels", UintegerValue (1));
  /* Set operating channel */
  wifiPhy2.Set ("ChannelNumber", UintegerValue (2));
  /* Add support for the OFDM PHY */
  wifiPhy2.Set ("SupportOfdmPhy", BooleanValue (true));


  if (standard == "ay")
    {
      /* Set the correct error model */
      wifiPhy.SetErrorRateModel ("ns3::DmgErrorModel",
                                 "FileName", StringValue ("WigigFiles/ErrorModel/LookupTable_1458_ay.txt"));
      wifiPhy2.SetErrorRateModel ("ns3::DmgErrorModel",
                                 "FileName", StringValue ("WigigFiles/ErrorModel/LookupTable_1458_ay.txt"));
    }
  /* Set default algorithm for all nodes to be constant rate */
  wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager", "DataMode", StringValue (phyMode));

  /* Make two nodes and set them up with the PHY and the MAC */
  NodeContainer p2pSvNode;
  p2pSvNode.Create(1);
  ServerNode = p2pSvNode.Get(0);  //NowNodeID = 0

  NodeContainer p2pGwNode;
  p2pGwNode.Create(2);
  GwNode1 = p2pGwNode.Get (0);   //NowNodeID = 1
  GwNode = p2pGwNode.Get (1);    //NowNodeID = 2

  NodeContainer wifiApNode;
  wifiApNode.Create (2);
  apWifiNode = wifiApNode.Get (0);  //NowNodeID = 3
  ap2WifiNode = wifiApNode.Get (1); //NowNodeID = 4

  NodeContainer wifiStaNode;
  wifiStaNode.Create (2*UserNum);
  for (int a=0; a<2*UserNum; a++)
  {staWifiNode[a] = wifiStaNode.Get (a);}
  // staWifiNode[0] = wifiStaNode.Get (0);  //NowNodeID = 5
  // staWifiNode[1] = wifiStaNode.Get (1); //NowNodeID = 6
  // staWifiNode[2] = wifiStaNode.Get (2);  //NowNodeID = 7
  // staWifiNode[3] = wifiStaNode.Get (3); //NowNodeID = 8

  NodeContainer p2pEndNode;
  p2pEndNode.Create(UserNum);
  for (int a=0; a<UserNum; a++)
  {UserNode[a] = p2pEndNode.Get (a);}
  // UserNode[0] = p2pEndNode.Get(0);   //NowNodeID = 9
  // UserNode[1] = p2pEndNode.Get(1);   //NowNodeID = 10

  NodeContainer n0n1 = NodeContainer(ServerNode, GwNode1);
  NodeContainer n1n1 = NodeContainer(GwNode1, GwNode);
  NodeContainer n1n2 = NodeContainer(GwNode, apWifiNode);
  NodeContainer n1n3 = NodeContainer(GwNode, ap2WifiNode);
  // NodeContainer freeway = NodeContainer(UserNode[0], ServerNode);
  // NodeContainer n4n6 = NodeContainer(staWifiNode[0], UserNode[0]);
  // NodeContainer n5n6 = NodeContainer(staWifiNode[1], UserNode[0]);
  // NodeContainer n7n10 = NodeContainer(staWifiNode[2], UserNode[1]);
  // NodeContainer n8n10 = NodeContainer(staWifiNode[3], UserNode[1]);

  NodeContainer NodeToNode[2*UserNum];
  for (int a=0; a<2*UserNum; a++)
  {NodeToNode[a] = NodeContainer(staWifiNode[a], UserNode[a/2]);}



  PointToPointHelper p2pHelper;
  // p2pHelper.SetDeviceAttribute ("DataRate", DatarateValue ("10Gbps"));
  p2pHelper.SetDeviceAttribute ("DataRate", DataRateValue (DataRate ("1Gb/s")));
  p2pHelper.SetChannelAttribute ("Delay", TimeValue (Seconds(0.005)));
  p2pHelper.SetQueue("ns3::DropTailQueue",  "MaxSize",QueueSizeValue(QueueSize ("4294967295p")));
  /* Create p2p Network Devices (P2PNetDevice) */
  // NetDeviceContainer s0s1 = p2pHelper.Install (n0n1);
  // NetDeviceContainer s2ap2 = p2pHelper.Install (n1n3);

  PointToPointHelper p2pHelper2;
  p2pHelper2.SetDeviceAttribute ("DataRate", DataRateValue (DataRate ("5Gb/s")));
  p2pHelper2.SetChannelAttribute ("Delay", TimeValue (Seconds(0.000)));
  p2pHelper2.SetQueue("ns3::DropTailQueue",  "MaxSize",QueueSizeValue(QueueSize ("4294967295p")));
  /* Create p2p Network Devices (P2PNetDevice) */
  NetDeviceContainer g1g1 = p2pHelper2.Install (n1n1);


  PointToPointHelper p2pHelper3;
  // p2pHelper.SetDeviceAttribute ("DataRate", DatarateValue ("10Gbps"));
  p2pHelper3.SetDeviceAttribute ("DataRate", DataRateValue (DataRate ("5Gb/s")));
  p2pHelper3.SetChannelAttribute ("Delay", TimeValue (Seconds(0.004)));
  p2pHelper3.SetQueue("ns3::DropTailQueue",  "MaxSize",QueueSizeValue(QueueSize ("4294967295p")));
  /* Create p2p Network Devices (P2PNetDevice) */
  NetDeviceContainer s0s1 = p2pHelper3.Install (n0n1);

  PointToPointHelper p2pHelper4;
  // p2pHelper.SetDeviceAttribute ("DataRate", DatarateValue ("10Gbps"));
  p2pHelper4.SetDeviceAttribute ("DataRate", DataRateValue (DataRate ("5Gb/s")));
  p2pHelper4.SetChannelAttribute ("Delay", TimeValue (Seconds(0.001)));
  p2pHelper4.SetQueue("ns3::DropTailQueue",  "MaxSize",QueueSizeValue(QueueSize ("4294967295p")));
  /* Create p2p Network Devices (P2PNetDevice) */
  NetDeviceContainer s2ap1 = p2pHelper4.Install (n1n2);
  NetDeviceContainer s2ap2 = p2pHelper4.Install (n1n3);



  NetDeviceContainer s1e[2*UserNum];

  for (int a=0; a<2*UserNum; a++)
  {
    s1e[a] = p2pHelper2.Install (NodeToNode[a]);
  }
  // NetDeviceContainer s1e = p2pHelper2.Install (n4n6);
  // NetDeviceContainer s2e = p2pHelper2.Install (n5n6);
  // NetDeviceContainer s3e = p2pHelper2.Install (n7n10);
  // NetDeviceContainer s4e = p2pHelper2.Install (n8n10);
  // NetDeviceContainer gEgE = p2pHelper2.Install (nEnE);

  // PointToPointHelper p2pHelper3;
  // p2pHelper3.SetDeviceAttribute ("DataRate", DataRateValue (DataRate ("10Gb/s")));
  // p2pHelper3.SetChannelAttribute ("Delay", TimeValue (Seconds(0.000)));
  // p2pHelper3.SetQueue("ns3::DropTailQueue",  "MaxSize",QueueSizeValue(QueueSize ("4294967295p")));
  // p2pHelper3.SetQueue("ns3::DropTailQueue",  "MaxPackets",UintegerValue(100000000));


  /* Add a DMG upper mac */
  DmgWifiMacHelper wifiMac = DmgWifiMacHelper::Default ();
  DmgWifiMacHelper wifiMac2 = DmgWifiMacHelper::Default ();

  Ssid ssid = Ssid ("Compare");
  wifiMac.SetType ("ns3::DmgApWifiMac",
                   "Ssid", SsidValue(ssid),
                   "BE_MaxAmpduSize", StringValue (mpduAggSize),
                   "BE_MaxAmsduSize", StringValue (msduAggSize),
                   "SSSlotsPerABFT", UintegerValue (8), "SSFramesPerSlot", UintegerValue (8),
                   "BeaconInterval", TimeValue (MicroSeconds (102400)),
                   "EDMGSupported", BooleanValue ((standard == "ay")));

  /* Set Analytical Codebook for the DMG Devices */
  wifi.SetCodebook ("ns3::CodebookAnalytical",
                    "CodebookType", EnumValue (SIMPLE_CODEBOOK),
                    "Antennas", UintegerValue (1),
                    "Sectors", UintegerValue (8));

  /* Create Wifi Network Devices (WifiNetDevice) */
  NetDeviceContainer apDevice;
  apDevice = wifi.Install (wifiPhy, wifiMac, apWifiNode);

  wifiMac.SetType ("ns3::DmgStaWifiMac",
                   "Ssid", SsidValue (ssid), "ActiveProbing", BooleanValue (false),
                   "BE_MaxAmpduSize", StringValue (mpduAggSize),
                   "BE_MaxAmsduSize", StringValue (msduAggSize),
                   "EDMGSupported", BooleanValue ((standard == "ay")));
  NetDeviceContainer staDevice[2*UserNum];
  for (int a=0; a<UserNum; a++)
  {staDevice[2*a] = wifi.Install (wifiPhy, wifiMac, staWifiNode[2*a]);}
  // staDevice[0] = wifi.Install (wifiPhy, wifiMac, staWifiNode[0]);
  // staDevice[2] = wifi.Install (wifiPhy, wifiMac, staWifiNode[2]);


  Ssid ssid2 = Ssid ("Compare2");
  wifiMac2.SetType ("ns3::DmgApWifiMac",
                   "Ssid", SsidValue(ssid2),
                   "BE_MaxAmpduSize", StringValue (mpduAggSize),
                   "BE_MaxAmsduSize", StringValue (msduAggSize),
                   "SSSlotsPerABFT", UintegerValue (8), "SSFramesPerSlot", UintegerValue (8),
                   "BeaconInterval", TimeValue (MicroSeconds (102400)),
                   "EDMGSupported", BooleanValue ((standard == "ay")));

  /* Set Analytical Codebook for the DMG Devices */
  wifi.SetCodebook ("ns3::CodebookAnalytical",
                    "CodebookType", EnumValue (SIMPLE_CODEBOOK),
                    "Antennas", UintegerValue (1),
                    "Sectors", UintegerValue (8));

  /* Create Wifi Network Devices (WifiNetDevice) */
  NetDeviceContainer ap2Device;
  ap2Device = wifi.Install (wifiPhy2, wifiMac2, ap2WifiNode);

  wifiMac2.SetType ("ns3::DmgStaWifiMac",
                   "Ssid", SsidValue (ssid2), "ActiveProbing", BooleanValue (false),
                   "BE_MaxAmpduSize", StringValue (mpduAggSize),
                   "BE_MaxAmsduSize", StringValue (msduAggSize),
                   "EDMGSupported", BooleanValue ((standard == "ay")));
  for (int a=0; a<UserNum; a++)
  {staDevice[2*a+1] = wifi.Install (wifiPhy2, wifiMac2, staWifiNode[2*a+1]);}
  // staDevice[1] = wifi.Install (wifiPhy2, wifiMac2, staWifiNode[1]);
  // staDevice[3] = wifi.Install (wifiPhy2, wifiMac2, staWifiNode[3]);

//============================================================================


  /* Setting mobility model */
  MobilityHelper mobility;
  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
if (condition ==2)
  {
    positionAlloc->Add (Vector (0.0, 10.0, 0.0));  //p2pSvNode
    positionAlloc->Add (Vector (0.0 , 9.0, 0.0));  //p2pGw1Node
    positionAlloc->Add (Vector (0.0 , 9.0, 0.0));  //p2pGwNode
    positionAlloc->Add (Vector (0.0, 5.0, 0.0));   // PCP/AP 
    positionAlloc->Add (Vector (2.0 , 5.0, 0.0));  // PCP/AP_2

    positionAlloc->Add (Vector (-5.0 , 0.0, 0.0));  // DMG STA_1 
    positionAlloc->Add (Vector (-5.0 , 0.0, 0.0));  // DMG STA_2 
    positionAlloc->Add (Vector (-5.0 , 0.0, 0.0));  // DMG STA_3

    positionAlloc->Add (Vector (-5.0 , 0.0, 0.0));  // DMG STA_4 
    positionAlloc->Add (Vector (-5.0 , 0.0, 0.0));  // DMG STA_5
    positionAlloc->Add (Vector (-5.0 , 0.0, 0.0));  // DMG STA_6 

    positionAlloc->Add (Vector (-5.0 , 0.0, 0.0));  //p2pEndNode
    positionAlloc->Add (Vector (-5.0, 0.0, 0.0));  //p2pEndNode2
    positionAlloc->Add (Vector (-5.0, 0.0, 0.0));  //p2pEndNode3

    positionAlloc->Add (Vector (-5.0, 0.0, 0.0));  //p2pEndNode
    positionAlloc->Add (Vector (-5.0 , 0.0, 0.0));  //p2pEndNode2
    positionAlloc->Add (Vector (-5.0 , 0.0, 0.0));  //p2pEndNode3

    positionAlloc->Add (Vector (-5.0 , 0.0, 0.0));  //p2pEndNode
    positionAlloc->Add (Vector (-5.0 , 0.0, 0.0));  //p2pEndNode2
    positionAlloc->Add (Vector (-5.0 , 0.0, 0.0));  //p2pEndNode3

    positionAlloc->Add (Vector (-5.0 , 0.0, 0.0));  //p2pEndNode
    positionAlloc->Add (Vector (-5.0 , 0.0, 0.0));  //p2pEndNode2
    positionAlloc->Add (Vector (-5.0 , 0.0, 0.0));  //p2pEndNode3

    positionAlloc->Add (Vector (-5.0 , 0.0, 0.0));  //p2pEndNode
    positionAlloc->Add (Vector (-5.0, 0.0, 0.0));  //p2pEndNode2
    positionAlloc->Add (Vector (-5.0, 0.0, 0.0));  //p2pEndNode3

    positionAlloc->Add (Vector (-5.0 , 0.0, 0.0));  //p2pEndNode
    positionAlloc->Add (Vector (-5.0 , 0.0, 0.0));  //p2pEndNode2
    positionAlloc->Add (Vector (-5.0 , 0.0, 0.0));  //p2pEndNode3
  }
  else if (condition)
  {
    positionAlloc->Add (Vector (0.0, 10.0, 0.0));  //p2pSvNode
    positionAlloc->Add (Vector (0.0 , 9.0, 0.0));  //p2pGw1Node
    positionAlloc->Add (Vector (0.0 , 9.0, 0.0));  //p2pGwNode
    positionAlloc->Add (Vector (0.0, 5.0, 0.0));   // PCP/AP 
    positionAlloc->Add (Vector (2.0 , 5.0, 0.0));  // PCP/AP_2

    positionAlloc->Add (Vector (-3.7 , 0.0, 0.0));  // DMG STA_1 
    positionAlloc->Add (Vector (-3.7, 0.0, 0.0));  // DMG STA_2 
    positionAlloc->Add (Vector (-3.7 , 0.0, 0.0));  // DMG STA_3

    positionAlloc->Add (Vector (-3.7 , 0.0, 0.0));  // DMG STA_4 
    positionAlloc->Add (Vector (-3.7 , 0.0, 0.0));  // DMG STA_5
    positionAlloc->Add (Vector (-3.7 , 0.0, 0.0));  // DMG STA_6 

    positionAlloc->Add (Vector (-3.7, 0.0, 0.0));  //p2pEndNode
    positionAlloc->Add (Vector (-3.7, 0.0, 0.0));  //p2pEndNode2
    positionAlloc->Add (Vector (-3.7, 0.0, 0.0));  //p2pEndNode3

    positionAlloc->Add (Vector (-3.7, 0.0, 0.0));  //p2pEndNode
    positionAlloc->Add (Vector (-3.7, 0.0, 0.0));  //p2pEndNode2
    positionAlloc->Add (Vector (-3.7, 0.0, 0.0));  //p2pEndNode3

     positionAlloc->Add (Vector (-3.7, 0.0, 0.0));  //p2pEndNode
    positionAlloc->Add (Vector (-3.7, 0.0, 0.0));  //p2pEndNode2
    positionAlloc->Add (Vector (-3.7, 0.0, 0.0));  //p2pEndNode3
    positionAlloc->Add (Vector (-3.7, 0.0, 0.0));  //p2pEndNode
    positionAlloc->Add (Vector (-3.7, 0.0, 0.0));  //p2pEndNode2
    positionAlloc->Add (Vector (-3.7, 0.0, 0.0));  //p2pEndNode3

    positionAlloc->Add (Vector (-3.7, 0.0, 0.0));  //p2pEndNode
    positionAlloc->Add (Vector (-3.7, 0.0, 0.0));  //p2pEndNode2
    positionAlloc->Add (Vector (-3.7, 0.0, 0.0));  //p2pEndNode3

    positionAlloc->Add (Vector (-3.7, 0.0, 0.0));  //p2pEndNode
    positionAlloc->Add (Vector (-3.7, 0.0, 0.0));  //p2pEndNode2
    positionAlloc->Add (Vector (-3.7, 0.0, 0.0));  //p2pEndNode3
  }

  mobility.SetPositionAllocator (positionAlloc);
  mobility.SetMobilityModel ("ns3::ConstantVelocityMobilityModel");
  mobility.Install (p2pSvNode);
  mobility.Install (p2pGwNode);
  mobility.Install (wifiApNode);
  mobility.Install (wifiStaNode);
  mobility.Install (p2pEndNode);

  /* Internet stack*/
  InternetStackHelper stack;
  stack.Install (p2pSvNode);
  stack.Install (p2pGwNode);
  stack.Install (wifiApNode);
  stack.Install (wifiStaNode);
  stack.Install (p2pEndNode);


  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer i0i1 = address.Assign (s0s1);

  address.SetBase ("10.1.10.0", "255.255.255.0");
  Ipv4InterfaceContainer iGg = address.Assign (g1g1);


  address.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer iGap = address.Assign (s2ap1);
  address.Assign (s2ap2);
  // Ipv4InterfaceContainer iuserver = address.Assign (userver1);

  address.SetBase ("10.1.3.0", "255.255.255.0");
  Ipv4InterfaceContainer apInterface = address.Assign (apDevice);
  Ipv4InterfaceContainer staInterface[2*UserNum];
  for (int a=0; a<UserNum; a++)
  {staInterface[2*a] = address.Assign (staDevice[2*a]);}
  // staInterface[0] = address.Assign (staDevice[0]);
  // staInterface[2] = address.Assign (staDevice[2]);

  address.SetBase ("10.1.5.0", "255.255.255.0");
  Ipv4InterfaceContainer ap2Interface = address.Assign (ap2Device);
  for (int a=0; a<UserNum; a++)
  {staInterface[2*a+1] = address.Assign (staDevice[2*a+1]);}
  // staInterface[1] = address.Assign (staDevice[1]);
  // staInterface[3] = address.Assign (staDevice[3]);

  address.SetBase ("10.1.4.0", "255.255.255.0");
  Ipv4InterfaceContainer is1e[2*UserNum];
  for (int a=0; a<2*UserNum; a++)
  {
    is1e[a] = address.Assign (s1e[a]);
  }

    /* Populate routing table */
    Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
    /* We do not want any ARP packets */
    PopulateArpCache ();

    // ====================================================
    NodeContainer bypass[UserNum];
    NetDeviceContainer Netbypass[UserNum];
    Ipv4InterfaceContainer ibypass[UserNum];
    address.SetBase ("10.1.6.0", "255.255.255.0");
    for (int a=0; a<UserNum; a++)
    {
      bypass[a] = NodeContainer(ServerNode,UserNode[a]);
      Netbypass[a] = p2pHelper.Install (bypass[a]); // 5ms latency
      ibypass[a] = address.Assign (Netbypass[a]);
    }
    // NodeContainer nEnE1 = NodeContainer(ServerNode,UserNode[0]);
    // NodeContainer nEnE2 = NodeContainer(ServerNode,UserNode[1]);
    // NetDeviceContainer userver1 = p2pHelper.Install (nEnE1);
    // NetDeviceContainer userver2 = p2pHelper.Install (nEnE2);

    // address.SetBase ("10.1.6.0", "255.255.255.0");
    // Ipv4InterfaceContainer iuserver = address.Assign (userver1);
    // address.Assign (userver2);

    Ptr<SimpleNetDevice> deviceA = CreateObject<SimpleNetDevice> ();
    deviceA->SetAddress (Mac48Address::Allocate ());
    ServerNode->AddDevice (deviceA);
    Ptr<Ipv4> ipv4A = ServerNode->GetObject<Ipv4> ();
    uint32_t ifIndexA = ipv4A->AddInterface (deviceA);
    Ipv4InterfaceAddress ifInAddrA = Ipv4InterfaceAddress (Ipv4Address ("10.1.1.0"), Ipv4Mask ("255.255.255.0"));
    ipv4A->AddAddress (ifIndexA, ifInAddrA);
    ipv4A->SetMetric (ifIndexA, 1);
    ipv4A->SetUp (ifIndexA);
    Ipv4StaticRoutingHelper ipv4RoutingHelper;
    Ptr<Ipv4StaticRouting> staticRoutingA = ipv4RoutingHelper.GetStaticRouting (ipv4A);
    // staticRoutingA->AddHostRouteTo (Ipv4Address ("10.1.4.4"),1);
    // staticRoutingA->AddHostRouteTo (Ipv4Address ("10.1.4.8"),1);

    for (int a = 0; a < UserNum; a++)
    {
      staticRoutingA->AddHostRouteTo (is1e[2*a+1].GetAddress (1),1);
    }


    // Ptr<SimpleNetDevice> deviceB = CreateObject<SimpleNetDevice> ();
    // deviceB->SetAddress (Mac48Address::Allocate ());
    // UserNode[0]->AddDevice (deviceB);
    // Ptr<Ipv4> ipv4B = UserNode[0]->GetObject<Ipv4> ();
    // uint32_t ifIndexB = ipv4B->AddInterface (deviceB);
    // Ipv4InterfaceAddress ifInAddrB = Ipv4InterfaceAddress (Ipv4Address ("10.1.4.0"), Ipv4Mask ("255.255.255.0"));
    // ipv4B->AddAddress (ifIndexB, ifInAddrB);
    // ipv4B->SetMetric (ifIndexB, 1);
    // ipv4B->SetUp (ifIndexB);
    // Ipv4StaticRoutingHelper ipv4RoutingHelper1;
    // Ptr<Ipv4StaticRouting> staticRoutingB = ipv4RoutingHelper1.GetStaticRouting (ipv4B);
    // staticRoutingB->AddHostRouteTo (Ipv4Address ("10.1.1.1"),3);


    // Ptr<SimpleNetDevice> deviceC = CreateObject<SimpleNetDevice> ();
    // deviceC->SetAddress (Mac48Address::Allocate ());
    // UserNode[1]->AddDevice (deviceC);
    // Ptr<Ipv4> ipv4C = UserNode[1]->GetObject<Ipv4> ();
    // uint32_t ifIndexC = ipv4C->AddInterface (deviceC);
    // Ipv4InterfaceAddress ifInAddrC = Ipv4InterfaceAddress (Ipv4Address ("10.1.4.0"), Ipv4Mask ("255.255.255.0"));
    // ipv4C->AddAddress (ifIndexC, ifInAddrC);
    // ipv4C->SetMetric (ifIndexC, 1);
    // ipv4C->SetUp (ifIndexC);
    // Ipv4StaticRoutingHelper ipv4RoutingHelper2;
    // Ptr<Ipv4StaticRouting> staticRoutingC = ipv4RoutingHelper2.GetStaticRouting (ipv4C);
    // staticRoutingC->AddHostRouteTo (Ipv4Address ("10.1.1.1"),3);



    Ptr<SimpleNetDevice> device[UserNum];
    Ptr<Ipv4> ipv4[UserNum];
    int32_t ifIndex[UserNum];
    Ipv4InterfaceAddress ifInAddr[UserNum];
    Ipv4StaticRoutingHelper ipv4RoutingHelper1[UserNum];
    Ptr<Ipv4StaticRouting> staticRouting[UserNum];

    for (int a=0; a<UserNum; a++)
    {
      device[a] = CreateObject<SimpleNetDevice> ();
      device[a]->SetAddress (Mac48Address::Allocate ());
      UserNode[a]->AddDevice (device[a]);
      ipv4[a] = UserNode[a]->GetObject<Ipv4> ();
      ifIndex[a] = ipv4[a]->AddInterface (device[a]);

      ifInAddr[a] = Ipv4InterfaceAddress (Ipv4Address ("10.1.4.0"), Ipv4Mask ("255.255.255.0"));
      ipv4[a]->AddAddress (ifIndex[a], ifInAddr[a]);
      ipv4[a]->SetMetric (ifIndex[a], 1);
      ipv4[a]->SetUp (ifIndex[a]);
      staticRouting[a] = ipv4RoutingHelper1[a].GetStaticRouting (ipv4[a]);
      staticRouting[a]->AddHostRouteTo (Ipv4Address ("10.1.1.1"),3);
    }
  // ====================================================






 for (uint32_t i = 0; i < UserNum; i++)
  {
    InstallApplications (ServerNode, UserNode[i], is1e[2*i+1].GetAddress (1), i);
    // InstallApplications (ServerNode, GwNode1, iGg.GetAddress (0), i);
    port-=1;
  }

  /* Print Traces */
  if (pcapTracing)
    {
      wifiPhy.SetPcapDataLinkType (YansWifiPhyHelper::DLT_IEEE802_11_RADIO);
      wifiPhy.EnablePcap ("Traces/AccessPoint", apDevice, false);
      wifiPhy.EnablePcap ("Traces/Station", staDevice[0], false);
    }

  /* Stations */
  apWifiNetDevice = StaticCast<WifiNetDevice> (apDevice.Get (0));
  apWifiMac = StaticCast<DmgApWifiMac> (apWifiNetDevice->GetMac ());
  ap2WifiNetDevice = StaticCast<WifiNetDevice> (ap2Device.Get (0));
  ap2WifiMac = StaticCast<DmgApWifiMac> (ap2WifiNetDevice->GetMac ());

  for (int a=0;a<2*UserNum;a++)
  {
    staWifiNetDevice[a] = StaticCast<WifiNetDevice> (staDevice[a].Get (0));
    staWifiMac[a] = StaticCast<DmgStaWifiMac> (staWifiNetDevice[a]->GetMac ());
    staWifiMac[a]->TraceConnectWithoutContext ("Assoc", MakeBoundCallback (&StationAssoicated, staWifiMac[a]));
    staWifiMac[a]->TraceConnectWithoutContext ("SLSCompleted", MakeBoundCallback (&SLSCompleted, staWifiMac[a]));
  }

  // staWifiNetDevice[0] = StaticCast<WifiNetDevice> (staDevice[0].Get (0));
  // staWifiMac[0] = StaticCast<DmgStaWifiMac> (staWifiNetDevice[0]->GetMac ());
  // staWifiNetDevice[1] = StaticCast<WifiNetDevice> (staDevice[1].Get (0));
  // staWifiMac[1] = StaticCast<DmgStaWifiMac> (staWifiNetDevice[1]->GetMac ());
  // staWifiNetDevice[2] = StaticCast<WifiNetDevice> (staDevice[2].Get (0));
  // staWifiMac[2] = StaticCast<DmgStaWifiMac> (staWifiNetDevice[2]->GetMac ());
  // staWifiNetDevice[3] = StaticCast<WifiNetDevice> (staDevice[3].Get (0));
  // staWifiMac[3] = StaticCast<DmgStaWifiMac> (staWifiNetDevice[3]->GetMac ());

  // /* Connect Traces */
  // staWifiMac[0]->TraceConnectWithoutContext ("Assoc", MakeBoundCallback (&StationAssoicated, staWifiMac[0]));
  // staWifiMac[0]->TraceConnectWithoutContext ("SLSCompleted", MakeBoundCallback (&SLSCompleted, staWifiMac[0]));
  // staWifiMac[1]->TraceConnectWithoutContext ("Assoc", MakeBoundCallback (&StationAssoicated2, staWifiMac[1]));
  // staWifiMac[1]->TraceConnectWithoutContext ("SLSCompleted", MakeBoundCallback (&SLSCompleted2, staWifiMac[1]));

  // staWifiMac[2]->TraceConnectWithoutContext ("Assoc", MakeBoundCallback (&StationAssoicated, staWifiMac[2]));
  // staWifiMac[2]->TraceConnectWithoutContext ("SLSCompleted", MakeBoundCallback (&SLSCompleted, staWifiMac[2]));
  // staWifiMac[3]->TraceConnectWithoutContext ("Assoc", MakeBoundCallback (&StationAssoicated2, staWifiMac[3]));
  // staWifiMac[3]->TraceConnectWithoutContext ("SLSCompleted", MakeBoundCallback (&SLSCompleted2, staWifiMac[3]));



  // apWifiMac->TraceConnectWithoutContext ("SLSCompleted", MakeBoundCallback (&SLSCompleted, apWifiMac));
  // ap2WifiMac->TraceConnectWithoutContext ("SLSCompleted", MakeBoundCallback (&SLSCompleted2, ap2WifiMac));

  /* Print Output*/
  std::cout << std::left << std::setw (12) << "Time [s]"
            << std::left << std::setw (18) << "Throughput [Mbps]" 
            << std::left << std::setw (15) << "STA1-SNR(dB)" 
            << std::left << std::setw (15) << "STA2-SNR(dB)" 
            // << std::left << std::setw (12) << "Angle"
            << std::left << std::setw (12) << "Delay(µs)"  << std::endl;

    // ofstream fout;
    fout.open( file_des+"2_overall.csv" ,ios::app);
    fout  << "Time [s],";
          for(int i=1;i<UserNum+1;i++ )
          {
            fout<< "User" << i << "_Tput(Mbps),";
          }
          fout<< "Total_Tput(Mbps),";
          fout << "STA1-SNR(dB)," ;
          fout << "STA2-SNR(dB)," ;
          for(int i=1;i<UserNum+1;i++ )
          {
            fout<< "User" << i << "_latency(µs),";
          }
          fout<< "Avg_latency(µs),";
          fout << "\n";

    fout.close();

  /* Schedule Throughput Calulcations */
  for (int a=0;a<UserNum;a++)
  {
    Simulator::Schedule (Seconds (1.4), &CalculateThroughput,a);
  }
  for (int a=0;a<1;a++) //UserNum
  {
    Simulator::Schedule (Seconds (1.4), &CalculateSnr,staWifiMac[2*a], apWifiMac);
    Simulator::Schedule (Seconds (1.4), &CalculateSnr,staWifiMac[2*a+1], ap2WifiMac);
  }

  // Simulator::Schedule (Seconds (1.4), &CalcNodeDistance,apWifiNode,staWifiNode[0]);

  for (int a=0;a<UserNum;a++)
  {
    Simulator::Schedule (Seconds (1.4), &GetDelay,a);
  }
  for (int a=0;a<UserNum;a++)
  {
    Simulator::Schedule (Seconds (1.38), &SectortSweep, staWifiMac[2*a], apWifiMac);
    Simulator::Schedule (Seconds (1.38), &SectortSweep, staWifiMac[2*a+1], ap2WifiMac);
  }


  
  //===============================================

  /* Schedule User Walking */
  if (UserNum > 1)
  {
    for (int a=2;a<2*UserNum;a++)
    {
      Simulator::Schedule (Seconds (1.4+timeoffset), &SetVelocity, staWifiNode[a] ,Vector(0.0 ,0.0,0.0));
    }
  }


 
  if (condition == 2)
  {  
    Simulator::Schedule (Seconds (1.4+timeoffset), &SetVelocity, staWifiNode[0] ,Vector(5.0 ,0.0,0.0));
    Simulator::Schedule (Seconds (1.4+timeoffset), &SetVelocity, staWifiNode[1] ,Vector(5.0 ,0.0,0.0));

    Simulator::Schedule (Seconds (1.8+timeoffset), &SetVelocity, staWifiNode[0] ,Vector(6.0 ,0.0,0.0)); //arr
    Simulator::Schedule (Seconds (1.8+timeoffset), &SetVelocity, staWifiNode[1] ,Vector(6.0 ,0.0,0.0));

    Simulator::Schedule (Seconds (1.9+timeoffset), &SetVelocity, staWifiNode[0] ,Vector(17.0 ,0.0,0.0)); //Sector Switch time 1_0.85
    Simulator::Schedule (Seconds (1.9+timeoffset), &SetVelocity, staWifiNode[1] ,Vector(17.0 ,0.0,0.0));
    Simulator::Schedule (Seconds (1.95+timeoffset), &SetVelocity, staWifiNode[0] ,Vector(0.0 ,0.0,0.0)); 
    Simulator::Schedule (Seconds (1.95+timeoffset), &SetVelocity, staWifiNode[1] ,Vector(0.0 ,0.0,0.0));

    Simulator::Schedule (Seconds (2.0+timeoffset), &SetVelocity, staWifiNode[0] ,Vector(15.0 ,0.0,0.0));//arr
    Simulator::Schedule (Seconds (2.0+timeoffset), &SetVelocity, staWifiNode[1] ,Vector(15.0 ,0.0,0.0));

    Simulator::Schedule (Seconds (2.1+timeoffset), &SetVelocity, staWifiNode[0] ,Vector(10.0 ,0.0,0.0)); //Sector Switch time 2_0.5
    Simulator::Schedule (Seconds (2.1+timeoffset), &SetVelocity, staWifiNode[1] ,Vector(10.0 ,0.0,0.0));
    Simulator::Schedule (Seconds (2.15+timeoffset), &SetVelocity, staWifiNode[0] ,Vector(0.0 ,0.0,0.0)); 
    Simulator::Schedule (Seconds (2.15+timeoffset), &SetVelocity, staWifiNode[1] ,Vector(0.0 ,0.0,0.0));

    Simulator::Schedule (Seconds (2.2+timeoffset), &SetVelocity, staWifiNode[0] ,Vector(17.0 ,0.0,0.0));//arr
    Simulator::Schedule (Seconds (2.2+timeoffset), &SetVelocity, staWifiNode[1] ,Vector(17.0 ,0.0,0.0));

    Simulator::Schedule (Seconds (2.3+timeoffset), &SetVelocity, staWifiNode[0] ,Vector(10.0 ,0.0,0.0)); //Sector Switch time 3_0.5
    Simulator::Schedule (Seconds (2.3+timeoffset), &SetVelocity, staWifiNode[1] ,Vector(10.0 ,0.0,0.0));
    Simulator::Schedule (Seconds (2.35+timeoffset), &SetVelocity, staWifiNode[0] ,Vector(0.0 ,0.0,0.0)); 
    Simulator::Schedule (Seconds (2.35+timeoffset), &SetVelocity, staWifiNode[1] ,Vector(0.0 ,0.0,0.0));

    Simulator::Schedule (Seconds (2.4+timeoffset), &SetVelocity, staWifiNode[0] ,Vector(13.0 ,0.0,0.0));//arr
    Simulator::Schedule (Seconds (2.4+timeoffset), &SetVelocity, staWifiNode[1] ,Vector(13.0 ,0.0,0.0));

    Simulator::Schedule (Seconds (2.5+timeoffset), &SetVelocity, staWifiNode[0] ,Vector(14.0 ,0.0,0.0)); //Sector Switch time 4_0.7
    Simulator::Schedule (Seconds (2.5+timeoffset), &SetVelocity, staWifiNode[1] ,Vector(14.0 ,0.0,0.0));
    Simulator::Schedule (Seconds (2.55+timeoffset), &SetVelocity, staWifiNode[0] ,Vector(0.0 ,0.0,0.0)); 
    Simulator::Schedule (Seconds (2.55+timeoffset), &SetVelocity, staWifiNode[1] ,Vector(0.0 ,0.0,0.0));

    Simulator::Schedule (Seconds (2.6+timeoffset), &SetVelocity, staWifiNode[0] ,Vector(20.0 ,0.0,0.0));
    Simulator::Schedule (Seconds (2.6+timeoffset), &SetVelocity, staWifiNode[1] ,Vector(20.0 ,0.0,0.0));

    Simulator::Schedule (Seconds (2.7+timeoffset), &SetVelocity, staWifiNode[0] ,Vector(0.5 ,0.0,0.0));
    Simulator::Schedule (Seconds (2.7+timeoffset), &SetVelocity, staWifiNode[1] ,Vector(0.5 ,0.0,0.0));


    Simulator::Schedule (Seconds (3.2+timeoffset), &SetVelocity, staWifiNode[0] ,Vector(0.0 ,0.0,0.0));
    Simulator::Schedule (Seconds (3.2+timeoffset), &SetVelocity, staWifiNode[1] ,Vector(0.0 ,0.0,0.0));


  }

  //實驗1================================================================================================
  else if(condition == 1)
  {
    Simulator::Schedule (Seconds (1.4+timeoffset), &SetVelocity, staWifiNode[0] ,Vector(0.5 ,0.0,0.0));
    Simulator::Schedule (Seconds (1.4+timeoffset), &SetVelocity, staWifiNode[1] ,Vector(0.5 ,0.0,0.0));

    Simulator::Schedule (Seconds (3.6+timeoffset), &SetVelocity, staWifiNode[0] ,Vector(21.0 ,0.0,0.0)); //Sector Switch time 1
    Simulator::Schedule (Seconds (3.6+timeoffset), &SetVelocity, staWifiNode[1] ,Vector(21.0 ,0.0,0.0));
    Simulator::Schedule (Seconds (3.65+timeoffset), &SetVelocity, staWifiNode[0] ,Vector(0.5 ,0.0,0.0));
    Simulator::Schedule (Seconds (3.65+timeoffset), &SetVelocity, staWifiNode[1] ,Vector(0.5 ,0.0,0.0));

    Simulator::Schedule (Seconds (5.5+timeoffset), &SetVelocity, staWifiNode[0] ,Vector(24.0 ,0.0,0.0)); //Sector Switch time 2
    Simulator::Schedule (Seconds (5.5+timeoffset), &SetVelocity, staWifiNode[1] ,Vector(24.0 ,0.0,0.0));
    Simulator::Schedule (Seconds (5.545+timeoffset), &SetVelocity, staWifiNode[0] ,Vector(0.5 ,0.0,0.0));
    Simulator::Schedule (Seconds (5.545+timeoffset), &SetVelocity, staWifiNode[1] ,Vector(0.5 ,0.0,0.0));

    Simulator::Schedule (Seconds (7.8+timeoffset), &SetVelocity, staWifiNode[0] ,Vector(22.0 ,0.0,0.0)); //Sector Switch time 3
    Simulator::Schedule (Seconds (7.8+timeoffset), &SetVelocity, staWifiNode[1] ,Vector(22.0 ,0.0,0.0));
    Simulator::Schedule (Seconds (7.85+timeoffset), &SetVelocity, staWifiNode[0] ,Vector(0.5 ,0.0,0.0));
    Simulator::Schedule (Seconds (7.85+timeoffset), &SetVelocity, staWifiNode[1] ,Vector(0.5 ,0.0,0.0));

  }








  /* Install FlowMonitor on all nodes */
  FlowMonitorHelper flowmon;
  Ptr<FlowMonitor> monitor;
  monitor = flowmon.InstallAll ();

  // p2pHelper.EnablePcap ("1Server_Gatway",s0s1);
  // p2pHelper.EnablePcap ("2Gatway_AP1",s2ap1);
  // p2pHelper.EnablePcap ("3Gatway_AP2",s2ap2);
  // p2pHelper2.EnablePcap ("4Sta1_User",s1e[0]);
  // p2pHelper2.EnablePcap ("5Sta2_User",s1e[1]);

  // p2pHelper2.EnablePcap ("6Freeway",Netbypass[0]);
  // p2pHelper2.EnablePcap ("6Sta3_User2",s1e[8]);
  // p2pHelper2.EnablePcap ("7Sta4_User2",s1e[14]);


  Simulator::Stop (Seconds (simulationTime + 0.001));
  Simulator::Run ();
  Simulator::Destroy ();

  /* Print Flow-Monitor Statistics */
  PrintFlowMonitorStatistics (flowmon, monitor, simulationTime - 1);                         // 2 >> D     7 >> I
                                                                                             // 3 >> E     8 >> J
  fout.open(file_des+"2_overall.csv" ,ios::app);                                             // 4 >> F
    fout  << "1.9s-End_Avg_Tput(Mbps),";                                            // 5 >> G

    char T_start = 'C'+UserNum-1;
    string T_start_S (1,T_start) ;
    // std::cout << T_start;

    if (condition ==1)
    {
      fout << "=AVERAGE("+T_start_S+"7:"+T_start_S+"88)\n"; 
    }
    else if (condition ==2)
    {
      fout << "=AVERAGE("+T_start_S+"7:"+T_start_S+"28)\n";   //(1.9 >> line7 ; 4.0 >> 28)                        // 6 >> H
    }
    fout.close();


  ifstream src;
  ofstream dst;
  // src.open("0_AP1_lable.txt", ios::in | ios::binary);
  // dst.open(file_des+"0_AP1_lable.txt", ios::out | ios::binary);
  // dst << src.rdbuf();
  // src.close();
  // dst.close();

  // src.open("0_AP2_lable.txt", ios::in | ios::binary);
  // dst.open(file_des+"0_AP2_lable.txt", ios::out | ios::binary);
  // dst << src.rdbuf();
  // src.close();
  // dst.close();

  // src.open("0_decodeLabel.txt", ios::in | ios::binary);
  // dst.open(file_des+"0_decodeLabel.txt", ios::out | ios::binary);
  // dst << src.rdbuf();
  // src.close();
  // dst.close();

  // src.open("0_Decode_lable.txt", ios::in | ios::binary);
  // dst.open(file_des+"0_Decode_lable.txt", ios::out | ios::binary);
  // dst << src.rdbuf();
  // src.close();
  // dst.close();

  src.open("0_packet_latency.txt", ios::in | ios::binary);
  dst.open(file_des+"0_packet_latency.txt", ios::out | ios::binary);
  dst << src.rdbuf();
  src.close();
  dst.close();

  // src.open("1_RTT.txt", ios::in | ios::binary);
  // dst.open(file_des+"1_RTT.txt", ios::out | ios::binary);
  // dst << src.rdbuf();
  // src.close();
  // dst.close();

  // src.open("1_seq.txt", ios::in | ios::binary);
  // dst.open(file_des+"1_seq.txt", ios::out | ios::binary);
  // dst << src.rdbuf();
  // src.close();
  // dst.close();

  // wifiPhy1.EnablePcap ("Traces/Station", staDeviceA, false);
  /* Print Results Summary */
  std::cout << "Total #Received Packets = " << packetSink[0]->GetTotalReceivedPackets () << std::endl;
  std::cout << "Total Throughput [Mbps] = " << throughput[0]/((simulationTime-1.4) * 10) << std::endl;
  // std::cout << "Total #Received Packets = " << packetSink2->GetTotalReceivedPackets () << std::endl;
  // std::cout << "Total Throughput [Mbps] = " << throughput2/(1 * 10) << std::endl;
  return 0;
}

