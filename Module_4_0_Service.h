#ifndef MODULE_4_0_SERVICE_H
#define MODULE_4_0_SERVICE_H

#include "MicroBitConfig.h"
#include "pxt.h"
#include "BLEAdvManager.h"

#define CHANNEL_COUNT 12                    // number of channels
#define SETVALUE_ARRAY_SIZE 6               // size of setvalue array
#define ZERO_HYSTERESIS_BOUNDS_DEFAULT 1.0  // default value of iszero hysteresis
#define CHANNEL_OFFSET_DEFAULT 0.0          // default  of channel offset hysteresis
#define CHANNEL_MAXIMUM_DEFAULT 100.0       // default of channel maximum value
#define CHANNEL_REVERSE_DEFAULT false       // default of channel reverse value
#define CHANNEL_ZERO_VALUE 0x88             // means stop

class Module_4_0_Service : public IBLEAdvClient
{
    public:
    /**
      * Constructor.
      * Create a representation of the Module_4_0_Service
      * @param _BLEAdvManager The instance of a BLEAdvManager that we're running on.
      */
    Module_4_0_Service(BLEAdvManager &_BLEAdvManager);

    /**
     *  set _telegram_Connect to advertiser
     */
    void connect();

    /**
     *  stop advertising
     */
    void stopAdvertising();

    /**
     *  reset internal data to defaults
     */
    void reset();

    /**
     *  set data to advertiser
     */
    void setData();

    /**
     *  set value (in percent) of channel
     * @param channelNo [0..5]
     * @param value_pct [0..100], eg: "80"
     */
    void setChannelValue(uint8_t channelNo, float value_pct);

    /**
     *  set offset (in percent) of channel
     * @param channelNo [0..5]
     * @param offset_pct [0..100], eg: "80"
     */
    void setChannelOffset(uint8_t channelNo, float offset_pct);

    /**
     *  set maximum value (in percent) of channel
     * @param channelNo [0..5]
     * @param maximum_pct [0..100], eg: "80"
     */
    void setChannelMax(uint8_t channelNo, float maximum_pct);

    /**
     *  set channel reverse
     * @param channelNo [0..3]
     * @param reverse [true, false], eg: "false"
     */
    void setChannelReverse(uint8_t channelNo, bool reverse);

    /**
     *  set bound value (in percent) zero hysteresis
     * @param zeroHysteresisBounds_pct default: 1.0
     */
    void setZeroHysteresis(float zeroHysteresis_pct);

    /**
     *  get channel value in percent
     * @param channelNo [0..3]
     */
    float getChannelValue(uint8_t channelNo);

    uint8_t getVersion();

  private:

    // advertising manager
    BLEAdvManager &m_bleAdvManager;
    
    // handle from bleAdvManager returned on registration
    uint8_t m_bleAdvManager_handle;

    // left/right border in percent of a hysteresis taking a setvalue as zero
    float m_zeroHysteresisBounds_abs_pct = ZERO_HYSTERESIS_BOUNDS_DEFAULT;

    // array of channel specific offsets in percent beeing added to a channels setvalue (to finetune)
    float m_channelOffsets_abs_pct[CHANNEL_COUNT] = {
        CHANNEL_OFFSET_DEFAULT, CHANNEL_OFFSET_DEFAULT, CHANNEL_OFFSET_DEFAULT, CHANNEL_OFFSET_DEFAULT, CHANNEL_OFFSET_DEFAULT, CHANNEL_OFFSET_DEFAULT,
        CHANNEL_OFFSET_DEFAULT, CHANNEL_OFFSET_DEFAULT, CHANNEL_OFFSET_DEFAULT, CHANNEL_OFFSET_DEFAULT, CHANNEL_OFFSET_DEFAULT, CHANNEL_OFFSET_DEFAULT };

    // array of channel specific maximums in percent to limit a channels setvalue (to finetune)
    float m_channelMaximums_abs_pct[CHANNEL_COUNT] = {
        CHANNEL_MAXIMUM_DEFAULT, CHANNEL_MAXIMUM_DEFAULT, CHANNEL_MAXIMUM_DEFAULT, CHANNEL_MAXIMUM_DEFAULT, CHANNEL_MAXIMUM_DEFAULT, CHANNEL_MAXIMUM_DEFAULT, 
        CHANNEL_MAXIMUM_DEFAULT, CHANNEL_MAXIMUM_DEFAULT, CHANNEL_MAXIMUM_DEFAULT, CHANNEL_MAXIMUM_DEFAULT, CHANNEL_MAXIMUM_DEFAULT, CHANNEL_MAXIMUM_DEFAULT };

    // array of channel specific maximums in percent to limit a channels setvalue (to finetune)
    bool m_channelReverse[CHANNEL_COUNT] = {
      CHANNEL_REVERSE_DEFAULT, CHANNEL_REVERSE_DEFAULT, CHANNEL_REVERSE_DEFAULT, CHANNEL_REVERSE_DEFAULT, CHANNEL_REVERSE_DEFAULT, CHANNEL_REVERSE_DEFAULT, 
      CHANNEL_REVERSE_DEFAULT, CHANNEL_REVERSE_DEFAULT, CHANNEL_REVERSE_DEFAULT, CHANNEL_REVERSE_DEFAULT, CHANNEL_REVERSE_DEFAULT, CHANNEL_REVERSE_DEFAULT };

  // array of absolute (finetuned) setvalues to be sent - one nibble per channel
    uint8_t m_channelValues_nibble[SETVALUE_ARRAY_SIZE] = {
        CHANNEL_ZERO_VALUE, CHANNEL_ZERO_VALUE, CHANNEL_ZERO_VALUE, CHANNEL_ZERO_VALUE, CHANNEL_ZERO_VALUE, CHANNEL_ZERO_VALUE, };

    uint8_t m_pPayload[31] = {
        0x02, // length: 0x2 (2)
        0x01, // type:   flags (0x01)
        0x06, // 0x06,

        0x1b, // length: 0x1b (27)
        0xff, // type:   manufacturer specific (0xff)
        0xf0, 0xff, // company Id: unkown 0xfff0
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
      };
      
      uint8_t m_telegram_Data[10] = { 
        0x7D, 0x7B, 0xA7, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x82 }; // connect
};

#endif // MODULE_4_0_SERVICE_H