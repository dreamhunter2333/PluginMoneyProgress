#include "pch.h"
#include <wchar.h>
#include "PluginProgress.h"
#include "DataManager.h"

CPluginProgress::CPluginProgress()
{
}

const wchar_t* CPluginProgress::GetItemName() const
{
    return CDataManager::Instance().StringRes(IDS_MONEY);
}

const wchar_t* CPluginProgress::GetItemId() const
{
    return L"PluginMoneyProgress";
}

const wchar_t* CPluginProgress::GetItemLableText() const
{
    if (CDataManager::Instance().m_end) {
        return L"今日到手";
    }
    return CDataManager::Instance().StringRes(IDS_MONEY);
}

const wchar_t* CPluginProgress::GetItemValueText() const
{
    return CDataManager::Instance().m_money.c_str();
}

const wchar_t* CPluginProgress::GetItemValueSampleText() const
{
    return L"500 元";
}
