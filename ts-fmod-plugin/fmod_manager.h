#pragma once
#include <scssdk/scssdk.h>

#include "fmod_event.h"

class fmod_manager
{
    FMOD::Studio::System* system_ = nullptr;
    FMOD::Studio::Bank* sound_bank_ = nullptr;
    std::string selected_bank_name_ = "";

    scs_log_t scs_log_;

    std::unordered_map<std::string, fmod_event> fmod_events_map_;
    std::unordered_map<std::string, FMOD::Studio::Bus*> fmod_busses_map_;


    bool load_selected_bank(const std::string& plugin_files_dir);
    bool init_channels(const std::string& plugin_files_dir);

public:
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

