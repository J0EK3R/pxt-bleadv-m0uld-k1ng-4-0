// tests go here; this will not be compiled when this package is used as an extension.
input.onButtonPressed(Button.A, function () {
    MK4.setChannelAndSend(MK4.Module.M1, MK4.Channel.A, 50)
})
input.onButtonPressed(Button.B, function () {
    MK4.setChannelAndSend(MK4.Module.M1, MK4.Channel.A, 0)
})
MK4.init(MK4.Module.M1)
MK4.setChannelOffset(MK4.Module.M1, MK4.Channel.A, 20)
