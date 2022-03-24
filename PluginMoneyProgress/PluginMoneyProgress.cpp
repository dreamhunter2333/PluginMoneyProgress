#include "pch.h"
#include "PluginMoneyProgress.h"
#include "DataManager.h"
#include "OptionsDlg.h"

PluginMoneyProgress PluginMoneyProgress::m_instance;

PluginMoneyProgress::PluginMoneyProgress()
{
}

PluginMoneyProgress& PluginMoneyProgress::Instance()
{
    return m_instance;
}

IPluginItem* PluginMoneyProgress::GetItem(int index)
{
    switch (index)
    {
    case 0:
        return &m_system_time;
    default:
        break;
    }
    return nullptr;
}

void PluginMoneyProgress::DataRequired()
{
    //获取时间和日期
    SYSTEMTIME& system_time{ CDataManager::Instance().m_system_time };
    GetLocalTime(&system_time);
    wchar_t buff[128];
    std::string delimiter = ":";

    CString start_time = CDataManager::Instance().m_setting_data.start_time;
    std::wstring startTimeWStr(start_time);
    std::string startTimeStr(startTimeWStr.begin(), startTimeWStr.end());
 
    int start_hour = std::stoi(startTimeStr.substr(0, startTimeStr.find(delimiter)));
    int start_minute = std::stoi(startTimeStr.substr(startTimeStr.find(delimiter) + 1));

    CString end_time = CDataManager::Instance().m_setting_data.end_time;
    std::wstring endTimeWStr(end_time);
    std::string endTimeStr(endTimeWStr.begin(), endTimeWStr.end());
    int end_hour = std::stoi(endTimeStr.substr(0, endTimeStr.find(delimiter)));
    int end_minute = std::stoi(endTimeStr.substr(endTimeStr.find(delimiter) + 1));

    CString day_money = CDataManager::Instance().m_setting_data.day_money;
    std::wstring dayMoneyWStr(day_money);
    std::string dayMoneyStr(dayMoneyWStr.begin(), dayMoneyWStr.end());
    int dayMoneyInt = std::stoi(dayMoneyStr);

    if (
        system_time.wHour < start_hour || system_time.wHour > end_hour ||
        (system_time.wHour == start_hour && system_time.wMinute < start_minute) ||
        (system_time.wHour == end_hour && system_time.wMinute > end_minute)
    ){
        swprintf_s(buff, L"%d元", dayMoneyInt);
        CDataManager::Instance().m_money = buff;
        CDataManager::Instance().m_end = true;
        return;
    }

    CDataManager::Instance().m_end = false;
    int cur = (system_time.wHour - start_hour) * 60 * 60 + ( - start_minute) * 60 + system_time.wSecond;
    int all = (end_hour - start_hour) * 60 * 60 + (end_minute - start_minute) * 60;
    double money = ((double)cur * dayMoneyInt) / (double) all;
    swprintf_s(buff, L"%5.2f元", money);
    CDataManager::Instance().m_money = buff;
}

const wchar_t* PluginMoneyProgress::GetInfo(PluginInfoIndex index)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    static CString str;
    switch (index)
    {
    case TMI_NAME:
        str.LoadString(IDS_PLUGIN_NAME);
        return str.GetString();
    case TMI_DESCRIPTION:
        str.LoadString(IDS_PLUGIN_DESCRIPTION);
        return str.GetString();
    case TMI_AUTHOR:
        return L"Dreamhunter";
    case TMI_COPYRIGHT:
        return L"Copyright (C) by Dreamhunter 2022";
    case TMI_VERSION:
        return L"1.0";
    case ITMPlugin::TMI_URL:
        return L"https://github.com/jinmu333/PluginMoneyProgress";
        break;
    default:
        break;
    }
    return L"";
}

ITMPlugin::OptionReturn PluginMoneyProgress::ShowOptionsDialog(void* hParent)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    COptionsDlg dlg(CWnd::FromHandle((HWND)hParent));
    dlg.m_data = CDataManager::Instance().m_setting_data;
    if (dlg.DoModal() == IDOK)
    {
        CDataManager::Instance().m_setting_data = dlg.m_data;
        return ITMPlugin::OR_OPTION_CHANGED;
    }
    return ITMPlugin::OR_OPTION_UNCHANGED;
}


void PluginMoneyProgress::OnExtenedInfo(ExtendedInfoIndex index, const wchar_t* data)
{
    switch (index)
    {
    case ITMPlugin::EI_CONFIG_DIR:
        //从配置文件读取配置
        g_data.LoadConfig(std::wstring(data));

        break;
    default:
        break;
    }
}

ITMPlugin* TMPluginGetInstance()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return &PluginMoneyProgress::Instance();
}
