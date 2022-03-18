#ifndef TESTINPORTPROVIDER_H
#define TESTINPORTPROVIDER_H

#include <rtm/InPortProvider.h>
#include <thread>

class TestInPortProvider
    : public RTC::InPortProvider
{
public:
  TestInPortProvider();
  ~TestInPortProvider() override;
  void init(coil::Properties& prop) override;
  void setBuffer(RTC::BufferBase<RTC::ByteData>* buffer) override;
  void setListener(RTC::ConnectorInfo& info,
                             RTC::ConnectorListenersBase* listeners) override;
  void setConnector(RTC::InPortConnector* connector) override;
private:
  std::thread m_thread;
  bool m_running;
  RTC::InPortConnector* m_connector;
};

#endif