#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import OpenRTM_aist
import struct
import threading
import os


class TestOutPortProvider(OpenRTM_aist.OutPortProvider):

    def __init__(self):
        OpenRTM_aist.OutPortProvider.__init__(self)
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

        filename_in = prop.getProperty("testif.filename_in", "test_in.dat")
        filename_out = prop.getProperty("testif.filename_out", "test_out.dat")

        def polling():
            self._running = True
            lastid = 0
            while self._running:
                if self._connector:
                    if os.path.exists(filename_in):
                        with open(filename_in, 'rb') as fin:
                            try:
                                id = struct.unpack(
                                    "L", fin.read(struct.calcsize("L")))[0]
                                if id == lastid:
                                    continue
                            except BaseException:
                                continue
                        with open(filename_out, 'wb') as fout:
                            try:
                                fout.write(struct.pack('L', id))
                                ret, data = self._connector.read()
                                fout.write(struct.pack('L', len(data)))
                                if ret == OpenRTM_aist.BufferStatus.BUFFER_OK:
                                    fout.write(data)
                                    lastid = id
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


testifpull_option = [
    "filename_in.__value__", "test_in.dat",
    "filename_in.__widget__", "text",
    "filename_in.__constraint__", "none",
    "filename_out.__value__", "test_out.dat",
    "filename_out.__widget__", "text",
    "filename_out.__constraint__", "none",
    ""
]


def TestOutPortProviderInit():
    prop = OpenRTM_aist.Properties(defaults_str=testifpull_option)
    factory = OpenRTM_aist.OutPortProviderFactory.instance()
    factory.addFactory("testif",
                       TestOutPortProvider,
                       prop)
