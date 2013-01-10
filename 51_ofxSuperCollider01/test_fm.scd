// Simple FM

(
SynthDef("test_fm", {
	arg car=440, mod=220, index=1.0, amp=1.0;
	var mix;
	mix = SinOsc.ar(car + SinOsc.ar(mod, 0, index), 0, amp);
	Out.ar(0, mix);
}).store;
)

// Simple FM test
Synth("test_fm");
Synth("test_fm", ["mod", 333, "index", 1000]);