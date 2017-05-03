const config = require('./config.json');

const Server = require('./server.js');
const server = Server.create();
Server.init(server, config);
server.listen(config.port);
