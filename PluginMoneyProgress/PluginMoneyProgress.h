#pragma once
#include "PluginInterface.h"
#include "PluginProgress.h"

class PluginMoneyProgress : public ITMPlugin
{
private:
    PluginMoneyProgress();

public:
    static PluginMoneyProgress& Instance();

    // 通过 ITMPlugin 继承
    virtual IPluginItem* GetItem(int index) override;
    virtual void DataRequired() override;
    virtual const wchar_t* GetInfo(PluginInfoIndex index) override;
    virtual OptionReturn ShowOptionsDialog(void* hParent) override;
    virtual void OnExtenedInfo(ExtendedInfoIndex index, const wchar_t* data) override;

private:
    CPluginProgress m_system_time;

    static PluginMoneyProgress m_instance;
};

#ifdef __cplusplus
extern "C" {
#endif
    __declspec(dllexport) ITMPlugin* TMPluginGetInstance();

#ifdef __cplusplus
}
#endif
