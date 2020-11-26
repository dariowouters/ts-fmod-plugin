#include "pch.h"
#include "fmod_event_manager.h"

fmod_event_manager::fmod_event_manager() {

}

void fmod_event_manager::set_paused(bool state) {
    FMOD::Studio::EventInstance* event_inst;
    for (auto& event_item : fmod_events_map_)
    {
        event_item.second.get_instance(&event_inst);
        event_inst->setPaused(state);
    }
}

std::unique_ptr<fmod_event> fmod_event_manager::get_event(std::string name) {
    auto res = fmod_events_map_.find(name);
    if (res == fmod_events_map_.end()) {
        return nullptr;
    }
    return std::make_unique<fmod_event>(res->second);
}

void fmod_event_manager::add_event(std::string name, fmod_event event) {
    fmod_events_map_.insert(std::make_pair(name, event));
}