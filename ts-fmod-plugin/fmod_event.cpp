#include "pch.h"
#include "fmod_event.h"

const FMOD_RESULT fmod_event::load_event_description()
{
    if (event_desc_ == nullptr)
    {
        return fmod_system_->getEventByID(&guid_, &event_desc_);
    }
    return FMOD_ERR_EVENT_ALREADY_LOADED;
}

fmod_event::fmod_event(FMOD::Studio::System *fmod_system, std::string s_guid)
{
    fmod_system_ = fmod_system;
    sscanf_s(s_guid.c_str(),
        "{%8x-%4hx-%4hx-%2hhx%2hhx-%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx}",
        &guid_.Data1, &guid_.Data2, &guid_.Data3,
        &guid_.Data4[0], &guid_.Data4[1], &guid_.Data4[2], &guid_.Data4[3],
        &guid_.Data4[4], &guid_.Data4[5], &guid_.Data4[6], &guid_.Data4[7]);
}

const FMOD_RESULT fmod_event::create_event_instance()
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

const FMOD_RESULT fmod_event::get_instance(FMOD::Studio::EventInstance** inst)
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

const FMOD_RESULT fmod_event::set_parameter_by_name(const char* name, float value)
{
    if (event_instance_ == nullptr) return FMOD_ERR_NOTREADY;
    return event_instance_->setParameterByName(name, value);
}
const FMOD_RESULT fmod_event::start()
{
    if (event_instance_ == nullptr) return FMOD_ERR_NOTREADY;
    return event_instance_->start();
}
const FMOD_RESULT fmod_event::stop(FMOD_STUDIO_STOP_MODE mode)
{
    if (event_instance_ == nullptr) return FMOD_ERR_NOTREADY;
    return event_instance_->stop(mode);
}
const FMOD_RESULT fmod_event::set_volume(float value)
{
    if (event_instance_ == nullptr) return FMOD_ERR_NOTREADY;
    return event_instance_->setVolume(value);
}

const FMOD_RESULT fmod_event::get_playback_state(FMOD_STUDIO_PLAYBACK_STATE* state)
{
    if (event_instance_ == nullptr) return FMOD_ERR_NOTREADY;
    return event_instance_->getPlaybackState(state);
}