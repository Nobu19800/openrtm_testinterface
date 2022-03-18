#include "TestOutPortConsumer.h"
#include <fstream>


TestOutPortConsumer::TestOutPortConsumer() : m_dataid(0)
{
}

TestOutPortConsumer::~TestOutPortConsumer()
{
}

void TestOutPortConsumer::init(coil::Properties& prop)
{
  if (prop.propertyNames().size() == 0)
  {
    return;
  }

  m_filename_in = prop.getProperty("testif.filename_in", "test_in.dat");
  m_filename_out = prop.getProperty("testif.filename_out", "test_out.dat");
}

void TestOutPortConsumer::setBuffer(RTC::CdrBufferBase* buffer)
{
}

void TestOutPortConsumer::setListener(RTC::ConnectorInfo& info,
  RTC::ConnectorListenersBase* listeners)
{
}

RTC::DataPortStatus TestOutPortConsumer::get(RTC::ByteData& data)
{
  std::ofstream fout;
  fout.open(m_filename_in, std::ios::out | std::ios::binary | std::ios::trunc);

  if (fout.fail())
  {
    return RTC::DataPortStatus::PORT_ERROR;
  }
  else
  {
    m_dataid += 1;
    fout.write((const char*)&m_dataid, sizeof(unsigned long));
    fout.close();

    for (int i = 0; i < 100; i++)
    {
      std::ifstream fin(m_filename_out, std::ios::in | std::ios::binary);
      if (!fin.fail())
      {
        unsigned long id = 0;
        fin.read((char*)&id, sizeof(unsigned long));

        if (id == m_dataid)
        {
          unsigned long size = 0;
          fin.read((char*)&size, sizeof(unsigned long));
          if (size > 0)
          {
            data.setDataLength(size);
            fin.read((char*)data.getBuffer(), size);
            return RTC::DataPortStatus::PORT_OK;
          }

        }
      }
    }
  }

  return RTC::DataPortStatus::PORT_ERROR;
}

bool TestOutPortConsumer::subscribeInterface(const SDOPackage::NVList& properties)
{
  return true;
}

void TestOutPortConsumer::unsubscribeInterface(const SDOPackage::NVList& properties)
{
}