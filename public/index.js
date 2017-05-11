(function() {

	//Set up Websockets
	let ws = new WebSocket("ws://localhost:9000/socket");
	let ready = false;

	ws.onerror = function() { show_message("Websocket error") };
	ws.onopen = function() {
		ready = true;
		show_message("Websocket open");
	};
	ws.onclose = function() {
		ready = false;
		show_message("Websocket close");
	};
	ws.onmessage = function(event) {
		handle_message(event.data);
	}

	const show_message = function(msg) {
		console.log(msg);
	};

	const send_message = function(msg) {
		if(ready) {
			ws.send(msg);
		}
	}

	const handle_message = function(msg) {
		if(msg === "Arduino is ready") {
			document.querySelector("#status").textContent = "Connection established"
		}
		show_message(msg);
	}

	//Controls for manual control
	const speed_input = document.querySelector("#speed");
	let timer;
	const ccw_button = document.querySelector("#ccw");
	ccw_button.onmousedown = function() {
		timer = setInterval(
			function() {
				command = `l${speed_input.value}\n`;
				send_message(command)
			},
			25
		);
	}
	ccw_button.onmouseup = function() {
		if(timer) { clearInterval(timer) }
	}

	const cw_button = document.querySelector("#cw");
	cw_button.onmousedown = function() {
		timer = setInterval(
			function() {
				command = `r${speed_input.value}\n`;
				send_message(command)
			},
			25
		);
	}
	cw_button.onmouseup = function() {
		if(timer) { clearInterval(timer) }
	}


	//Controls for direct setting
	const angle_input = document.querySelector("#angle");
	const direct_button = document.querySelector("#set");
	direct_button.onclick = function() {
		command = `a${angle_input.value}\n`;
		send_message(command)
	}

	//Controls for computer vision
	const image = document.querySelector("#image");
	const imageselect = document.querySelector("#imageselect");
	imageselect.onchange = function() {
		image.src = imageselect.value;
	}
	const orient = document.querySelector("#orient");
	orient.onclick = function() {
		request = new XMLHttpRequest();
		request.open(
			'GET',
			`/vision?img=${imageselect.value}`
		);
		request.send();
	}

})();
