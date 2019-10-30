#ifndef UPSAMPLE_PLUGIN_H
#define UPSAMPLE_PLUGIN_H

#include "NvInferPlugin.h"
#include <string>
#include <vector>

using namespace nvinfer1;

class UpsamplePlugin : public IPluginV2Ext
{
public:
    UpsamplePlugin(const std::string name, int scale_factor = 2, bool align_corners = 0);

    UpsamplePlugin(const std::string name, const void *data, size_t length);

    // It doesn't make sense to make UpsamplePlugin without arguments, so we delete default constructor.
    UpsamplePlugin() = delete;

    int getNbOutputs() const override;

    Dims getOutputDimensions(int index, const Dims *inputs, int nbInputDims) override;

    int initialize() override;

    void terminate() override;

    size_t getWorkspaceSize(int) const override { return 0; };

    int enqueue(int batchSize, const void *const *inputs, void **outputs, void *workspace, cudaStream_t stream) override;

    size_t getSerializationSize() const override;

    void serialize(void *buffer) const override;

    void configurePlugin(const Dims *inputDims, int nbInputs, const Dims *outputDims, int nbOutputs, const DataType *type, const DataType *type2, const bool *inputIsBroadcast, const bool *outputIsBroadcast, PluginFormat format, int maxBatchSize) override;

    bool supportsFormat(DataType type, PluginFormat format) const override;

    const char *getPluginType() const override;

    const char *getPluginVersion() const override;

    void destroy() override;

    nvinfer1::IPluginV2Ext *clone() const override;

    void setPluginNamespace(const char *pluginNamespace) override;

    const char *getPluginNamespace() const override;

    DataType getOutputDataType(int index, const DataType *inputTypes, int nbInputs) const override
    {
        return inputTypes[0];
    }
    bool isOutputBroadcastAcrossBatch(int outputIndex, const bool *inputIsBroadcasted, int nbInputs) const override
    {
        return false;
    }

    bool canBroadcastInputAcrossBatch(int inputIndex) const override
    {
        return false;
    }

private:
    const std::string mLayerName;
    bool mAlignCorners;
    int mScaleFactor;
    size_t mInputVolume;
    DimsCHW mInputShape;
    std::string mNamespace;
};

class UpsamplePluginCreator : public IPluginCreator
{
public:
    UpsamplePluginCreator();

    const char *getPluginName() const override;

    const char *getPluginVersion() const override;

    const PluginFieldCollection *getFieldNames() override;

    IPluginV2Ext *createPlugin(const char *name, const PluginFieldCollection *fc) override;

    IPluginV2Ext *deserializePlugin(const char *name, const void *serialData, size_t serialLength) override;

    void setPluginNamespace(const char *pluginNamespace) override;

    const char *getPluginNamespace() const override;

private:
    static PluginFieldCollection mFC;
    static std::vector<PluginField> mPluginAttributes;
    std::string mNamespace;
};

#endif