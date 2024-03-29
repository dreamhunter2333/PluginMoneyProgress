﻿#include "pch.h"
#include "DataManager.h"

CDataManager CDataManager::m_instance;

CDataManager::CDataManager()
{
}

CDataManager::~CDataManager()
{
    SaveConfig();
}

CDataManager& CDataManager::Instance()
{
    return m_instance;
}

void CDataManager::LoadConfig(const std::wstring& config_dir)
{
    //获取模块的路径
    HMODULE hModule = reinterpret_cast<HMODULE>(&__ImageBase);
    wchar_t path[MAX_PATH];
    GetModuleFileNameW(hModule, path, MAX_PATH);
    std::wstring module_path = path;
    m_config_path = module_path;
    if (!config_dir.empty())
    {
        size_t index = module_path.find_last_of(L"\\/");
        //模块的文件名
        std::wstring module_file_name = module_path.substr(index + 1);
        m_config_path = config_dir + module_file_name;
    }
    m_config_path += L".ini";
    m_setting_data.show_second = GetPrivateProfileInt(_T("config"), _T("show_second"), 0, m_config_path.c_str());
    GetPrivateProfileString(L"config", L"start_time", L"09:00", m_setting_data.start_time.GetBuffer(MAX_PATH), MAX_PATH, m_config_path.c_str());
    GetPrivateProfileString(L"config", L"end_time", L"18:00", m_setting_data.end_time.GetBuffer(MAX_PATH), MAX_PATH, m_config_path.c_str());
    GetPrivateProfileString(L"config", L"day_money", L"500", m_setting_data.day_money.GetBuffer(MAX_PATH), MAX_PATH, m_config_path.c_str());
}

static void WritePrivateProfileInt(const wchar_t* app_name, const wchar_t* key_name, int value, const wchar_t* file_path)
{
    wchar_t buff[16];
    swprintf_s(buff, L"%d", value);
    WritePrivateProfileString(app_name, key_name, buff, file_path);
}

void CDataManager::SaveConfig() const
{
    WritePrivateProfileInt(_T("config"), _T("show_second"), m_setting_data.show_second, m_config_path.c_str());
    WritePrivateProfileString(L"config", L"start_time", m_setting_data.start_time, m_config_path.c_str());
    WritePrivateProfileString(L"config", L"end_time", m_setting_data.end_time, m_config_path.c_str());
    WritePrivateProfileString(L"config", L"day_money", m_setting_data.day_money, m_config_path.c_str());
}

const CString& CDataManager::StringRes(UINT id)
{
    auto iter = m_string_table.find(id);
    if (iter != m_string_table.end())
    {
        return iter->second;
    }
    else
    {
        AFX_MANAGE_STATE(AfxGetStaticModuleState());
        m_string_table[id].LoadString(id);
        return m_string_table[id];
    }
}
