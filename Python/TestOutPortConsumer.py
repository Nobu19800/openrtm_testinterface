#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import OpenRTM_aist
import struct
import os


class TestOutPortConsumer(
        OpenRTM_aist.OutPortConsumer):

    def __init__(self):
        self._filename_in = "test_in.dat"
        self._filename_out = "test_out.dat"
        self._dataid = 0

    def __del__(self):
        pass

    def init(self, prop):
        if not prop.propertyNames():
            return
        self._filename_in = prop.getProperty(
            "testif.filename_in", "test_in.dat")
        self._filename_out = prop.getProperty(
            "testif.filename_out", "test_out.dat")

    def setBuffer(self, buffer):
        pass

    def setListener(self, info, listeners):
        pass

    def get(self):
        with open(self._filename_in, 'wb') as fout:
            self._dataid += 1
            try:
                print(self._dataid)
                fout.write(struct.pack('L', self._dataid))
            except BaseException:
                return self.PORT_ERROR

        for i in range(100):
            if os.path.exists(self._filename_out):
                with open(self._filename_out, 'rb') as fin:
                    try:
                        id = struct.unpack("L", fin.read(4))[0]
                        if id == self._dataid:
                            self._dataid = id
                            size = struct.unpack("L", fin.read(4))[0]
                            if size > 0:
                                data = fin.read(size)
                                return self.PORT_OK, data
                    except BaseException:
                        pass

        return self.PORT_ERROR, ""

    def subscribeInterface(self, properties):
        return True

    def unsubscribeInterface(self, properties):
        pass


testifpull_option = [
    "filename_in.__value__", "test_in.dat",
    "filename_in.__widget__", "text",
    "filename_in.__constraint__", "none",
    "filename_out.__value__", "test_out.dat",
    "filename_out.__widget__", "text",
    "filename_out.__constraint__", "none",
    ""
]


def TestOutPortConsumerInit():
    prop = OpenRTM_aist.Properties(defaults_str=testifpull_option)
    factory = OpenRTM_aist.OutPortConsumerFactory.instance()
    factory.addFactory("testif",
                       TestOutPortConsumer,
                       prop)
    return
