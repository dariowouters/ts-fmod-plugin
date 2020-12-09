#pragma once
class fmod_event
{
    FMOD_GUID guid_ {};
    FMOD::Studio::EventDescription* event_desc_ = nullptr;
    FMOD::Studio::EventInstance* event_instance_ = nullptr;
    FMOD::Studio::System *fmod_system_ = nullptr;

    FMOD_RESULT load_event_description();

public:
    fmod_event(FMOD::Studio::System* fmod_system, const std::string& s_guid);
    FMOD_RESULT create_event_instance();
    FMOD_RESULT get_instance(FMOD::Studio::EventInstance** inst);
    FMOD_RESULT set_parameter_by_name(const char* name, float value) const;
    FMOD_RESULT start() const;
    FMOD_RESULT stop(FMOD_STUDIO_STOP_MODE mode) const;
    FMOD_RESULT set_volume(float value) const;
    FMOD_RESULT get_playback_state(FMOD_STUDIO_PLAYBACK_STATE* state) const;
};

