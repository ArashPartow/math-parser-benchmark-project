function js_string_to_c_string(js_string)
{
	var len = lengthBytesUTF8(js_string);
	var c_string = _malloc(len+1);
	stringToUTF8(js_string, c_string, len+1);

	return c_string;
}

var em_string_registry = Module.cwrap('em_string_registry', 'undefined', ['number', 'number'], { async: true });

function em_register_string(id, js_string)
{
	var c_string = js_string_to_c_string(js_string);
	em_string_registry(id, c_string);
}

function em_enumerate_av_devices()
{
	navigator.mediaDevices.enumerateDevices()
		.then(
			function(devices)
			{
				var str="";
				devices.forEach(
					function(device)
					{
						//console.log(device.kind + ": " + device.label + " id = " + device.deviceId);
						str += device.kind + " \"" + device.label + "\" id = " + device.deviceId + "\n";
					}
				);
				//console.log(str);
				em_register_string(1327, str);		// register the string for later retrieval from C
			})
		.catch(function(err) { console.log(err.name + ": " + err.message); });
}

function em_exit_fullscreen_ret_promise()	// adapted from _emscripten_exit_fullscreen to return the promise
{
	if (!JSEvents.fullscreenEnabled())
		return null;

	// Make sure no queued up calls will fire after this.
	JSEvents.removeDeferredCalls(_JSEvents_requestFullscreen);

	if (document.exitFullscreen)
	{
		if (document.fullscreenElement)
			return document.exitFullscreen();
	}
	else if (document.webkitExitFullscreen)
	{
		if (document.webkitFullscreenElement)
			return document.webkitExitFullscreen();
	}

	return null;
}

function em_sync_by_mutex_js(lock)
{
	Module.ccall('em_sync_by_mutex', 'undefined', ['number'], [lock], { async: true });
}

// Audio worklet
/*var AudioContext = window.AudioContext;
var ac = new AudioContext();
var text = "registerProcessor('test-param', class param extends AudioWorkletProcessor { constructor() { super(); } process(input, output, parameters) { return true; } });";
const blob = new Blob([text], {type: "application/javascript"});

var url = URL.createObjectURL(blob);
ac.audioWorklet.addModule(url).then(() => {
  var node = new AudioWorkletNode(ac, 'test-param');
});*/
