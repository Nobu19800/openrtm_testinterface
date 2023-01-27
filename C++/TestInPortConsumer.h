#ifndef TESTINPORTCONSUMER_H
#define TESTINPORTCONSUMER_H

#include <rtm/SystemLogger.h>
#include <rtm/InPortConsumer.h>

class TestInPortConsumer
    : public RTC::InPortConsumer
{
public:
  TestInPortConsumer();
  ~TestInPortConsumer() override;
  void init(coil::Properties& prop) override;
  RTC::DataPortStatus put(RTC::ByteData& data) override;
  void publishInterfaceProfile(SDOPackage::NVList& properties) override;
  bool subscribeInterface(const SDOPackage::NVList& properties) override;
  void unsubscribeInterface(const SDOPackage::NVList& properties) override;
private:
  std::string m_filename;
  unsigned long m_dataid;
};

#endif