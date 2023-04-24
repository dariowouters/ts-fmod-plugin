#pragma once
#include <scssdk/scssdk.h>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

#include "fmod_event.h"

struct sound_levels_t {
    float master = 0.40f;
    float engine = 0.45f;
    float exhaust = 0.45f;
    float turbo = 0.35f;
    float interior = 0.5f;
    float windows_closed = 0.35f;
};

class fmod_manager
{
    FMOD::System* core_system_ = nullptr;
    FMOD::Studio::System* system_ = nullptr;
    std::vector<std::string> selected_bank_names_;

    scs_log_t scs_log_;

    std::unordered_map<std::string, fmod_event> fmod_events_map_;
    std::unordered_map<std::string, FMOD::Studio::Bus*> fmod_busses_map_;


    bool load_selected_bank(const std::string& plugin_files_dir);
    bool init_channels(const std::string& plugin_files_dir);

    float get_sound_level_from_json(json j, const char* key, float defaultValue);
    bool load_sound_levels(const std::string& plugin_files_dir);

public:
    sound_levels_t sound_levels;

    explicit fmod_manager(scs_log_t scs_log);
    ~fmod_manager();

    bool init();

    void add_event(const char*, fmod_event event);
    void add_bus(const char* name, FMOD::Studio::Bus* bus);
    std::unique_ptr<fmod_event> get_event(const char* name);
    FMOD::Studio::Bus* get_bus(const char* name);

    void set_paused(bool state);
    FMOD_RESULT update() const;
    FMOD_RESULT set_global_parameter(const char* param_name, float value) const;
    FMOD_RESULT set_event_parameter(const char* event_name, const char* param_name, float value);
    FMOD_RESULT set_event_state(const char* event_name, bool state, bool only_when_event_stopped = false);
    FMOD_RESULT set_bus_volume(const char* bus_name, float value);
    FMOD_RESULT pause_bus(const char* bus_name, bool state);
};

