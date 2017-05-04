(function() {


	const show_message = function(msg) {
		console.log(msg);
	};

	const send_message = function(msg) {
		if(ready) {
			ws.send(msg);
		}
	}

	let timer;
	const ccw_button = document.querySelector("#ccw");
	ccw_button.onmousedown = function() {
		timer = setInterval(
			function() { send_message('l') },
			25
		);
	}
	ccw_button.onmouseup = function() {
		if(timer) { clearInterval(timer) }
	}
	/*
	ccw_button.onclick = function() {
		send_message('l');
	};
	*/

	const cw_button = document.querySelector("#cw");
	cw_button.onmousedown = function() {
		timer = setInterval(
			function() { send_message('r') },
			25
		);
	}
	cw_button.onmouseup = function() {
		if(timer) { clearInterval(timer) }
	}
	/*
	cw_button.onclick = function() {
		send_message('r');
	};
	*/

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
		show_message(event.data);
	}

})();
