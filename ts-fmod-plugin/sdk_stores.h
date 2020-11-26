#pragma once

/**
 * @brief Bool storage callback.
 *
 * Can be used together with SCS_TELEMETRY_CHANNEL_FLAG_no_value in which case it
 * will store zero if the value is not available.
 */
SCSAPI_VOID telemetry_store_bool(const scs_string_t name, const scs_u32_t index, const scs_value_t* const value,
    const scs_context_t context)
{
    assert(context);
    const auto storage = static_cast<char*>(context);

    if (value)
    {
        assert(value->type == SCS_VALUE_TYPE_bool);
        *storage = value->value_bool.value;
    }
    else
    {
        *storage = 0;
    }
}
/**
 * @brief Float storage callback.
 *
 * Can be used together with SCS_TELEMETRY_CHANNEL_FLAG_no_value in which case it
 * will store zero if the value is not available.
 */
SCSAPI_VOID telemetry_store_float(const scs_string_t name, const scs_u32_t index, const scs_value_t* const value,
    const scs_context_t context)
{
    assert(context);
    const auto storage = static_cast<scs_float_t*>(context);

    if (value)
    {
        assert(value->type == SCS_VALUE_TYPE_float);
        *storage = value->value_float.value;
    }
    else
    {
        *storage = 0.0f;
    }
}
/**
 * @brief s32 storage callback.
 *
 * Can be used together with SCS_TELEMETRY_CHANNEL_FLAG_no_value in which case it
 * will store zero if the value is not available.
 */
SCSAPI_VOID telemetry_store_s32(const scs_string_t name, const scs_u32_t index, const scs_value_t* const value,
    const scs_context_t context)
{
    assert(context);
    const auto storage = static_cast<scs_s32_t*>(context);

    if (value)
    {
        assert(value->type == SCS_VALUE_TYPE_s32);
        *storage = value->value_s32.value;
    }
    else
    {
        *storage = 0;
    }
}

/**
 * @brief u32 storage callback.
 *
 * Can be used together with SCS_TELEMETRY_CHANNEL_FLAG_no_value in which case it
 * will store zero if the value is not available.
 */
SCSAPI_VOID telemetry_store_u32(const scs_string_t name, const scs_u32_t index, const scs_value_t* const value,
    const scs_context_t context)
{
    assert(context);
    const auto storage = static_cast<scs_u32_t*>(context);

    if (value)
    {
        assert(value->type == SCS_VALUE_TYPE_u32);
        *storage = value->value_u32.value;
    }
    else
    {
        *storage = 0;
    }
}

/**
 * @brief Placement storage callback.
 *
 * Can be used together with SCS_TELEMETRY_CHANNEL_FLAG_no_value in which case it
 * will store zeros if the value is not available.
 */
SCSAPI_VOID telemetry_store_fplacement(const scs_string_t name, const scs_u32_t index, const scs_value_t* const value,
    const scs_context_t context)
{
    assert(context);
    const auto storage = static_cast<scs_value_fplacement_t*>(context);

    if (value)
    {
        assert(value->type == SCS_VALUE_TYPE_fplacement);
        *storage = value->value_fplacement;
    }
    else
    {
        storage->position.x = 0.0;
        storage->position.y = 0.0;
        storage->position.z = 0.0;
        storage->orientation.heading = 0.0f;
        storage->orientation.pitch = 0.0f;
        storage->orientation.roll = 0.0f;
    }
}