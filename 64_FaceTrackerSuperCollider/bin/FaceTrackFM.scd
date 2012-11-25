
(
s.boot;

// defin FM Synth
SynthDef("fm2", { 
	arg bus = 0, freq = 220, carPartial = 0.5, 
	modPartial = 0.5, detune=2.0, index = 3, mul = 0.2, ts = 1;
	var mod;
	var car;
	mod = SinOsc.ar(freq * modPartial, 0, freq * index * LFNoise1.kr(5.reciprocal).abs);
	car = SinOsc.ar([(freq * carPartial) + mod,(freq+detune * carPartial) + mod] , 0, mul);
	car = FreeVerb.ar(car* EnvGen.kr(Env.new([0,1], [5])), 0.5, 0.8, 0.2, 1.0);
	Out.ar(bus, car);
}).load(s);
)

// OSC Responder
(
var playing = false;

// Synth start/stop
a = OSCresponderNode(nil, "/found", 
{
	arg time, resp, msg;
	if(msg[1] == 1,
	{
		if(playing == false, {s.sendMsg("/s_new", "fm2", 10000, 1,1)});
		playing = true;
	},
	{
		if(playing, {s.sendMsg("/n_free", 10000)});
		playing = false;
	}
) }).add;
// car and mod ratio
b = OSCresponderNode(nil, "/pose/orientation", 
{
	arg time, resp, msg;
	var car, mod;
	mod = msg[1]*10.0 + 1.0;
	car = msg[2]*10.0 + 1.0;
     s.sendMsg("/n_set", 10000, "carPartial", car, "modPartial", mod);
}).add;
// index
c = OSCresponderNode(nil, "/gesture/mouth/height", 
{
	arg time, resp, msg;
	var ind;
	ind = msg[1] * 3.0;
     s.sendMsg("/n_set", 10000, "index", ind);
}).add;
)

a.free;
b.free;
c.free;
//test
s.sendMsg("/s_new", "fm2", 10000, 1,1);
s.sendMsg("/n_set", 10000, "index", 10);
s.sendMsg("/n_free", 10000);