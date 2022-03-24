#pragma once
#include <string>
#include <map>

#define g_data CDataManager::Instance()

struct SettingData
{
    bool show_second{};
    CString start_time{};
    CString end_time{};
    CString day_money{};
};

class CDataManager
{
private:
    CDataManager();
    ~CDataManager();

public:
    static CDataManager& Instance();

    void LoadConfig(const std::wstring& config_dir);
    void SaveConfig() const;
    const CString& StringRes(UINT id);      //根据资源id获取一个字符串资源

public:
    std::wstring m_cur_time;
    std::wstring m_cur_date;
    std::wstring m_money;
    bool m_end;
    SYSTEMTIME m_system_time;
    SettingData m_setting_data;

private:
    static CDataManager m_instance;
    std::wstring m_config_path;
    std::map<UINT, CString> m_string_table;
};
