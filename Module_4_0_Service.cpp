#include "MicroBitConfig.h"
#include "Module_4_0_Service.h"
#include "CryptTool.h"

static uint8_t _ctxValue = 0x25; // CTXValue for Encryption
static uint8_t _addressArray[5]     = { 0xC1, 0xC2, 0xC3, 0xC4, 0xC5 };
static uint8_t _telegram_Connect[8] = { 0xAD, 0x7B, 0xA7, 0x80, 0x80, 0x80, 0x4F, 0x52, };


/**
 * Constructor.
 * Create a representation of the Module_4_0_Service
 * @param _BLEAdvManager The instance of a BLEAdvManager that we're running on.
 */
Module_4_0_Service::Module_4_0_Service(BLEAdvManager &_BLEAdvManager) : 
    m_bleAdvManager(_BLEAdvManager)
{

    m_bleAdvManager_handle = m_bleAdvManager.register_client(this);

    reset();
}


/**
 *  reset internal data to defaults
 */
void Module_4_0_Service::reset() 
{
    m_zeroHysteresisBounds_abs_pct = ZERO_HYSTERESIS_BOUNDS_DEFAULT;

    for (uint8_t index = 0; index < CHANNEL_COUNT; index++)
    {
        m_channelOffsets_abs_pct[index] = CHANNEL_OFFSET_DEFAULT;
        m_channelMaximums_abs_pct[index] = CHANNEL_MAXIMUM_DEFAULT;
        m_channelReverse [index] = CHANNEL_REVERSE_DEFAULT;
    }

    for (uint8_t index = 0; index < SETVALUE_ARRAY_SIZE; index++)
    {
        m_channelValues_nibble[index] = CHANNEL_ZERO_VALUE;
    }
}


/**
 *  set _telegram_Connect to advertiser
 */
void Module_4_0_Service::connect() 
{
    if (m_bleAdvManager_handle != UNSET_HANDLE) 
    {
        // MICROBIT_DEBUG_DMESG("Module_4_0_Service::connect");

        get_rf_payload(_addressArray, 5, _telegram_Connect, 8, _ctxValue, m_pPayload);

        m_bleAdvManager.advertise(m_bleAdvManager_handle, m_pPayload);
    }
}


/**
 *  stop advertising
 */
void Module_4_0_Service::stopAdvertising() 
{
    m_bleAdvManager.advertise_stop(m_bleAdvManager_handle);
}


/**
 *  set data to advertiser
 */
void Module_4_0_Service::setData() 
{
    if (m_bleAdvManager_handle != UNSET_HANDLE) 
    {
        memcpy(&m_telegram_Data[3], m_channelValues_nibble, sizeof(uint8_t) * 6);

        get_rf_payload(_addressArray, 5, m_telegram_Data, 10, _ctxValue, m_pPayload);

        m_bleAdvManager.advertise(m_bleAdvManager_handle, m_pPayload);
    }
}


/**
 *  set value (in percent) of channel
 * @param channelNo [0..5]
 * @param value_pct [0..100], eg: "80"
 */
void Module_4_0_Service::setChannelValue(uint8_t channelNo, float value_pct) 
{
    // MICROBIT_DEBUG_DMESG("Module_4_0_Service::setChannel");

     // check 
    if (channelNo >= CHANNEL_COUNT)
    {
        return;
    }
   
    // revert input
    if (m_channelReverse[channelNo])
    {
        value_pct *= -1;
    }

    bool isOdd = (channelNo & 0x01) == 0x01; // is odd
    uint8_t channelOffset = channelNo >> 1;  // div 2
    uint8_t originValue_byte = m_channelValues_nibble[channelOffset];
    uint8_t setValue_nibble = 0x00;

    if (value_pct >= -m_zeroHysteresisBounds_abs_pct && // is value_pct inside m_isZero_hysteresis_pct?
        value_pct <= m_zeroHysteresisBounds_abs_pct) 
    {
        setValue_nibble = 0x08;
    }
    else if (value_pct < 0) 
    {
        float result_abs_pct = fmin(-value_pct + m_channelOffsets_abs_pct[channelNo], m_channelMaximums_abs_pct[channelNo]);
        float result_abs = fmin(0x07, result_abs_pct * 0x07 / 100.0);

        setValue_nibble = 0x0F & (uint8_t)result_abs;
    }
    else 
    {
        float result_abs_pct = fmin(value_pct + m_channelOffsets_abs_pct[channelNo], m_channelMaximums_abs_pct[channelNo]);
        float result_abs = fmin(0x07, result_abs_pct * 0x07 / 100.0);

        setValue_nibble = 0x0F & (uint8_t)(result_abs + 0x08);
    }

    if (isOdd)
    {
        originValue_byte = (originValue_byte & 0xF0) + setValue_nibble;
    }
    else
    {
        originValue_byte = (originValue_byte & 0x0F) + (setValue_nibble << 4);
    }

    m_channelValues_nibble[channelOffset] = originValue_byte;
}


/**
 *  get channel value in percent
 * @param channelNo [0..3]
 */
float Module_4_0_Service::getChannelValue(uint8_t channelNo) 
{
     // check 
    if (channelNo >= CHANNEL_COUNT)
    {
        return 0.0;
    }

    bool isOdd = (channelNo & 0x01) == 0x01; // is odd
    uint8_t channelOffset = channelNo >> 1;  // div 2
    uint8_t originValue_byte = m_channelValues_nibble[channelOffset];

    uint8_t setValue_nibble;

    if (isOdd)
    {
        setValue_nibble = originValue_byte & 0x0F;
    }
    else
    {
        setValue_nibble = (originValue_byte >> 4) & 0x0F;
    }

    if (setValue_nibble == 0x08)
    {
        return 0.0;
    }
    else if (setValue_nibble > 0x08)
    {
        return (float)(setValue_nibble - 0x08) * 100.0 / 0x07;
    }
    else
    {
        return (float)setValue_nibble * 100.0 / 0x07;
    }
}


/**
 *  set offset (in percent) of channel
 * @param channelNo [0..5]
 * @param offset_pct [0..100], eg: "80"
 */
void Module_4_0_Service::setChannelOffset(uint8_t channelNo, float offset_pct) 
{
     // check 
    if (channelNo >= CHANNEL_COUNT)
    {
        return;
    }

    float offset_abs_pct = fabsf(offset_pct);

    if (m_channelOffsets_abs_pct[channelNo] != offset_abs_pct)
    {
        m_channelOffsets_abs_pct[channelNo] = offset_abs_pct;

        float value_pct = getChannelValue(channelNo);   // get current value
        float value_abs_pct = fabsf(value_pct);

        if (value_abs_pct < offset_abs_pct)             // new offset is greater than old one
        {
            setChannelValue(channelNo, value_pct);      // set value
        }
    }
}


/**
 *  set maximum value (in percent) of channel
 * @param channelNo [0..3]
 * @param maximum_pct [0..100], eg: "80"
 */
void Module_4_0_Service::setChannelMax(uint8_t channelNo, float maximum_pct) 
{
     // check 
    if (channelNo >= CHANNEL_COUNT)
    {
        return;
    }

    float maximum_abs_pct = fabsf(maximum_pct);

    if (m_channelMaximums_abs_pct[channelNo] != maximum_abs_pct)
    {
        m_channelMaximums_abs_pct[channelNo] = maximum_abs_pct;

        float value_pct = getChannelValue(channelNo);   // get current value
        float value_abs_pct = fabsf(value_pct);

        if (maximum_abs_pct < value_abs_pct)            // new maximum ist smaller than old one
        {
            setChannelValue(channelNo, value_pct);      // set value
        }
    }
}


/**
 *  set channel reverse
 * @param channelNo [0..3]
 * @param reverse [true, false], eg: "false"
 */
void Module_4_0_Service::setChannelReverse(uint8_t channelNo, bool reverse) 
{
     // check 
    if (channelNo >= CHANNEL_COUNT)
    {
        return;
    }

    if (m_channelReverse[channelNo] != reverse)
    {
        m_channelReverse[channelNo] = reverse;

        float value_pct = getChannelValue(channelNo);   // get current value
        setChannelValue(channelNo, -value_pct);         // set reverted value
    }
}


/**
 *  set bound value (in percent) zero hysteresis
 * @param zeroHysteresisBounds_pct default: 1.0
 */
void Module_4_0_Service::setZeroHysteresis(float zeroHysteresisBounds_pct) 
{
    m_zeroHysteresisBounds_abs_pct = fabsf(zeroHysteresisBounds_pct);
}


uint8_t Module_4_0_Service::getVersion() 
{
    return this->m_bleAdvManager_handle;
}
