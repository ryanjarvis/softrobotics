const arduino = require('./build/Release/arduino');
const imager = require('./build/Release/imager');

const koa = require('koa');
const koa_static = require('koa-static');
const koa_route = require('koa-route');
const websockify = require('koa-websocket');

const library = Object.create(null);

library.create = function() {
	let server = new koa();
	server = websockify(server);
	return server;
}

library.init = function(server, config) {
	server.use(
		koa_static('public')
	);
	server.ws.use(
		koa_route.all(
			'/socket/',
			async function(ctx, next) {
				arduino.open(
					config.devicename,
					config.baudrate
				);
				ctx.websocket.send("Arduino is ready");
				ctx.websocket.on(
					'message',
					function(message) {
						arduino.send(message);
					}
				)
			}
		)
	);
	server.use(
		koa_route.get(
			'/vision',
			async function(ctx, next) {
				angle = imager.get_orientation("public/" + ctx.request.query.img);
				command = `a${angle}\n`;
				arduino.send(command);
				ctx.body = {success: true};
			}
		)
	);
	server.use(
		async function(ctx) {
			ctx.body = "Unknown request";
		}
	);
};

module.exports = library
