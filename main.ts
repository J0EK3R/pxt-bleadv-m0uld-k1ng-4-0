/**
 * Support for M0uld K1ng Module 4.0.
 */
//% block="MK Module 4.0"
//% color=#0000e3 
//% weight=100 
//% icon="\uf294" 
namespace MK4 {
    export enum Module {
        //% block="MK4 1" 
        //% enumval=0
        M1 = 0,
        //% block="MK4 2" 
        //% enumval=1
        M2 = 1,
        //% block="MK4 3" 
        //% enumval=2
        M3 = 2,
    }


    export enum Channel {
        //% block="Channel A" 
        //% enumval=0
        A = 0,
        //% block="Channel B" 
        //% enumval=1
        B = 1,
        //% block="Channel C" 
        //% enumval=2
        C = 2,
        //% block="Channel D" 
        //& enumval=3
        D = 3,
    }


    /**
      *  initialisation of the module
      * @param module module, eg: "Module.M1"
      */
    //% blockId=mk4_init
    //% block="init $module"
    //% group="M0uld K1ng Module 4.0"
    //% shim=mk_module_4_0::init
    //% blockGap=8
    //% weight=60
    export function init(module: Module): void {
        return;
    }


    /**
     *  set value (in percent) of channel
     * @param module module, eg: "Module.M1"
     * @param channel channel, eg: "Channel.A"
     * @param value_pct [-100..100], eg: "0"
     */
    //% blockId=mk4_setchannel 
    //% block="set $module $channel to $value_pct"
    //% group="M0uld K1ng Module 4.0"
    //% shim=mk_module_4_0::setChannelValue
    //% value_pct.min=-100
    //% value_pct.max=100
    //% value_pct.defl=0
    //% blockGap=8 
    //% weight=60
    export function setChannel(module: Module, channel: Channel, value_pct: number): void {
        return;
    }


    /**
     *  set value (in percent) of channel and send
     * @param module module, eg: "Module.M1"
     * @param channel channel, eg: "Channel.A"
     * @param value_pct [-100..100], eg: "0"
     */
    //% blockId=mk4_setchannelandsend 
    //% block="send $module $channel to $value_pct"
    //% group="M0uld K1ng Module 4.0"
    //% value_pct.min=-100
    //% value_pct.max=100
    //% value_pct.defl=0
    //% blockGap=8 
    //% weight=60
    export function setChannelAndSend(module: Module, channel: Channel, value_pct: number): void {
        setChannel(module, channel, value_pct);
        sendData(module);
    }


    /**
     *  take over data to send
     * @param module module, eg: "Module.M1"
     */
    //% blockId=mk4_senddata 
    //% block="send $module data"
    //% group="M0uld K1ng Module 4.0"
    //% shim=mk_module_4_0::setData
    //% blockGap=8
    //% weight=60
    export function sendData(module: Module): void {
        return;
    }


    /**
     * stop advertising
     * @param module module, eg: "Module.M1"
     */
    //% blockId=mk4_stopadvertising
    //% block="stop $module advertising"
    //% group="M0uld K1ng Module 4.0"
    //% shim=mk_module_4_0::stopAdvertising
    //% blockGap=8
    //% weight=10
    export function stopAdvertising(module: Module): void {
        return;
    }


    /**
     *  set offset value (in percent) of channel
     * @param module module, eg: "Module.M1"
     * @param channel channel, eg: "Channel.A"
     * @param offset_pct [0..100], eg: "0"
     */
    //% blockId=mk4_setchanneloffset
    //% block="set $module $channel offset to $offset_pct"
    //% group="M0uld K1ng Module 4.0 - finetune"
    //% shim=mk_module_4_0::setChannelOffset
    //% offset_pct.min=0 
    //% offset_pct.max=100 
    //% offset_pct.defl=0
    //% blockGap=8
    //% weight=60
    //% advanced=true
    export function setChannelOffset(module: Module, channel: Channel, offset_pct: number): void {
        return;
    }


    /**
     *  set maximum value (in percent) of channel
     * @param module module, eg: "Module.M1"
     * @param channel channel, eg: "Channel.A"
     * @param maximum_pct [0..100], eg: "100"
     */
    //% blockId=mk4_setchannelmax
    //% block="set $module $channel max to $maximum_pct"
    //% group="M0uld K1ng Module 4.0 - finetune"
    //% shim=mk_module_4_0::setChannelMax
    //% maximum_pct.min=0
    //% maximum_pct.max=100
    //% maximum_pct.defl=100
    //% blockGap=8
    //% weight=60
    //% advanced=true
    export function setChannelMax(module: Module, channel: Channel, maximum_pct: number): void {
        return;
    }


    /**
     *  reverse direction of channel
     * @param module module, eg: "Module.M1"
     * @param channel channel, eg: "Channel.A"
     * @param reverse [True, False], eg: "False"
     */
    //% blockId=mk4_setchannelreverse
    //% block="set $module $channel reverse $reverse"
    //% group="M0uld K1ng Module 4.0 - finetune"
    //% shim=mk_module_4_0::setChannelReverse
    //% reverse.defl=False
    //% blockGap=8
    //% weight=60
    //% advanced=true
    export function setChannelReverse(module: Module, channel: Channel, reverse: boolean): void {
        return;
    }


    /**
     *  set zero hysteresis value (in percent)
     * @param module module, eg: "Module.M1"
     * @param zeroHysteresis_pct [0..100], eg: "1"
     */
    //% blockId=mk4_setzerohysteresis
    //% block="set $module zero hysteresis to $zeroHysteresis_pct"
    //% group="M0uld K1ng Module 4.0 - finetune"
    //% shim=mk_module_4_0::setZeroHysteresis
    //% zeroHysteresis_pct.min=0 
    //% zeroHysteresis_pct.max=100 
    //% zeroHysteresis_pct.defl=1
    //% blockGap=8
    //% weight=60
    //% advanced=true
    export function setZeroHysteresis(module: Module, zeroHysteresis_pct: number): void {
        return;
    }


    /**
     *  reset channel data, offset and max
     * @param module module, eg: "Module.M1"
     */
    //% blockId=mk6_reset
    //% block="reset $module"
    //% group="M0uld K1ng Module 4.0 - advanced"
    //% shim=mk_module_4_0::reset
    //% blockGap=8 
    //% weight=60
    //% advanced=true
    export function reset(module: Module): void {
        return;
    }
}
