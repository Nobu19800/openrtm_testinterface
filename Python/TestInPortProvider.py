#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import OpenRTM_aist
import struct
import threading
import os


class TestInPortProvider(OpenRTM_aist.InPortProvider):

    def __init__(self):
        OpenRTM_aist.InPortProvider.__init__(self)

        self.setInterfaceType("testif")

        self._thread = None
        self._running = False
        self._connector = None

    def __del__(self):
        pass

    def exit(self):
        if self._running:
            self._running = False
            self._thread.join()

    def init(self, prop):
        if not prop.propertyNames():
            return
        filename = prop.getProperty("testif.filename", "test.dat")

        def polling():
            self._running = True
            lastid = 0
            while self._running:
                if self._connector:
                    if os.path.exists(filename):
                        with open(filename, 'rb') as fin:
                            try:
                                id = struct.unpack("L", fin.read(4))[0]
                                if id != lastid:
                                    lastid = id
                                    size = struct.unpack("L", fin.read(4))[0]
                                    if size > 0:
                                        data = fin.read(size)
                                        self._connector.write(data)
                            except BaseException:
                                pass

        self._thread = threading.Thread(target=polling)
        self._thread.start()

    def setBuffer(self, buffer):
        pass

    def setListener(self, info, listeners):
        pass

    def setConnector(self, connector):
        self._connector = connector


testifpush_option = [
    "filename_in.__value__", "test_in.dat",
    "filename_in.__widget__", "text",
    "filename_in.__constraint__", "none",
    "filename_out.__value__", "test_out.dat",
    "filename_out.__widget__", "text",
    "filename_out.__constraint__", "none",
    ""
]


def TestInPortProviderInit():
    prop = OpenRTM_aist.Properties(defaults_str=testifpush_option)
    factory = OpenRTM_aist.InPortProviderFactory.instance()
    factory.addFactory("testif",
                       TestInPortProvider,
                       prop)
