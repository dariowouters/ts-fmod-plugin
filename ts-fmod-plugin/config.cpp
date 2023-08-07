#include "pch.h"
#include "config.h"

config::config(const scs_log_t scs_log, const std::filesystem::path& config_file_path) : scs_log_(scs_log),
    config_path_(config_file_path)
{
}

template <typename T>
bool config::read_value(const json& j, const char* key, T* out_value) const
{
    try
    {
        *out_value = j[key].get<T>();
    }
    catch (...)
    {
        std::stringstream ss;
        ss << "[ts-fmod-plugin] Could not read config value '" << key << "', using default value '" << *out_value <<
            "'";
        scs_log_(SCS_LOG_TYPE_error, ss.str().c_str());
        return false;
    }

    return true;
}

// version 1 sound volumes were divided by 2, from v2 this is no longer the case,
// so save the halved values to the file so volumes from the plugin stay the same as before.
void config::upgrade_to_v2(const json& j)
{
    read_value(j, "master", &master);
    read_value(j, "engine", &engine);
    read_value(j, "exhaust", &exhaust);
    read_value(j, "turbo", &turbo);
    read_value(j, "interior", &interior);
    if (read_value(j, "navigation", &navigation))
    {
        navigation /= 2;
    }
    read_value(j, "exterior_when_windows_closed", &windows_closed);
    master /= 2;
    engine /= 2;
    exhaust /= 2;
    turbo /= 2;
    interior /= 2;
    windows_closed /= 2;

    save_config();
}

bool config::load_config()
{
    if (!exists(config_path_))
    {
        scs_log_(SCS_LOG_TYPE_error, "[ts-fmod-plugin] Could not find the 'sound_levels.txt' file");
        return false;
    }

    std::ifstream sound_levels_file(config_path_);
    std::string line;

    if (!sound_levels_file.is_open())
    {
        scs_log_(SCS_LOG_TYPE_error, "[ts-fmod-plugin] Could not read the 'sound_levels.txt' file");
        return false;
    }

    json j;

    try
    {
        sound_levels_file >> j;
    }
    catch (json::parse_error&)
    {
        scs_log_(SCS_LOG_TYPE_error, "[ts-fmod-plugin] Could not parse JSON from 'sound_levels.txt'");
        return false;
    }

    if (!read_value(j, "config_version", &version) || version < current_config_version_)
    {
        scs_log_(SCS_LOG_TYPE_message,
                 "[ts-fmod-plugin] Found older 'sound_levels.txt' version, upgrading to newer version");
        upgrade_to_v2(j);
    }
    else
    {
        if (
            !read_value(j, "master", &master) ||
            !read_value(j, "engine", &engine) ||
            !read_value(j, "exhaust", &exhaust) ||
            !read_value(j, "turbo", &turbo) ||
            !read_value(j, "interior", &interior) ||
            !read_value(j, "navigation", &navigation) ||
            !read_value(j, "exterior_when_windows_closed", &windows_closed))
        {
            scs_log_(SCS_LOG_TYPE_warning,
                     "[ts-fmod-plugin] Found an incorrect setting in 'sound_levels.txt' file, resetting its value to default");
            save_config();
        }
    }


    return true;
}

bool config::save_config()
{
    scs_log_(SCS_LOG_TYPE_message, "[ts-fmod-plugin] Saving the 'sound_levels.txt' file...");

    std::ofstream sound_levels_file(config_path_, std::ios::trunc);

    if (!sound_levels_file.is_open())
    {
        scs_log_(SCS_LOG_TYPE_error, "[ts-fmod-plugin] Could not open the 'sound_levels.txt' file to write to.");
        return false;
    }

    const nlohmann::ordered_json j = {

        {"master", master},
        {"engine", engine},
        {"exhaust", exhaust},
        {"turbo", turbo},
        {"interior", interior},
        {"navigation", navigation},
        {"exterior_when_windows_closed", windows_closed},
        {"config_version", version},
    };

    sound_levels_file << j.dump(4);
    sound_levels_file.close();

    return true;
}
