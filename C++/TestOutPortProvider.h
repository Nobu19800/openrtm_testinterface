#ifndef TESTOUTPORTPROVIDER_H
#define TESTOUTPORTPROVIDER_H

#include <rtm/OutPortProvider.h>
#include <thread>

class TestOutPortProvider
  : public RTC::OutPortProvider
{
public:
  TestOutPortProvider();
  ~TestOutPortProvider() override;
  void init(coil::Properties& prop) override;
  void setBuffer(RTC::CdrBufferBase* buffer) override;
  void setListener(RTC::ConnectorInfo& info,
    RTC::ConnectorListenersBase* listeners) override;
  void setConnector(RTC::OutPortConnector* connector) override;
private:
  std::thread m_thread;
  bool m_running;
  RTC::OutPortConnector* m_connector;
};

#endif