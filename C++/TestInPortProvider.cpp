#include "TestInPortProvider.h"
#include <fstream>

TestInPortProvider::TestInPortProvider() : m_running(false), m_connector(nullptr)
{
}

TestInPortProvider::~TestInPortProvider()
{
  if (m_running)
  {
    m_running = false;
    m_thread.join();
  }
}

void TestInPortProvider::init(coil::Properties& prop)
{
  if (prop.propertyNames().size() == 0)
  {
    return;
  }

  const std::string filename = prop.getProperty("testif.filename", "test.dat");

  if (!m_running)
  {
    m_thread = std::thread([this, filename] {
      this->m_running = true;
      unsigned long lastid = 0;
      while (this->m_running)
      {
        if (this->m_connector != nullptr)
        {
          std::ifstream fin(filename, std::ios::in | std::ios::binary);
          if (!fin.fail())
          {
            unsigned long id = 0;
            fin.read((char*)&id, sizeof(unsigned long));

            if (id != lastid)
            {
              lastid = id;
              unsigned long size = 0;
              fin.read((char*)&size, sizeof(unsigned long));
              if (size > 0)
              {
                RTC::ByteData data;
                data.setDataLength(size);
                fin.read((char*)data.getBuffer(), size);
                this->m_connector->write(data);
              }
            }
          }
        }
      }
      });
  }
}

void TestInPortProvider::setBuffer(RTC::BufferBase<RTC::ByteData>* buffer)
{
}

void TestInPortProvider::setListener(RTC::ConnectorInfo& info,
  RTC::ConnectorListenersBase* listeners)
{
}

void TestInPortProvider::setConnector(RTC::InPortConnector* connector)
{
  m_connector = connector;
}