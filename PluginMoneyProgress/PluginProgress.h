#pragma once
#include "PluginInterface.h"

class CPluginProgress: public IPluginItem
{
public:
    CPluginProgress();

public:
    // 通过 IPluginItem 继承
    virtual const wchar_t* GetItemName() const override;
    virtual const wchar_t* GetItemId() const override;
    virtual const wchar_t* GetItemLableText() const override;
    virtual const wchar_t* GetItemValueText() const override;
    virtual const wchar_t* GetItemValueSampleText() const override;

private:
};
