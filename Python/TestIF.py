#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-


import TestInPortConsumer
import TestInPortProvider
import TestOutPortConsumer
import TestOutPortProvider


def TestIFInit(mgr):
    TestInPortConsumer.TestInPortConsumerInit()
    TestInPortProvider.TestInPortProviderInit()
    TestOutPortConsumer.TestOutPortConsumerInit()
    TestOutPortProvider.TestOutPortProviderInit()
