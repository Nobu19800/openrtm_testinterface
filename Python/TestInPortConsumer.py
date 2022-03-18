#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import OpenRTM_aist
import struct


class TestInPortConsumer(
        OpenRTM_aist.InPortConsumer):

    def __init__(self):
        self._filename = "test.dat"
        self._dataid = 0

    def __del__(self):
        pass

    def init(self, prop):
        if not prop.propertyNames():
            return
        self._filename = prop.getProperty("testif.filename", "test.dat")

    def put(self, data):
        with open(self._filename, 'wb') as fout:
            self._dataid += 1
            try:
                fout.write(struct.pack('L', self._dataid))
                fout.write(struct.pack('L', len(data)))
                fout.write(data)
            except BaseException:
                return self.PORT_ERROR
            return self.PORT_OK

    def publishInterfaceProfile(self, properties):
        pass

    def subscribeInterface(self, properties):
        return True

    def unsubscribeInterface(self, properties):
        pass


testifpush_option = [
    "filename_in.__value__", "test_in.dat",
    "filename_in.__widget__", "text",
    "filename_in.__constraint__", "none",
    "filename_out.__value__", "test_out.dat",
    "filename_out.__widget__", "text",
    "filename_out.__constraint__", "none",
    ""
]


def TestInPortConsumerInit():
    prop = OpenRTM_aist.Properties(defaults_str=testifpush_option)
    factory = OpenRTM_aist.InPortConsumerFactory.instance()
    factory.addFactory("testif",
                       TestInPortConsumer,
                       prop)
