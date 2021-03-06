/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2008 INRIA
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */

#ifndef WIFI_MAC_H
#define WIFI_MAC_H

#include "ns3/net-device.h"
#include "wifi-phy-standard.h"
#include "wifi-remote-station-manager.h"
#include "qos-utils.h"

namespace ns3 {

class Ssid;
class Txop;
class HtConfiguration;
class VhtConfiguration;
class HeConfiguration;

/**
 * \brief base class for all MAC-level wifi objects.
 * \ingroup wifi
 *
 * This class encapsulates all the low-level MAC functionality
 * DCA, EDCA, etc) and all the high-level MAC functionality
 * (association/disassociation state machines).
 *
 */
class WifiMac : public Object
{
public:
  virtual void DoDispose ();

  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);

  /**
   * Sets the device this PHY is associated with.
   *
   * \param device the device this PHY is associated with
   */
  void SetDevice (const Ptr<NetDevice> device);
  /**
   * Return the device this PHY is associated with
   *
   * \return the device this PHY is associated with
   */
  Ptr<NetDevice> GetDevice (void) const;

  /**
   * \param slotTime the slot duration
   */
  virtual void SetSlot (Time slotTime) = 0;
  /**
   * \param sifs the SIFS duration
   */
  virtual void SetSifs (Time sifs) = 0;
  /**
   * \param eifsNoDifs the duration of an EIFS minus DIFS.
   *
   * This value is used to calculate the EIFS depending
   * on AIFSN.
   */
  virtual void SetEifsNoDifs (Time eifsNoDifs) = 0;
  /**
   * \param pifs the PIFS duration.
   */
  virtual void SetPifs (Time pifs) = 0;
  /**
   * \param rifs the RIFS duration.
   */
  virtual void SetRifs (Time rifs) = 0;
  /**
   * \param ackTimeout the duration of an Ack timeout.
   */
  virtual void SetAckTimeout (Time ackTimeout) = 0;
  /**
   * \param delay the max propagation delay.
   *
   * Unused for now.
   */
  void SetMaxPropagationDelay (Time delay);
  /**
   * \param ssid the current SSID of this MAC layer.
   */
  virtual void SetSsid (Ssid ssid) = 0;
  /**
   * Enable or disable short slot time feature.
   *
   * \param enable true if short slot time is to be supported,
   *               false otherwise
   */
  virtual void SetShortSlotTimeSupported (bool enable) = 0;
  /**
   * \brief Sets the interface in promiscuous mode.
   *
   * Enables promiscuous mode on the interface. Note that any further
   * filtering on the incoming frame path may affect the overall
   * behavior.
   */
  virtual void SetPromisc (void) = 0;

  /**
   * \return the current RIFS duration.
   */
  virtual Time GetRifs (void) const = 0;
  /**
   * \return the current PIFS duration.
   */
  virtual Time GetPifs (void) const = 0;
  /**
   * \return the current SIFS duration.
   */
  virtual Time GetSifs (void) const = 0;
  /**
   * \return the current slot duration.
   */
  virtual Time GetSlot (void) const = 0;
  /**
   * \return the current EIFS minus DIFS duration
   */
  virtual Time GetEifsNoDifs (void) const = 0;
  /**
   * \return the current Ack timeout duration.
   */
  virtual Time GetAckTimeout (void) const = 0;
  /**
   * \return the maximum propagation delay.
   *
   * Unused for now.
   */
  Time GetMaxPropagationDelay (void) const;
  /**
   * \return the MAC address associated to this MAC layer.
   */
  virtual Mac48Address GetAddress (void) const = 0;
  /**
   * \return the SSID which this MAC layer is going to try to stay in.
   */
  virtual Ssid GetSsid (void) const = 0;
  /**
   * \param address the current address of this MAC layer.
   */
  virtual void SetAddress (Mac48Address address) = 0;
  /**
   * \return the BSSID of the network this device belongs to.
   */
  virtual Mac48Address GetBssid (void) const = 0;
  /**
   * \return whether the device supports short slot time capability.
   */
  virtual bool GetShortSlotTimeSupported (void) const = 0;

  /**
   * \param packet the packet to send.
   * \param to the address to which the packet should be sent.
   * \param from the address from which the packet should be sent.
   *
   * The packet should be enqueued in a TX queue, and should be
   * dequeued as soon as the DCF function determines that
   * access it granted to this MAC. The extra parameter "from" allows
   * this device to operate in a bridged mode, forwarding received
   * frames without altering the source address.
   */
  virtual void Enqueue (Ptr<Packet> packet, Mac48Address to, Mac48Address from) = 0;
  /**
   * \param packet the packet to send.
   * \param to the address to which the packet should be sent.
   *
   * The packet should be enqueued in a TX queue, and should be
   * dequeued as soon as the DCF function determines that
   * access it granted to this MAC.
   */
  virtual void Enqueue (Ptr<Packet> packet, Mac48Address to) = 0;
  /**
   * \return if this MAC supports sending from arbitrary address.
   *
   * The interface may or may not support sending from arbitrary address.
   * This function returns true if sending from arbitrary address is supported,
   * false otherwise.
   */
  virtual bool SupportsSendFrom (void) const = 0;
  /**
   * \param phy the physical layer attached to this MAC.
   */
  virtual void SetWifiPhy (Ptr<WifiPhy> phy) = 0;
  /**
   * \return the physical layer attached to this MAC
   */
  virtual Ptr<WifiPhy> GetWifiPhy (void) const = 0;
  /**
   * Remove currently attached WifiPhy device from this MAC.
   */
  virtual void ResetWifiPhy (void) = 0;
  /**
   * \param stationManager the station manager attached to this MAC.
   */
  virtual void SetWifiRemoteStationManager (Ptr<WifiRemoteStationManager> stationManager) = 0;
  /**
   * \return the station manager attached to this MAC.
   */
  virtual Ptr<WifiRemoteStationManager> GetWifiRemoteStationManager (void) const = 0;

  /**
   * \param upCallback the callback to invoke when a packet must be
   *        forwarded up the stack.
   */
  virtual void SetForwardUpCallback (Callback<void, Ptr<const Packet>, Mac48Address, Mac48Address> upCallback) = 0;
  /**
   * \param linkUp the callback to invoke when the link becomes up.
   */
  virtual void SetLinkUpCallback (Callback<void> linkUp) = 0;
  /**
   * \param linkDown the callback to invoke when the link becomes down.
   */
  virtual void SetLinkDownCallback (Callback<void> linkDown) = 0;
  /* Next functions are not pure virtual so non QoS WifiMacs are not
   * forced to implement them.
   */

  /**
   * \param blockAckTimeout the duration for basic BlockAck timeout.
   *
   * Sets the timeout for basic BlockAck.
   */
  virtual void SetBasicBlockAckTimeout (Time blockAckTimeout) = 0;
  /**
   * \return the current basic BlockAck timeout duration.
   */
  virtual Time GetBasicBlockAckTimeout (void) const = 0;
  /**
   * \param blockAckTimeout the duration for compressed BlockAck timeout
   *
   * Sets the timeout for compressed BlockAck.
   */
  virtual void SetCompressedBlockAckTimeout (Time blockAckTimeout) = 0;
  /**
   * \return the current compressed BlockAck timeout duration.
   */
  virtual Time GetCompressedBlockAckTimeout (void) const = 0;

  /**
   * \param packet the packet being enqueued
   *
   * Public method used to fire a MacTx trace. Implemented for encapsulation purposes.
   * Note this trace indicates that the packet was accepted by the device only.
   * The packet may be dropped later (e.g. if the queue is full).
   */
  void NotifyTx (Ptr<const Packet> packet);
  /**
   * \param packet the packet being dropped
   *
   * Public method used to fire a MacTxDrop trace. Implemented for encapsulation purposes.
   * This trace indicates that the packet was dropped before it was transmitted
   * (e.g. when a STA is not associated with an AP).
   */
  void NotifyTxDrop (Ptr<const Packet> packet);
  /**
   * \param packet the packet we received
   *
   * Public method used to fire a MacRx trace. Implemented for encapsulation purposes.
   */
  void NotifyRx (Ptr<const Packet> packet);
  /**
   * \param packet the packet we received promiscuously
   *
   * Public method used to fire a MacPromiscRx trace. Implemented for encapsulation purposes.
   */
  void NotifyPromiscRx (Ptr<const Packet> packet);
  /**
   * \param packet the packet we received but is not destined for us
   *
   * Public method used to fire a MacRxDrop trace. Implemented for encapsulation purposes.
   */
  void NotifyRxDrop (Ptr<const Packet> packet);

  /**
   * \param standard the wifi standard to be configured
   *
   * This method sets standards-compliant defaults for WifiMac
   * parameters such as SIFS time, slot time, timeout values, etc.,
   * based on the standard selected.
   *
   * \sa WifiMac::Configure80211a
   * \sa WifiMac::Configure80211b
   * \sa WifiMac::Configure80211g
   * \sa WifiMac::Configure80211_10Mhz
   * \sa WifiMac::Configure80211_5Mhz
   * \sa WifiMac::Configure80211n_2_4Ghz
   * \sa WifiMac::Configure80211n_5Ghz
   * \sa WifiMac::Configure80211ac
   * \sa WifiMac::Configure80211ax_2_4Ghz
   * \sa WifiMac::Configure80211ax_5Ghz
   * \sa WifiMac::Configure80211ad
   * \sa WifiMac::Configure80211ay
   */
  void ConfigureStandard (WifiPhyStandard standard);
  WifiPhyStandard GetCurrentstandard (void) const;

  //// WIGIG ////
  typedef Callback<void, WifiPhyStandard, Mac48Address, bool> BandChangedCallback;
  void RegisterBandChangedCallback (BandChangedCallback callback);
  virtual void NotifyBandChanged (WifiPhyStandard, Mac48Address address, bool isInitiator) = 0;
  //// WIGIG ////

  /**
   * \return pointer to HtConfiguration if it exists
   */
  Ptr<HtConfiguration> GetHtConfiguration (void) const;
  /**
   * \return pointer to VhtConfiguration if it exists
   */
  Ptr<VhtConfiguration> GetVhtConfiguration (void) const;
  /**
   * \return pointer to HeConfiguration if it exists
   */
  Ptr<HeConfiguration> GetHeConfiguration (void) const;


protected:
  /**
   * \param dcf the DCF to be configured
   * \param cwmin the minimum contention window for the DCF
   * \param cwmax the maximum contention window for the DCF
   * \param isDsss flag to indicate whether PHY is DSSS or HR/DSSS
   * \param ac the access category for the DCF
   *
   * Configure the DCF with appropriate values depending on the given access category.
   */
  void ConfigureDcf (Ptr<Txop> dcf, uint32_t cwmin, uint32_t cwmax, bool isDsss, AcIndex ac);

  //// WIGIG ////
  /**
   * This method sets 802.11ad 60 GHz standards-compliant defaults for following attributes:
   * Sifs, Slot, EifsNoDifs, Pifs, CtsTimeout, and AckTimeout.
   */
  virtual void Configure80211ad (void);
  /**
   * This method sets 802.11ay 60 GHz standards-compliant defaults for following attributes:
   * Sifs, Slot, EifsNoDifs, Pifs, CtsTimeout, and AckTimeout.
   */
  virtual void Configure80211ay (void);

  WifiPhyStandard m_standard;
  BandChangedCallback m_bandChangedCallback;
  //// WIGIG ////

private:
  /**
   * \return the default maximum propagation delay
   *
   * By default, we get the maximum propagation delay from 1000 m and speed of light
   * (3e8 m/s).
   */
  static Time GetDefaultMaxPropagationDelay (void);
  /**
   * \return the default slot duration
   *
   * Return a default slot value for 802.11a (9 microseconds).
   */
  static Time GetDefaultSlot (void);
  /**
   * \return the default short interframe space (SIFS)
   *
   * Return a default SIFS value for 802.11a (16 microseconds).
   */
  static Time GetDefaultSifs (void);
  /**
   * \return the default reduced interframe space (RIFS)
   *
   * Return a default RIFS value for 802.11n (2 microseconds).
   */
  static Time GetDefaultRifs (void);
  /**
   * \return the default extended interframe space (EIFS) without
   *         DCF interframe space (DIFS)
   *
   * Return default SIFS + default CTS-Ack delay
   */
  static Time GetDefaultEifsNoDifs (void);
  /**
   * \return the default CTS-Ack delay
   *
   * Return a default value for 802.11a at 6Mbps (44 microseconds)
   */
  static Time GetDefaultCtsAckDelay (void);
  /**
   * \return the default CTS and Ack timeout
   *
   * Return the default CTS and Ack timeout.
   * Cts_Timeout and Ack_Timeout are specified in the Annex C
   * (Formal description of MAC operation, see details on the
   * Trsp timer setting at page 346)
   */
  static Time GetDefaultCtsAckTimeout (void);
  /**
   * Return the default basic BlockAck delay.
   * Currently it returns 250 microseconds.
   *
   * \return the default basic BlockAck delay
   */
  static Time GetDefaultBasicBlockAckDelay (void);
  /**
   * Return the default basic BlockAck timeout.
   *
   * \return the default basic BlockAck timeout
   */
  static Time GetDefaultBasicBlockAckTimeout (void);
  /**
   * Return the default compressed BlockAck delay.
   * Currently it returns 76 microseconds.
   *
   * \return the default compressed BlockAck delay
   */
  static Time GetDefaultCompressedBlockAckDelay (void);
  /**
   * Return the default compressed BlockAck timeout.
   *
   * \return the default compressed BlockAck timeout
   */
  static Time GetDefaultCompressedBlockAckTimeout (void);

  /**
   * \param standard the PHY standard to be used
   *
   * This method is called by ns3::WifiMac::ConfigureStandard to complete
   * the configuration process for a requested PHY standard. Subclasses should
   * implement this method to configure their DCF queues according to the
   * requested standard.
   */
  virtual void FinishConfigureStandard (WifiPhyStandard standard) = 0;

  Time m_maxPropagationDelay; ///< maximum propagation delay
  Ptr<NetDevice> m_device;    ///< Pointer to the device

  /**
   * This method sets 802.11a standards-compliant defaults for following attributes:
   * SIFS, Slot, EifsNoDifs, PIFS, CtsTimeout, and AckTimeout.
   */
  void Configure80211a (void);
  /**
   * This method sets 802.11b standards-compliant defaults for following attributes:
   * SIFS, Slot, EifsNoDifs, PIFS, CtsTimeout, and AckTimeout.
   */
  void Configure80211b (void);
  /**
   * This method sets 802.11g standards-compliant defaults for following attributes:
   * SIFS, Slot, EifsNoDifs, PIFS, CtsTimeout, and AckTimeout.
   * There is no support for short slot time.
   */
  void Configure80211g (void);
  /**
   * This method sets 802.11 with 10 MHz channel spacing standards-compliant defaults
   * for following attributes: SIFS, Slot, EifsNoDifs, PIFS, CtsTimeout, and AckTimeout.
   */
  void Configure80211_10Mhz (void);
  /**
   * This method sets 802.11 with 5 MHz channel spacing standards-compliant defaults
   * for following attributes: SIFS, Slot, EifsNoDifs, PIFS, CtsTimeout, and AckTimeout.
   */
  void Configure80211_5Mhz ();
  /**
   * This method sets 802.11n 2.4 GHz standards-compliant defaults for following attributes:
   * SIFS, RIFS, Slot, EifsNoDifs, PIFS, CtsTimeout, and AckTimeout.
   * There is no support for short slot time.
   */
  void Configure80211n_2_4Ghz (void);
  /**
   * This method sets 802.11n 5 GHz standards-compliant defaults for following attributes:
   * SIFS, RIFS, Slot, EifsNoDifs, PIFS, CtsTimeout, and AckTimeout.
   */
  void Configure80211n_5Ghz (void);
  /**
  * This method sets 802.11ac standards-compliant defaults for following attributes:
  * SIFS, Slot, EifsNoDifs, PIFS, CtsTimeout, and AckTimeout.
  */
  void Configure80211ac (void);
  /**
   * This method sets 802.11ax 2.4 GHz standards-compliant defaults for following attributes:
   * SIFS, Slot, EifsNoDifs, PIFS, CtsTimeout, and AckTimeout.
   * There is no support for short slot time.
   */
  void Configure80211ax_2_4Ghz (void);
  /**
   * This method sets 802.11ax 5 GHz standards-compliant defaults for following attributes:
   * SIFS, Slot, EifsNoDifs, PIFS, CtsTimeout, and AckTimeout.
   */
  void Configure80211ax_5Ghz (void);

  /**
   * The trace source fired when packets come into the "top" of the device
   * at the L3/L2 transition, before being queued for transmission.
   *
   * \see class CallBackTraceSource
   */
  TracedCallback<Ptr<const Packet> > m_macTxTrace;
  /**
   * The trace source fired when packets coming into the "top" of the device
   * are dropped at the MAC layer during transmission.
   *
   * \see class CallBackTraceSource
   */
  TracedCallback<Ptr<const Packet> > m_macTxDropTrace;
  /**
   * The trace source fired for packets successfully received by the device
   * immediately before being forwarded up to higher layers (at the L2/L3
   * transition).  This is a promiscuous trace.
   *
   * \see class CallBackTraceSource
   */
  TracedCallback<Ptr<const Packet> > m_macPromiscRxTrace;
  /**
   * The trace source fired for packets successfully received by the device
   * immediately before being forwarded up to higher layers (at the L2/L3
   * transition).  This is a non- promiscuous trace.
   *
   * \see class CallBackTraceSource
   */
  TracedCallback<Ptr<const Packet> > m_macRxTrace;
  /**
   * The trace source fired when packets coming into the "top" of the device
   * are dropped at the MAC layer during reception.
   *
   * \see class CallBackTraceSource
   */
  TracedCallback<Ptr<const Packet> > m_macRxDropTrace;
};

} //namespace ns3

#endif /* WIFI_MAC_H */

