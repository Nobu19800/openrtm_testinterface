#ifndef TESTOUTPORTCONSUMER_H
#define TESTOUTPORTCONSUMER_H

#include <rtm/SystemLogger.h>
#include <rtm/OutPortConsumer.h>

class TestOutPortConsumer
  : public RTC::OutPortConsumer
{
public:
  TestOutPortConsumer();
  ~TestOutPortConsumer() override;
  void init(coil::Properties& prop) override;
  void setBuffer(RTC::CdrBufferBase* buffer) override;
  void setListener(RTC::ConnectorInfo& info,
    RTC::ConnectorListenersBase* listeners) override;
  RTC::DataPortStatus get(RTC::ByteData& data) override;
  bool subscribeInterface(const SDOPackage::NVList& properties) override;
  void unsubscribeInterface(const SDOPackage::NVList& properties) override;
private:
  std::string m_filename_in;
  std::string m_filename_out;
  unsigned long m_dataid;
};

#endif