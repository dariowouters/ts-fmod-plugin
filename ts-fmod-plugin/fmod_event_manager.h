#pragma once

class fmod_event_manager
{
    std::unordered_map<std::string, fmod_event> fmod_events_map_;

public:
    fmod_event_manager();

    void add_event(std::string name, fmod_event event);
    std::unique_ptr<fmod_event> get_event(std::string name);

    void set_paused(bool state);
};

