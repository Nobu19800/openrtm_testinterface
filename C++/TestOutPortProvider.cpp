#include "TestOutPortProvider.h"
#include <fstream>

TestOutPortProvider::TestOutPortProvider() : m_running(false), m_connector(nullptr)
{
  setInterfaceType("testif");
}

TestOutPortProvider::~TestOutPortProvider()
{
  if (m_running)
  {
    m_running = false;
    m_thread.join();
  }
}

void TestOutPortProvider::init(coil::Properties &prop)
{
  if (prop.propertyNames().size() == 0)
  {
    return;
  }

  const std::string filename_in = prop.getProperty("testif.filename_in", "test_in.dat");
  const std::string filename_out = prop.getProperty("testif.filename_out", "test_out.dat");

  if (!m_running)
  {
    m_thread = std::thread([this, filename_in, filename_out]
                           {
      this->m_running = true;
      unsigned long lastid = 0;
      while (this->m_running)
      {
        if (this->m_connector != nullptr)
        {
          std::ifstream fin(filename_in, std::ios::in | std::ios::binary);
          if (!fin.fail())
          {
            unsigned long id = 0;
            fin.read((char*)&id, sizeof(unsigned long));
            fin.close();

            if (lastid != id)
            {
              lastid = id;
              std::ofstream fout;
              fout.open(filename_out, std::ios::out | std::ios::binary | std::ios::trunc);
              if (!fout.fail())
              {
                fout.write((const char*)&id, sizeof(unsigned long));

                RTC::ByteData data;
                m_connector->read(data);

                const unsigned long size = data.getDataLength();
                fout.write((const char*)&size, sizeof(unsigned long));

                if (size > 0)
                {
                  fout.write((const char*)data.getBuffer(), size);
                }
              }

              
            }
          }
        }
      } });
  }
}

void TestOutPortProvider::setBuffer(RTC::CdrBufferBase *buffer)
{
}

void TestOutPortProvider::setListener(RTC::ConnectorInfo &info,
                                      RTC::ConnectorListenersBase *listeners)
{
}

void TestOutPortProvider::setConnector(RTC::OutPortConnector *connector)
{
  m_connector = connector;
}