const arduino = require('./build/Release/arduino');

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
				arduino.open();
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
		async function(ctx) {
			ctx.body = "Unknown request";
		}
	);
};

module.exports = library
