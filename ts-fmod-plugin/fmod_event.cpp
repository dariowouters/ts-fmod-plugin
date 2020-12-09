#include "pch.h"
#include "fmod_event.h"

FMOD_RESULT fmod_event::load_event_description()
{
    if (event_desc_ == nullptr)
    {
        return fmod_system_->getEventByID(&guid_, &event_desc_);
    }
    return FMOD_ERR_EVENT_ALREADY_LOADED;
}

fmod_event::fmod_event(FMOD::Studio::System *fmod_system, const std::string& s_guid)
{
    fmod_system_ = fmod_system;
    guid_ = common::get_guid(s_guid);
}

FMOD_RESULT fmod_event::create_event_instance()
{
    FMOD_RESULT res = FMOD_OK;
    if (event_instance_ == nullptr)
    {
        if (event_desc_ == nullptr)
        {
            res = load_event_description();
            if (res != FMOD_OK) return res;
        }
        return event_desc_->createInstance(&event_instance_);
    }
    return res;
}

FMOD_RESULT fmod_event::get_instance(FMOD::Studio::EventInstance** inst)
{
    FMOD_RESULT res = FMOD_OK;
    if (event_instance_ == nullptr)
    {
        res = create_event_instance();
        if (res != FMOD_OK) return res;
    }
    *inst = event_instance_;
    return res;
}

FMOD_RESULT fmod_event::set_parameter_by_name(const char* name, float value) const
{
    if (event_instance_ == nullptr) return FMOD_ERR_NOTREADY;
    return event_instance_->setParameterByName(name, value);
}
FMOD_RESULT fmod_event::start() const
{
    if (event_instance_ == nullptr) return FMOD_ERR_NOTREADY;
    return event_instance_->start();
}
FMOD_RESULT fmod_event::stop(FMOD_STUDIO_STOP_MODE mode) const
{
    if (event_instance_ == nullptr) return FMOD_ERR_NOTREADY;
    return event_instance_->stop(mode);
}
FMOD_RESULT fmod_event::set_volume(float value) const
{
    if (event_instance_ == nullptr) return FMOD_ERR_NOTREADY;
    return event_instance_->setVolume(value);
}

FMOD_RESULT fmod_event::get_playback_state(FMOD_STUDIO_PLAYBACK_STATE* state) const
{
    if (event_instance_ == nullptr) return FMOD_ERR_NOTREADY;
    return event_instance_->getPlaybackState(state);
}
