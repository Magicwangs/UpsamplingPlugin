# -*- coding: utf-8 -*-

import tensorrt as trt

TRT_LOGGER = trt.Logger()
trt.init_libnvinfer_plugins(TRT_LOGGER, '')
PLUGIN_CREATORS = trt.get_plugin_registry().plugin_creator_list

for plugin_creator in PLUGIN_CREATORS:
    print(plugin_creator.name)
