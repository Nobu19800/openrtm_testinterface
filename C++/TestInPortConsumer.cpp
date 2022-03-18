#include "TestInPortConsumer.h"
#include <fstream>
#include <rtm/NVUtil.h>

TestInPortConsumer::TestInPortConsumer() : m_dataid(0)
{
}

TestInPortConsumer::~TestInPortConsumer()
{
}

void TestInPortConsumer::init(coil::Properties& prop)
{
  if (prop.propertyNames().size() == 0)
  {
    return;
  }

  m_filename = prop.getProperty("testif.filename", "test.dat");

}

RTC::DataPortStatus TestInPortConsumer::put(RTC::ByteData& data)
{

  std::ofstream fout;
  fout.open(m_filename, std::ios::out | std::ios::binary | std::ios::trunc);

  if (fout.fail())
  {
    return RTC::DataPortStatus::PORT_ERROR;
  }
  else
  {
    m_dataid += 1;
    fout.write((const char*)&m_dataid, sizeof(unsigned long));

    const unsigned long size = data.getDataLength();
    fout.write((const char*)&size, sizeof(unsigned long));

    if (size > 0)
    {
      fout.write((const char*)data.getBuffer(), size);
    }
  }


  return RTC::DataPortStatus::PORT_OK;
}

void TestInPortConsumer::publishInterfaceProfile(SDOPackage::NVList& properties)
{
}

bool TestInPortConsumer::subscribeInterface(const SDOPackage::NVList& properties)
{

  return true;
}

void TestInPortConsumer::unsubscribeInterface(const SDOPackage::NVList& properties)
{
}
