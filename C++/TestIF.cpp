#include "TestInPortConsumer.h"
#include "TestInPortProvider.h"
#include "TestOutPortConsumer.h"
#include "TestOutPortProvider.h"
#include <rtm/Manager.h>

static const char* const testifpush_option[] =
{
  "filename.__value__", "test.dat",
  "filename.__widget__", "text",
  "filename.__constraint__", "none",
  ""
};

static const char* const testifpull_option[] =
{
  "filename_in.__value__", "test_in.dat",
  "filename_in.__widget__", "text",
  "filename_in.__constraint__", "none",
  "filename_out.__value__", "test_out.dat",
  "filename_out.__widget__", "text",
  "filename_out.__constraint__", "none",
  ""
};


extern "C"
{
  DLL_EXPORT void TestIFInit(RTC::Manager* manager)
  {
     {
       coil::Properties prop(testifpush_option);
       RTC::InPortProviderFactory& factory(RTC::InPortProviderFactory::instance());
       factory.addFactory("testif",
                      ::coil::Creator< ::RTC::InPortProvider,
                                        TestInPortProvider>,
                      ::coil::Destructor< ::RTC::InPortProvider,
                                        TestInPortProvider>,
                      prop);
     }

     {
       coil::Properties prop(testifpush_option);
       RTC::InPortConsumerFactory& factory(RTC::InPortConsumerFactory::instance());
       factory.addFactory("testif",
                      ::coil::Creator< ::RTC::InPortConsumer,
                                        TestInPortConsumer>,
                      ::coil::Destructor< ::RTC::InPortConsumer,
                                        TestInPortConsumer>,
                      prop);
     }

     {
       coil::Properties prop(testifpull_option);
       RTC::OutPortProviderFactory& factory(RTC::OutPortProviderFactory::instance());
       factory.addFactory("testif",
                      ::coil::Creator< ::RTC::OutPortProvider,
                                        TestOutPortProvider>,
                      ::coil::Destructor< ::RTC::OutPortProvider,
                                        TestOutPortProvider>,
                      prop);
     }

     {
       coil::Properties prop(testifpull_option);
       RTC::OutPortConsumerFactory& factory(RTC::OutPortConsumerFactory::instance());
       factory.addFactory("testif",
                      ::coil::Creator< ::RTC::OutPortConsumer,
                                        TestOutPortConsumer>,
                      ::coil::Destructor< ::RTC::OutPortConsumer,
                                        TestOutPortConsumer>,
                      prop);
     }
  }
}